/*
 * shell.c
 *
 *  Created on: 25 Nov 2021
 *      Author: andrew
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"
#include "shell.h"

typedef void (*pf_command)(const char *command_string);

#define LINE_LENGTH 60
#define HISTORY_DEPTH 5
static char input[LINE_LENGTH];
static char input_history[HISTORY_DEPTH][LINE_LENGTH];
static int8_t history_index = 0;
static uint32_t inputIndex = 0;

typedef struct _command
{
	const char * const command;
	const char * const help_string;
	const pf_command command_interpreter;
}
command_t;

// forward references
static void shell_help_command(const char *command_string);
static void shell_example_command(const char *command_string);
static void shell_history_command(const char *command_string);

/** list of commands */
static command_t commands[] =
{
    {"help", "help on commands", shell_help_command},
	{"clock", "clock get | set [HH:MM:SS DD/MM/YY] set or get the clock", shell_clock_command},
    {"fsinfo", "info on file system", shell_fsinfo_command},
    {"fstest", "test the file system", shell_fstest_command},
    {"format", "format the file system", shell_format_command},
    {"ls", "list files", shell_ls_command},
    {"tree", "print a tree of the file system", shell_tree_command},
    {"rm", "remove a named file", shell_rm_command},
    {"cp", "copy a named file to another named file", shell_cp_command},
    {"mkdir", "remove a named file", shell_mkdir_command},
    {"rmdir", "remove a named file", shell_rmdir_command},
    {"cat", "print a named file [binary] as option", shell_cat_command},

	{"uptime", "display time since last reboot",shell_uptime_command},
	{"reboot", "reboot the system",shell_reboot_command},
	{"meminfo", "info on stacks and heaps",shell_meminfo_command},
	{"random", "generate a random number from hardware",shell_random_command},
	{"bbregisters", "display the mcu battery backed registers",shell_bbregisters_command},
	{"bbmemory", "read|clear: operations on battery backed memory",shell_bbmemory_command},
	{"battery", "backup battery voltage",shell_battery_command},
	{"gpio", "4|22-27 on|off",shell_gpio_command},
	{"timer", "set|get on|off [0..23] ",shell_timer_command},

	{"wifi", "ip|reset|host|chipid|echo|ping", shell_wifi_command},
	{"tcp", "client|server|ssl|ssh", shell_tcp_command},
	{"lora", "lora radio utilities", shell_lora_command },
	{"sensor", "id|temperature", shell_sensor_command },
	{"led", "led 0|1 on|off : turn LEDs on and off", shell_led_command },
	{"flash", "reset|id|config|status|erase_sector|test_page|test_device|write_page|write_byte|erase_chip|unlock [address]", shell_flash_command },
	{"serial", "loopback", shell_serial_command},
	{"nfc", "nfc uid|memory_size|mbox|write_mbox|read|write|read_rfsecurity : read info from the nfc chip", shell_nfc_command},
	{"example", "", shell_example_command},
	{"history", "linux-like command history", shell_history_command},
};

/** */
static void shell_help_command(const char *command_string)
{
	for(int idx = 0; idx < sizeof(commands)/sizeof(command_t); idx++)
	{
		printf("%s: %s\n", commands[idx].command, commands[idx].help_string);
	}
}

/** */
void shell_example_command(const char *command_string)
{
    uint8_t arg1_len;
    uint8_t arg2_len;
    const char *arg1 = shell_get_parameter(command_string, 1, &arg1_len);
    const char *arg2 = shell_get_parameter(command_string, 2, &arg2_len);

    if (shell_arg_is("get", arg1, arg1_len))
    {
    }
    else if (shell_arg_is("set", arg1, arg1_len))
    {
        if (arg2)
        {
        }
        else
        {
            printf("missing argument");
        }
    }
    else
    {
        printf("incorrect argument\n");
    }
}

/** */
void shell_display_alert(char *message)
{
	printf("\x1B[s");
	printf("\x1B[1;1H");
	printf("\x1B[5m");
	printf("\x1B[41m");
	printf("* ");

	if(message)
	{
		printf(message);
	}
	else
	{
		printf("ALERT");
	}
	printf(" *");
	printf("\x1B[0m");
	printf("\x1B[u");
}

/** */
static void put_history(char *input)
{
    strcpy(input_history[history_index], input);

    if (++history_index == HISTORY_DEPTH)
    {
        history_index = 0;
    }
}

/** */
static void get_history(char *input, bool reset)
{
    static int8_t index = 0;
    if (reset)
    {
        index = history_index -1;

        if (index < 0)
        {
            index = HISTORY_DEPTH;
        }
        return;
    }

    strcpy(input, input_history[index]);

    if (--index < 0)
    {
        index = HISTORY_DEPTH;
    }
}

/** */
static void shell_history_command(const char *command_string)
{
    (void)command_string;

    for (uint8_t i = 0; i < HISTORY_DEPTH; i++)
    {
        printf("%d %s\n", i + 1, input_history[i]);
    }
}

