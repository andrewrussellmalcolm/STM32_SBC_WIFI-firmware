/*
 * mcu.h
 *
 *  Created on: Jan 17, 2024
 *      Author: andrew
 */

#ifndef INC_MCU_H_
#define INC_MCU_H_

#include <stdint.h>
#include <stdbool.h>

#define MCU_BBRAM_SIZE 4096

void MCU_ReadMemory(uint8_t *data,uint16_t len);
void MCU_WriteMemory(uint8_t *data, uint16_t len);
void MCU_ClearMemory(uint16_t len);
// Read at the offset from the beginning of the BBRAM
void MCU_ReadMemoryAtOffset(uint32_t offset, uint8_t *data,uint16_t len);
// Write at the offset from the beginning of the BBRAM
void MCU_WriteMemoryAtOffset(uint32_t offset, uint8_t *data, uint16_t len);

void MCU_ReadRegisters(uint32_t *regs, uint16_t len);

uint32_t MCU_ReadRegister(uint32_t reg);
void MCU_WriteRegsiter(uint32_t reg, uint32_t value);

void MCU_IncrementRegister(uint32_t reg);

bool MCU_GetBatteryVoltage(float *voltage);

void MCU_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t date, uint8_t month, uint8_t year);
void MCU_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds, uint8_t *date, uint8_t *month, uint8_t *year);

uint32_t MCU_GetUniqueID(void);
void MCU_SetBrownoutLevel(void);
uint32_t MCU_GetBrownoutLevel(void);
#endif /* INC_MCU_H_ */
