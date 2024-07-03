/*
 * HubCore
 * Copyright (c) Guru Systems 2020
 * Author: Andrew Malcolm <arm@gurusystems.com>
 */

#ifndef __SX1272_H
#define __SX1272_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// set to 0 to suppress debugging to stderr
#define SX1272_DEBUG_LEVEL 0

// register set
#define SX1272_FIFO 0x00
#define SX1272_OP_MODE 0x01
#define SX1272_BITRATE_MSB 0x02
#define SX1272_BITRATE_LSB 0x03
#define SX1272_FRF_MSB 0x06
#define SX1272_FRF_MID 0x07
#define SX1272_FRF_LSB 0x08
#define SX1272_PA_CONFIG 0x09
#define SX1272_PA_RAMP 0x0A
#define SX1272_OCP 0x0B
#define SX1272_LNA_GAIN 0x0C
#define SX1272_FIFO_ADDR_PTR 0x0D
#define SX1272_FIFO_TX_BASE_ADDR 0x0E
#define SX1272_FIFO_RX_BASE_ADDR 0x0F
#define SX1272_FIFO_RX_CURRENT_ADDR 0x10
#define SX1272_IRQ_FLAGS_MASK 0x11
#define SX1272_IRQ_FLAGS 0x12
#define SX1272_RX_NB_BYTES 0x13
#define SX1272_MODEM_STAT 0x18
#define SX1272_PKT_SNR_VALUE 0x19
#define SX1272_PACKET_RSSI 0x1A
#define SX1272_CURRENT_RSSI 0x1B
#define SX1272_HOP_CHANNEL 0x1C
#define SX1272_MODEM_CONFIG1 0x1D
#define SX1272_MODEM_CONFIG2 0x1E
#define SX1272_PREAMBLE_MSB 0x20
#define SX1272_PREAMBLE_LSB 0x21
#define SX1272_PAYLOAD_LENGTH_LORA 0x22
#define SX1272_MAX_PAYLOAD_LENGTH 0x23
#define SX1272_OSC 0x24
#define SX1272_FIFO_RX_BYTE_ADDR 0x25
#define SX1272_FREQ_ERROR_MSB 0x28
#define SX1272_FREQ_ERROR_MID 0x29
#define SX1272_FREQ_ERROR_LSB 0x2a
#define SX1272_INVERTIQ 0x33
#define SX1272_SYNC_WORD 0x39
#define SX1272_INVERTIQ2 0x3B
#define SX1272_TEMPERATURE 0x3C
#define SX1272_DIO_MAPPING1 0x40
#define SX1272_DIO_MAPPING2 0x41
#define SX1272_VERSION 0x42
#define SX1272_PA_DAC 0x5A

#define MAX_PACKET_SIZE 0xFF
#define NUM_PREAMBLE_BYTES 0x08

// RegOpMode
#define SX1272_MODE_LORA_RESET 0x00
#define SX1272_MODE_LORA_SLEEP 0x80
#define SX1272_MODE_LORA_STANDBY 0x81
#define SX1272_MODE_LORA_TX 0x83
#define SX1272_MODE_LORA_RX 0x85
#define SX1272_MODE_LORA_CAD 0x87
#define SX1272_MODE_FSK_STANDBY 0x01
#define SX1272_MODE_FSK_TX 0x03
#define SX1272_MODE_FSK_RX 0x05
#define SX1272_MODE_ACCESS_SHARED 0x40

// RegIrqFlags
#define SX1272_IRQ_FLAG_CAD_DETECTED 0x01
#define SX1272_IRQ_FLAG_CAD_DONE 0x04
#define SX1272_IRQ_FLAG_TXDONE 0x08
#define SX1272_IRQ_FLAG_HEADER_VALID 0x10
#define SX1272_IRQ_FLAG_PAYLOAD_CRC_ERROR 0x20
#define SX1272_IRQ_FLAG_RXDONE 0x40
#define SX1272_IRQ_FLAG_RX_TIMEOUT 0x80

// frequency constants
#define SX1272_XTAL_FREQ 32000000
#define SX1272_FREQ_STEP 61.03515625

typedef enum {
  Bandwidth_125 = 125000,
  Bandwidth_250 = 250000,
  Bandwidth_500 = 500000,
} Bandwidth;

typedef enum {
  CodingRate_4by5 = 0x01,
  CodingRate_4by6 = 0x02,
  CodingRate_4by7 = 0x03,
  CodingRate_4by8 = 0x04,
} CodingRate;

typedef enum {
  SpreadingFactor_6 = 0x06,  // not supported
  SpreadingFactor_7 = 0x07,
  SpreadingFactor_8 = 0x08,
  SpreadingFactor_9 = 0x09,
  SpreadingFactor_10 = 0x0A,
  SpreadingFactor_11 = 0x0B,  // lowdata rate optimise is mandated for SF11 and
                              // SF12 with BW = 125 kHz
  SpreadingFactor_12 = 0x0C,
} SpreadingFactor;

typedef enum {
  TxContinousModeOn = 0x28,
  TxContinousModeOff = 0x0,
} TxContinousMode;

typedef enum {
  PaRamp_3400us = 0,
  PaRamp_2000us = 1,
  PaRamp_1000us = 2,
  PaRamp_500us = 3,
  PaRamp_250us = 4,
  PaRamp_125us = 5,
  PaRamp_100us = 6,
  PaRamp_62us = 7,
  PaRamp_50us = 8,
  PaRamp_40us = 9,
  PaRamp_31us = 10,
  PaRamp_25us = 11,
  PaRamp_20us = 12,
  PaRamp_15us = 13,
  PaRamp_12us = 14,
  PaRamp_10us = 15,
} PaRamp;

