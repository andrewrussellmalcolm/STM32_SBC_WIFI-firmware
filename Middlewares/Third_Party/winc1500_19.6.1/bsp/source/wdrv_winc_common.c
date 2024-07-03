/*
 * wdrv_winc_common.c
 *
 *  Created on: Jan 9, 2024
 *      Author: andrew
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "main.h"

static void wdrv_print(const char* format, ...)
{
    va_list vlist;
    va_start(vlist, format);
    fprintf(stderr, format, vlist);
    va_end(vlist);
}

typedef void (*WDRV_WINC_DEBUG_PRINT_CALLBACK)(const char*, ...);

WDRV_WINC_DEBUG_PRINT_CALLBACK pfWINCDebugPrintCb = (WDRV_WINC_DEBUG_PRINT_CALLBACK)wdrv_print;

/** */
void WDRV_MSDelay(uint32_t delay)
{
    HAL_Delay(delay);
}
