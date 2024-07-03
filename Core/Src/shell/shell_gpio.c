/*
 * shell_gpio.c
 *
 *  Created on: Apr 28, 2024
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

/** */
void shell_gpio_command(const char *command_string)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

	uint32_t gpio = atoi(arg1);
	bool state = false;

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
		printf("missing gpio state argument\n");
		return;
	}

	switch (gpio)
	{
	case 4:
		HAL_GPIO_WritePin(IO_GPIO04_GPIO_Port, IO_GPIO04_Pin, state);
		return;
	case 22:
		HAL_GPIO_WritePin(IO_GPIO22_GPIO_Port, IO_GPIO22_Pin, state);
		return;
	case 23:
		HAL_GPIO_WritePin(IO_GPIO23_GPIO_Port, IO_GPIO23_Pin, state);
		return;
	case 24:
		HAL_GPIO_WritePin(IO_GPIO24_GPIO_Port, IO_GPIO24_Pin, state);
		return;
	case 26:
		HAL_GPIO_WritePin(IO_GPIO26_GPIO_Port, IO_GPIO26_Pin, state);
		return;
	case 25:
		HAL_GPIO_WritePin(IO_GPIO25_GPIO_Port, IO_GPIO25_Pin, state);
		return;
	case 27:
		HAL_GPIO_WritePin(IO_GPIO27_GPIO_Port, IO_GPIO27_Pin, state);
		return;
	default:
	{
		printf("invalid gpio number argument\n");
		return;
	}

	}
}

