/*
 * shell_wifi.c
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

#include "main.h"
#include "m2m_wifi.h"
#include "socket.h"
#include "wifi.h"
#include "led.h"
#include "tcp.h"

static osThreadId_t shell_thread_id;

/** */
void shell_wifi_command(const char *command_string)
{
    uint8_t arg1_len;
    uint8_t arg2_len;
    const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
    const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

    shell_thread_id =  osThreadGetId();

    if (shell_arg_is("reset", arg1, arg1_len))
    {
    	nm_reset();
        printf("wifi module reset. reboot for normal operation\n");
    }
    else if (shell_arg_is("mac", arg1, arg1_len))
    {
    	uint8_t mac[6];
    	uint8_t valid;
    	m2m_wifi_get_otp_mac_address(mac, &valid);

    	if(valid)
    	{
    		printf("%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    	}
    	else
    	{
    		printf("no valid mac address\n");

    	}
    }
    else if (shell_arg_is("host", arg1, arg1_len))
    {
    	if(arg2)
    	{
    		uint32_t ip_addr = tcp_resolve(arg2);

    		if(ip_addr != 0)
    		{
    			printf("resolved ip address of host %s = %s\n", arg2, inet_ntoa(ip_addr));
    		}
    		else
    		{
    			printf("could not resolve ip address of host %s\n", arg2);
    		}
      	}
    	else
    	{
    		printf("missing host name\n");
    	}
    }
    else if (shell_arg_is("chipid", arg1, arg1_len))
    {
    	printf("chip id = %lx\r\n", m2m_wifi_get_chipId());
    }
    else if (shell_arg_is("ping", arg1, arg1_len))
    {
    	const char * remote = DEFAULT_HOST;
    	if(arg2)
    	{
    		remote = arg2;
    	}

    	/** */
    	void ping_cb(uint32_t ip_addr, uint32_t tt, uint8_t error)
    	{
    		if(!error)
    		{
    			printf("ping response from ip address %s in %ld ms\n", inet_ntoa(ip_addr), tt);
    		}
    		else
    		{
    			printf("no response from ip address %s\n", inet_ntoa(ip_addr));
    		}
    	}

    	m2m_ping_req(inet_addr(remote), 20, ping_cb);
    }
    else if (shell_arg_is("ip", arg1, arg1_len))
    {
    	uint32_t ip_addr = wifi_get_ip_address();
		printf("ip address %s\n", inet_ntoa(ip_addr));
    }
    else if (shell_arg_is("rssi", arg1, arg1_len))
    {
    	uint32_t rssi = wifi_get_rssi();
		printf("rssi %ld\n", rssi);
    }
    else
    {
        printf("incorrect argument\n");
    }
}

