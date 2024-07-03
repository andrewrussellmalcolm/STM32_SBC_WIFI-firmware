/**
 *
 *  Created on: Nov 28, 2023
 *      Author: andrew
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"
#include "sx1272.h"
#include "math.h"

static int16_t currentRssi = 0;

/** */
void SX1272_Init(void)
{
	SX1272_HAL_Init();
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_RESET);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_SLEEP);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	SX1272_WriteRegister(SX1272_MAX_PAYLOAD_LENGTH, 0xFF);
	SX1272_WriteRegister(SX1272_FIFO_RX_BASE_ADDR, 0x00);
	SX1272_WriteRegister(SX1272_FIFO_TX_BASE_ADDR, 0x00);
	SX1272_WriteRegister(SX1272_PREAMBLE_MSB, 0);
	SX1272_WriteRegister(SX1272_PREAMBLE_LSB, NUM_PREAMBLE_BYTES);
	SX1272_SetLowDataRateOptimise(false);
	SX1272_SetMode(Bandwidth_500, SpreadingFactor_7, CodingRate_4by8);
	SX1272_SetExplicitHeaderMode(true);
	SX1272_SetPower(Power_15dB);
	SX1272_SetChannel(Channel_1);
	SX1272_SetCRCOn(true);
	SX1272_SetCWMode(false);
	SX1272_GetTimeOnAir(250);
}

/** */
void SX1272_SetDIO(void)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetDIO\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY | SX1272_MODE_ACCESS_SHARED);
	SX1272_WriteRegister(SX1272_DIO_MAPPING2, 0x20); // clock out to DIO5
	SX1272_WriteRegister(SX1272_OSC, 0x03);          // 4MHz
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
void SX1272_SetCodingRate(CodingRate codingRate)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetCodingRate\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config &= 0xC7;
	switch (codingRate)
	{
	case CodingRate_4by5:
	{
		config |= 0x08;
		break;
	}
	case CodingRate_4by6:
	{
		config |= 0x10;
		break;
	}
	case CodingRate_4by7:
	{
		config |= 0x18;
		break;
	}
	case CodingRate_4by8:
	{
		config |= 0x20;
		break;
	}
	}

	SX1272_WriteRegister(SX1272_MODEM_CONFIG1, config);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
CodingRate SX1272_GetCodingRate(void)
{
	CodingRate codingRate = CodingRate_4by5;
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config &= 0x28;
	switch (config)
	{
	case 0x08:
	{
		codingRate = CodingRate_4by5;
		break;
	}
	case 0x10:
	{
		codingRate = CodingRate_4by6;
		break;
	}
	case 0x18:
	{
		codingRate = CodingRate_4by7;
		break;
	}
	case 0x20:
	{
		codingRate = CodingRate_4by8;
		break;
	}
	}

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetCodingRate %d\n", codingRate);
#endif

	return codingRate;
}

/** */
void SX1272_SetSpreadingFactor(SpreadingFactor spreadingFactor)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetSpreadingFactor\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG2);
	config &= 0x0f;
	switch (spreadingFactor)
	{
	case SpreadingFactor_6:
	{
		config |= 0x60;
		break;
	}
	case SpreadingFactor_7:
	{
		config |= 0x70;
		break;
	}
	case SpreadingFactor_8:
	{
		config |= 0x80;
		break;
	}
	case SpreadingFactor_9:
	{
		config |= 0x90;
		break;
	}
	case SpreadingFactor_10:
	{
		config |= 0xa0;
		break;
	}
	case SpreadingFactor_11:
	{
		config |= 0xb0;
		break;
	}
	case SpreadingFactor_12:
	{
		config |= 0xc0;
		break;
	}
	}

	config |= 0x07;
	SX1272_WriteRegister(SX1272_MODEM_CONFIG2, config);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
