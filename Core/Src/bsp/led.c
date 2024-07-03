/*
 * led.c
 *
 *  Created on: 15 Jan 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"
#include "led.h"

/** */
static void led0_timer_callback(TIM_HandleTypeDef *timer)
{
    led_set_state(LED_0, LED_OFF);
    HAL_TIM_Base_Stop(&htim6);
}

/** */
static void led1_timer_callback(TIM_HandleTypeDef *timer)
{
    led_set_state(LED_1, LED_OFF);
    HAL_TIM_Base_Stop(&htim7);
}

/** */
void led_set_state(led_number_t led, led_state_t state)
{
    switch (led)
    {
    case LED_0:
    {
    	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state);
        break;
    }

    case LED_1:
    {
    	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
        break;
    }
    }
}

/** */
void led_toggle_state(led_number_t led)
{
    switch (led)
    {
    case LED_0:
    {
    	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
        break;
    }

    case LED_1:
    {
    	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        break;
    }
    }
}

/** */
void led_flash(led_number_t led)
{
    switch (led)
    {
    case LED_0:
    {
        led_set_state(led, LED_ON);
        HAL_TIM_RegisterCallback(&htim6, HAL_TIM_PERIOD_ELAPSED_CB_ID, led0_timer_callback);
        HAL_TIM_Base_Start_IT(&htim6);
        break;
    }

    case LED_1:
    {
        led_set_state(led, LED_ON);
        HAL_TIM_RegisterCallback(&htim7, HAL_TIM_PERIOD_ELAPSED_CB_ID, led1_timer_callback);
        HAL_TIM_Base_Start_IT(&htim7);
        break;
    }
    }
}

