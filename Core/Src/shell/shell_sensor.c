/*
 * shell_sensor.c
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
#include "sensor.h"

/** */
void shell_sensor_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

	if (shell_arg_is("get", arg1, arg1_len))
	{
		if (shell_arg_is("id", arg2, arg2_len))
		{
			printf("sensor id=%2.2x\n", sensor_get_id());
		}
		else if (shell_arg_is("temperature", arg2, arg2_len))
		{
			printf("sensor temperature=%3.1f\n", sensor_get_temperature());
		}
		else
		{
			printf("missing argument");
		}
	}
	else if (shell_arg_is("set", arg1, arg1_len))
	{
		if (arg2)
		{
		}
		else
		{
			printf("missing argument");
		}
	}
	else if (shell_arg_is("test", arg1, arg1_len))
	{
		while(!kbhit())
		{
			sensor_get_id();
			HAL_Delay(100);
		}

		getchar();
	}
	else
	{
		printf("incorrect argument\n");
	}
}

