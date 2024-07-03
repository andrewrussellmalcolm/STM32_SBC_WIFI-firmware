/*
 * ssh_utils.c
 *
 *  Created on: Jan 31, 2024
 *      Author: andrew
 */

#include "ssh_server_config.h"
#include "ssh_server.h"
#include "ssh_server_utils.h"

#include "socket.h"
#include "tcp.h"

#include "fs.h"
#include "utils.h"

/* returns buffer size on success */
int load_key(byte *buf, word32 buffer_size)
{
	word32 sz = 0;

	if ((word32) sizeof_ecc_key_der_256 > buffer_size)
	{
		return 0;
	}
	WMEMCPY(buf, ecc_key_der_256, sizeof_ecc_key_der_256);
	sz = sizeof_ecc_key_der_256;

	return sz;
}

/* our own little c word32 to array */
static inline void c32toa(word32 u32, byte *c)
{
	c[0] = (u32 >> 24) & 0xff;
	c[1] = (u32 >> 16) & 0xff;
	c[2] = (u32 >> 8) & 0xff;
	c[3] = u32 & 0xff;
}

/** */
PwMap* new_password_map(PwMapList *list, byte type, const byte *username, word32 usernameSz, const byte *p, word32 pSz)
{
	PwMap *map;

	map = (PwMap*) malloc(sizeof(PwMap));
	if (map != NULL)
	{
		wc_Sha256 sha;
		byte flatSz[4];

		map->type = type;
		if (usernameSz >= sizeof(map->username))
			usernameSz = sizeof(map->username) - 1;
		memcpy(map->username, username, usernameSz + 1);
		map->username[usernameSz] = 0;
		map->usernameSz = usernameSz;

		wc_InitSha256(&sha);
		c32toa(pSz, flatSz);
		wc_Sha256Update(&sha, flatSz, sizeof(flatSz));
		wc_Sha256Update(&sha, p, pSz);
		wc_Sha256Final(&sha, map->p);

		map->next = list->head;
		list->head = map;
	}

	return map;
}

/** */
void delete_password_map(PwMapList *list)
{
	if (list != NULL)
	{
		PwMap *head = list->head;

		while (head != NULL)
		{
			PwMap *cur = head;
			head = head->next;
			memset(cur, 0, sizeof(PwMap));
			free(cur);
		}
	}
}

/** */
int load_password_buffer(byte *buf, word32 buffer_size, PwMapList *list)
{
	char *str = (char*) buf;
	char *delimiter;
	char *username;
	char *password;

	/* Each line of passwd.txt is in the format
	 *     username:password\n
	 * This function modifies the passed-in buffer. */

	if (list == NULL)
		return -1;

	if (buf == NULL || buffer_size == 0)
		return 0;

	while (*str != 0)
	{
		delimiter = strchr(str, ':');
		if (delimiter == NULL)
		{
			return -1;
		}
		username = str;
		*delimiter = 0;
		password = delimiter + 1;
		str = strchr(password, '\n');
		if (str == NULL)
		{
			return -1;
		}
		*str = 0;
		str++;
		if (new_password_map(list, WOLFSSH_USERAUTH_PASSWORD, (byte*) username, (word32) strlen(username), (byte*) password, (word32) strlen(password)) == NULL)
		{
			return -1;
		}
	}

	return 0;
}

