/*
 * radio.h
 *
 *  Created on: Jan 11, 2024
 *      Author: andrew
 */

#ifndef INC_RADIO_H_
#define INC_RADIO_H_

typedef struct
{
	uint32_t id;
	float temperature;
	float humidity;
	float pressure;
	uint16_t intensity;
	float battery;
}
radio_message_t;

#endif /* INC_RADIO_H_ */