SpreadingFactor SX1272_GetSpreadingFactor(void)
{
	SpreadingFactor spreadingFactor = SpreadingFactor_12;

	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG2);
	config &= 0xf0;
	switch (config)
	{
	case 0x60:
	{
		spreadingFactor = SpreadingFactor_6;
		break;
	}
	case 0x70:
	{
		spreadingFactor = SpreadingFactor_7;
		break;
	}
	case 0x80:
	{
		spreadingFactor = SpreadingFactor_8;
		break;
	}
	case 0x90:
	{
		spreadingFactor = SpreadingFactor_9;
		break;
	}
	case 0x0a:
	{
		spreadingFactor = SpreadingFactor_10;
		break;
	}
	case 0x0b:
	{
		spreadingFactor = SpreadingFactor_11;
		break;
	}
	case 0x0c:
	{
		spreadingFactor = SpreadingFactor_12;
		break;
	}
	}

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetSpreadingFactor %d\n", spreadingFactor);
#endif
	return spreadingFactor;
}

/** */
void SX1272_SetBandwidth(Bandwidth bw)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetBandwidth\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config &= 0x3f;
	switch (bw)
	{
	case Bandwidth_125:
	{
		config |= 0x00;
		break;
	}
	case Bandwidth_250:
	{
		config |= 0x40;
		break;
	}
	case Bandwidth_500:
	{
		config |= 0x80;
		break;
	}
	}

	SX1272_WriteRegister(SX1272_MODEM_CONFIG1, config);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
Bandwidth SX1272_GetBandwidth(void)
{
	Bandwidth bandwidth = Bandwidth_125;

	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config &= 0xc0;
	switch (config)
	{
	case 0x00:
	{
		bandwidth = Bandwidth_125;
		break;
	}
	case 0x40:
	{
		bandwidth = Bandwidth_250;
		break;
	}
	case 0x80:
	{
		bandwidth = Bandwidth_500;
		break;
	}
	}

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetBandwidth %d\n", bandwidth);
#endif

	return bandwidth;
}

/** */
void SX1272_SetPower(PA_Power power)
{
	if (power < Power_6dB || power > Power_16dB)
	{
		power = Power_14dB;
	}

	power = (PA_Power) (power - Power_3dB); // take off 3dB for boost + filter
	power = (PA_Power) (power | 0x80);      // turn boost on

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetPower %x\n", power);
#endif
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	SX1272_WriteRegister(SX1272_PA_CONFIG, power);
	SX1272_WriteRegister(SX1272_PA_DAC, PaDAC_HighPower);
	SX1272_WriteRegister(SX1272_OCP, OCPTrim_240mA);
	SX1272_WriteRegister(SX1272_PA_RAMP, PaRamp_40us);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
PA_Power SX1272_GetPower(void)
{
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	PA_Power power = (PA_Power) SX1272_ReadRegister(SX1272_PA_CONFIG);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetPower %x\n", power);
#endif

	power = (PA_Power) (power & ~0x80); // remove boost flag
	power = (PA_Power) (power + Power_3dB);     // add 6dB for boost + filter

	return power;
}

/** */
void SX1272_SetFrequency(uint32_t frequency)
{
#if (SX1272_DEBUG_LEVEL > 1)
    fprintf(stderr, "SX1272_SetFrequency\n");
#endif
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);

	frequency = (uint32_t) ((double) frequency / (double) SX1272_FREQ_STEP);
	SX1272_WriteRegister(SX1272_FRF_MSB, (uint8_t) ((frequency >> 16) & 0xFF));
	SX1272_WriteRegister(SX1272_FRF_MID, (uint8_t) ((frequency >> 8) & 0xFF));
	SX1272_WriteRegister(SX1272_FRF_LSB, (uint8_t) (frequency & 0xFF));
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
uint32_t SX1272_GetFrequency(void)
{
#if (SX1272_DEBUG_LEVEL > 1)
    fprintf(stderr, "SX1272_GetFrequency\n");
#endif
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);

	uint8_t msb = SX1272_ReadRegister(SX1272_FRF_MSB);
	uint8_t mid = SX1272_ReadRegister(SX1272_FRF_MID);
	uint8_t lsb = SX1272_ReadRegister(SX1272_FRF_LSB);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);

	return (uint32_t)((msb << 16 | mid << 8 | lsb) * SX1272_FREQ_STEP);
}


