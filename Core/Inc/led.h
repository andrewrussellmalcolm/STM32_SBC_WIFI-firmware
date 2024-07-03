/*
 * led.h
 *
 *  Created on: 15 Jan 2024
 *      Author: andrew
 */

#ifndef INC_LED_H_
#define INC_LED_H_

typedef enum
{
	LED_0 = 0U,
	LED_1
} led_number_t;

typedef enum
{
	LED_ON = 0U,
	LED_OFF
} led_state_t;

void led_set_state(led_number_t led, led_state_t state);
void led_toggle_state(led_number_t led);
void led_flash(led_number_t led);

#endif /* INC_LED_H_ */
