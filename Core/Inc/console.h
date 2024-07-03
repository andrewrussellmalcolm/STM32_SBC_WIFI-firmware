/*
 * console.h
 *
 *  Created on: 25 Nov 2021
 *      Author: andrew
 */

#ifndef INC_CONSOLE_H_
#define INC_CONSOLE_H_

void console_init(void);
bool console_process_key(char ch);
bool console_arg_is(const char *name, const char *arg, uint8_t length);
const char* console_get_parameter( const char *command_string, uint8_t wanted_parameter, uint8_t *parameter_string_length);
void console_print_array(uint32_t addr, uint8_t data[], uint16_t len);
void console_display_alert(char *message);

void console_wifi_command(const char *command_string);
void console_fs_command(const char *command_string);
void console_lora_command(const char *commandString);
void console_sys_command(const char *command_string);
void console_sensor_command(const char *command_string);
void console_clock_command(const char *command_string);
void console_led_command(const char *command_string);
void console_serial_command(const char *commandString);
void console_nfc_command(const char *commandString);
void console_tcp_command(const char *command_string);
#endif /* INC_CONSOLE_H_ */
