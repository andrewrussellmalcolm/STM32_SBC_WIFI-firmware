/*
 * ssh_server_thread.h
 *
 *  Created on: Feb 12, 2024
 *      Author: andrew
 */

#ifndef INC_SSH_SERVER_THREAD_H_
#define INC_SSH_SERVER_THREAD_H_

#include <socket.h>
#include <cmsis_os2.h>

typedef struct PwMap
{
	byte type;
	byte username[32];
	word32 usernameSz;
	byte p[WC_SHA256_DIGEST_SIZE];
	struct PwMap *next;
} PwMap;

typedef struct PwMapList
{
	PwMap *head;
} PwMapList;

#define RX_BUFFER_LENGTH 1600
typedef struct
{
	WOLFSSH *ssh;
	SOCKET client_socket;
	uint8_t rx_buffer[RX_BUFFER_LENGTH];
	uint8_t *rx_ptr;
	uint16_t available;
	osEventFlagsId_t exit_flag_id;
} thread_ctx_t;

#endif /* INC_SSH_SERVER_THREAD_H_ */
