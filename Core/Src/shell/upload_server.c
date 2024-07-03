/*
 * upload_server.c
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
#include "lora.h"

/** */
void upload_server(thread_ctx_t *thread_ctx)
{
	uint32_t count = lora_mesage_count();

	for (int index = 0; index < count; index++)
	{
		sensor_message_t sensor_message;

		memset(&sensor_message, 0, sizeof(sensor_message_t));

		lora_get_sensor_message(&sensor_message);

		wolfSSH_stream_send(thread_ctx->ssh, (byte*) &sensor_message, sizeof(sensor_message_t));
	}

	wolfSSH_stream_exit(thread_ctx->ssh, 0);
	wolfSSH_free(thread_ctx->ssh);
	shutdown(thread_ctx->client_socket);
	fprintf(stderr, "upload server session ended\n");
	osEventFlagsSet(thread_ctx->exit_flag_id, 1);
	free(thread_ctx);
	osThreadExit();
}
