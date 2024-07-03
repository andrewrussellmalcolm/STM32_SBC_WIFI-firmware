/*
 * tcp_client.c
 *
 *  Created on: Jan 29, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "cmsis_os.h"

#include "main.h"

#include "socket.h"
#include "tcp.h"

static uint8_t * send_buffer = (uint8_t*)"ABCDEZGHIJKLMNOPQRSTUVWXYZ01234567890 !\"£$%^&*()_+`@~#;:<>?/\\,.|";
static uint8_t recv_buffer[128];
static uint16_t send_length;
static uint16_t recv_length;

/** */
bool tcp_echo_client(uint32_t dest, uint32_t port)
{
	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (client_socket < 0)
	{
		return false;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(port);
	addr.sin_addr.s_addr = dest;

	if(!tcp_connect(client_socket, (struct sockaddr *)&addr))
	{
		printf("connect failed\n");
		return false;
	}

	while(true)
	{
		send_length = strlen((char *)send);
		if(!tcp_send(client_socket, send_buffer, send_length))
		{
			printf("send failed\n");
			return false;
		}

		if(!tcp_recv(client_socket, recv_buffer, &recv_length))
		{
			printf("receive failed\n");
			return false;
		}

		if(send_length != recv_length || strcmp((const char *)send, (const char *)recv)!= 0)
		{
			printf("transaction failed, data corrupt\n");
			break;
		}

		printf("sent %d [%s]\n", send_length, send_buffer);
		printf("recv %d [%s]\n", recv_length, recv_buffer);

		if(kbhit())
		{
			getchar();
			break;
		}
	}

	shutdown(client_socket);
	return true;
}


