/*
 * timer.c
 *
 *  Created on: May 6, 2024
 *      Author: andrew
 */

#include <lora.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "main.h"
#include "mcu.h"

/** */
void periodic_callback (void *argument)
{
	uint32_t timer_register = MCU_ReadRegister(0);

	uint8_t hours, minutes, seconds, date, month, year;

	MCU_GetTime(&hours, &minutes, &seconds, &date, &month, &year);

	bool state = timer_register & (1 << hours);

	//fprintf(stderr, "timer register = %8.8lx hour = %d state = %d\n", timer_register, hours, state);

	HAL_GPIO_WritePin(IO_GPIO04_GPIO_Port, IO_GPIO04_Pin, state);
}

/** */
void init_timer(void)
{
	osTimerId_t periodic_id = osTimerNew(periodic_callback, osTimerPeriodic, NULL, NULL);

	if(periodic_id)
	{
		if(osTimerStart(periodic_id, 60*1000U)!= osOK)// once every 60 seconds
		{
			fprintf(stderr, "could not start periodic timer\n");
		}
	}
	else
	{
		fprintf(stderr, "failed to create periodic timer\n");
	}
}