/** */
void SX1272_SetChannel(Channel channel)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetChannel %8.8x\n", channel);
#endif

	if ((channel != Channel_0) && (channel != Channel_1))
	{
		channel = Channel_0;
	}

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t msb = ((channel >> 16) & 0xFF); // frequency channel MSB
	uint8_t mid = ((channel >> 8) & 0xFF);  // frequency channel MIB
	uint8_t lsb = ((channel >> 0) & 0xFF);  // frequency channel LSB

	SX1272_WriteRegister(SX1272_FRF_MSB, msb);
	SX1272_WriteRegister(SX1272_FRF_MID, mid);
	SX1272_WriteRegister(SX1272_FRF_LSB, lsb);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
Channel SX1272_GetChannel(void)
{
	uint8_t msb = SX1272_ReadRegister(SX1272_FRF_MSB);
	uint8_t mid = SX1272_ReadRegister(SX1272_FRF_MID);
	uint8_t lsb = SX1272_ReadRegister(SX1272_FRF_LSB);

	Channel channel = (Channel) (msb << 16 | mid << 8 | lsb);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetChannel %8.8x\n", channel);
#endif

	return channel;
}

/** */
void SX1272_SetCRCOn(bool on)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetCRCOn\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config = on ? (config | 0x02) : (config & ~0x02);
	SX1272_WriteRegister(SX1272_MODEM_CONFIG1, config);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
bool SX1272_GetCRCOn(void)
{
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	bool crcOn = (config & 0x02);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetCRCOn %d\n", crcOn);
#endif
	return crcOn;
}

/** */
void SX1272_SetExplicitHeaderMode(bool on)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetExplicitHeaderMode\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config = on ? (config & ~0x04) : (config | 0x04);
	SX1272_WriteRegister(SX1272_MODEM_CONFIG1, config);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
bool SX1272_GetExplicitHeaderMode(void)
{
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	bool expl = !(config & 0x04);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetExplicitHeaderMode %d\n", expl);
#endif
	return expl;
}

/** */
void SX1272_SetLowDataRateOptimise(bool on)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetLowDataRateOptimise\n");
#endif

	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	config = on ? (config | 0x01) : (config & ~0x01);
	SX1272_WriteRegister(SX1272_MODEM_CONFIG1, config);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
bool SX1272_GetLowDataRateOptimise(void)
{
	uint8_t config = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
	bool optimize = (config & 0x01);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetLowDataRateOptimise %d\n", optimize);
#endif
	return optimize;
}

/** */
void SX1272_SetMode(Bandwidth bw, SpreadingFactor sf, CodingRate cr)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetMode\n");
#endif

	SX1272_SetCodingRate(cr);
	SX1272_SetSpreadingFactor(sf);
	SX1272_SetBandwidth(bw);
}

/** */
int8_t SX1272_GetTemperature(void)
{
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY | SX1272_MODE_ACCESS_SHARED);

	uint8_t temperature = SX1272_ReadRegister(SX1272_TEMPERATURE);

	// 2's complement conversion
	temperature = (temperature & 0x80) ? ((~temperature + 1) & 0xff) : (temperature & 0xff);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetTemperature reg=%2.2x\n", temperature);
#endif

	return temperature;
}

/** */
void SX1272_SetCWMode(bool on)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetCWMode %s\n", on ? "on" : "off");
#endif

	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);

	static uint8_t config1 = 0;
	static uint8_t config2 = 0;

	if (on)
	{
		config1 = SX1272_ReadRegister(SX1272_MODEM_CONFIG1);
		config2 = SX1272_ReadRegister(SX1272_MODEM_CONFIG2);
		SX1272_WriteRegister(SX1272_MODEM_CONFIG1, 0x00);
		SX1272_WriteRegister(SX1272_MODEM_CONFIG2, TxContinousModeOn);
		SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_TX);
	}
	else
	{
		if (config1 != 0)
		{
			SX1272_WriteRegister(SX1272_MODEM_CONFIG1, config1);
			SX1272_WriteRegister(SX1272_MODEM_CONFIG2, config2);
			SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
		}
	}
}

/** */
bool SX1272_GetCWMode(void)
{
	uint8_t config2 = SX1272_ReadRegister(SX1272_MODEM_CONFIG2);

	bool on = config2 & 0x08;

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetCWMode %s\n", on ? "on" : "off");
#endif

	return on;
}

/** */
uint8_t SX1272_GetVersion(void)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_Version\n");
#endif

	return SX1272_ReadRegister(SX1272_VERSION);
}