/** */
int load_public_key_buffer(byte *buf, word32 buffer_size, PwMapList *list)
{
	char *str = (char*) buf;
	char *delimiter;
	byte *publicKey64;
	word32 publicKey64Sz;
	byte *username;
	word32 usernameSz;
	byte publicKey[300];
	word32 publicKeySz;

	/* Each line of passwd.txt is in the format
	 *     ecdsa-sha2-nistp256 AAAB3BASE64ENCODEDPUBLICKEYBLOB username\n
	 * This function modifies the passed-in buffer. */
	if (list == NULL)
		return -1;

	if (buf == NULL || buffer_size == 0)
		return 0;

	while (*str != 0)
	{
		/* Skip the public key type. This example will always be ssh-rsa. */
		delimiter = strchr(str, ' ');
		if (delimiter == NULL)
		{
			return -1;
		}
		str = delimiter + 1;
		delimiter = strchr(str, ' ');
		if (delimiter == NULL)
		{
			return -1;
		}
		publicKey64 = (byte*) str;
		*delimiter = 0;
		publicKey64Sz = (word32) (delimiter - str);
		str = delimiter + 1;
		delimiter = strchr(str, '\n');
		if (delimiter == NULL)
		{
			return -1;
		}
		username = (byte*) str;
		*delimiter = 0;
		usernameSz = (word32) (delimiter - str);
		str = delimiter + 1;
		publicKeySz = sizeof(publicKey);

		if (Base64_Decode(publicKey64, publicKey64Sz, publicKey, &publicKeySz) != 0)
		{
			return -1;
		}

		if (new_password_map(list, WOLFSSH_USERAUTH_PUBLICKEY, username, usernameSz, publicKey, publicKeySz) == NULL)
		{
			return -1;
		}
	}

	return 0;
}

/** */
int auth_user(byte authType, WS_UserAuthData *authData, void *ctx)
{
	PwMapList *list;
	PwMap *map;
	byte authHash[WC_SHA256_DIGEST_SIZE];

	if (ctx == NULL)
	{
		fprintf(stderr, "wsUserAuth: ctx not set");
		return WOLFSSH_USERAUTH_FAILURE;
	}

	if (authType != WOLFSSH_USERAUTH_PASSWORD && authType != WOLFSSH_USERAUTH_PUBLICKEY)
	{

		return WOLFSSH_USERAUTH_FAILURE;
	}

	/* Hash the password or public key with its length. */
	{
		wc_Sha256 sha;
		byte flatSz[4];
		wc_InitSha256(&sha);
		if (authType == WOLFSSH_USERAUTH_PASSWORD)
		{
			c32toa(authData->sf.password.passwordSz, flatSz);
			wc_Sha256Update(&sha, flatSz, sizeof(flatSz));
			wc_Sha256Update(&sha, authData->sf.password.password, authData->sf.password.passwordSz);
		}
		else if (authType == WOLFSSH_USERAUTH_PUBLICKEY)
		{
			c32toa(authData->sf.publicKey.publicKeySz, flatSz);
			wc_Sha256Update(&sha, flatSz, sizeof(flatSz));
			wc_Sha256Update(&sha, authData->sf.publicKey.publicKey, authData->sf.publicKey.publicKeySz);
		}
		wc_Sha256Final(&sha, authHash);
	}

	list = (PwMapList*) ctx;
	map = list->head;

	while (map != NULL)
	{
		if (authData->usernameSz == map->usernameSz && memcmp(authData->username, map->username, map->usernameSz) == 0)
		{

			if (authData->type == map->type)
			{
				if (memcmp(map->p, authHash, WC_SHA256_DIGEST_SIZE) == 0)
				{
					return WOLFSSH_USERAUTH_SUCCESS;
				}
				else
				{
					return (authType == WOLFSSH_USERAUTH_PASSWORD ? WOLFSSH_USERAUTH_INVALID_PASSWORD : WOLFSSH_USERAUTH_INVALID_PUBLICKEY);
				}
			}
			else
			{
				return WOLFSSH_USERAUTH_INVALID_AUTHTYPE;
			}
		}
		map = map->next;
	}

	return WOLFSSH_USERAUTH_INVALID_USER;
}

/* find a byte character [str] of length [buffer_size] within [buf];
 * returns byte position if found, otherwise zero
 * TODO what if buffer_size > 255?
 */
byte find_char(const byte *str, const byte *buf, word32 buffer_size)
{
	const byte *cur;
	while (buffer_size)
	{
		cur = str;
		while (*cur != '\0')
		{
			if (*cur == *buf)
				return *cur;
			cur++;
		}
		buf++;
		buffer_size--;
	}

	return 0;
}

/** */
int dump_stats(thread_ctx_t *ctx)
{
	//fprintf(stderr,"dumpstats");
	char stats[1024];
	word32 statsSz;
	word32 txCount, rxCount, seq, peerSeq;

	wolfSSH_GetStats(ctx->ssh, &txCount, &rxCount, &seq, &peerSeq);

	WSNPRINTF(stats, sizeof(stats), "Statistics for Thread #%u:\r\n"
			"  txCount = %u\r\n  rxCount = %u\r\n"
			"  seq = %u\r\n  peerSeq = %u\r\n", 0, txCount, rxCount, seq, peerSeq);
	statsSz = (word32) strlen(stats);

	fprintf(stderr, "%s", stats);
	return wolfSSH_stream_send(ctx->ssh, (byte*) stats, statsSz);
}

