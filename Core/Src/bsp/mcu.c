/*
 * mcu.c
 *
 *  Created on: Jan 17, 2024
 *      Author: andrew
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "mcu.h"

/** */
void MCU_ReadMemory(uint8_t *data, uint16_t len)
{
    uint8_t *bram = (uint8_t *)BKPSRAM_BASE;

    __HAL_RCC_BKPSRAM_CLK_ENABLE();
    memcpy(data, bram, len);
    __HAL_RCC_BKPSRAM_CLK_DISABLE();
}

/** */
void MCU_WriteMemory(uint8_t *data, uint16_t len)
{
    uint8_t *bram = (uint8_t *)BKPSRAM_BASE;

    __HAL_RCC_BKPSRAM_CLK_ENABLE();
    memcpy(bram, data, len);
    __HAL_RCC_BKPSRAM_CLK_DISABLE();
}

/** */
void MCU_ClearMemory(uint16_t len)
{
    uint8_t *bram = (uint8_t *)BKPSRAM_BASE;

    __HAL_RCC_BKPSRAM_CLK_ENABLE();
    memset(bram, 0, len);
    __HAL_RCC_BKPSRAM_CLK_DISABLE();
}

/** */
void MCU_ReadMemoryAtOffset(uint32_t offset, uint8_t *data,uint16_t len)
{
  uint8_t *bram = (uint8_t *)BKPSRAM_BASE + offset;

  __HAL_RCC_BKPSRAM_CLK_ENABLE();
  memcpy(data, bram, len);
  __HAL_RCC_BKPSRAM_CLK_DISABLE();
}

/** */
void MCU_WriteMemoryAtOffset(uint32_t offset, uint8_t *data, uint16_t len)
{
  uint8_t *bram = (uint8_t *)BKPSRAM_BASE + offset;

  __HAL_RCC_BKPSRAM_CLK_ENABLE();
  memcpy(bram, data, len);
  __HAL_RCC_BKPSRAM_CLK_DISABLE();
}

/** */
void MCU_ReadRegisters(uint32_t *regs, uint16_t len)
{
    for (int reg = 0; reg < len; reg++)
    {
        regs[reg] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0 + reg);
    }
}

/** */
uint32_t MCU_ReadRegister(uint32_t reg)
{
    return HAL_RTCEx_BKUPRead(&hrtc, reg);
}

/** */
void MCU_WriteRegsiter(uint32_t reg, uint32_t value)
{
    HAL_PWR_EnableBkUpAccess();
    HAL_RTCEx_BKUPWrite(&hrtc, reg, value);
    HAL_PWR_DisableBkUpAccess();
}

/** */
void MCU_IncrementRegister(uint32_t reg)
{
    HAL_PWR_EnableBkUpAccess();
    uint64_t value = (uint64_t)MCU_ReadRegister(reg);
    value++;
    HAL_RTCEx_BKUPWrite(&hrtc, reg, (uint32_t)value);
    HAL_PWR_DisableBkUpAccess();
}

/** */
bool MCU_GetBatteryVoltage(float *voltage)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, -1) != HAL_OK)
    {
        return false;
    }

    float vbatraw = HAL_ADC_GetValue(&hadc1);

    *voltage=vbatraw;
    *voltage *= 3300;    // ADC reference (Vcc)
    *voltage /= 4095.0;  // Reading in mV
    *voltage /= 500.0;   // Reading in Volts (compensating for internal divide by 2 )
    *voltage *= 2.95/2.8; // calibration

    return true;
}

/** */
void MCU_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t date, uint8_t month, uint8_t year)
{
    RTC_TimeTypeDef sTime = {.Hours = hours, .Minutes = minutes, .Seconds = seconds};
    RTC_DateTypeDef sDate = {.Date = date, .Month = month, .Year = year};

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

/** */
void MCU_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint8_t *date, uint8_t *month, uint8_t *year)
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    *hours = sTime.Hours;
    *minutes = sTime.Minutes;
    *seconds = sTime.Seconds;
    *date = sDate.Date;
    *month = sDate.Month;
    *year = sDate.Year;
}

/**
 * Unique device IDs register set
 * See ST reference manual RM0033
 */
#define ID1 (0x1FFF7A10)
#define ID2 (0x1FFF7A14)
#define ID3 (0x1FFF7A18)

/** */
uint32_t MCU_GetUniqueID(void)
{
    return (*(uint32_t *)ID1) + (*(uint32_t *)ID2) + (*(uint32_t *)ID3);
}

/** */
void MCU_SetBrownoutLevel(void)
{
	FLASH_OBProgramInitTypeDef obInit;

	HAL_FLASHEx_OBGetConfig(&obInit);
	obInit.BORLevel=OB_BOR_LEVEL3; /*!< Supply voltage ranges from 2.70 to 3.60 V */
	HAL_FLASH_OB_Unlock();
	HAL_FLASHEx_OBProgram(&obInit);
	HAL_FLASH_OB_Lock();
}

/** */
uint32_t MCU_GetBrownoutLevel(void)
{
	FLASH_OBProgramInitTypeDef obInit;
	HAL_FLASHEx_OBGetConfig(&obInit);
	return obInit.BORLevel;
}

