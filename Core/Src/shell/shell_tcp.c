/*
 * shell_tcp.c
 *
 *  Created on: Jan 29, 2024
 *      Author: andrew
 */

#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "cmsis_os.h"

#include "main.h"
#include "m2m_wifi.h"
#include "socket.h"
#include "wifi.h"
#include "led.h"
#include "tcp.h"

/** */
void shell_tcp_command(const char *command_string)
{
    uint8_t arg1_len;
    uint8_t arg2_len;
    const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
    const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

    if (shell_arg_is("client", arg1, arg1_len))
    {
    	const char * remote = DEFAULT_HOST;
    	if(arg2)
    	{
    		remote = arg2;
    	}

		tcp_echo_client(inet_addr(remote), DEFAULT_PORT);
    }
    else if (shell_arg_is("server", arg1, arg1_len))
    {
		tcp_echo_server();
    }
}
