/*
 * lora.h
 *
 *  Created on: Jan 11, 2024
 *      Author: andrew
 */

#ifndef INC_LORA_H_
#define INC_LORA_H_

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "main.h"

#pragma pack(4)
typedef struct
{
	uint32_t id;
	float temperature;
	float humidity;
	float pressure;
	uint16_t intensity;
	float battery;
}
sensor_data_t;

#pragma pack()

#pragma pack(4)
typedef struct
{
	sensor_data_t sensor_data;
	time_t timestamp;
	uint32_t ferr;
	int16_t rssi;
	int8_t snr;
}
sensor_message_t;
#pragma pack()

#pragma pack(4)
typedef struct
{
	uint32_t message_count;
	uint32_t pad[9];
} upload_header_t;
#pragma pack()

void lora_stop(void);
uint32_t lora_mesage_count(void);
bool lora_get_sensor_message(sensor_message_t *sensor_message);
bool lora_put_sensor_message(sensor_message_t *sensor_message);
#endif /* INC_LORA_H_ */
