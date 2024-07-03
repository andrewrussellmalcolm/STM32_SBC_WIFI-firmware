/*
 * wifi_task.c
 *
 *  Created on: Dec 31, 2023
 *      Author: andrew
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "cmsis_os.h"

#include "main.h"
#include "m2m_wifi.h"
#include "conf_winc.h"
#include "nm_bsp.h"
#include "led.h"
#include "socket.h"
#include "tcp.h"
/**
 * --- documentation ---
 * https://ww1.microchip.com/downloads/aemDocuments/documents/WSG/ProductDocuments/DataSheets/ATWINC15x0-MR210xB-IEEE-802.11-b-g-n-SmartConnect-IoT-Module-DS70005304E.pdf
 * https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42420-WINC1500-Software-Design-Guide_UserGuide.pdf
 * https://ww1.microchip.com/downloads/en/appnotes/atmel-42654-atwinc1500-weather-client-example-application_applicationnote_at15058.pdf
 * https://ww1.microchip.com/downloads/en/devicedoc/atmel-42418-software-programming-guide-for-atwinc1500-wifi-using-samd21-xplained-pro_userguide.pdf
 * https://ww1.microchip.com/downloads/en/DeviceDoc/ATWINC15x0-MR210xB-IEEE-802.11-b-g-n-SmartConnect-IoT-Module-DS70005304E.pdf
 */

const char *default_ssid = "GetOffMyLawn";
const char *default_pkey = "KkhT41rPkHp1";
const char *device_name = "STM32-SBC-WIFI";

static osEventFlagsId_t wifi_event_flags_id;
static const uint32_t wifi_interrupt_flag = 1;

static uint32_t ip_address = 0;
static uint32_t rssi = 0;

/** */
char* inet_ntoa(uint32_t ip_addr)
{
	static char ascii_addr[20];
	uint8_t bytes[4];
	bytes[0] = ip_addr & 0xFF;
	bytes[1] = (ip_addr >> 8) & 0xFF;
	bytes[2] = (ip_addr >> 16) & 0xFF;
	bytes[3] = (ip_addr >> 24) & 0xFF;
	snprintf(ascii_addr, sizeof(ascii_addr), "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
	return ascii_addr;
}

/** */
uint32_t wifi_get_ip_address(void)
{
	return ip_address;
}

/** */
uint32_t wifi_get_rssi(void)
{
	return rssi;
}

/** */
static void connect_to_ssid(const char *ssid, const char *pkey)
{
	tstrNetworkId network_id;
	tstrAuthPsk auth_psk;

	network_id.pu8Bssid = NULL;
	network_id.pu8Ssid = (uint8_t*) ssid;
	network_id.u8SsidLen = strlen(ssid);
	network_id.enuChannel = M2M_WIFI_CH_ALL;

	auth_psk.pu8Psk = NULL;
	auth_psk.pu8Passphrase = (uint8_t*) pkey;
	auth_psk.u8PassphraseLen = strlen(pkey);
	m2m_wifi_connect_psk(WIFI_CRED_DONTSAVE, &network_id, &auth_psk);
}

/* ** */
static void wifi_callback(uint8_t message_type, const void *const message)
{
	static uint8_t scan_request_index = 0;
	static uint8_t scan_request_result = 0;
	static bool ssid_found = false;

	switch (message_type)
	{
		case M2M_WIFI_RESP_SCAN_DONE:
		{
			tstrM2mScanDone *info = (tstrM2mScanDone*) message;

			scan_request_index = 0;
			if (info->u8NumofCh >= 1)
			{
				m2m_wifi_req_scan_result(scan_request_index);
				scan_request_index++;
			}
			else
			{
				m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
			}

			break;
		}

		case M2M_WIFI_RESP_SCAN_RESULT:
		{
			tstrM2mWifiscanResult *scan_result = (tstrM2mWifiscanResult*) message;
			uint16_t default_ssid_len = strlen(default_ssid);
			const char * scan_ssid = (const char*) scan_result->au8SSID;
			uint16_t scan_ssid_len = strlen(scan_ssid);

			scan_request_result = m2m_wifi_get_num_ap_found();
			if (scan_ssid_len)
			{
				if ((default_ssid_len == scan_ssid_len) && (!strncmp(default_ssid, default_ssid, default_ssid_len)))
				{
					fprintf(stderr, "AP %s found\n", scan_ssid);
					connect_to_ssid(default_ssid, default_pkey);
					ssid_found = true;
					break;
				}
			}

			if (scan_request_index < scan_request_result)
			{
				m2m_wifi_req_scan_result(scan_request_index);
				scan_request_index++;
			}
			else
			{
				if (!ssid_found)
				{
					fprintf(stderr, "cannot find AP %s\n", default_ssid);
					m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
				}
			}

			break;
		}

		case M2M_WIFI_RESP_CON_STATE_CHANGED:
		{
			tstrM2mWifiStateChanged *wifi_state = (tstrM2mWifiStateChanged*) message;
			if (wifi_state->u8CurrState == M2M_WIFI_CONNECTED)
			{
				m2m_wifi_get_connection_info();
				tcp_reset();
			}
			else if (wifi_state->u8CurrState == M2M_WIFI_DISCONNECTED)
			{
				led_set_state(LED_1, LED_OFF);
				ssid_found = false;
				m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
			}

			break;
		}

		case M2M_WIFI_RESP_CONN_INFO:
		{
			tstrM2MConnInfo *connection_info = (tstrM2MConnInfo*) message;
			rssi = connection_info->s8RSSI;
			break;
		}

		case M2M_WIFI_REQ_DHCP_CONF:
		{
			ip_address = ((tstrM2MIPConfig*) message)->u32StaticIP;
			led_set_state(LED_1, LED_ON);
			fprintf(stderr, "ip address = %s\n", inet_ntoa(ip_address));
			break;
		}

		default:
		{
			break;
		}
	}
}

/** */
void wifi_init(void)
{
	tstrWifiInitParam param;
	int8_t ret;

	memset((uint8_t*) &param, 0, sizeof(tstrWifiInitParam));
	param.pfAppWifiCb = wifi_callback;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret)
	{
		fprintf(stderr, "main: m2m_wifi_init call error!(%d)\r\n", ret);
	}

	m2m_wifi_set_device_name((uint8_t*) device_name, strlen(device_name));
	m2m_wifi_request_scan(M2M_WIFI_CH_ALL);
	socketInit();
	tcp_init();
}

/** */
void wifi_interrupt_pending(void)
{
	osEventFlagsSet(wifi_event_flags_id, wifi_interrupt_flag);
}

/** */
void wifi_task(void)
{
	wifi_event_flags_id = osEventFlagsNew(NULL);

	while (true)
	{
		osEventFlagsWait(wifi_event_flags_id, wifi_interrupt_flag, osFlagsWaitAny, osWaitForever);
		m2m_wifi_handle_events();
	}
}
