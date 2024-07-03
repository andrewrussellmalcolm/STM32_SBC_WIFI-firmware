/*
 * echo_server.c
 *
 *  Created on: Feb 12, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdbool.h>
#include <sys/unistd.h>
#include <string.h>

#include "main.h"
#include "ssh_server.h"
#include "shell.h"

/** */
#define BUFFER_SIZE 16
void echo_server(thread_ctx_t *thread_ctx)
{
	fprintf(stderr, "entering echo server\n");

	uint8_t tx_buffer[BUFFER_SIZE];
	uint8_t rx_buffer[BUFFER_SIZE];

	bool stop = 0;
	int rx_size;

	while (!stop)
	{
		rx_size = wolfSSH_stream_read(thread_ctx->ssh, rx_buffer, BUFFER_SIZE);

		if (rx_size <= 0)
		{
			fprintf(stderr, "wolfSSH_stream_read error: %s\n", wolfSSH_get_error_name(thread_ctx->ssh));
			break;
		}

		if (strchr((char*) rx_buffer, 4) != NULL)
		{
			fprintf(stderr, "ctrl-D detected ... exiting\n");
			break;
		}

		fprintf(stderr, "echoing %.*s\n", rx_size, rx_buffer);

		memcpy(tx_buffer, rx_buffer, rx_size);

		wolfSSH_stream_send(thread_ctx->ssh, tx_buffer, rx_size);
	}

	wolfSSH_stream_exit(thread_ctx->ssh, 0);
	wolfSSH_shutdown(thread_ctx->ssh);
	wolfSSH_free(thread_ctx->ssh);
	shutdown(thread_ctx->client_socket);
	fprintf(stderr, "echo server session ended\n");
	osEventFlagsSet(thread_ctx->exit_flag_id, 1);
	free(thread_ctx);
	osThreadExit();
}
