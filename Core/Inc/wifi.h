/*
 * wifi.h
 *
 *  Created on: Dec 31, 2023
 *      Author: andrew
 */

#ifndef INC_WIFI_H_
#define INC_WIFI_H_

#include <stdbool.h>

void wifi_init(void);
void wifi_process_events(void);
void wifi_interrupt_pending(void);
uint32_t wifi_get_ip_address(void);
uint32_t wifi_get_rssi(void);
char * inet_ntoa(uint32_t ip_addr);

bool wifi_transact(uint32_t dest, uint32_t port, uint8_t *send_buffer, uint32_t send_length, uint8_t *recv_buffer, uint32_t* recv_length);
#endif /* INC_WIFI_H_ */
