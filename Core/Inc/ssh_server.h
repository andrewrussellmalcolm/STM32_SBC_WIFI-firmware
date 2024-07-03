/*
 * ssh_server.h
 *
 */


#ifndef _SSH_SERVER_H_
#define _SSH_SERVER_H_

#include <FreeRTOS.h>
#include <stdbool.h>

#include <wolfssl/wolfcrypt/settings.h>

#include <wolfssl/ssl.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/coding.h>

#include <wolfssh/ssh.h>
#include <wolfssl/wolfcrypt/ecc.h>

#include <wolfssh/certs_test.h>
#include <wolfssh/wolfscp.h>

#include "ssh_server_thread.h"
#include "ssh_server_utils.h"

void ssh_start(char *banner);
void shell_server(thread_ctx_t *ctx);
void upload_server(thread_ctx_t *thread_ctx);
void echo_server(thread_ctx_t *thread_ctx);
#endif /* _SSH_SERVER_H_ */