/** */
int recv_callback(WOLFSSH *ssh, void *recv_buffer, word32 recv_length, void *ctx)
{
	if (ctx != NULL)
	{
		thread_ctx_t * thread_ctx = (thread_ctx_t*)ctx;

		if(thread_ctx->available <= 0)
		{
			thread_ctx->rx_ptr = thread_ctx->rx_buffer;

			thread_ctx->available = RX_BUFFER_LENGTH;
			if (!tcp_recv(thread_ctx->client_socket, thread_ctx->rx_buffer, &thread_ctx->available))
			{
				return WS_CBIO_ERR_GENERAL;
			}
		}

		if (thread_ctx->available < recv_length)
		{
			recv_length = thread_ctx->available;
		}
		// copy requested data
		memcpy(recv_buffer, thread_ctx->rx_ptr, recv_length);

		thread_ctx->rx_ptr+=recv_length;
		thread_ctx->available -= recv_length;
	}
	else
	{
		return WS_CBIO_ERR_GENERAL;
	}

	return recv_length;
}

/** */
int send_callback(WOLFSSH *ssh, void *send_buffer, word32 send_length, void *ctx)
{
	if (ctx != NULL)
	{
		thread_ctx_t * thread_ctx = (thread_ctx_t*)ctx;


		if (!tcp_send(thread_ctx->client_socket, send_buffer, send_length))
		{
			return WS_CBIO_ERR_GENERAL;
		}
	}

	return send_length;
}

static int ExtractFileName(const char* filePath, char* fileName, word32 fileNameSz)
{
    int ret = WS_SUCCESS;
    word32 fileLen;
    int idx = 0, pathLen, separator = -1;

    if (filePath == NULL || fileName == NULL)
        return WS_BAD_ARGUMENT;

    pathLen = (int)WSTRLEN(filePath);

    /* find last separator */
    while (idx < pathLen) {
        if (filePath[idx] == '/' || filePath[idx] == '\\')
            separator = idx;
        idx++;
    }

    if (separator < 0)
        return WS_BAD_ARGUMENT;

    fileLen = pathLen - separator - 1;
    if (fileLen + 1 > fileNameSz)
        return WS_SCP_PATH_LEN_E;

    WMEMCPY(fileName, filePath + separator + 1, fileLen);
    fileName[fileLen] = '\0';

    return ret;
}

/** */
void ssh_scp_init(thread_ctx_t *thread_ctx)
{
	static lfs_file_t file;
	wolfSSH_SetScpRecvCtx(thread_ctx->ssh, (void*)&file);
	wolfSSH_SetScpSendCtx(thread_ctx->ssh, (void*)&file);
}

/** */
int scp_send_callback(WOLFSSH *ssh, int request, const char *basepath, char *filename, word32 filename_size, word64 *m_time, word64 *a_time, int *file_mode, word32 offset, word32 *file_size, byte *buffer, word32 buffer_size, void *ctx)
{
	lfs_file_t *file = (lfs_file_t*) ctx;
	int ret = WS_SCP_CONTINUE;

	switch (request)
	{
	case WOLFSSH_SCP_NEW_REQUEST:
	{
		return WS_SCP_CONTINUE;
		break;
	}

	case WOLFSSH_SCP_SINGLE_FILE_REQUEST:
	{
		if (lfs_file_open(&lfs, file, basepath, LFS_O_RDONLY ) != 0)
		{
			WLOG(WS_LOG_ERROR, "scp: unable to open file for reading, abort");
			wolfSSH_SetScpErrorMsg(ssh, "unable to open file for reading");
			ret = WS_SCP_ABORT;
			break;
		}

		ExtractFileName(basepath, filename, filename_size);

		*file_size = lfs_file_size(&lfs, file);

		ret = lfs_file_read(&lfs, file, buffer, buffer_size);

		offset += ret;
		if ((ret < 0) || (*file_size == (word32)ret))
		{
			*file_mode = 0644;
			*m_time = utc_timestamp();
			*a_time = utc_timestamp();
			lfs_file_close(&lfs, file);
		}

		break;
	}

	case WOLFSSH_SCP_RECURSIVE_REQUEST:
	{
		return WS_SCP_ABORT;
		break;
	}

	case WOLFSSH_SCP_CONTINUE_FILE_TRANSFER:
	{
		ret = lfs_file_read(&lfs, file, buffer, buffer_size);

		offset += ret;

		if ((ret < 0) || (*file_size == offset))
		{
			*file_mode = 0644;
			*m_time = utc_timestamp();
			*a_time = utc_timestamp();
			lfs_file_close(&lfs, file);
		}

		break;
	}

	default:
	{
		return WS_SCP_ABORT;
	}
	}

	return ret;
}

