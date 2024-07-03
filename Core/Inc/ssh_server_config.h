/* ssh_server_config.h
 *
 * Copyright (C) 2014-2022 wolfSSL Inc.
 *
 * This file is part of wolfSSH.
 *
 * wolfSSH is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * wolfSSH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with wolfSSH.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#undef  SO_REUSEPORT

/*
 * Time server settings.
 *
 * Accurate time is often important in cryptographic key exchange.
 *
 * see https://tf.nist.gov/tf-cgi/servers.cgi
 */
#define NTP_SERVER_LIST ( (char*[]) {        \
                                     "pool.ntp.org",         \
                                     "time.nist.gov",        \
                                     "utcnist.colorado.edu"  \
                                     }                       \
                        )


#define TIME_ZONE "PST-8"

#define WFD_SET_TYPE fd_set
#define WFD_SET FD_SET
#define WFD_ZERO FD_ZERO
#define WFD_ISSET FD_ISSET

#define HIGHWATER_MARK 0x3FFF8000 /* 1GB - 32kB */

#define SCRATCH_BUFFER_SIZE 256


/* NELEMS(x) number of elements
 * To determine the number of elements in the array, we can divide the total size of
 * the array by the size of the array element
 * See https://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c
 **/
#define NELEMS(x)  ( (int)(sizeof(x) / sizeof((x)[0])) )

/* #define NTP_SERVER_COUNT  (int)(sizeof(NTP_SERVER_LIST) / sizeof(NTP_SERVER_LIST[0])) */
#define NTP_SERVER_COUNT NELEMS(NTP_SERVER_LIST)

/* our NTP server list is global info */
extern char* ntpServerList[NTP_SERVER_COUNT];

