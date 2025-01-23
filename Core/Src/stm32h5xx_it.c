/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h5xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h5xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32H5xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h5xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles GPDMA1 Channel 0 global interrupt.
  */
void GPDMA1_Channel0_IRQHandler(void)
{
  /* USER CODE BEGIN GPDMA1_Channel0_IRQn 0 */
	//LL_DMA_IsActiveFlag_TC(GPDMA1, LL_DMA_CHANNEL_0)

	LL_DMA_DisableIT_TC(Line1_DMA, Line1_DMA_CH);
	LL_DMA_SuspendChannel(Line1_DMA, Line1_DMA_CH);
		//LL_DMA_IsActiveFlag_SUSP(const DMA_TypeDef *DMAx, uint32_t Channel)
		//LL_DMA_EnableChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
		LL_DMA_DisableChannel(Line1_DMA, Line1_DMA_CH);
		//LL_DMA_IsEnabledChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
		LL_DMA_ClearFlag_HT(Line1_DMA, Line1_DMA_CH);
		LL_DMA_ClearFlag_TC(Line1_DMA, Line1_DMA_CH);
		LL_DMA_ClearFlag_SUSP(Line1_DMA, Line1_DMA_CH);
		//LL_DMA_ResetChannel(GPDMA1, LL_DMA_CHANNEL_0);
		//LL_DMA_SuspendChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
		//LL_DMA_IsSuspendedChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
		//LL_DMA_ResumeChannel(const DMA_TypeDef *DMAx, uint32_t Channel)
		LL_DMA_SetDestAddress(Line1_DMA, Line1_DMA_CH, &LineX_RX_Buffer[Line1_BUF_Index]);
		LL_DMA_SetBlkDataLength(Line1_DMA, Line1_DMA_CH, Line_BUF_Size);
		//LL_DMA_GetBlkDataLength(const DMA_TypeDef *DMAx, uint32_t Channel)

		LL_DMA_EnableIT_TC(Line1_DMA, Line1_DMA_CH);
		LL_DMA_EnableChannel(Line1_DMA, Line1_DMA_CH);

  /* USER CODE END GPDMA1_Channel0_IRQn 0 */

  /* USER CODE BEGIN GPDMA1_Channel0_IRQn 1 */

  /* USER CODE END GPDMA1_Channel0_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void GPDMA1_Channel1_IRQHandler(void)
{

	LL_DMA_DisableIT_TC(Line2_DMA, Line2_DMA_CH);
	LL_DMA_SuspendChannel(Line2_DMA, Line2_DMA_CH);
	LL_DMA_DisableChannel(Line2_DMA, Line2_DMA_CH);

	LL_DMA_ClearFlag_HT(Line2_DMA, Line2_DMA_CH);
	LL_DMA_ClearFlag_TC(Line2_DMA, Line2_DMA_CH);
	LL_DMA_ClearFlag_SUSP(Line2_DMA, Line2_DMA_CH);

	LL_DMA_SetDestAddress(Line2_DMA, Line2_DMA_CH, &LineX_RX_Buffer[Line2_BUF_Index]);
	LL_DMA_SetBlkDataLength(Line2_DMA, Line2_DMA_CH, Line_BUF_Size);

	LL_DMA_EnableIT_TC(Line2_DMA, Line2_DMA_CH);
	LL_DMA_EnableChannel(Line2_DMA, Line2_DMA_CH);
}

void GPDMA1_Channel2_IRQHandler(void)
{

	LL_DMA_DisableIT_TC(Line3_DMA, Line3_DMA_CH);
	LL_DMA_SuspendChannel(Line3_DMA, Line3_DMA_CH);
	LL_DMA_DisableChannel(Line3_DMA, Line3_DMA_CH);

	LL_DMA_ClearFlag_HT(Line3_DMA, Line3_DMA_CH);
	LL_DMA_ClearFlag_TC(Line3_DMA, Line3_DMA_CH);
	LL_DMA_ClearFlag_SUSP(Line3_DMA, Line3_DMA_CH);

	LL_DMA_SetDestAddress(Line3_DMA, Line3_DMA_CH, &LineX_RX_Buffer[Line3_BUF_Index]);
	LL_DMA_SetBlkDataLength(Line3_DMA, Line3_DMA_CH, Line_BUF_Size);

	LL_DMA_EnableIT_TC(Line3_DMA, Line3_DMA_CH);
	LL_DMA_EnableChannel(Line3_DMA, Line3_DMA_CH);
}

void GPDMA1_Channel3_IRQHandler(void)
{

	LL_DMA_DisableIT_TC(Line4_DMA, Line4_DMA_CH);
	LL_DMA_SuspendChannel(Line4_DMA, Line4_DMA_CH);
	LL_DMA_DisableChannel(Line4_DMA, Line4_DMA_CH);

	LL_DMA_ClearFlag_HT(Line4_DMA, Line4_DMA_CH);
	LL_DMA_ClearFlag_TC(Line4_DMA, Line4_DMA_CH);
	LL_DMA_ClearFlag_SUSP(Line4_DMA, Line4_DMA_CH);

	LL_DMA_SetDestAddress(Line4_DMA, Line4_DMA_CH, &LineX_RX_Buffer[Line4_BUF_Index]);
	LL_DMA_SetBlkDataLength(Line4_DMA, Line4_DMA_CH, Line_BUF_Size);

	LL_DMA_EnableIT_TC(Line4_DMA, Line4_DMA_CH);
	LL_DMA_EnableChannel(Line4_DMA, Line4_DMA_CH);
}

void GPDMA1_Channel4_IRQHandler(void)
{

	LL_DMA_DisableIT_TC(Line5_DMA, Line5_DMA_CH);
	LL_DMA_SuspendChannel(Line5_DMA, Line5_DMA_CH);
	LL_DMA_DisableChannel(Line5_DMA, Line5_DMA_CH);

	LL_DMA_ClearFlag_HT(Line5_DMA, Line5_DMA_CH);
	LL_DMA_ClearFlag_TC(Line5_DMA, Line5_DMA_CH);
	LL_DMA_ClearFlag_SUSP(Line5_DMA, Line5_DMA_CH);

	LL_DMA_SetDestAddress(Line5_DMA, Line5_DMA_CH, &LineX_RX_Buffer[Line5_BUF_Index]);
	LL_DMA_SetBlkDataLength(Line5_DMA, Line5_DMA_CH, Line_BUF_Size);

	LL_DMA_EnableIT_TC(Line5_DMA, Line5_DMA_CH);
	LL_DMA_EnableChannel(Line5_DMA, Line5_DMA_CH);
}

void GPDMA1_Channel5_IRQHandler(void)
{

	LL_DMA_DisableIT_TC(Line6_DMA, Line6_DMA_CH);
	LL_DMA_SuspendChannel(Line6_DMA, Line6_DMA_CH);
	LL_DMA_DisableChannel(Line6_DMA, Line6_DMA_CH);

	LL_DMA_ClearFlag_HT(Line6_DMA, Line6_DMA_CH);
	LL_DMA_ClearFlag_TC(Line6_DMA, Line6_DMA_CH);
	LL_DMA_ClearFlag_SUSP(Line6_DMA, Line6_DMA_CH);

	LL_DMA_SetDestAddress(Line6_DMA, Line6_DMA_CH, &LineX_RX_Buffer[Line6_BUF_Index]);
	LL_DMA_SetBlkDataLength(Line6_DMA, Line6_DMA_CH, Line_BUF_Size);

	LL_DMA_EnableIT_TC(Line6_DMA, Line6_DMA_CH);
	LL_DMA_EnableChannel(Line6_DMA, Line6_DMA_CH);
}

void GPDMA1_Channel6_IRQHandler(void)
{

	LL_DMA_DisableIT_TC(Line7_DMA, Line7_DMA_CH);
	LL_DMA_SuspendChannel(Line7_DMA, Line7_DMA_CH);
	LL_DMA_DisableChannel(Line7_DMA, Line7_DMA_CH);

	LL_DMA_ClearFlag_HT(Line7_DMA, Line7_DMA_CH);
	LL_DMA_ClearFlag_TC(Line7_DMA, Line7_DMA_CH);
	LL_DMA_ClearFlag_SUSP(Line7_DMA, Line7_DMA_CH);

	LL_DMA_SetDestAddress(Line7_DMA, Line7_DMA_CH, &LineX_RX_Buffer[Line7_BUF_Index]);
	LL_DMA_SetBlkDataLength(Line7_DMA, Line7_DMA_CH, Line_BUF_Size);

	LL_DMA_EnableIT_TC(Line7_DMA, Line7_DMA_CH);
	LL_DMA_EnableChannel(Line7_DMA, Line7_DMA_CH);
}
/* USER CODE END 1 */
