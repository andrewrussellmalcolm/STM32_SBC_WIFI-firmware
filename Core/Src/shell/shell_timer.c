/*
 * shell_timer.c
 *
 *  Created on: May 6, 2024
 *      Author: andrew
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "shell.h"
#include "led.h"
#include "mcu.h"

/** */
void shell_timer_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	uint8_t arg3_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);
	const char *arg3 = shell_get_parameter(command_string, 3, &arg3_len);

	uint32_t timer_register = MCU_ReadRegister(0);
	if (shell_arg_is("get", arg1, arg1_len))
	{
		for(int i= 0; i < 24; i++)
		{
			printf("%2.2d:%d ", i, timer_register & (1 << i)?1:0);
			if((i == 5) || (i == 11) || (i == 17))
			{
				printf("\n");
			}
		}

		printf("\n");
	}
	else if (shell_arg_is("set", arg1, arg1_len))
	{
		bool state = 0;
		if (shell_arg_is("on", arg2, arg2_len))
		{
			state = true;
		}
		else if (shell_arg_is("off", arg2, arg2_len))
		{
			state = false;
		}
		else
		{
			printf("invalid argument\n");
			return;
		}

		if(!arg3)
		{
			printf("missing hour argument\n");
			return;
		}

		int8_t hour = atoi(arg3);

		if(hour < 0 || hour > 23 )
		{
			printf("invalid hour argument\n");
			return;
		}

		uint32_t value = (timer_register & ~(1 << hour)) | (state << hour);
		MCU_WriteRegsiter(0, value);


	}
	else
	{
		printf("invalid argument\n");
	}
}
