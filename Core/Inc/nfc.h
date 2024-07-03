/**
 * HubCore
 * Copyright (c) Guru Systems 2020
 * Author: Andrew Malcolm <arm@gurusystems.com>
 */

#ifndef __NFC_H
#define __NFC_H

#include <stdint.h>
#include <stdbool.h>


#define NFC_EEPROM_SIZE 512

// layout of memory (See src/cc/board/core/core/Src/secure_storage_map.h)
#define NFC_MEM_DEV_MAC 0 // (uint32_t)
#define NFC_MEM_ENABLE_SIO 4 // (uint8_t)
#define NFC_MEM_SEC_KEY 8 // (35 x uint8_t) x 5 slots
#define NFC_MEM_NXT_ENT 183 // next spare location

void NFC_Init(void);
void NFC_InterfaceISR(void);
void NFC_ReadUID(uint64_t *puid);
void NFC_EnableMailbox(bool enable);
void NFC_ReadMemorySize(uint16_t *size);
void NFC_ReadMemory(uint32_t addr, uint8_t * const data, uint16_t len);
void NFC_WriteMemory(uint32_t addr, uint8_t * const data,uint16_t len);
void NFC_ReadMailbox(uint8_t * const data, uint8_t *len);
void NFC_WriteMailbox(uint8_t *data,uint16_t len);
bool NFC_CheckMessageReady(void);
bool NFC_CheckInField(void);
void NFC_ReadRFSecurityZoneStatus(uint8_t *rfctl, uint8_t *rfprot);
void NFC_WriteRFSecurityZoneStatus(uint8_t rfctl, uint8_t rfprot);

#endif