/** */
int8_t SX1272_GetPacketSNR(void)
{
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);

	uint8_t snr = SX1272_ReadRegister(SX1272_PKT_SNR_VALUE);
	snr = (snr & 0x80) ? ((~snr + 1) & 0xff) : (snr & 0xff);
	snr /= 4;
	SX1272_WriteRegister(SX1272_OP_MODE, mode);

	return snr;
}

/** */
int16_t SX1272_GetDebug(void)
{
	return 0;
}

/** */
int16_t SX1272_GetPacketRSSI(void)
{
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);

	int16_t rssi = -139 + SX1272_ReadRegister(SX1272_PACKET_RSSI);
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetPacketRssi raw rssi %d\n", rssi);
#endif

	SX1272_WriteRegister(SX1272_OP_MODE, mode);
	return rssi;
}

/** */
int16_t SX1272_GetCurrentRSSI(void)
{
	return -139 + currentRssi;
}

/** */
bool SX1272_IsChannelFree(void)
{
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);

	// unmask cad interrupts
	uint8_t irqFlags = SX1272_IRQ_FLAG_RXDONE | SX1272_IRQ_FLAG_CAD_DONE | SX1272_IRQ_FLAG_CAD_DETECTED;

	SX1272_WriteRegister(SX1272_IRQ_FLAGS_MASK, ~irqFlags);

	// clear the irq flags
	SX1272_WriteRegister(SX1272_IRQ_FLAGS, irqFlags);

	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_CAD);

	// wait for channel activity or timeout
	uint8_t flags;

	while (true)
	{
		flags = SX1272_ReadRegister(SX1272_IRQ_FLAGS);

		if ((flags & SX1272_IRQ_FLAG_CAD_DONE) == SX1272_IRQ_FLAG_CAD_DONE)
		{
			if ((flags & SX1272_IRQ_FLAG_CAD_DETECTED) == SX1272_IRQ_FLAG_CAD_DETECTED)
			{
#if (SX1272_DEBUG_LEVEL > 1)
      fprintf(stderr, "SX1272_IsChannelFree channel activity detected\n");
#endif
				return false;
			}
			return true;
		}

		SX1272_Delay(5);
	}
}

/** */
void SX1272_SetInvertIQ(bool invert)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetInvertIQ %d\n", invert);
#endif
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t invertiq = SX1272_ReadRegister(SX1272_INVERTIQ);

	if (invert)
	{
		invertiq |= 0x41;
		SX1272_WriteRegister(SX1272_INVERTIQ2, 0x19);
	}
	else
	{
		invertiq &= ~0x41;
		SX1272_WriteRegister(SX1272_INVERTIQ2, 0x1D);
	}

	SX1272_WriteRegister(SX1272_INVERTIQ, invertiq);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
bool SX1272_GetInvertIQ(void)
{
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t invert = SX1272_ReadRegister(SX1272_INVERTIQ);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetInvertIQ %d\n", invert);
#endif
	return (invert & 0x26) != 0;
}

/** */
void SX1272_SetSyncWord(uint8_t syncWord)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_SetSyncWord %d\n", syncWord);
#endif
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	SX1272_WriteRegister(SX1272_SYNC_WORD, syncWord);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);
}

/** */
uint8_t SX1272_GetSyncWord(void)
{
	uint8_t mode = SX1272_ReadRegister(SX1272_OP_MODE);
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	uint8_t syncWord = SX1272_ReadRegister(SX1272_SYNC_WORD);
	SX1272_WriteRegister(SX1272_OP_MODE, mode);

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetSyncWord %d\n", syncWord);
#endif
	return syncWord;
}

