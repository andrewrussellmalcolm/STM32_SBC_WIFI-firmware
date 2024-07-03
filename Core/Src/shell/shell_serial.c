/*
 * shell_serial.c
 *
 *  Created on: Jan 16, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "main.h"
#include "shell.h"

/** */
void shell_serial_command(const char *commandString)
{
    uint8_t arg1_len;
    const char *arg1 = shell_get_parameter(commandString, 1, &arg1_len);

    if (shell_arg_is("loopback", arg1, arg1_len))
	{
		for(int i= 0; i < 100000; i++)
		{
			uint8_t ch0 = 'A';
			HAL_UART_Transmit(&huart4, &ch0, 1, 500);

			uint8_t ch1 = 0;
			HAL_UART_Receive(&huart4, &ch1, 1, 500);

			if(ch0 != ch1)
			{
				printf("loopback failed\n");
   		    }

			if( (i%20) == 0)
			{
				HAL_Delay(50);
			}

			if (kbhit())
			{
				if (getchar() == 'q')
				{
					break;
				}
			}
		}
	}
	else
	{
	   printf("incorrect argument\n");
	}
}
