/*
 * shell_flash.c
 *
 *  Created on: Feb 14, 2024
 *      Author: andrew
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include "main.h"
#include "shell.h"
#include "flash.h"

/** */
static bool test_flash_page(uint16_t addr)
{
    FSH_WriteEnable();
    FSH_EraseSector(addr);
    FSH_WaitWhileBusy();
    FSH_WriteDisable();
    uint8_t wr_data[FSH_PAGE_SIZE];
    uint8_t rd_data[FSH_PAGE_SIZE];

    for (size_t i = 0; i < FSH_PAGE_SIZE; i++)
    {
        wr_data[i] = rand();
    }

    FSH_WriteEnable();
    FSH_ProgramPage(addr, wr_data, FSH_PAGE_SIZE);
    FSH_WaitWhileBusy();
    FSH_WriteDisable();

    FSH_Read(addr, rd_data, FSH_PAGE_SIZE);

    return memcmp(rd_data, wr_data, FSH_PAGE_SIZE) == 0;
}

/** */
void shell_flash_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	uint8_t arg3_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);
	const char *arg3 = shell_get_parameter(command_string, 3, &arg3_len);
	static uint32_t addr = 0;
	static uint8_t data = 0xaa;

	if (arg2)
	{
		sscanf(arg2, "%lx", &addr);
	}

	if (arg3)
	{
		sscanf(arg3, "%2x", (unsigned int*) &data);
	}

	if (shell_arg_is("reset", arg1, arg1_len))
	{
		FSH_ResetEnable();
		FSH_Reset();

		printf("flash reset\n");
	}
	else if (shell_arg_is("unlock", arg1, arg1_len))
	{
		FSH_GlobalUnlock();

		FSH_WriteEnable();
		FSH_ClearBlockProtectionRegister();
		FSH_WaitWhileBusy();
		FSH_WriteDisable();

		printf("flash unlocked\n");
	}
	else if (shell_arg_is("id", arg1, arg1_len))
	{
		uint32_t id = FSH_ReadJedecID();
		printf("flash Jedec ID=%6.6lx (should be bf2642)\n", id);
	}
	else if (shell_arg_is("config", arg1, arg1_len))
	{
		uint8_t config = FSH_ReadConfig();
		printf("flash config=%2.2x\n", config);
	}
	else if (shell_arg_is("status", arg1, arg1_len))
	{
		uint8_t status = FSH_ReadStatus();
		printf("flash status=%2.2x\n", status);
	}
	else if (shell_arg_is("erase_sector", arg1, arg1_len))
	{
		FSH_WriteEnable();
		FSH_EraseSector(addr);
		FSH_WaitWhileBusy();
		FSH_WriteDisable();
		printf("flash sector at %lx erased\n", addr);
	}
	else if (shell_arg_is("test_page", arg1, arg1_len))
	{
		printf("********** WARNING *********\n");
		printf("********* TEST ONLY ********\n");
		printf("* THIS WILL SHORTEN flash  *\n");
		printf("*            LIFE          *\n");
		printf("********** WARNING *********\n");
		printf("\npress q to quit\n");

		bool ok;
		size_t cycle = 0;

		// 1 million cycles is 10 times the documented lifetime of the flash device
		for (cycle = 0; cycle < 1000000; cycle++)
		{
			ok = test_flash_page(addr);

			if (!ok)
			{
				break;
			}

			if (kbhit())
			{
				if (getchar() == 'q')
				{
					break;
				}
			}

			if ((cycle % 100) == 0)
			{
				printf("cycles=%d\n", cycle);
			}
		}

		printf("\nflash page at %lx tested %d times %s\n", addr, cycle, ok ? "OK" : "NOT OK");
	}
	else if (shell_arg_is("test_device", arg1, arg1_len))
	{
		printf("********** WARNING *********\n");
		printf("********* TEST ONLY ********\n");
		printf("* THIS WILL SHORTEN flash  *\n");
		printf("*            LIFE          *\n");
		printf("********** WARNING *********\n");
		printf("\npress q to quit\n");

		bool ok;
		size_t cycle = 0;
		bool done = false;

		// 1 million cycles is 10 times the documented lifetime of the flash device
		for (cycle = 0; cycle < 1000000; cycle++)
		{
			for (addr = 0; addr < FSH_MEMORY_SIZE; addr += FSH_PAGE_SIZE)
			{
				ok = test_flash_page(addr);

				if (!ok)
				{
					done = true;
					break;
				}

				if (kbhit())
				{
					if (getchar() == 'q')
					{
						done = true;
						break;
					}
				}

				if ((addr % 0x4000) == 0)
				{
					printf("page address=%8.8lx cycles=%d\n", addr, cycle);
				}
			}
			if (done)
			{
				break;
			}
		}

		printf("\nflash device tested %d times %s\n", cycle, ok ? "OK" : "NOT OK");
	}
	else if (shell_arg_is("erase_chip", arg1, arg1_len))
	{
		FSH_WriteEnable();
		FSH_EraseChip();
		FSH_WaitWhileBusy();
		FSH_WriteDisable();
		printf("flash chip erased\n");
	}
	else if (shell_arg_is("read_page", arg1, arg1_len))
	{
		uint8_t data[FSH_PAGE_SIZE];
		memset(data, 0x00, sizeof(data));
		FSH_Read(addr, data, sizeof(data));
		shell_print_array(addr, data, sizeof(data));
		printf("flash page at %lx\n", addr);
		addr += FSH_PAGE_SIZE;
	}
	else if (shell_arg_is("read_repeat", arg1, arg1_len))
	{
		uint8_t data[1];
		uint32_t count = 0;
		for (int i = 0; i < 1000000; i++)
		{
			data[0] = 0;

			FSH_Read(addr, data, sizeof(data));

			// if (data[0] != 0x6c)
			// {
			//     HAL_GPIO_WritePin(GPIOB, EXP_GP1_Pin, GPIO_PIN_SET);
			//     HAL_GPIO_WritePin(GPIOB, EXP_GP1_Pin, GPIO_PIN_RESET);
			//     printf("reads before error=%ld data=%2.2x\n", count, data[0]);
			//     return false;
			// }
			count++;

			if (kbhit())
			{
				if (getchar() == 'q')
				{
					break;
				}
			}
		}
		printf("test complete\n");
	}
	else if (shell_arg_is("write_page", arg1, arg1_len))
	{
		uint8_t wr_buffer[FSH_PAGE_SIZE];
		memset(wr_buffer, data, sizeof(wr_buffer));
		FSH_WriteEnable();
		FSH_ProgramPage(addr, wr_buffer, sizeof(wr_buffer));
		FSH_WaitWhileBusy();
		FSH_WriteDisable();
		printf("flash page at %lx written with %x\n", addr, data);
		addr += FSH_PAGE_SIZE;
	}
	else if (shell_arg_is("write_byte", arg1, arg1_len))
	{
		uint8_t wr_buffer[FSH_PAGE_SIZE];
		memset(wr_buffer, data, sizeof(wr_buffer));
		FSH_WriteEnable();
		FSH_ProgramPage(addr, wr_buffer, 1);
		FSH_WaitWhileBusy();
		FSH_WriteDisable();
		printf("flash byte at %lx written with %x\n", addr, data);
		addr += FSH_PAGE_SIZE;
	}
	else
	{
		printf("incorrect argument\n");
	}
}