/** */
bool SX1272_Transmit(const uint8_t *buffer, size_t len)
{
#if (SX1272_DEBUG_LEVEL > 6)
  fprintf(stderr, "SX1272_Transmit [%s]\n", buffer);
#endif
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	SX1272_WriteRegister(SX1272_PAYLOAD_LENGTH_LORA, len);

	// set address pointer in FIFO data buffer
	SX1272_WriteRegister(SX1272_FIFO_ADDR_PTR, 0x0);

	// write the packet data to  FIFO
	for (uint8_t idx = 0; idx < len; idx++)
	{
		SX1272_WriteRegister(SX1272_FIFO, buffer[idx]);
	}

	// unmask tx done interrupt
	SX1272_WriteRegister(SX1272_IRQ_FLAGS_MASK, ~SX1272_IRQ_FLAG_TXDONE);
	// clear the tx done flag
	SX1272_WriteRegister(SX1272_IRQ_FLAGS, SX1272_IRQ_FLAG_TXDONE);
	// start transmit
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_TX);

	uint32_t start = SX1272_GetTick();
	uint32_t timeout = 3000;
	uint8_t flags = 0;

	while (true)
	{
		flags = SX1272_ReadRegister(SX1272_IRQ_FLAGS);

		if ((flags & SX1272_IRQ_FLAG_TXDONE) != 0)
		{
			return true;
		}

		if ((SX1272_GetTick() - start) > timeout)
		{
			return false;
		}

		SX1272_Delay(10);
	}
}

/** */
PollResult SX1272_Receive(uint8_t *buffer, size_t *len, uint16_t timeout)
{
	size_t bufferSize = *len;

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_Receive\n");
#endif
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	SX1272_WriteRegister(SX1272_LNA_GAIN, LNAGain_G1 | LNABoost_On);
	SX1272_WriteRegister(SX1272_FIFO_ADDR_PTR, 0x00);
	SX1272_WriteRegister(SX1272_PAYLOAD_LENGTH_LORA, MAX_PACKET_SIZE);

	// unmask rx interrupts
	uint8_t irqFlags = SX1272_IRQ_FLAG_RXDONE | SX1272_IRQ_FLAG_HEADER_VALID |
	SX1272_IRQ_FLAG_PAYLOAD_CRC_ERROR;
	SX1272_WriteRegister(SX1272_IRQ_FLAGS_MASK, ~irqFlags);

	// clear the irq flags
	SX1272_WriteRegister(SX1272_IRQ_FLAGS, irqFlags);
	// start reception
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_RX);

	uint32_t start = SX1272_GetTick();
	uint8_t flags = 0;

	// wait for a valid LORA header
	while (true)
	{
		flags = SX1272_ReadRegister(SX1272_IRQ_FLAGS);

		if ((flags & SX1272_IRQ_FLAG_HEADER_VALID) != 0)
		{
			break;
		}

		if ((SX1272_GetTick() - start) > timeout)
		{
			return NoPacket;
		}

		SX1272_Delay(10);
	}

	currentRssi = (int16_t) SX1272_ReadRegister(SX1272_CURRENT_RSSI);

	// wait for complete packet & check crc
	while (true)
	{
		flags = SX1272_ReadRegister(SX1272_IRQ_FLAGS);

		if ((flags & SX1272_IRQ_FLAG_PAYLOAD_CRC_ERROR) != 0)
		{
#if (SX1272_DEBUG_LEVEL > 1)
      fprintf(stderr, "SX1272_Receive crc error\n");
#endif
			return PacketError;
		}

		if ((flags & SX1272_IRQ_FLAG_RXDONE) != 0)
		{
			break;
		}

		if ((SX1272_GetTick() - start) > timeout)
		{
			return NoPacket;
		}

		SX1272_Delay(10);
	}

	size_t packetSize = SX1272_ReadRegister(SX1272_RX_NB_BYTES);

	if ((SX1272_ReadRegister(SX1272_HOP_CHANNEL) & 0x40) == 0)
	{

#if (SX1272_DEBUG_LEVEL > 1)
    fprintf(stderr, "SX1272_Receive no CRC present %d bytes\n", packetSize);
#endif
		return PacketError;
	}
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_Receive payload length %d\n", *len);
#endif

	// empty the packet buffer, copying the first *len bytes into the caller's
	// buffer
	size_t outputBytes = packetSize < bufferSize ? packetSize : bufferSize;

	size_t packetIndex;
	for (packetIndex = 0; packetIndex < outputBytes; packetIndex++)
	{
		buffer[packetIndex] = SX1272_ReadRegister(SX1272_FIFO);
	}

	for (; packetIndex < packetSize; packetIndex++)
	{
		SX1272_ReadRegister(SX1272_FIFO); // drain FIFO
	}

	*len = outputBytes;
	return PacketWaiting;
}

