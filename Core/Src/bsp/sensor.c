/*
 * sensor.c
 *
 *  Created on: Dec 19, 2023
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

#include "main.h"

#define I2C_ADDRESS 			    0x90
#define I2C_TIMEOUT 				500

#define ADT7410_TEMPERATURE			0x00
#define ADT7410_STATUS				0x02
#define ADT7410_CONFIG				0x03
#define ADT7410_T_ALARM_HIGH		0x04
#define ADT7410_T_ALARM_LOW			0x06
#define ADT7410_T_CRIT				0x08
#define ADT7410_T_HYST				0x0A
#define ADT7410_ID			    	0x0B
#define ADT7410_RESET				0x2F

#define ADT7410_FAULT_QUEUE_MASK	0x03
#define ADT7410_CT_POLARITY			0x04
#define ADT7410_INT_POLARITY		0x08
#define ADT7410_EVENT_MODE			0x10
#define ADT7410_MODE_MASK			0x60
#define ADT7410_ONESHOT				0x20
#define ADT7410_SPS					0x40
#define ADT7410_PD					0x60
#define ADT7410_RESOLUTION_16_BIT	0x80
#define ADT7410_SHUTDOWN	        0x60

#define CAL_FACTOR 					2.0

/** */
void sensor_init(void)
{
	uint8_t data = 0;
	HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, ADT7410_RESET, 1, &data, 1, I2C_TIMEOUT);
}

/** */
uint8_t sensor_get_id(void)
{
	uint8_t recv_data;
	HAL_I2C_Mem_Read(&hi2c3, I2C_ADDRESS, ADT7410_ID, 1, &recv_data, 1, I2C_TIMEOUT);
	return recv_data;
}

/** */
uint8_t sensor_get_status(void)
{
	uint8_t recv_data;
	HAL_I2C_Mem_Read(&hi2c3, I2C_ADDRESS, ADT7410_STATUS, 1, &recv_data, 1, I2C_TIMEOUT);
	return recv_data;
}

/** */
void sensor_start_conversion(void)
{
	uint8_t data[2] = {ADT7410_CONFIG, ADT7410_RESOLUTION_16_BIT|ADT7410_ONESHOT};
	HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, ADT7410_ID, 1, data, 2, I2C_TIMEOUT);
}

/** */
uint16_t sensor_get_raw_temperature(void)
{
	uint8_t recv_data[2];
	HAL_I2C_Mem_Read(&hi2c3, I2C_ADDRESS, ADT7410_TEMPERATURE, 1, recv_data, 2, I2C_TIMEOUT);
	return ((recv_data[0] << 8) + (recv_data[1] << 0)) & 0xfff8;
}

/** */
float sensor_convert_temperature(uint16_t raw_temperature)
{
	float temperature;

	if ((raw_temperature & 0x8000) == 0x8000)
	{
		temperature = ((float)(raw_temperature - 65536) / 128.0);
	}
	else
	{
		temperature = ((float)(raw_temperature)) / 128.0;
	}

	return temperature - CAL_FACTOR;
}

/** */
float sensor_get_temperature(void)
{
	sensor_start_conversion();

	uint32_t t0 = HAL_GetTick();

	while(true)
	{
		uint8_t status = sensor_get_status();

		if(!(status & 0x80))
		{
			break;
		}

		HAL_Delay(10);
		if(HAL_GetTick() - t0 > 5000)
		{
			return -100.0;
		}
	}

	uint16_t raw_temperature = sensor_get_raw_temperature();
	float temperature = sensor_convert_temperature(raw_temperature);
	//fprintf(stderr, "%ld\t%3.1f\n",HAL_GetTick(), temperature);
	return temperature;
}
