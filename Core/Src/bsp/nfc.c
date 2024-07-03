/**
 * HubCore
 * Copyright (c) Guru Systems 2020
 * Author: Andrew Malcolm <arm@gurusystems.com>
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "nfc.h"
#include "st25dv.h"

static ST25DV_Object_t obj;
static NFCTAG_DrvTypeDef *Nfctag_Drv = NULL;
static bool messageReady = false;
static bool inField = false;

// #define DEBUG
static int32_t IOInit(void)
{
    return 0;
}

static int32_t IODeInit(void)
{
    return 0;
}
static uint32_t IOGetTick(void)
{
    return HAL_GetTick();
}
static int32_t IOIsReady(uint16_t addr, const uint32_t ready)
{
    (void)ready;
    return HAL_I2C_IsDeviceReady(&hi2c3, addr, 2, 10);
}

static int32_t IOWrite(uint16_t devAddr, uint16_t addr, const uint8_t *data, uint16_t len)
{
    //fprintf(stderr, "iowrite %4.4x %4.4x\n", devAddr, addr);
    return HAL_I2C_Mem_Write(&hi2c3, devAddr, addr, sizeof(addr), (uint8_t *)data, len, 100);
}

static int32_t IORead(uint16_t devAddr, uint16_t addr, uint8_t *data, uint16_t len)
{
    //fprintf(stderr, "ioread %4.4x %4.4x\n", devAddr, addr);
    return HAL_I2C_Mem_Read(&hi2c3, devAddr, addr, sizeof(addr), data, len, 100);
}

/** */
void NFC_Init(void)
{
    ST25DV_IO_t IO;
    IO.Init = IOInit;
    IO.DeInit = IODeInit;
    IO.GetTick = IOGetTick;
    IO.IsReady = IOIsReady;
    IO.Read = IORead;
    IO.Write = IOWrite;

    ST25DV_RegisterBusIO(&obj, &IO);

    Nfctag_Drv = (NFCTAG_DrvTypeDef *)(void *)&St25Dv_Drv;
    Nfctag_Drv->Init(&obj);

    NFC_WriteRFSecurityZoneStatus(1, 2);

    Nfctag_Drv->ConfigIT(&obj, ST25DV_GPO_RFPUTMSG_MASK|ST25DV_GPO_ENABLE_MASK|ST25DV_GPO_FIELDCHANGE_MASK);
}

void NFC_EnableMailbox(bool enable)
{
    ST25DV_WriteMBMode(&obj, enable);
    ST25DV_SetMBEN_Dyn(&obj);
}

/** */
void NFC_ReadUID(uint64_t *puid)
{
    ST25DV_UID uid;
    ST25DV_ReadUID(&obj, &uid);
    *puid = uid.LsbUid | (uint64_t)uid.MsbUid << 32;
}

/** */
void NFC_ReadMemorySize(uint16_t *size)
{
    ST25DV_MEM_SIZE sz;
    ST25DV_ReadMemSize(&obj, &sz);
    *size = sz.Mem_Size;
}

/** */
void NFC_ReadMemory(uint32_t addr, uint8_t *data, uint16_t len)
{
    ST25DV_ReadData(&obj, data, addr, len);
}

/** */
void NFC_WriteMemory(uint32_t addr, uint8_t *data, uint16_t len)
{
    ST25DV_WriteData(&obj, data, addr, len);
}

/** */
void NFC_ReadMailbox(uint8_t *const data, uint8_t *len)
{
    ST25DV_ReadMBLength_Dyn(&obj, len);
    ST25DV_ReadMailboxData(&obj, data, 0, *len);
    messageReady = false;
}

/** */
void NFC_WriteMailbox(uint8_t *data, uint16_t len)
{
    ST25DV_WriteMailboxData(&obj, data, len);
}

/** */
void NFC_ReadRFSecurityZoneStatus(uint8_t *rfctl, uint8_t *rfprot)
{
    ST25DV_RF_PROT_ZONE rfprotZone;
    ST25DV_ReadRFZxSS(&obj, ST25DV_PROT_ZONE1, &rfprotZone);
    *rfctl = rfprotZone.PasswdCtrl;
    *rfprot = rfprotZone.RWprotection;
}

void NFC_WriteRFSecurityZoneStatus(uint8_t rfctl, uint8_t rfprot)
{
    ST25DV_RF_PROT_ZONE rfprotZone;

    ST25DV_PASSWD password;

    password.MsbPasswd = 0;
    password.LsbPasswd = 0;
    ST25DV_PresentI2CPassword(&obj, password);
    rfprotZone.PasswdCtrl = rfctl;
    rfprotZone.RWprotection = rfprot;
    ST25DV_WriteRFZxSS(&obj, ST25DV_PROT_ZONE1, rfprotZone);
}

/** */
bool NFC_CheckMessageReady(void)
{
	return messageReady;
}

/** */
bool NFC_CheckInField(void)
{
	return inField;
}

/** */
void NFC_InterfaceISR(void)
{
    uint8_t status;
    ST25DV_ReadITSTStatus_Dyn(&obj, &status);

    if (status & ST25DV_ITSTS_DYN_RFPUTMSG_MASK)
    {    
        messageReady = true;
    }

    if (status & ST25DV_ITSTS_DYN_FIELDRISING_MASK)
	{
		inField = true;
	}
    else if (status & ST25DV_ITSTS_DYN_FIELDFALLING_MASK)
	{
		inField = false;
	}
}