/** */
void SX1272_ReceiveAsyncStart(void)
{
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_ReceiveAsyncStart\n");
#endif
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_STANDBY);
	SX1272_WriteRegister(SX1272_LNA_GAIN, LNAGain_G1 | LNABoost_On);
	SX1272_WriteRegister(SX1272_FIFO_ADDR_PTR, 0x00);
	SX1272_WriteRegister(SX1272_FIFO_RX_CURRENT_ADDR, 0x00);
	SX1272_WriteRegister(SX1272_PAYLOAD_LENGTH_LORA, MAX_PACKET_SIZE);

	// unmask rx interrupts
	uint8_t irqFlags = SX1272_IRQ_FLAG_RXDONE | SX1272_IRQ_FLAG_HEADER_VALID |
	SX1272_IRQ_FLAG_PAYLOAD_CRC_ERROR;
	SX1272_WriteRegister(SX1272_IRQ_FLAGS_MASK, ~irqFlags);

	// clear the irq flags
	SX1272_WriteRegister(SX1272_IRQ_FLAGS, irqFlags);
	// start reception
	SX1272_WriteRegister(SX1272_OP_MODE, SX1272_MODE_LORA_RX);
}

/** */
PollResult SX1272_ReceiveAsyncPoll(uint8_t *buffer, size_t *len)
{
	size_t bufferSize = *len;

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_ReceiveAsyncPoll\n");
#endif

	uint8_t flags = SX1272_ReadRegister(SX1272_IRQ_FLAGS);

	if ((flags & SX1272_IRQ_FLAG_RXDONE) == 0)
	{
		return NoPacket;
	}

	SX1272_WriteRegister(SX1272_IRQ_FLAGS, SX1272_IRQ_FLAG_RXDONE);

	// check for a valid LORA header
	if ((flags & SX1272_IRQ_FLAG_HEADER_VALID) == 0)
	{
		return NoPacket;
	}

	currentRssi = (int16_t) SX1272_ReadRegister(SX1272_CURRENT_RSSI);

	// if there is no CRC present, it cannot be our packet
	if ((SX1272_ReadRegister(SX1272_HOP_CHANNEL) & 0x40) == 0)
	{

#if (SX1272_DEBUG_LEVEL > 1)
    fprintf(stderr, "SX1272_Receive no CRC present\n");
#endif
		return NoPacket;
	}
#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_Receive payload length %d\n", bufferSize);
#endif

	if ((flags & SX1272_IRQ_FLAG_PAYLOAD_CRC_ERROR) != 0)
	{
#if (SX1272_DEBUG_LEVEL > 1)
    fprintf(stderr, "SX1272_Receive crc error\n");
#endif

		SX1272_WriteRegister(SX1272_IRQ_FLAGS, SX1272_IRQ_FLAG_PAYLOAD_CRC_ERROR);

		return PacketError;
	}

	size_t packetSize = SX1272_ReadRegister(SX1272_RX_NB_BYTES);

	SX1272_WriteRegister(SX1272_FIFO_ADDR_PTR, SX1272_ReadRegister(SX1272_FIFO_RX_CURRENT_ADDR));

	// empty the packet buffer, copying the first *len bytes into the caller's buffer
	size_t outputBytes = packetSize < bufferSize ? packetSize : bufferSize;

	for (size_t packetIndex = 0; packetIndex < outputBytes; packetIndex++)
	{
		buffer[packetIndex] = SX1272_ReadRegister(SX1272_FIFO);
	}

	*len = outputBytes;
	return PacketWaiting;
}

/** */
int32_t SX1272_GetFrequencyError(void)
{
	int32_t frequencyError = 0;
	frequencyError = SX1272_ReadRegister(SX1272_FREQ_ERROR_MSB) & 0x07;
	frequencyError <<= 8L;
	frequencyError += SX1272_ReadRegister(SX1272_FREQ_ERROR_MID);
	frequencyError <<= 8L;
	frequencyError += SX1272_ReadRegister(SX1272_FREQ_ERROR_LSB);

	// set sign bit
	if (SX1272_ReadRegister(SX1272_FREQ_ERROR_MSB) & 0x08)
	{
		frequencyError -= 0x80000;
	}

	// as per datasheet multiply by 2^24 and divide by
	// xtal frequency
	return (int32_t) (frequencyError * 0.524);
}

