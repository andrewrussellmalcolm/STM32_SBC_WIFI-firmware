/*
 * heap.c
 *
 *  Created on: Mar 15, 2024
 *      Author: andrew
 */


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"

/**
 * Notes.
 * heap_4.c is the freertos heap allocator in use, so heap size = configTOTAL_HEAP_SIZE
 * malloc, calloc & free are reimplemented here to make sure they are thread-safe
 * freertos task stacks are allocated from this heap. The 'main' thread just starts the
 * default freertos task an so needs no stack beyond that requred to set up the hardware
 * the default thread & timer thread really do need 4K stacks!
 * */

/** */
void *malloc(size_t size)
{
    void *ptr = NULL;

    if (size > 0)
    {
        ptr = pvPortMalloc(size);
    }

    return ptr;
}

/** */
void free(void *ptr)
{
    if (ptr)
    {
        vPortFree(ptr);
    }
}
