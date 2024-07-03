/*
 * shell_server.c
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

static WOLFSSH *ssh;

/** override of system getchar etc. */
int _read(int file, char *data, int len)
{
	if (file == STDERR_FILENO)
	{
	}
	else if (file == STDIN_FILENO)
	{
		if (ssh)
		{
			if(wolfSSH_stream_read(ssh, (uint8_t*) data, len) < 0)
			{
				*data = -1;
			}
		}
	}
	return len;
}

/** override of system putchar, printf etc */
int _write(int file, char *src_ptr, int len)
{
	if (file == STDERR_FILENO)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*) src_ptr, 1, -1);
	}
	else if (file == STDOUT_FILENO)
	{
		if (ssh)
		{
			if (len > 80)
			{
				len = 80;
			}
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));

			char *dst_ptr = buffer;

			for (int i = 0; i < len; i++)
			{
				*dst_ptr = *src_ptr;
				if (*dst_ptr == '\n')
				{
					*dst_ptr++ = '\r';
					*dst_ptr = '\n';
				}

				src_ptr++;
				dst_ptr++;
			}
			wolfSSH_stream_send(ssh, (uint8_t*) buffer, strlen(buffer));
		}
	}

	return len;
}

/** */
bool kbhit(void)
{
//	uint8_t data = 0;
//	int res = wolfSSH_stream_peek(ssh, (uint8_t*)&data, 1) > 0;
//
//	if(res)
//	{
//		return true;
//	}

	return false;
}

/** */
void shell_server(thread_ctx_t *thread_ctx)
{
	fprintf(stderr, "shell server session started\n");

	ssh = thread_ctx->ssh;

	setvbuf(stdin, NULL, _IONBF, 0);

	printf("$ ");

	while (true)
	{
		char ch = getchar();

		if (!shell_process_key(ch))
		{
			break;
		}
	}

	ssh = NULL;

	wolfSSH_stream_exit(thread_ctx->ssh, 0);
	wolfSSH_shutdown(thread_ctx->ssh);
	wolfSSH_free(thread_ctx->ssh);
	shutdown(thread_ctx->client_socket);
	fprintf(stderr, "shell server session ended\n");
	osEventFlagsSet(thread_ctx->exit_flag_id, 1);

	free(thread_ctx);
	osThreadExit();
}