/** */
uint16_t SX1272_GetTimeOnAir(uint8_t packetLen)
{
	// see the calculation in the SX1272 datasheet
	Bandwidth bw = SX1272_GetBandwidth();
	SpreadingFactor sf = SX1272_GetSpreadingFactor();
	CodingRate cr = SX1272_GetCodingRate();
	bool crcOn = SX1272_GetCRCOn();
	bool lowDROptimize = SX1272_GetLowDataRateOptimise();
	bool implicitHeader = !SX1272_GetExplicitHeaderMode();

	double symbolTime = pow(2, (uint32_t) sf) / bw;
	double preambleTime = symbolTime * (NUM_PREAMBLE_BYTES + 4.25);
	double num = (8 * packetLen) - (4 * sf) + 28 + (16 * crcOn) - (20 * implicitHeader);
	double dom = 4 * (sf - 2 * lowDROptimize);
	double payloadTime = (8 + ceil(num / dom) * (cr + 4)) * symbolTime;

	double timeOnAir = preambleTime + payloadTime;

#if (SX1272_DEBUG_LEVEL > 1)
  fprintf(stderr, "SX1272_GetTimeOnAir for %d bytes %dms\n", packetLen,
          (uint16_t)(timeOnAir * 1000));
#endif

	return (uint16_t) (timeOnAir * 1000);
}

/** */
uint8_t SX1272_ReadRegister(uint8_t addr)
{
	uint16_t txbuf;
	uint16_t rxbuf;

	txbuf = addr << 8;
	HAL_GPIO_WritePin(IO_SPI0_CE0_GPIO_Port, IO_SPI0_CE0_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)&txbuf, (uint8_t *)&rxbuf, 1, 10000L);
	HAL_GPIO_WritePin(IO_SPI0_CE0_GPIO_Port, IO_SPI0_CE0_Pin, GPIO_PIN_SET);

#if (SX1272_DEBUG_LEVEL > 8)
	printf("SX1272 read reg %2.2x val %2.2x\n", addr, rxbuf & 0xFF);
#endif

	return rxbuf & 0xFF;
}

/** */
void SX1272_WriteRegister(uint8_t addr, uint8_t data)
{
	uint16_t txbuf;
	uint16_t rxbuf;

	txbuf = ((addr | 0x80) << 8) | data;
	HAL_GPIO_WritePin(IO_SPI0_CE0_GPIO_Port, IO_SPI0_CE0_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)&txbuf, (uint8_t *)&rxbuf, 1, 10000L);
	HAL_GPIO_WritePin(IO_SPI0_CE0_GPIO_Port, IO_SPI0_CE0_Pin, GPIO_PIN_SET);

#if (SX1272_DEBUG_LEVEL > 8)
	printf("SX1272 write reg %2.2x val %2.2x\n", addr, data);
#endif
}

/** */
void SX1272_Delay(uint32_t delay)
{
    HAL_Delay(delay);
}

/** */
uint32_t SX1272_GetTick(void)
{
    return HAL_GetTick();
}

/** */
void SX1272_HAL_Init(void)
{
	HAL_GPIO_WritePin(IO_GPIO23_GPIO_Port, IO_GPIO23_Pin, 1);
	HAL_GPIO_WritePin(IO_GPIO24_GPIO_Port, IO_GPIO24_Pin, 1);
}

/** */
void SX1272_FlashRX(void)
{
	HAL_GPIO_WritePin(IO_GPIO23_GPIO_Port, IO_GPIO23_Pin, 0);
	HAL_Delay(10);
	HAL_GPIO_WritePin(IO_GPIO23_GPIO_Port, IO_GPIO23_Pin, 1);
}

/** */
void SX1272_FlashTX(void)
{
	HAL_GPIO_WritePin(IO_GPIO24_GPIO_Port, IO_GPIO24_Pin, 0);
	HAL_Delay(10);
	HAL_GPIO_WritePin(IO_GPIO24_GPIO_Port, IO_GPIO24_Pin, 1);
}
