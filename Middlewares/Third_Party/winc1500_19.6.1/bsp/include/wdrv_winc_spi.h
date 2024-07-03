/*
 * wdrv_winc_spi.h
 *
 *  Created on: Jan 9, 2024
 *      Author: andrew
 */

#ifndef WINC1500_BSP_INCLUDE_WDRV_WINC_SPI_H_
#define WINC1500_BSP_INCLUDE_WDRV_WINC_SPI_H_

bool WDRV_WINC_SPIReceive(void* pReceiveData, size_t rxSize);
bool WDRV_WINC_SPISend(void* pTransmitData, size_t txSize);

#endif /* WINC1500_BSP_INCLUDE_WDRV_WINC_SPI_H_ */
