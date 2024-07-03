/* ssh_server.c
 *
 *  Created on: 25 Nov 2021
 *      Author: andrew
 */

#include <stdio.h>
#include <string.h>
#include <cmsis_os2.h>
#include <shell.h>
#include "main.h"
#include "socket.h"
#include "tcp.h"
#include "fs.h"

#include "ssh_server_config.h"
#include "ssh_server.h"
#include "ssh_server_utils.h"

static const char password_buffer[] = "andrew:plum\n";

//#define LOGGING
//#define NO_PK_FILE

#ifdef NO_PK_FILE

static const char public_key_buffer[] = "ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAA"
		"BBBEw0aA8Qs6FrrXoWC3jG+Z5rhfUNPhGixkY6iNSqmqq3ZSizQlL9/Sk3oSGa0ZpsM9ny"
		"k4YUoEgtOuc2MNCG/yw= andrew@andrews-Precision-3440\n";
#endif


const osThreadAttr_t shell_task_attributes = {
  .name = "shell_server_task",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t upload_task_attributes = {
  .name = "upload_server_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t echo_task_attributes = {
  .name = "echo_server_task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/** */
static void start_server_thread(thread_ctx_t *thread_ctx)
{
	fprintf(stderr, "waiting on wolfssh accept\n");

	int accept_return = wolfSSH_accept(thread_ctx->ssh);
	static osThreadId_t thread_id = 0;

	switch (accept_return)
	{
		case WS_SUCCESS:
		{
			const char *command = wolfSSH_GetSessionCommand(thread_ctx->ssh);

			if (command == NULL)
			{
				if(osThreadGetState(thread_id) != osThreadRunning)
				{
					osThreadNew((osThreadFunc_t)shell_server, thread_ctx, &shell_task_attributes);
					fprintf(stderr, "shell server thread started\n");
				}
				else
				{
					fprintf(stderr, "server thread busy\n");
				}
				break;
			}
			else if (strcmp(command, "upload") == 0)
			{
				if(osThreadGetState(thread_id) != osThreadRunning)
				{
					osThreadNew((osThreadFunc_t)upload_server, thread_ctx, &upload_task_attributes);
					fprintf(stderr, "upload thread started\n");
				}
				else
				{
					fprintf(stderr, "server thread busy\n");
				}
				break;
			}
			else if (strcmp(command, "echo") == 0)
			{
				if(osThreadGetState(thread_id) != osThreadRunning)
				{
				osThreadNew((osThreadFunc_t)echo_server, thread_ctx, &echo_task_attributes);
				fprintf(stderr, "echo thread started\n");
				}
				else
				{
					fprintf(stderr, "server thread busy\n");
				}
				break;
			}
		}

		case WS_SCP_INIT:
		{
			ssh_scp_init(thread_ctx);
			wolfSSH_accept(thread_ctx->ssh);
			wolfSSH_stream_exit(thread_ctx->ssh, 0);
			wolfSSH_shutdown(thread_ctx->ssh);
			shutdown(thread_ctx->client_socket);
			osEventFlagsSet(thread_ctx->exit_flag_id, 1);
			free(thread_ctx);
			wolfSSH_free(thread_ctx->ssh);
			break;
		}

		case WS_SCP_COMPLETE:
		{
			fprintf(stderr, "scp complete\n");
			break;
		}

		default:
		{
			fprintf(stderr, "ssh accept failed %d\n",accept_return);
			wolfSSH_stream_exit(thread_ctx->ssh, 0);
			wolfSSH_shutdown(thread_ctx->ssh);
			shutdown(thread_ctx->client_socket);
			osEventFlagsSet(thread_ctx->exit_flag_id, 1);
			free(thread_ctx);
			wolfSSH_free(thread_ctx->ssh);
			break;
		}
	}
}


#ifdef LOGGING
/** */
static void ssh_logging_callback(enum wolfSSH_LogLevel level, const char *const message)
{
	if (WS_LOG_ERROR == level)
	{
		fprintf(stderr, "\x1B[41m%s\x1B[0m\n", message);
	}
	else
	{
		fprintf(stderr, "%s\n", message);
	}
}
#endif

/** */
static void ssh_server(char *banner)
{
	fprintf(stderr, "starting  wolfSSH\n");
	if (wolfSSH_Init() != WS_SUCCESS)
	{
		fprintf(stderr, "could not initialize wolfSSH\n");
		return;
	}

#ifdef LOGGING
	wolfSSH_SetLoggingCb(ssh_logging_callback);
	wolfSSH_Debugging_ON();
#else
	wolfSSH_SetLoggingCb(NULL);
	wolfSSH_Debugging_OFF();
#endif

	WOLFSSH_CTX *wolfssh_ctx;
	if ((wolfssh_ctx = wolfSSH_CTX_new(WOLFSSH_ENDPOINT_SERVER, NULL)) == NULL)
	{
		fprintf(stderr, "could not allocate SSH CTX data\n");
		return;
	}

	PwMapList password_map_list;
	memset(&password_map_list, 0, sizeof(PwMapList));

	wolfSSH_SetUserAuth(wolfssh_ctx, auth_user);
	wolfSSH_CTX_SetBanner(wolfssh_ctx, banner);
	wolfSSH_SetIORecv(wolfssh_ctx, recv_callback);
	wolfSSH_SetIOSend(wolfssh_ctx, send_callback);
	wolfSSH_SetScpRecv(wolfssh_ctx, scp_recv_callback);
	wolfSSH_SetScpSend(wolfssh_ctx, scp_send_callback);

	byte buffer[SCRATCH_BUFFER_SIZE];
	int buffer_size = load_key(buffer, SCRATCH_BUFFER_SIZE);

	if (buffer_size == 0)
	{
		fprintf(stderr, "could not load key\n");
		return;
	}
	if (wolfSSH_CTX_UsePrivateKey_buffer(wolfssh_ctx, buffer, buffer_size, WOLFSSH_FORMAT_ASN1) < 0)
	{
		fprintf(stderr, "could not use key buffer\n");
		return;
	}

	buffer_size = strlen(password_buffer);
	memcpy(buffer, password_buffer, buffer_size);
	buffer[buffer_size] = 0;
	load_password_buffer(buffer, buffer_size, &password_map_list);

#ifdef NO_PK_FILE
	const char *buffer_name;
	buffer_name = public_key_buffer;
	buffer_size = strlen(buffer_name);
	memcpy(buffer, buffer_name, buffer_size);
#else
	lfs_file_t file;
	int err = lfs_file_open(&lfs, &file, ".ssh/id_ecdsa.pub", LFS_O_RDWR);

	if (err < 0)
	{
		fprintf(stderr, "could not open public key file\n");
		return;
	}

	if (lfs_file_read(&lfs, &file, buffer, sizeof(buffer)) < 0)
	{
		fprintf(stderr, "could not read public key file\n");
		return;
	}

	lfs_file_close(&lfs, &file);
#endif

	buffer[buffer_size] = 0;
	load_public_key_buffer(buffer, buffer_size, &password_map_list);

	SOCKET server_socket;
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET; /* using IPv4      */
	servAddr.sin_port = _htons(4040); /* on 'RANDOM' port */
	servAddr.sin_addr.s_addr = 0; /* from anywhere   */

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "failed to create a socket\n");
		return;
	}

	if (!tcp_bind(server_socket, (struct sockaddr*) &servAddr))
	{
		fprintf(stderr, "failed to bind to socket\n");
		return;
	}

	if (!tcp_listen(server_socket))
	{
		fprintf(stderr, "failed to listen to socket\n");
		return;
	}

	osEventFlagsId_t exit_flag_id = osEventFlagsNew(NULL);
	while(true)
	{
		WOLFSSH *ssh;
		if ((ssh = wolfSSH_new(wolfssh_ctx)) == NULL)
		{
			fprintf(stderr, "could not allocate SSH data\n");
			return;
		}

		wolfSSH_SetUserAuthCtx(ssh, &password_map_list);
		wolfSSH_SetHighwaterCtx(ssh, (void*) ssh);
		wolfSSH_SetHighwater(ssh, HIGHWATER_MARK);

		fprintf(stderr, "waiting on tcp accept\n");

		SOCKET client_socket;
		if ((client_socket = tcp_accept(server_socket)) < 0)
		{
			wolfSSH_stream_exit(ssh, 0);
			wolfSSH_shutdown(ssh);
			wolfSSH_free(ssh);
			fprintf(stderr, "failed tcp accept\n");
			continue;
		}

		thread_ctx_t *thread_ctx;
		thread_ctx = (thread_ctx_t*) malloc(sizeof(thread_ctx_t));
		if (thread_ctx == NULL)
		{
			fprintf(stderr, "could not allocate thread context data\n");
			break;
		}

		memset(thread_ctx, 0, sizeof(thread_ctx_t));

		wolfSSH_set_fd(ssh, client_socket);

		thread_ctx->ssh = ssh;
		thread_ctx->client_socket = client_socket;
		thread_ctx->available = 0;
		thread_ctx->exit_flag_id = exit_flag_id;
		wolfSSH_SetIOReadCtx(ssh, thread_ctx);
		wolfSSH_SetIOWriteCtx(ssh, thread_ctx);

		start_server_thread(thread_ctx);

		osEventFlagsWait(exit_flag_id, 1, osFlagsWaitAny, osWaitForever);
	}
}

/** */
void ssh_start(char *banner)
{
	ssh_server(banner);

	// something broke
	fprintf(stderr, "ssh server failed. resetting system\n");
	NVIC_SystemReset();
}