typedef enum {
  OCPTrim_40To120mA = 0x0f,
  OCPTrim_130To240mA = 0x10,
  OCPTrim_240mA = 0x1b,

} OCPTrim;

typedef enum {
  LNAGain_G1 = 0x20,  // MAX
  LNAGain_G2 = 0x40,  //
  LNAGain_G3 = 0x60,  //
  LNAGain_G4 = 0x80,  //
  LNAGain_G5 = 0xa0,  //
  LNAGain_G6 = 0xc0,  // MIN
} LNA_Gain;

typedef enum {
  LNABoost_Off = 0x00,
  LNABoost_On = 0x03,
} LNA_Boost;

typedef enum {
  Power_16dB = 0x10,
  Power_15dB = 0xf,
  Power_14dB = 0xe,
  Power_13dB = 0xd,
  Power_12dB = 0xc,
  Power_11dB = 0xb,
  Power_10dB = 0xa,
  Power_9dB = 0x9,
  Power_8dB = 0x8,
  Power_7dB = 0x7,
  Power_6dB = 0x6,
  Power_3dB = 0x3,
} PA_Power;

typedef enum {
  PaDAC_HighPower = 0x87,
  PaDAC_Default = 0x84,
} PaDAC;

typedef enum {
  Channel_0 = 0xD88024,  // channel 12, central freq = 866.00MHz
  Channel_1 = 0xD8C000,  // channel 16, central freq = 867.00MHz
} Channel;

typedef enum {
  Off,
  CW,
  TX,
  RX,
} TestMode;

typedef enum {
  PacketWaiting,
  NoPacket,
  PacketError,
} PollResult;

// notes
// this driver does no adderess filtering: it is just a byte pipe
// it is up to the caller to format transmitter packets
// and to filter received packets based on that format

// set up the chip and set some defaults
void SX1272_Init(void);

// set the lora mode: convenience function, calls the next three funtions in
// turn
void SX1272_SetMode(Bandwidth bw, SpreadingFactor sf, CodingRate cr);

// set the various LoRa parameters - transmitter and receiver must match on
// thyese
void SX1272_SetCodingRate(CodingRate cr);
CodingRate SX1272_GetCodingRate(void);
void SX1272_SetSpreadingFactor(SpreadingFactor sf);
SpreadingFactor SX1272_GetSpreadingFactor(void);
void SX1272_SetBandwidth(Bandwidth bw);
Bandwidth SX1272_GetBandwidth(void);
void SX1272_SetCRCOn(bool on);
bool SX1272_GetCRCOn(void);
void SX1272_SetLowDataRateOptimise(bool on);
bool SX1272_GetLowDataRateOptimise(void);
void SX1272_SetExplicitHeaderMode(bool on);
bool SX1272_GetExplicitHeaderMode(void);
int32_t SX1272_GetFrequencyError(void);

// set the LoRa channel to one of the standard frequencies
void SX1272_SetChannel(Channel channel);
Channel SX1272_GetChannel(void);

// direct frequency set, for debugging
void SX1272_SetFrequency(uint32_t frequency);

uint32_t SX1272_GetFrequency(void);
// transmit will send length bytes (up to 255) the buffer and return. A CRC is
// appended automatically
bool SX1272_Transmit(const uint8_t *buffer, size_t length);

// receive will write any packet it receives with a valid CRC to the provided
// buffer, up to a maximum of *length bytes. Returns false after timeout if no
// packet received, else true with length set to packet length received
PollResult SX1272_Receive(uint8_t *buffer, size_t *length, uint16_t timeout);

// async versions of receive
void SX1272_ReceiveAsyncStart(void);
PollResult SX1272_ReceiveAsyncPoll(uint8_t *buffer, size_t *length);

// set CW mode is for testing ONLY
void SX1272_SetCWMode(bool on);
bool SX1272_GetCWMode(void);

// set power
void SX1272_SetPower(PA_Power power);

// get power
PA_Power SX1272_GetPower(void);

// get the SNR of the previous packet reception,units dB
int8_t SX1272_GetPacketSNR(void);

// get the RSSI of the previous packet reception,units dBm
int16_t SX1272_GetPacketRSSI(void);

// get the current RSSI of the channel,units dBm
int16_t SX1272_GetCurrentRSSI(void);

// for debugging
int16_t SX1272_GetDebug(void);

// query the channel free
bool SX1272_IsChannelFree(void);

// get the chip temperature on deg C
int8_t SX1272_GetTemperature(void);

// get the chip version number (currently 22)
uint8_t SX1272_GetVersion(void);

// calculatre time on air for a given packet length
uint16_t SX1272_GetTimeOnAir(uint8_t packetLen);

// set up dio pins
void SX1272_SetDIO(void);

// invert IQ
void SX1272_SetInvertIQ(bool invert);
bool SX1272_GetInvertIQ(void);

// sync word
void SX1272_SetSyncWord(uint8_t syncWord);
uint8_t SX1272_GetSyncWord(void);

// hardware-dependant functions
uint8_t SX1272_ReadRegister(uint8_t addr);
void SX1272_WriteRegister(uint8_t addr, uint8_t data);
void SX1272_Delay(uint32_t delay);
uint32_t SX1272_GetTick(void);
void SX1272_HAL_Init(void);

void SX1272_FlashRX(void);
void SX1272_FlashTX(void);
#ifdef __cplusplus
}
#endif

#endif
