/*
 * wdrv_winc_common.h
 *
 *  Created on: Jan 9, 2024
 *      Author: andrew
 */

#ifndef WINC1500_BSP_INCLUDE_WDRV_WINC_COMMON_H_
#define WINC1500_BSP_INCLUDE_WDRV_WINC_COMMON_H_

extern WDRV_WINC_DEBUG_PRINT_CALLBACK pfWINCDebugPrintCb;

void WDRV_WINC_GPIOChipEnableDeassert(void);
void WDRV_WINC_GPIOChipEnableAssert(void);
void WDRV_WINC_GPIOResetAssert(void);
void WDRV_WINC_GPIOResetDeassert(void);
void WDRV_MSDelay(uint32_t delay);

#endif /* WINC1500_BSP_INCLUDE_WDRV_WINC_COMMON_H_ */