/** */
int scp_recv_callback(WOLFSSH *ssh, int state, const char *basepath, const char *filename, int file_mode, word64 m_time, word64 a_time, word32 totalFileSz, byte *buffer, word32 buffer_size, word32 fileOffset, void *ctx)
{
	lfs_file_t *file = (lfs_file_t*) ctx;
	int ret = WS_SCP_CONTINUE;

	switch (state)
	{

	case WOLFSSH_SCP_NEW_REQUEST:
	{
		break;
	}

	case WOLFSSH_SCP_NEW_FILE:
	{
		/* make dir if it does not already exist */
		lfs_mkdir(&lfs, basepath);

		/* build absolute filename: lfs has no chdir */
		char absolute[WOLFSSH_MAX_FILENAME];
		memset(absolute,0, WOLFSSH_MAX_FILENAME);
		strncat(absolute, (char*)basepath, WOLFSSH_MAX_FILENAME);
		strcat(absolute, "/");
		strncat(absolute, filename, WOLFSSH_MAX_FILENAME);

		/* open file */
		if (lfs_file_open(&lfs, file, absolute, LFS_O_WRONLY | LFS_O_TRUNC | LFS_O_CREAT) != 0)
		{
			WLOG(WS_LOG_ERROR, "scp: unable to open file for writing, abort");
			wolfSSH_SetScpErrorMsg(ssh, "unable to open file for writing");
			ret = WS_SCP_ABORT;
			break;
		}

		/* store file pointer in user ctx */
		wolfSSH_SetScpRecvCtx(ssh, file);
		break;
	}

	case WOLFSSH_SCP_FILE_PART:
	{
		/* write file, or file part */
		word32 bytes = (word32) lfs_file_write(&lfs, file, buffer, buffer_size);

		if (bytes != buffer_size)
		{
			WLOG(WS_LOG_ERROR, "scp error: %s, %d", "scp receive callback unable to write requested size to file", bytes);
			lfs_file_close(&lfs, file);
			ret = WS_SCP_ABORT;
		}
		break;
	}

	case WOLFSSH_SCP_FILE_DONE:
	{
		lfs_file_close(&lfs, file);

//		/* set timestamp info */
//		if (mTime != 0 || aTime != 0)
//		{
//			ret = WS_SUCCESS; //SetTimestampInfo(filename, mTime, aTime);
//
//			if (ret == WS_SUCCESS)
//			{
//				ret = WS_SCP_CONTINUE;
//			}
//			else
//			{
//				WLOG(WS_LOG_ERROR, "scp: unable to set timestamp info, abort");
//				ret = WS_SCP_ABORT;
//			}
//		}

		break;
	}

	case WOLFSSH_SCP_NEW_DIR:
	{
		if (WSTRLEN(filename) > 0)
		{
			/* try to create new directory */
			if (lfs_mkdir(&lfs, filename) < 0)
			{
				WLOG(WS_LOG_ERROR, "scp: error creating directory, abort");
				wolfSSH_SetScpErrorMsg(ssh, "error creating directory");
				ret = WS_SCP_ABORT;
				break;
			}

		}
		break;
	}

	case WOLFSSH_SCP_END_DIR:
	{
		break;
	}

	default:
		ret = WS_SCP_ABORT;
	}

	return ret;
}
