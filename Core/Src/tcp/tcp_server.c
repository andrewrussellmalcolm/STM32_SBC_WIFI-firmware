/*
 * tcp_server.c
 *
 *  Created on: Jan 29, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os.h"

#include "main.h"
#include "socket.h"
#include "tcp.h"

static uint8_t send_buffer[128];
static uint8_t recv_buffer[128];
static uint16_t send_length = 128;
static uint16_t recv_length = 128;

/** */
void tcp_echo_server(void)
{
	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET client_socket;

	if (server_socket < 0)
	{
		fprintf(stderr, "socket create failed\n");
		return;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = _htons(4040);
	addr.sin_addr.s_addr = _htonl(0);

	if(!tcp_bind(server_socket, (struct sockaddr *)&addr))
	{
		fprintf(stderr, "bind failed\n");
		goto end;
	}

	if(!tcp_listen(server_socket))
	{
		fprintf(stderr, "listen failed\n");
		goto end;
	}

	fprintf(stderr, "waiting for connection...\n");

	while (true)
	{
		client_socket=tcp_accept(server_socket);

		if(client_socket < 0)
		{
			fprintf(stderr, "accept failed\n");
			goto end;
		}

		fprintf(stderr, "accept\n");

		if(!tcp_recv(client_socket, recv_buffer, &recv_length))
		{
			fprintf(stderr, "receive failed\n");
			goto end;
		}

		fprintf(stderr, "recv %d bytes\n", recv_length);

		strcpy((char*)send_buffer, (char*)recv_buffer);
		send_length = recv_length;
		if(!tcp_send(client_socket, send_buffer, send_length))
		{
			fprintf(stderr, "send failed\n");
			goto end;
		}

		fprintf(stderr, "send %d bytes\n", send_length);
 		shutdown(client_socket);

		if(kbhit())
		{
			getchar();
			break;
		}
	}

end:
	shutdown(server_socket);
}


