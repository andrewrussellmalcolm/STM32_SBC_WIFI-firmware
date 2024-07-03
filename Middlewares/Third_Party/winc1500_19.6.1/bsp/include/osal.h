/*
 * osal.h
 *
 *  Created on: Jan 9, 2024
 *      Author: andrew
 */

#ifndef WINC1500_DRIVER_SOURCE_OSAL_OSAL_H_
#define WINC1500_DRIVER_SOURCE_OSAL_OSAL_H_

#include <stdint.h>
#include "cmsis_os.h"

typedef osSemaphoreId_t OSAL_SEM_HANDLE_TYPE;
typedef osMutexId_t OSAL_MUTEX_HANDLE_TYPE;
typedef uint32_t OSAL_CRITSECT_DATA_TYPE;
#define OSAL_WAIT_FOREVER           (uint16_t) 0xFFFF

typedef enum OSAL_SEM_TYPE
{
	OSAL_SEM_TYPE_BINARY, OSAL_SEM_TYPE_COUNTING
}
OSAL_SEM_TYPE;

typedef enum OSAL_CRIT_TYPE
{
	OSAL_CRIT_TYPE_LOW, OSAL_CRIT_TYPE_HIGH
}
OSAL_CRIT_TYPE;

typedef enum OSAL_RESULT
{
	OSAL_RESULT_NOT_IMPLEMENTED = -1, OSAL_RESULT_FALSE = 0, OSAL_RESULT_FAIL = 0, OSAL_RESULT_TRUE = 1, OSAL_RESULT_SUCCESS = 1,
}
OSAL_RESULT;

static inline OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE *semID, OSAL_SEM_TYPE type, uint8_t maxCount, uint8_t initialCount);
static inline OSAL_RESULT OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE *semID);
static inline OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE *semID, uint16_t waitMS);
static inline OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE *semID);
static inline OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE *semID);
static inline uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE *semID);
static inline OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE *mutexID);
static inline OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE *mutexID);
static inline OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE *mutexID, uint16_t waitMS);
static inline OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE *mutexID);

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE *semID, OSAL_SEM_TYPE type, uint8_t maxCount, uint8_t initialCount)
{
	*semID = osSemaphoreNew(maxCount, initialCount, NULL);
	return OSAL_RESULT_SUCCESS;
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE *semID)
{
	osSemaphoreDelete(semID);
	return (OSAL_RESULT_SUCCESS);
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE *semID, uint16_t waitMS)
{
	if (osSemaphoreGetCount(*semID) > 0U)
	{
		osSemaphoreAcquire(*semID, osWaitForever);
	}

	return OSAL_RESULT_SUCCESS;
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE *semID)
{
	osSemaphoreRelease(*semID);
	return OSAL_RESULT_SUCCESS;
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE *semID)
{
	osSemaphoreRelease(*semID);
	return OSAL_RESULT_SUCCESS;
}

/** */
static uint8_t __attribute__((always_inline)) OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE *semID)
{
	return osSemaphoreGetCount(*semID);
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE *mutexID)
{
	*mutexID = osMutexNew(NULL);
	return OSAL_RESULT_SUCCESS;
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE *mutexID)
{
	osMutexDelete(*mutexID);
	return (OSAL_RESULT_SUCCESS);
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE *mutexID, uint16_t waitMS)
{
	return (OSAL_RESULT_SUCCESS);
	osMutexAcquire(*mutexID, waitMS);
}

/** */
static OSAL_RESULT __attribute__((always_inline)) OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE *mutexID)
{
	osMutexRelease(*mutexID);
	return OSAL_RESULT_SUCCESS;
}

#endif /* WINC1500_DRIVER_SOURCE_OSAL_OSAL_H_ */
