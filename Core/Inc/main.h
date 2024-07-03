/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;

extern RTC_HandleTypeDef hrtc;

extern RNG_HandleTypeDef hrng;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;

extern UART_HandleTypeDef huart4;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

extern osThreadId_t main_taskHandle;
extern osThreadId_t wifi_taskHandle;
extern osThreadId_t lora_taskHandle;
extern const osThreadAttr_t main_task_attributes;
extern const osThreadAttr_t wifi_task_attributes;
extern const osThreadAttr_t lora_task_attributes;

extern uint8_t usb_char_waiting(void);
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define CLS "\x1B[2J"
#define CLL "\x1B[2K"
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define DEFAULT_HOST "192.168.1.10"
#define DEFAULT_PORT 4040

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LOCAL_I2C_INT_Pin GPIO_PIN_13
#define LOCAL_I2C_INT_GPIO_Port GPIOC
#define LOCAL_I2C_INT_EXTI_IRQn EXTI15_10_IRQn
#define WIFI_RSTN_Pin GPIO_PIN_0
#define WIFI_RSTN_GPIO_Port GPIOC
#define FLASH_NSS_Pin GPIO_PIN_1
#define FLASH_NSS_GPIO_Port GPIOC
#define FLASH_MISO_Pin GPIO_PIN_2
#define FLASH_MISO_GPIO_Port GPIOC
#define FLASH_MOSI_Pin GPIO_PIN_3
#define FLASH_MOSI_GPIO_Port GPIOC
#define IO_UART_TX_Pin GPIO_PIN_0
#define IO_UART_TX_GPIO_Port GPIOA
#define IO_UART_RX_Pin GPIO_PIN_1
#define IO_UART_RX_GPIO_Port GPIOA
#define IO_GPIO26_Pin GPIO_PIN_2
#define IO_GPIO26_GPIO_Port GPIOA
#define WIFI_INT_Pin GPIO_PIN_3
#define WIFI_INT_GPIO_Port GPIOA
#define WIFI_INT_EXTI_IRQn EXTI3_IRQn
#define IO_GPIO22_Pin GPIO_PIN_4
#define IO_GPIO22_GPIO_Port GPIOA
#define IO_SPI0_SCK_Pin GPIO_PIN_5
#define IO_SPI0_SCK_GPIO_Port GPIOA
#define IO_SPI0_MISO_Pin GPIO_PIN_6
#define IO_SPI0_MISO_GPIO_Port GPIOA
#define IO_SPI0_MOSI_Pin GPIO_PIN_7
#define IO_SPI0_MOSI_GPIO_Port GPIOA
#define IO_GPIO27_Pin GPIO_PIN_4
#define IO_GPIO27_GPIO_Port GPIOC
#define IO_GPIO24_Pin GPIO_PIN_5
#define IO_GPIO24_GPIO_Port GPIOC
#define IO_SPI1_CE0_Pin GPIO_PIN_0
#define IO_SPI1_CE0_GPIO_Port GPIOB
#define IO_SPI1_CE1_Pin GPIO_PIN_1
#define IO_SPI1_CE1_GPIO_Port GPIOB
#define IO_SPI1_CE2_Pin GPIO_PIN_2
#define IO_SPI1_CE2_GPIO_Port GPIOB
#define IO_I2C1_SCL_Pin GPIO_PIN_10
#define IO_I2C1_SCL_GPIO_Port GPIOB
#define IO_I2C1_SDA_Pin GPIO_PIN_11
#define IO_I2C1_SDA_GPIO_Port GPIOB
#define IO_GPIO23_Pin GPIO_PIN_12
#define IO_GPIO23_GPIO_Port GPIOB
#define FLASH_SCK_Pin GPIO_PIN_13
#define FLASH_SCK_GPIO_Port GPIOB
#define IO_PWM0_Pin GPIO_PIN_14
#define IO_PWM0_GPIO_Port GPIOB
#define IO_PWM1_Pin GPIO_PIN_15
#define IO_PWM1_GPIO_Port GPIOB
#define LED0_Pin GPIO_PIN_6
#define LED0_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOC
#define IO_SPI0_CE0_Pin GPIO_PIN_8
#define IO_SPI0_CE0_GPIO_Port GPIOC
#define LOCAL_SDA_Pin GPIO_PIN_9
#define LOCAL_SDA_GPIO_Port GPIOC
#define LOCAL_SCL_Pin GPIO_PIN_8
#define LOCAL_SCL_GPIO_Port GPIOA
#define IO_SPI0_CE1_Pin GPIO_PIN_9
#define IO_SPI0_CE1_GPIO_Port GPIOA
#define IO_GPCLK1_Pin GPIO_PIN_10
#define IO_GPCLK1_GPIO_Port GPIOA
#define IO_GPCLK2_Pin GPIO_PIN_15
#define IO_GPCLK2_GPIO_Port GPIOA
#define WIFI_SCK_Pin GPIO_PIN_10
#define WIFI_SCK_GPIO_Port GPIOC
#define WIFI_MISO_Pin GPIO_PIN_11
#define WIFI_MISO_GPIO_Port GPIOC
#define WIFI_WAKE_Pin GPIO_PIN_12
#define WIFI_WAKE_GPIO_Port GPIOC
#define WIFI_CEN_Pin GPIO_PIN_2
#define WIFI_CEN_GPIO_Port GPIOD
#define WIFI_NSS_Pin GPIO_PIN_4
#define WIFI_NSS_GPIO_Port GPIOB
#define WIFI_MOSI_Pin GPIO_PIN_5
#define WIFI_MOSI_GPIO_Port GPIOB
#define IO_I2C0_SCL_Pin GPIO_PIN_6
#define IO_I2C0_SCL_GPIO_Port GPIOB
#define IO_I2C0_SDA_Pin GPIO_PIN_7
#define IO_I2C0_SDA_GPIO_Port GPIOB
#define IO_GPIO25_Pin GPIO_PIN_8
#define IO_GPIO25_GPIO_Port GPIOB
#define IO_GPIO04_Pin GPIO_PIN_9
#define IO_GPIO04_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
