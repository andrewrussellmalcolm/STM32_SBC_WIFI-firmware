/*
 * shell_lora.c
 *
 *  Created on: Jan 15, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "shell.h"
#include "socket.h"
#include "sx1272.h"
#include "lora.h"
#include "wifi.h"

/** */
static uint8_t channelToChannelNum(Channel channel)
{
	if (channel == Channel_0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

///** */
//static Channel channelNumToChannel(uint8_t channelNum)
//{
//    if (channelNum == 0)
//    {
//        return Channel_0;
//    }
//    else
//    {
//        return Channel_1;
//    }
//}

/** */
void shell_lora_command(const char *commandString)
{
	uint8_t arg1Length;
	uint8_t arg2Length;
	const char *arg1 = shell_get_parameter(commandString, 1, &arg1Length);
	const char *arg2 = shell_get_parameter(commandString, 2, &arg2Length);

	if (shell_arg_is("version", arg1, arg1Length))
	{
		printf("SX1272 chip version = %x\n", SX1272_GetVersion());
	}
	else if (shell_arg_is("cw", arg1, arg1Length))
	{
		if (arg2Length > 0)
		{
			if (shell_arg_is("on", arg2, arg2Length))
			{
				printf("********** WARNING *********\n");
				printf("********* TEST ONLY ********\n");
				printf("* USE ONLY IN TEST CHAMBER *\n");
				printf("* MAY INTERFERE WITH OTHER *\n");
				printf("***** DEVICES/NETWORKS *****\n");
				printf("********** WARNING *********\n");

				SX1272_SetCWMode(true);

				printf("CW mode on\n");
			}
			else if (shell_arg_is("off", arg2, arg2Length))
			{
				SX1272_SetCWMode(false);
				printf("CW mode off\n");
			}
		}
		else
		{
			bool cwMode = SX1272_GetCWMode();
			printf("CW mode %s\n", cwMode ? "on" : "off");
		}
	}
	else if (shell_arg_is("tx", arg1, arg1Length))
	{
		uint8_t *message = (uint8_t*) "01234567890123456789012345678901234567890123456789";
		uint8_t len = strlen((char*) message);
		uint16_t toa = 36; //SX1272_GetTimeOnAir(len);
		uint16_t repeat = 100; //toa * 100;
		uint16_t pktCount = 0;

		if (arg2 != NULL)
		{
			repeat = atoi(arg2);
		}

		printf("sending messages every %dms. Press 'q' to stop test.\n\n", repeat);

		while (1)
		{
			SX1272_Transmit(message, len);

			printf("[%d] sent %d bytes: time on air=%dms, repeat=%dms\n", ++pktCount, len, toa, repeat);
			SX1272_FlashTX();

			for (uint16_t d = 0; d < repeat; d += 50)
			{
				HAL_Delay(50);
			}

			if (kbhit())
			{
				if (getchar() == 'q')
				{
					break;
				}
			}
		}

		printf("\ndone. packet count=%d\n", pktCount);
	}
	else if (shell_arg_is("rx", arg1, arg1Length))
	{
		printf("Waiting for messages. Press 'q' to stop test.\n\n");

		uint8_t buffer[256];
		uint16_t pktCount = 0;
		uint16_t errCount = 0;

		SX1272_ReceiveAsyncStart();

		while (true)
		{
			size_t len = sizeof(buffer);
			memset(buffer, 0, sizeof(buffer));
			PollResult poll_result = SX1272_ReceiveAsyncPoll(buffer, &len);

			switch (poll_result)
			{
			case PacketWaiting:
			{
				uint32_t ferr = SX1272_GetFrequencyError();
				int16_t rssi = SX1272_GetPacketRSSI();
				int8_t snr = SX1272_GetPacketSNR();

				SX1272_ReceiveAsyncStart();

				pktCount++;
				SX1272_FlashRX();

				RTC_TimeTypeDef sTime;
				HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

				printf("[%d] received %d bytes. snr=%ddB, rssi=%ddBm, ferr=%ld. CRC errors=%d at %2.2d:%2.2d:%2.2d\n", pktCount, len, snr, rssi, ferr, errCount, sTime.Hours, sTime.Minutes, sTime.Seconds);

				if (shell_arg_is("print", arg2, arg2Length))
				{
					shell_print_array(0, buffer, len);
				}

				break;
			}

			case PacketError:
			{
				SX1272_ReceiveAsyncStart();
				errCount++;
				printf("bad packet received. crc errors=%d\n", errCount);
				break;
			}

			case NoPacket:
			default:
			{
				break;
			}
			}

			if (kbhit())
			{
				if (getchar() == 'q')
				{
					break;
				}
			}

			HAL_Delay(50);
		}

		printf("\ndone. packet count=%d, error count=%d\n", pktCount, errCount);
	}
	else if (shell_arg_is("settings", arg1, arg1Length))
	{
		Channel channel = SX1272_GetChannel();
		Bandwidth bw = SX1272_GetBandwidth();
		CodingRate cr = SX1272_GetCodingRate();
		SpreadingFactor sf = SX1272_GetSpreadingFactor();
		bool crcOn = SX1272_GetCRCOn();
		PA_Power power = SX1272_GetPower();
		uint32_t frequency = SX1272_GetFrequency();

		printf("frequency %ldMHz\n"
				"channel=%d\n"
				"bandwidth=%dkHz\n"
				"coding rate=4/%d\n"
				"spreading factor=%d\n"
				"power=%ddB\n"
				"crc on=%s\n", frequency, channelToChannelNum(channel), bw / 1000, cr + 4, sf, power, crcOn ? "on" : "off");

	}
	else if (shell_arg_is("stop", arg1, arg1Length))
	{
		lora_stop();
	}
	else if (shell_arg_is("message", arg1, arg1Length))
	{
		if (shell_arg_is("count", arg2, arg2Length))
		{
			printf("there are %ld messages waiting\n", lora_mesage_count());
		}
		else if (shell_arg_is("print", arg2, arg2Length))
		{
			printf("there are %ld messages waiting\n", lora_mesage_count());

			int count = (lora_mesage_count());

			for (int index = 0; index < count; index++)
			{
				sensor_message_t sensor_message;

				lora_get_sensor_message(&sensor_message);

				printf("id=%8lx temp=%4.1f batt=%2.1f (snr=%ddB, rssi=%ddBm, ferr=%ldHz) timestamp = %s",
						sensor_message.sensor_data.id,
						sensor_message.sensor_data.temperature,
						sensor_message.sensor_data.battery,
						sensor_message.snr,
						sensor_message.rssi,
						sensor_message.ferr,
						ctime(&sensor_message.timestamp));

				lora_put_sensor_message(&sensor_message);
			}
		}
		else
		{
			printf("missing argument\n");
		}
	}
	else
	{
		printf("missing argument\n");
	}
}

