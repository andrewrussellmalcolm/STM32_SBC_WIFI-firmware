/*
 * tcp.c
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

static SOCKET accept_socket;
static uint16_t recv_length[6];
static uint32_t resolved_ip_address = 0;

static osEventFlagsId_t tcp_event_flags_id;

/** */
bool tcp_bind(SOCKET server_socket, struct sockaddr *addr)
{
	uint32_t done = 1 << server_socket;
	uint32_t fail = 0x8000;

	if (bind(server_socket, addr, sizeof(struct sockaddr)) != SOCK_ERR_NO_ERROR)
	{
		osEventFlagsSet(tcp_event_flags_id, fail);
	}

	if(osEventFlagsWait(tcp_event_flags_id, done | fail, osFlagsWaitAny, osWaitForever) == done)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/** */
bool tcp_listen(SOCKET server_socket)
{
	uint32_t done = 1 << server_socket;
	uint32_t fail = 0x8000;

	if (listen(server_socket, 0) != SOCK_ERR_NO_ERROR)
	{
		osEventFlagsSet(tcp_event_flags_id, fail);
	}

	if(osEventFlagsWait(tcp_event_flags_id, done | fail, osFlagsWaitAny, osWaitForever) == done)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/** */
SOCKET tcp_accept(SOCKET server_socket)
{
	uint32_t done = 1 << server_socket;
	uint32_t fail = 0x8000;

	if (accept(server_socket, NULL, NULL) != SOCK_ERR_NO_ERROR)
	{
		osEventFlagsSet(tcp_event_flags_id, fail);
	}

	if (osEventFlagsWait(tcp_event_flags_id, done | fail, osFlagsWaitAny, osWaitForever) == done)
	{
		return accept_socket;
	}
	else
	{
		return -1;
	}
}

/** */
bool tcp_recv(SOCKET client_socket, uint8_t *buffer, uint16_t *length)
{
	uint32_t done = 1 << client_socket;
	uint32_t fail = 0x8000;

	if (recv(client_socket, buffer, *length, 0) != SOCK_ERR_NO_ERROR)
	{
		osEventFlagsSet(tcp_event_flags_id, fail);
	}

	if (osEventFlagsWait(tcp_event_flags_id, fail | done, osFlagsWaitAny, 5*60*1000) == done)
	{
		*length = recv_length[(int8_t)client_socket];
		return true;
	}
	else
	{
		fprintf(stderr, "recv timeout\n");
		return false;
	}
}

/** */
bool tcp_send(SOCKET client_socket, uint8_t *buffer, uint32_t length)
{
	uint32_t done = 1 << client_socket;
	uint32_t fail = 0x8000;

	uint32_t offset = 0;

	do
	{
		uint32_t send_length = MIN(length, SOCKET_BUFFER_MAX_LENGTH);

		if (send(client_socket, buffer + offset, send_length, 0) != SOCK_ERR_NO_ERROR)
		{
			osEventFlagsSet(tcp_event_flags_id, fail);
		}

		if (osEventFlagsWait(tcp_event_flags_id, fail | done, osFlagsWaitAny, osWaitForever) == done)
		{
			length -= send_length;
			offset += send_length;
		}
		else
		{
			return false;
		}
	}
	while (length > 0);

	return true;
}

/** */
bool tcp_connect(SOCKET client_socket, struct sockaddr *addr)
{
	uint32_t done = 1 << client_socket;
	uint32_t fail = 0x8000;

	if (connect(client_socket, addr, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR)
	{
		osEventFlagsSet(tcp_event_flags_id, fail);
	}

	if(osEventFlagsWait(tcp_event_flags_id, fail | done, osFlagsWaitAny, osWaitForever) == done)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/** */
uint32_t tcp_resolve(const char * hostname)
{
	uint32_t fail = 0x8000;
	uint32_t done = 0x4000;

	if (gethostbyname(hostname) != SOCK_ERR_NO_ERROR)
	{
		osEventFlagsSet(tcp_event_flags_id, fail);
	}

	if(osEventFlagsWait(tcp_event_flags_id, fail | done, osFlagsWaitAny, osWaitForever) == done)
	{
		return resolved_ip_address;
	}
	else
	{
		return -1;
	}
}

/** */
static void socket_event_callback(SOCKET callback_socket, uint8_t message, void *data)
{
	uint32_t done = 1 << callback_socket;
	uint32_t fail = 0x8000;

	switch(message)
	{

	case SOCKET_MSG_CONNECT:
	{
		osEventFlagsSet(tcp_event_flags_id, done);
		return;
	}

	case SOCKET_MSG_BIND:
	{
		tstrSocketBindMsg *bind_msg = (tstrSocketBindMsg*) data;
		if (bind_msg && bind_msg->status == 0)
		{
			osEventFlagsSet(tcp_event_flags_id, done);
			return;
		}
		break;
	}

	case SOCKET_MSG_LISTEN:
	{
		tstrSocketListenMsg *listen_msg = (tstrSocketListenMsg*) data;

		if (listen_msg && listen_msg->status == 0)
		{
			osEventFlagsSet(tcp_event_flags_id, done);
			return;
		}
		break;
	}

	case SOCKET_MSG_ACCEPT:
	{
		tstrSocketAcceptMsg *accept_msg = (tstrSocketAcceptMsg*) data;

		if (accept_msg->sock >= 0)
		{
			accept_socket = accept_msg->sock;
			osEventFlagsSet(tcp_event_flags_id, done);
			return;
		}
		break;
	}

	case SOCKET_MSG_RECV:
	{
		tstrSocketRecvMsg *receive_msg = (tstrSocketRecvMsg*) data;

		recv_length[callback_socket] = receive_msg->s16BufferSize;
		if ((receive_msg->pu8Buffer != NULL) && (receive_msg->u16RemainingSize == 0))
		{
			osEventFlagsSet(tcp_event_flags_id, done);
			return;
		}

		break;
	}

	case SOCKET_MSG_SEND:
	{
		osEventFlagsSet(tcp_event_flags_id, done);
		return;
	}

	}
	osEventFlagsSet(tcp_event_flags_id, fail);
}

/** */
void socket_resolve_callback(uint8_t* domain_name, uint32_t ip_addr)
{
	resolved_ip_address = ip_addr;
	osEventFlagsSet(tcp_event_flags_id, 0x4000);
}

/** */
void tcp_reset(void)
{
	uint32_t fail = 0x8000;
	// force fail to wake up waiting threads
	osEventFlagsSet(tcp_event_flags_id, fail);
}
/** */
void tcp_init()
{
	registerSocketEventCallback(socket_event_callback);
	registerSocketResolveCallback(socket_resolve_callback);
	tcp_event_flags_id = osEventFlagsNew(NULL);

	memset(recv_length, 0, sizeof(recv_length));
}
