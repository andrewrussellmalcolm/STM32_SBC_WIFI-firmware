/*
 * sensor.h
 *
 *  Created on: Dec 19, 2023
 *      Author: andrew
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

void sensor_init(void);
float sensor_get_temperature(void);
uint16_t sensor_get_raw_temperature(void);
uint8_t sensor_get_id(void);
void sensor_interrupt_callback(void);

#endif /* INC_SENSOR_H_ */
