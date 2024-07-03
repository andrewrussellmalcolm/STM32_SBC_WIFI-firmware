/*
 * debug.c
 *
 *  Created on: Jan 18, 2024
 *      Author: andrew
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <fs.h>
#include "main.h"

/** */
time_t utc_timestamp(void)
{
	RTC_DateTypeDef  sDate;
	RTC_TimeTypeDef sTime;
	struct tm time_str;
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    time_str.tm_year = sDate.Year + 100; // RTC year is in range 0 - 99, e.g. 24
    time_str.tm_mon = sDate.Month - 1;   // so 24 + 100 + 1900 = 2024
    time_str.tm_mday = sDate.Date;
    time_str.tm_hour = sTime.Hours;
    time_str.tm_min = sTime.Minutes;
    time_str.tm_sec = sTime.Seconds;

    return mktime(&time_str);
}

/** */
void print_log(char *format, ...)
{
	char buffer[64];
	va_list aptr;
	va_start(aptr, format);
	int length = vsnprintf(buffer, sizeof(buffer), format, aptr);
	va_end(aptr);

	append_to_current_file(buffer, length);
}
