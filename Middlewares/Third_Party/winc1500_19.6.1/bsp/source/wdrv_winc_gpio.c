/*
 * wdrv_winc_common.c
 *
 *  Created on: Jan 9, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

/** */
void WDRV_WINC_GPIOChipEnableDeassert(void)
{
	HAL_GPIO_WritePin(WIFI_CEN_GPIO_Port,WIFI_CEN_Pin,GPIO_PIN_RESET);
}

/** */
void WDRV_WINC_GPIOChipEnableAssert(void)
{
	HAL_GPIO_WritePin(WIFI_CEN_GPIO_Port,WIFI_CEN_Pin,GPIO_PIN_SET);
}

/** */
void WDRV_WINC_GPIOResetAssert(void)
{
    HAL_GPIO_WritePin(WIFI_RSTN_GPIO_Port,WIFI_RSTN_Pin,GPIO_PIN_RESET);
}

/** */
void WDRV_WINC_GPIOResetDeassert(void)
{
    HAL_GPIO_WritePin(WIFI_RSTN_GPIO_Port,WIFI_RSTN_Pin,GPIO_PIN_SET);
}

