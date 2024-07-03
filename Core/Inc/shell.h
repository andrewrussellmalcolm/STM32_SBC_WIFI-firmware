/*
 * shell.h
 *
 *  Created on: 25 Nov 2021
 *      Author: andrew
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_

#include <stdint.h>
#include <stdbool.h>
bool kbhit(void);
void shell_init(void);
bool shell_process_key(char ch);
bool shell_arg_is(const char *name, const char *arg, uint8_t length);
const char* shell_get_parameter( const char *command_string, uint8_t wanted_parameter, uint8_t *parameter_string_length);
void shell_print_array(uint32_t addr, uint8_t data[], uint16_t len);
void shell_display_alert(char *message);

void shell_wifi_command(const char *command_string);
void shell_lora_command(const char *commandString);
void shell_sys_command(const char *command_string);
void shell_sensor_command(const char *command_string);
void shell_clock_command(const char *command_string);
void shell_led_command(const char *command_string);
void shell_serial_command(const char *commandString);
void shell_nfc_command(const char *commandString);
void shell_tcp_command(const char *command_string);
void shell_flash_command(const char *command_string);

void shell_fsinfo_command(const char *command_string);
void shell_fstest_command(const char *command_string);
void shell_format_command(const char *command_string);
void shell_ls_command(const char *command_string);
void shell_tree_command(const char *command_string);
void shell_rm_command(const char *command_string);
void shell_cp_command(const char *command_string);
void shell_mv_command(const char *command_string);
void shell_cat_command(const char *command_string);
void shell_mkdir_command(const char *command_string);
void shell_rmdir_command(const char *command_string);

void shell_reboot_command(const char *command_string);
void shell_uptime_command(const char *command_string);
void shell_meminfo_command(const char *command_string);
void shell_random_command(const char *command_string);
void shell_bbregisters_command(const char *command_string);
void shell_bbmemory_command(const char *command_string);
void shell_battery_command(const char *command_string);

void shell_gpio_command(const char *command_string);
void shell_timer_command(const char *command_string);

#endif /* INC_SHELL_H_ */
