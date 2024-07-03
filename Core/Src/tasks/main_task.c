/*
 * main_task.c
 *
 *  Created on: Dec 27, 2023
 *      Author: andrew
 */

#include <lora.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "wifi.h"
#include "fs.h"
#include "sensor.h"
#include "sx1272.h"
#include "nfc.h"
#include "mcu.h"
#include "socket.h"
#include "utils.h"
#include "led.h"
#include "mcu.h"
#include "timer.h"
#include "ssh_server.h"

#define SSH

/** */
void main_task(void)
{
	char banner[80];
	snprintf(banner, sizeof(banner), "STM32 SBC WIFI built at %s on %s [board id = %lx]\n",__TIME__, __DATE__, MCU_GetUniqueID());
	fprintf(stderr, banner);

	sensor_init();
	fs_init();
	wifi_init();
	SX1272_Init();
	NFC_Init();
	init_timer();

	osDelay(2000);

#ifdef SSH
	// never returns;
	ssh_start(banner);
#else
	while (true)
	{
		if (kbhit())
		{
			shell_process_key(getchar());
		}

		osDelay(1);
	}
#endif
}
