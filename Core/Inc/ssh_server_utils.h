/*
 * ssh_server_utils.h
 *
 *  Created on: Jan 31, 2024
 *      Author: andrew
 */

#ifndef INC_SSH_SERVER_UTILS_H_
#define INC_SSH_SERVER_UTILS_H_

#include <socket.h>

#include "ssh_server.h"
#include "ssh_server_thread.h"

/* Map user names to passwords */
/* Use arrays for username and p. The password or public key can
 * be hashed and the hash stored here. Then I won't need the type. */


int load_key(byte *buf, word32 bufSz);
void delete_password_map(PwMapList *list);
int load_password_buffer(byte *buf, word32 bufSz, PwMapList *list);

int load_public_key_buffer(byte *buf, word32 bufSz, PwMapList *list);
int auth_user(byte authType, WS_UserAuthData *authData, void *ctx);
byte find_char(const byte *str, const byte *buf, word32 bufSz);
int dump_stats(thread_ctx_t *ctx);
int recv_callback(WOLFSSH* ssh, void* recv_buffer, word32 recv_length, void * ctx);
int send_callback(WOLFSSH* ssh, void* send_buffer, word32 send_length, void * ctx);

void ssh_scp_init(thread_ctx_t *thread_ctx);
int scp_send_callback(WOLFSSH* ssh, int request, const char* basepath, char * filename, word32 filename_size,
                                  word64* mt_time, word64* st_time, int* file_mode, word32 offset, word32* file_size,
                                  byte* buffer, word32 buffer_size, void* send_ctx);

int scp_recv_callback(WOLFSSH* ssh, int request_type, const char* basepath, const char*filename,
                                  int filename_size, word64 mt_time, word64 at_time, word32 file_mode, byte* offset, word32 file_size,
                                  word32 buffer_size, void*snd_ctx);

#endif /* INC_SSH_SERVER_UTILS_H_ */
