/*
 * lora_task.c
 *
 *  Created on: Jan 17, 2024
 *      Author: andrew
 */

#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "cmsis_os.h"
#include "main.h"
#include "sx1272.h"
#include "lora.h"
#include "utils.h"
#include "fs.h"

//#define DEBUG_LORA

static osMessageQueueId_t sensor_queue;
static const uint32_t lora_stop_flag = 1;

static osEventFlagsId_t lora_event_flags_id;

/** */
uint32_t lora_mesage_count(void)
{
	return osMessageQueueGetCount(sensor_queue);
}

/** */
bool lora_get_sensor_message(sensor_message_t *sensor_message)
{
	return osMessageQueueGet(sensor_queue, sensor_message, NULL, 0) == osOK;
}

/** */
bool lora_put_sensor_message(sensor_message_t *sensor_message)
{
	return osMessageQueuePut(sensor_queue, sensor_message, 0, 0) == osOK;
}

/** */
void lora_stop(void)
{
	osEventFlagsSet(lora_event_flags_id, lora_stop_flag);
}

/** */
void lora_task(void)
{
	lora_event_flags_id = osEventFlagsNew(NULL);

	osDelay(2000);

	// do not continue if hardware not present
	if(SX1272_GetVersion() != 22)
	{
		osThreadExit();
	}

#ifdef DEBUG_LORA
	fprintf(stderr, "lora task started\n");
#endif

	sensor_queue = osMessageQueueNew(50, sizeof(sensor_message_t), NULL);

#ifdef DEBUG_LORA
	if(sensor_queue == NULL)
	{
		fprintf(stderr, "lora message queue creation failed\n");
		return;
	}
#endif

	SX1272_ReceiveAsyncStart();

	while (true)
	{
		uint8_t buffer[256];
		size_t len = sizeof(buffer);
		memset(buffer, 0, sizeof(buffer));
		PollResult pollResult = SX1272_ReceiveAsyncPoll(buffer, &len);

		switch (pollResult)
		{
		case PacketWaiting:
		{
			uint32_t ferr = SX1272_GetFrequencyError();
			int16_t rssi = SX1272_GetPacketRSSI();
			int8_t snr = SX1272_GetPacketSNR();

			SX1272_ReceiveAsyncStart();
			SX1272_FlashRX();

			if (len == sizeof(sensor_data_t))
			{
				sensor_message_t sensor_message;
				sensor_message.sensor_data = *((sensor_data_t*) buffer);
				sensor_message.ferr = ferr;
				sensor_message.rssi = rssi;
				sensor_message.snr = snr;
				sensor_message.timestamp = utc_timestamp();
#ifdef DEBUG_LORA
				    fprintf(stderr, "lora message received. length = %d at %s\n", len, ctime(&sensor_message.timestamp));
#endif

				//append_to_current_file((char *)&sensor_message, sizeof(sensor_message_t));

				if (lora_put_sensor_message(&sensor_message) != osOK)
				{
					//fprintf(stderr, "lora queue full\n");
				}
			}

			break;
		}

		case PacketError:
		{
			SX1272_ReceiveAsyncStart();
			break;
		}

		case NoPacket:
		default:
		{
			break;
		}
		}

		if (osEventFlagsWait(lora_event_flags_id, lora_stop_flag, osFlagsWaitAny, 1) == lora_stop_flag)
		{
			break;
		}
	}

#ifdef DEBUG_LORA
	fprintf(stderr, "lora task stopping. reboot to resume\n");
#endif
}

