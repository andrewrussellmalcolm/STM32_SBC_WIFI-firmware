/*
 * shell_nfc.c
 *
 *  Created on: Jan 16, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "shell.h"
#include "nfc.h"

/**
 * ST25DV04K-IER6S3 chip 4kbits/512 bytes eeprom
 */
void shell_nfc_command(const char *commandString)
{
	uint8_t arg1_len;
	uint8_t arg2_len;
	uint8_t arg3_len;
	uint8_t arg4_len;
	uint8_t arg5_len;
	const char *arg1 = shell_get_parameter(commandString, 1, &arg1_len);
	const char *arg2 = shell_get_parameter(commandString, 2, &arg2_len);
	const char *arg3 = shell_get_parameter(commandString, 3, &arg3_len);
	const char *arg4 = shell_get_parameter(commandString, 4, &arg4_len);
	const char *arg5 = shell_get_parameter(commandString, 5, &arg5_len);
	uint32_t addr = 0;
	uint8_t val = 0xaa;
	uint16_t len = 0;

	if (arg3)
	{
		sscanf(arg3, "%x", (unsigned int*) &addr);
		printf("addr=%lx ", addr);
	}

	if (arg4)
	{
		unsigned int temp;
		sscanf(arg4, "%x", &temp);
		val = (uint8_t) temp;
		printf("value=%x ", val);
	}

	if (arg5)
	{
		unsigned int temp;
		sscanf(arg5, "%d", &temp);
		len = (uint16_t) temp;
		printf("length=%d ", len);
	}
	printf("\n");

	if (len > NFC_EEPROM_SIZE)
	{
		printf("maximum read/write length is %d (0x%x) bytes\n", NFC_EEPROM_SIZE, NFC_EEPROM_SIZE);
		return;
	}

	if (shell_arg_is("read", arg1, arg1_len))
	{
		if ((shell_arg_is("memory", arg2, arg2_len)))
		{
			if (len == 0)
			{
				len = 0x40;
			}

			uint8_t *data = (uint8_t*) malloc(len);
			memset(data, 0x00, len);
			NFC_ReadMemory(addr, data, len);
			shell_print_array(addr, data, len);
			printf("NFC memory at %lx\n", addr);
			free(data);
		}
		else if ((shell_arg_is("mbox", arg2, arg2_len)))
		{
			uint8_t data[256];
			uint8_t len;
			memset(data, 0xaa, sizeof(data));
			NFC_ReadMailbox(data, &len);
			shell_print_array(0, data, len);
			printf("NFC mailbox message len %d\n", len);
		}
		else if ((shell_arg_is("rfsecurity", arg2, arg2_len)))
		{
			uint8_t rfctl;
			uint8_t rfprot;

			NFC_ReadRFSecurityZoneStatus(&rfctl, &rfprot);
			printf("nfc rf pwctl=%2.2x nfc rf rw prot=%2.2x\n", rfctl, rfprot);
		}
		else if (shell_arg_is("uid", arg2, arg2_len))
		{
			uint64_t snb;
			NFC_ReadUID(&snb);
			printf("NFC device uid number=%llx\n", snb);
		}
		else if (shell_arg_is("size", arg2, arg2_len))
		{
			uint16_t size;
			NFC_ReadMemorySize(&size);
			printf("NFC device memory size=%d bytes\n", size);
		}
		else
		{
			printf("unrecognised argument: %s\n", arg2);
		}
	}
	else if (shell_arg_is("write", arg1, arg1_len))
	{
		if ((shell_arg_is("memory", arg2, arg2_len)))
		{
			if (len == 0)
			{
				len = 1;
			}

			uint8_t *data = (uint8_t*) malloc(len);
			memset(data, val, len);
			NFC_WriteMemory(addr, data, len);
			printf("NFC memory at %lx set to %x\n", addr, data[0]);
			free(data);
		}
		else if ((shell_arg_is("mbox", arg2, arg2_len)))
		{
			uint8_t data[256];
			memset(data, 0xbb, sizeof(data));
			NFC_WriteMailbox(data, (uint16_t) sizeof(data));
			printf("NFC mailbox at set to %x\n", data[0]);
		}
	}
	else if (shell_arg_is("mailbox", arg1, arg1_len))
	{
		NFC_EnableMailbox(shell_arg_is("enable", arg2, arg2_len));
	}
	else if (shell_arg_is("device", arg1, arg1_len))
	{
		if(NFC_CheckInField())
		{
			printf("device in field\n");
		}
		else
		{
			printf("device not in field\n");
		}
	}
	else if (shell_arg_is("wait", arg1, arg1_len))
	{
		printf("press a key to exit\n");
		bool in_field = NFC_CheckInField();

		while (true)
		{
			if(in_field &!NFC_CheckInField())
			{
				printf("no device in field\n");
				in_field = false;
			}

			if(!in_field &NFC_CheckInField())
			{
				printf("device in field\n");
				in_field = true;
			}

			if (NFC_CheckMessageReady())
			{
				uint8_t message[256];
				memset(message, 0, 256);
				uint8_t len;
				NFC_ReadMailbox(message, &len);

				printf("NFC - mailbox message received [%s] length %d\n", message, len);
			}

			if(kbhit())
			{
				getchar();
				break;
			}
		}
	}
	else
	{
		printf("incorrect argument\n");
	}
}