/** */
void shell_print_array(uint32_t addr, uint8_t data[], uint16_t len)
{
    uint8_t str[17];

    for (int i = 0; i < len; i += 16)
    {
        uint16_t bytes_per_line = 16;

        if ((len - i) < 16)
        {
            bytes_per_line = len - i;
        }

        for (int j = 0; j < bytes_per_line; j++)
        {
            uint8_t ch = data[i + j];
            if (ch >= 0x20 && ch < 0x7f)
            {
                str[j] = ch;
            }
            else
            {
                str[j] = '.';
            }
        }

        str[bytes_per_line] = '\0';

        printf("%8.8lx  ", addr + i);
        for (int j = 0; j < bytes_per_line; j++)
        {
            printf("%2.2x ", data[i + j]);
        }

        printf("|%s|\n", str);
    }
}

/** */
bool shell_arg_is(const char *name, const char *arg, uint8_t arg_len)
{
    return arg != NULL && arg_len == strlen(name) && strncmp(name, arg, arg_len) == 0;
}

/** */
const char* shell_get_parameter( const char *command_string, uint8_t wanted_parameter, uint8_t *parameter_string_length)
{
	uint8_t parameters_found = 0;
	const char *return_parameter = NULL;

	*parameter_string_length = 0;

	while(parameters_found < wanted_parameter)
	{
		/* Index the character pointer past the current word.  If this is the start
		of the command string then the first word is the command itself. */
		while( ( ( *command_string ) != 0x00 ) && ( ( *command_string ) != ' ' ) )
		{
			command_string++;
		}

		/* Find the start of the next string. */
		while( ( ( *command_string ) != 0x00 ) && ( ( *command_string ) == ' ' ) )
		{
			command_string++;
		}

		/* Was a string found? */
		if( *command_string != 0x00 )
		{
			/* Is this the start of the required parameter? */
			parameters_found++;

			if( parameters_found == wanted_parameter )
			{
				/* How long is the parameter? */
				return_parameter = command_string;
				while( ( ( *command_string ) != 0x00 ) && ( ( *command_string ) != ' ' ) )
				{
					( *parameter_string_length )++;
					command_string++;
				}

				if( *parameter_string_length == 0 )
				{
					return_parameter = NULL;
				}

				break;
			}
		}
		else
		{
			break;
		}
	}

	return return_parameter;
}

/** */
static void process_command(const char * const input)
{
	for(int idx = 0; idx < sizeof(commands)/sizeof(command_t); idx++)
	{
		char command[32];
		memset(command, 0, sizeof(command));

		for (int i = 0; i < sizeof(command); i++)
		{
			if(input[i] == '\0' || input[i] == ' ')
			{
				break;
			}
			command[i] = input[i];
		}
		if(strncmp( commands[idx].command, command, strlen(command)) == 0)
		{
			commands[idx].command_interpreter(input);
			return;
		}
	}

	printf("unrecognised command %s\n", input);
}

/** */
bool shell_process_key(char ch)
{
	if(ch == 0xff)
	{
		return false;
	}

	// look for up arrow key
	if (ch == 0x1b)
	{
		char ch1 = getchar();
		char ch2 = getchar();

		if(ch1 == 0x5b)
		{
			if(ch2 == 0x41) // uparrow
			{
				printf(CLL);
				get_history(input, false);
				inputIndex = strlen(input);
				printf("\r$ %s", input);
			}
			if(ch2 == 0x44) // backarrow
			{
				ch = 0x7f; // translate to 'backspace'
			}
			else
			{
				//fprintf(stderr, "%2.2x %2.2x\n", ch1, ch2);
			}
		}
	}
	else if((ch == 3) || (ch == 4)) // ctrl-D, ctrl-C
	{
		inputIndex = 0;
		memset(input, 0x00, sizeof(input));
		return false;
	}
	else
	{
		putchar(ch);
	}

	if (ch == '\r')
	{
		printf("\n");

		if (inputIndex == 0)
		{
			printf("$ ");
		}
		else
		{
			if (strcmp(input, "exit") == 0)
			{
				inputIndex = 0;
				memset(input, 0x00, sizeof(input));
				return false;
			}

			process_command(input);

			if (strcmp(input, "history") != 0)
			{
				put_history(input);
			}

			get_history(NULL, true);

			inputIndex = 0;
			memset(input, 0x00, sizeof(input));
			printf("\n$ ");
		}
	}
	else
	{
		if (ch == '\n')
		{
			// ignore newline
		}
		else if ((ch == '\b') || ch == 0x7f)
		{
			// process backspace
			if (inputIndex > 0)
			{
				inputIndex--;
				input[inputIndex] = '\0';
			}

			printf(CLL "\r$ %s", input);
		}
		else if (ch >= ' ' && ch <= '~')
		{
			// save printable characters
			if (inputIndex < sizeof(input))
			{
				input[inputIndex] = ch;
				inputIndex++;
			}
		}
	}

	return true;
}
