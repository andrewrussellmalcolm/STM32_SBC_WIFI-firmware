/*
 * shell_clock.c
 *
 *  Created on: Jan 15, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "shell.h"
#include "mcu.h"

/** */
void shell_clock_command(const char *command_string)
{
    uint8_t arg1_len;
    uint8_t arg2_len;
    const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
    const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

    if (shell_arg_is("get", arg1, arg1_len))
    {
        uint8_t hours, minutes, seconds, date, month, year;
        MCU_GetTime(&hours, &minutes, &seconds, &date, &month, &year);
        printf("The date and time is set to %2.2d:%2.2d:%2.2d on %2.2d/%2.2d/%2.2d\n", hours, minutes, seconds, date, month, year);
    }
    else if (shell_arg_is("set", arg1, arg1_len))
    {
        if (arg2)
        {
        	int hours, minutes, seconds, date, month, year;
			if (sscanf(arg2, "%d:%d:%d %d/%d/%d", &hours, &minutes, &seconds, &date, &month, &year) == 6)
			{
				MCU_SetTime(hours, minutes, seconds, date, month, year);
				printf("Date and time set to %d:%d:%d %d/%d/%d\n", hours, minutes, seconds, date, month, year);
			}
			else
			{
				printf("Parse error. Enter date and time in the format HH:MM:SS DD/MM/YY\n");
			}
        }
        else
        {
            printf("missing argument");
        }
    }
    else
    {
        printf("incorrect argument\n");
    }
}
