/*
 * tcp.h
 *
 *  Created on: Jan 29, 2024
 *      Author: andrew
 */

#ifndef INC_TCP_H_
#define INC_TCP_H_

void tcp_reset(void);
void tcp_init(void);
bool tcp_echo_client(uint32_t dest, uint32_t port);
void tcp_echo_server(void);
bool tcp_bind(SOCKET server_socket, struct sockaddr * addr);
bool tcp_listen(SOCKET server_socket);
SOCKET tcp_accept(SOCKET server_socket);
bool tcp_recv(SOCKET client_socket, uint8_t *buffer, uint16_t *length);
bool tcp_send(SOCKET socket, uint8_t *buffer, uint16_t length);
bool tcp_connect(SOCKET client_socket, struct sockaddr * addr);
uint32_t tcp_resolve(const char * hostname);
#endif /* INC_TCP_H_ */
