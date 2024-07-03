/*
 * shell_led.c
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
#include "led.h"

/** */
void shell_led_command(const char *command_string)
{
    uint8_t arg1_len;
    uint8_t arg2_len;
    const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
    const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

    if (shell_arg_is("0", arg1, arg1_len))
    {
        if (shell_arg_is("on", arg2, arg2_len))
        {
        	led_set_state(LED_0, LED_ON);
        }
        else if (shell_arg_is("off", arg2, arg2_len))
        {
        	led_set_state(LED_0, LED_OFF);
        }
        else if (shell_arg_is("toggle", arg2, arg2_len))
        {
        	led_toggle_state(LED_0);
        }
        else if (shell_arg_is("flash", arg2, arg2_len))
        {
        	led_flash(LED_0);
        }
        else
        {
            printf("incorrect argument\n");
        }
    }
    else if (shell_arg_is("1", arg1, arg1_len))
    {
        if (shell_arg_is("on", arg2, arg2_len))
        {
        	led_set_state(LED_1, LED_ON);
        }
        else if (shell_arg_is("off", arg2, arg2_len))
        {
        	led_set_state(LED_1, LED_OFF);
        }
        else if (shell_arg_is("toggle", arg2, arg2_len))
        {
        	led_toggle_state(LED_1);
        }
        else if (shell_arg_is("flash", arg2, arg2_len))
        {
        	led_flash(LED_1);
        }
        else
        {
            printf("incorrect argument\n");
        }
    }
    else
    {
        printf("incorrect argument\n");
    }
}


