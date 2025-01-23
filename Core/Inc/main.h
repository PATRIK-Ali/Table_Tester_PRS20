/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h5xx_ll_dma.h"
#include "stm32h5xx_ll_lpuart.h"
#include "stm32h5xx_ll_rcc.h"
#include "stm32h5xx_ll_pwr.h"
#include "stm32h5xx_ll_crs.h"
#include "stm32h5xx_ll_bus.h"
#include "stm32h5xx_ll_system.h"
#include "stm32h5xx_ll_exti.h"
#include "stm32h5xx_ll_cortex.h"
#include "stm32h5xx_ll_utils.h"
#include "stm32h5xx_ll_spi.h"
#include "stm32h5xx_ll_usart.h"
#include "stm32h5xx_ll_gpio.h"
#include "stm32h5xx_ll_crc.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "xpt2046.h"
#include "RS485.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint16_t General_Buffer[76800];
extern uint8_t LineX_RX_Buffer[1000];
extern uint8_t Line1_RX_Buffer[100];
extern uint8_t Line2_RX_Buffer[100];
extern uint8_t Line3_RX_Buffer[100];
extern uint8_t Line4_RX_Buffer[100];
extern uint8_t Line5_RX_Buffer[100];
extern uint8_t Line6_RX_Buffer[100];
extern uint8_t Line7_RX_Buffer[100];
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI_TFT_CS_Pin LL_GPIO_PIN_14
#define SPI_TFT_CS_GPIO_Port GPIOC
#define TFT_RS_Pin LL_GPIO_PIN_0
#define TFT_RS_GPIO_Port GPIOC
#define Touch_CS_Pin LL_GPIO_PIN_1
#define Touch_CS_GPIO_Port GPIOC
#define Touch_IRQ_Pin LL_GPIO_PIN_2
#define Touch_IRQ_GPIO_Port GPIOC
#define UART11_TX_RS485_6_Pin LL_GPIO_PIN_6
#define UART11_TX_RS485_6_GPIO_Port GPIOA
#define UART11_RX_RS485_6_Pin LL_GPIO_PIN_7
#define UART11_RX_RS485_6_GPIO_Port GPIOA
#define RS485_1_DE_Pin LL_GPIO_PIN_0
#define RS485_1_DE_GPIO_Port GPIOB
#define RS485_6_DE_Pin LL_GPIO_PIN_1
#define RS485_6_DE_GPIO_Port GPIOB
#define RS485_7_DE_Pin LL_GPIO_PIN_2
#define RS485_7_DE_GPIO_Port GPIOB
#define UART3_TX_RS485_1_Pin LL_GPIO_PIN_10
#define UART3_TX_RS485_1_GPIO_Port GPIOB
#define UART3_RX_RS485_1_Pin LL_GPIO_PIN_11
#define UART3_RX_RS485_1_GPIO_Port GPIOB
#define UART5_RX_RS485_2_Pin LL_GPIO_PIN_12
#define UART5_RX_RS485_2_GPIO_Port GPIOB
#define UART5_TX_RS485_2_Pin LL_GPIO_PIN_13
#define UART5_TX_RS485_2_GPIO_Port GPIOB
#define RS485_3_DE_Pin LL_GPIO_PIN_14
#define RS485_3_DE_GPIO_Port GPIOB
#define RS485_4_DE_Pin LL_GPIO_PIN_15
#define RS485_4_DE_GPIO_Port GPIOB
#define UART4_RX_RS485_3_Pin LL_GPIO_PIN_11
#define UART4_RX_RS485_3_GPIO_Port GPIOD
#define UART4_TX_RS485_3_Pin LL_GPIO_PIN_12
#define UART4_TX_RS485_3_GPIO_Port GPIOD
#define UART6_TX_RS485_4_Pin LL_GPIO_PIN_6
#define UART6_TX_RS485_4_GPIO_Port GPIOC
#define UART6_RX_RS485_4_Pin LL_GPIO_PIN_7
#define UART6_RX_RS485_4_GPIO_Port GPIOC
#define RS485_2_DE_Pin LL_GPIO_PIN_8
#define RS485_2_DE_GPIO_Port GPIOC
#define RS485_5_DE_Pin LL_GPIO_PIN_9
#define RS485_5_DE_GPIO_Port GPIOC
#define UART7_RX_RS485_7_Pin LL_GPIO_PIN_8
#define UART7_RX_RS485_7_GPIO_Port GPIOA
#define LPUART1_TX_RS485_5_Pin LL_GPIO_PIN_9
#define LPUART1_TX_RS485_5_GPIO_Port GPIOA
#define LPUART1_RX_RS485_5_Pin LL_GPIO_PIN_10
#define LPUART1_RX_RS485_5_GPIO_Port GPIOA
#define UART7_TX_RS485_7_Pin LL_GPIO_PIN_15
#define UART7_TX_RS485_7_GPIO_Port GPIOA
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
