/*
 * shell_sys.c
 *
 *  Created on: Jan 15, 2024
 *      Author: andrew
 */

#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "main.h"
#include "mcu.h"

/** */
void shell_reboot_command(const char *command_string)
{
	printf("are you sure (y/n)\n");

	char ch = getchar();

	if(ch == 'y')
	{
		printf("\nrebooting\n");
		HAL_Delay(1000);
    	NVIC_SystemReset();
	}
}

/** */
void shell_uptime_command(const char *command_string)
{
	uint32_t uptime = HAL_GetTick()/1000;
	printf("last reboot was %ld minute(s) and %ld seconds ago\n", uptime/60, uptime%60);
}

/** */
void shell_meminfo_command(const char *command_string)
{
	size_t free = xPortGetFreeHeapSize();
	size_t minFree = xPortGetMinimumEverFreeHeapSize();

	size_t main_stack_size = main_task_attributes.stack_size;
	size_t wifi_stack_size = wifi_task_attributes.stack_size;
	size_t lora_stack_size = lora_task_attributes.stack_size;

	size_t main_stack_space = osThreadGetStackSpace(main_taskHandle) * sizeof(uint32_t);
	size_t wifi_stack_space = osThreadGetStackSpace(wifi_taskHandle) * sizeof(uint32_t);
	size_t lora_stack_space = osThreadGetStackSpace(lora_taskHandle) * sizeof(uint32_t);
	printf("heap size           %6d bytes\n", configTOTAL_HEAP_SIZE);
	printf("heap free           %6d bytes\n", free);
	printf("heap min free       %6d bytes\n", minFree);
	printf("\n");
	printf("main task stack size/free %6d/%6d bytes\n", main_stack_size, main_stack_space);
	printf("wifi task stack size/free %6d/%6d bytes\n", wifi_stack_size, wifi_stack_space);
	printf("lora task stack size/free %6d/%6d bytes\n", lora_stack_size, lora_stack_space);
}

/** */
void shell_random_command(const char *command_string)
{
	uint32_t rn = HAL_RNG_GetRandomNumber(&hrng);
	printf("random number=%lu\n", rn);
}

/** */
void shell_bbregisters_command(const char *command_string)
{
	uint32_t regs[RTC_BKP_DR19-RTC_BKP_DR0];
	MCU_ReadRegisters(regs, RTC_BKP_DR19-RTC_BKP_DR0);

	for (uint8_t reg = 0; reg < RTC_BKP_DR19-RTC_BKP_DR0; reg++)
	{
		printf("DR%2d=0x%8.8lx\n", reg, reg[regs]);
	}
}

/** */
void shell_bbmemory_command(const char *command_string)
{
    uint8_t arg1_len;
    uint8_t arg2_len;
    uint8_t arg3_len;
    const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
    const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);
    const char *arg3 = shell_get_parameter(command_string, 3, &arg3_len);

	if(shell_arg_is("read", arg1, arg1_len))
	{
		uint32_t length = 64;
		if(arg2)
		{
			length = atoi(arg2);
		}

		length = MIN(MCU_BBRAM_SIZE, length);
		uint8_t * data = malloc(length);
		MCU_ReadMemory(data, length);
		shell_print_array(0, data, length);
		free(data);
	}
	if(shell_arg_is("clear", arg1, arg1_len))
	{
		MCU_ClearMemory(MCU_BBRAM_SIZE);
	}
	if(shell_arg_is("write", arg1, arg1_len))
	{
		uint32_t length = 64;
		if(arg2)
		{
			length = atoi(arg3);
		}

		uint32_t offset = 0;
		if(arg3)
		{
			offset = atoi(arg3);
		}

		if(offset+length > MCU_BBRAM_SIZE)
		{
			printf("cannot write past end on memory\n");
			return;
		}

		uint8_t * data = malloc(length);
		memset(data, 'A', length);
		MCU_WriteMemoryAtOffset(offset, data, length);
		free(data);
	}
}

/** */
void shell_battery_command(const char *command_string)
{
	float voltage;
	if(!MCU_GetBatteryVoltage(&voltage))
	{
		printf("read of battery voltage failed\n");
		return;
	}

	printf("battery voltage is %.2fV\n", voltage);
}


