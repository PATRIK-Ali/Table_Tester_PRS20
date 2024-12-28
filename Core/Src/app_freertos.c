/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
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
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
char Str[50];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 8
};
/* Definitions for myMutex01 */
osMutexId_t myMutex01Handle;
const osMutexAttr_t myMutex01_attributes = {
  .name = "myMutex01"
};
/* Definitions for myTimer01 */
osTimerId_t myTimer01Handle;
const osTimerAttr_t myTimer01_attributes = {
  .name = "myTimer01"
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* creation of myMutex01 */
  myMutex01Handle = osMutexNew(&myMutex01_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */
  /* creation of myTimer01 */
  myTimer01Handle = osTimerNew(Callback01, osTimerPeriodic, NULL, &myTimer01_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  /* Infinite loop */
	Coordinate Touch_XY;
	int Coor_X = 0;
	int Coor_Y = 0;
	//Coordinate Touch_XY_Old;
	//char Str[50];
	char i = 0;
	memset(Str, 0, sizeof(Str));

	//LCD_DisplayOn();
	osDelay(100);
	LCD_Clear(RED);
	//LCD_ShowString(5,10,15,(u8 *)"This is Test.",1);
	//Show_Str(5, 30, YELLOW, RED, "This is Test.",15,1);
	matrix = Matrix_Default; //ts_calibrate( 240, 320 );
  for(;;)
  {
	  if(TS_Touched() == 1)
	  {
		  getDisplayPoint(&display, Read_Value(), &matrix ) ;
		  ts_draw_point(display.x,display.y,BLUE );

		  if( (10<display.x && display.x<20) && (10<display.y && display.y<20) && (TS_Touched() == 1) )
		  {
			  LCD_Clear(RED);
//			  RS485_Tx(1, "Salam az khate 1", 16);
//	  		  RS485_Tx(2, "Salam az khate 2", 16);
//	  		  RS485_Tx(3, "Salam az khate 3", 16);
//	  		  RS485_Tx(4, "Salam az khate 4", 16);
//	  		  RS485_Tx(5, "Salam az khate 5", 16);
//	  		  RS485_Tx(6, "Salam az khate 6", 16);
//	  		  RS485_Tx(7, "Salam az khate 7", 16);
			  Show_Str(5, 30, YELLOW, RED, Str,15,1);
			  i = 0;
	  		  display.x=0; display.y=0;
		  }
	  }

//	  RS485_Tx(1, "Salam az khate 1", 16);
//	  RS485_Tx(2, "Salam az khate 2", 16);
//	  RS485_Tx(3, "Salam az khate 3", 16);
//	  RS485_Tx(4, "Salam az khate 4", 16);
//	  RS485_Tx(5, "Salam az khate 5", 16);
//	  RS485_Tx(6, "Salam az khate 6", 16);
//	  RS485_Tx(7, "Salam az khate 7", 16);
//	  osDelay(2000/portTICK_PERIOD_MS);

	  //for(int L=0; L<=100000; L++)
//	  while(1)
//	  {
//		if(LL_USART_IsActiveFlag_RXNE(Line1_UART) == 1)
//		{
//			Str[i] = LL_USART_ReceiveData8(Line1_UART);
//			i++;
//			//LCD_Clear(GRAY);
//		}
//
//		if(LL_USART_IsActiveFlag_RXNE(Line2_UART) == 1)
//		{
//		  Str[i] = LL_USART_ReceiveData8(Line2_UART);
//		  i++;
//		//LCD_Clear(BRRED);
//		}
//
//		if(LL_USART_IsActiveFlag_RXNE(Line3_UART) == 1)
//		{
//		  Str[i] = LL_USART_ReceiveData8(Line3_UART);
//		  i++;
//		//LCD_Clear(BROWN);
//		}
//
//		if(LL_USART_IsActiveFlag_RXNE(Line4_UART) == 1)
//		{
//		  Str[i] = LL_USART_ReceiveData8(Line4_UART);
//		  i++;
//		//LCD_Clear(YELLOW);
//		}
//
//		if(LL_USART_IsActiveFlag_RXNE(Line5_UART) == 1)
//		{
//		  Str[i] = LL_LPUART_ReceiveData8(Line5_UART);
//		  i++;
//		//LCD_Clear(CYAN);
//		}
//
//		if(LL_USART_IsActiveFlag_RXNE(Line6_UART) == 1)
//		{
//		  Str[i] = LL_USART_ReceiveData8(Line6_UART);
//		  i++;
//		//LCD_Clear(GREEN);
//		}
//
//		if(LL_USART_IsActiveFlag_RXNE(Line7_UART) == 1)
//		{
//		  Str[i] = LL_USART_ReceiveData8(Line7_UART);
//		  i++;
//		//LCD_Clear(MAGENTA);
//		}
//	  }

//	  if(i > 0)
//	  {
//		  Show_Str(5, 30, YELLOW, RED, Str,15,1);
//		  i = 0;
//	  }


//	  if(TP_INT_IN == 0)
//	  {
//		  Show_Str(5, 280, YELLOW, BLUE, "                  ",15,0);
//		  Show_Str(5, 280, YELLOW, BLUE, "Touched.",15,0);
////		  Coor_X = Read_Value().x;
////		  Coor_Y = Read_Value().y;
//		  Touch_XY = Read_Value();
//		  //Touch_XY_Old.x = Touch_XY->x;
//		  if(Touch_XY.x != 65535)
//		  {
//			  Show_Str(5, 280, YELLOW, BLUE, "                      ",15,0);
//			  memset(Str, 0, sizeof(Str));
//			  sprintf(Str, "X: %d - Y: %d", Touch_XY.x, Touch_XY.y);
//			  Show_Str(100, 150, YELLOW, BLUE, Str,15,0);
//		  }
//	  }
//	  else
//	  {
//		  Show_Str(5, 280, YELLOW, BLUE, "                  ",15,0);
//		  Show_Str(5, 280, YELLOW, BLUE, "Not Touched.",15,0);
//	  }

	  //osDelay(50);
	  //Touch_XY = Read_Value();



//	LCD_Clear(RED);
//	LCD_Clear(GREEN);
//	LCD_Clear(BLUE);
//    osDelay(500);
//    LCD_Clear(YELLOW);
//    osDelay(500);
//    LCD_Clear(BROWN);
  }
  /* USER CODE END defaultTask */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */

  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

