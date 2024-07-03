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

////#define DEBUG_SPI
//
///** */
//bool WDRV_WINC_SPIReceive(void* pReceiveData, size_t rxSize)
//{
//	uint8_t dummy_buffer[300];
//	HAL_StatusTypeDef status;
//
//#ifdef DEBUG_SPI
//	printf("RECV %d ", rxSize);
//#endif
//
//	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_RESET);
//	status = HAL_SPI_TransmitReceive(&hspi3, dummy_buffer, pReceiveData, rxSize, 1000);
//	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_SET);
//
//#ifdef DEBUG_SPI
//	uint8_t * p = (uint8_t *)pReceiveData;
//	for(int i= 0; i < rxSize; i++)
//	{
//		printf("%2.2x ", p[i]);
//	}
//
//	printf("\n");
//#endif
//	return status == HAL_OK;
//}
//
///** */
//bool WDRV_WINC_SPISend(void* pTransmitData, size_t txSize)
//{
//	uint8_t dummy_buffer[300];
//	HAL_StatusTypeDef status;
//
//#ifdef DEBUG_SPI
//	printf("SEND %d ", txSize);
//#endif
//
//	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_RESET);
//	status = HAL_SPI_TransmitReceive(&hspi3, pTransmitData, dummy_buffer, txSize, 1000);
//	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_SET);
//
//#ifdef DEBUG_SPI
//
//	uint8_t * p = (uint8_t *)pTransmitData;
//	for(int i= 0; i < txSize; i++)
//	{
//		printf("%2.2x ", p[i]);
//	}
//	printf("\n");
//#endif
//
//	return status == HAL_OK;
//}


//#define DEBUG_SPI

/** */
bool WDRV_WINC_SPIReceive(void* pReceiveData, size_t rxSize)
{
	uint8_t dummy;
	HAL_StatusTypeDef status;

	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_RESET);

	while(rxSize--)
	{
		status = HAL_SPI_TransmitReceive(&hspi3, &dummy, pReceiveData++, 1, 1000);

		if(status != HAL_OK)
		{
			break;
		}
	}

	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_SET);

	return status == HAL_OK;
}

/** */
bool WDRV_WINC_SPISend(void* pTransmitData, size_t txSize)
{
	uint8_t dummy;
	HAL_StatusTypeDef status;

	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_RESET);

	while(txSize--)
	{
		status = HAL_SPI_TransmitReceive(&hspi3, pTransmitData++, &dummy, 1, 1000);

		if(status != HAL_OK)
		{
			break;
		}
	}

	HAL_GPIO_WritePin(WIFI_NSS_GPIO_Port, WIFI_NSS_Pin, GPIO_PIN_SET);

	return status == HAL_OK;
}

