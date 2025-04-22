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
#include "Main_CPU_Comm.h"
#include "Table_Tester_App.h"
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
char I = 0;
const uint8_t Lines_Sequence[10] = {0,1,2,3,4,5,6,7,0,0};
uint8_t RX_Task_Done = 0;
uint8_t LCD_Touch_Task_Done = 0;
uint32_t TX_Bytes_Count = 0;
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

osThreadId_t Lines_Sequence_Task_Handle;
const osThreadAttr_t Lines_Sequence_Task_attributes = {
  .name = "Lines_Sequence_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 8
};

osThreadId_t RX_Task_Handle;
const osThreadAttr_t RX_Task_attributes = {
  .name = "RX_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 8
};

osThreadId_t LCD_Touch_Task_Handle;
const osThreadAttr_t LCD_Touch_Task_attributes = {
  .name = "LCD_Touch_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 10
};

osMessageQueueId_t Lines_Seq_Queue_Handle;
const osMessageQueueAttr_t Lines_Seq_Queue_attributes = {
  .name = "Lines_Seq_Queue"
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
  Lines_Seq_Queue_Handle = osMessageQueueNew (100, sizeof(uint8_t), &Lines_Seq_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  //defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  //Lines_Sequence_Task_Handle = osThreadNew(Lines_Sequence_Task, NULL, &Lines_Sequence_Task_attributes);
  RX_Task_Handle = osThreadNew(RX_Task, NULL, &RX_Task_attributes);
  LCD_Touch_Task_Handle = osThreadNew(LCD_Touch_Task, NULL, &LCD_Touch_Task_attributes);

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
	LCD_Clear(BLACK);
	//LCD_ShowString(5,10,15,(u8 *)"This is Test.",1);
	//Show_Str(5, 30, YELLOW, RED, "This is Test.",15,1);
	Show_Str(5, 10, WHITE, BLACK, "FEU:",20,1);
	Show_Str(5, 30, WHITE, BLACK, "RX1",20,1);
	Show_Str(50, 30, WHITE, BLACK, "INJ OFF",20,1);
	Show_Str(150, 30, WHITE, BLACK, "RF 1.6-2.2",20,1);
	Show_Str(5, 55, WHITE, BLACK, "Low Gain Path",20,1);
	Show_Str(150, 55, WHITE, BLACK, "- Atten +",20,1);

	Show_Str(5, 10+85, WHITE, BLACK, "IJU:",20,1);
	//Show_Str(5, 30+85, WHITE, BLACK, "RX1",20,1);
	Show_Str(50, 30+85, WHITE, BLACK, "INJ OFF",20,1);
	Show_Str(150, 30+85, WHITE, BLACK, "RF 1.6-2.2",20,1);
	//Show_Str(5, 55+85, WHITE, BLACK, "Low Gain Path",20,1);
	Show_Str(150, 55+85, WHITE, BLACK, "- Atten +",20,1);

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
//--------------------------------------------------------------------------

void Lines_Sequence_Task(void *argument)
{
	for(;;)
	{
		if(LL_USART_IsActiveFlag_BUSY(Line1_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[1], 1, 100);}
		if(LL_USART_IsActiveFlag_BUSY(Line2_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[2], 1, 100);}
		if(LL_USART_IsActiveFlag_BUSY(Line3_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[3], 1, 100);}
		if(LL_USART_IsActiveFlag_BUSY(Line4_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[4], 1, 100);}
		if(LL_USART_IsActiveFlag_BUSY(Line5_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[5], 1, 100);}
		if(LL_USART_IsActiveFlag_BUSY(Line6_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[6], 1, 100);}
		if(LL_USART_IsActiveFlag_BUSY(Line7_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[7], 1, 100);}
	}
}
//--------------------------------------------------------------------------

void RX_Task(void *argument)
{
	uint8_t *Buffer_P = 0;
	static uint8_t *Line1_Next_SOP = &Line1_RX_Buffer;
	static uint8_t *Line2_Next_SOP = &Line2_RX_Buffer;
	static uint8_t *Line3_Next_SOP = &Line3_RX_Buffer;
	static uint8_t *Line4_Next_SOP = &Line4_RX_Buffer;
	static uint8_t *Line5_Next_SOP = &Line5_RX_Buffer;
	static uint8_t *Line6_Next_SOP = &Line6_RX_Buffer;
	static uint8_t *Line7_Next_SOP = &Line7_RX_Buffer;
	//uint8_t Lines_Sequence[10] = {0,1,2,3,4,5,6,7,0,0};
//	uint8_t Lines_Sequence[50];
//
//	memset(Lines_Sequence, 0, sizeof(Lines_Sequence));

	for(;;)
	{
		RX_Task_Done = 0;
		//osThreadFlagsWait (1, osFlagsWaitAny, osWaitForever);
//		if(LL_USART_IsActiveFlag_BUSY(Line1_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[1], 1, 100);}
//		if(LL_USART_IsActiveFlag_BUSY(Line2_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[2], 1, 100);}
//		if(LL_USART_IsActiveFlag_BUSY(Line3_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[3], 1, 100);}
//		if(LL_USART_IsActiveFlag_BUSY(Line4_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[4], 1, 100);}
//		if(LL_USART_IsActiveFlag_BUSY(Line5_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[5], 1, 100);}
//		if(LL_USART_IsActiveFlag_BUSY(Line6_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[6], 1, 100);}
//		if(LL_USART_IsActiveFlag_BUSY(Line7_UART)) {osMessageQueuePut (Lines_Seq_Queue_Handle, &Lines_Sequence[7], 1, 100);}

		switch (Message_Buffering(Line3_RX_Buffer, Line3_Next_SOP))
		{
		case Waiting:
			Delay_ms_OS(2);
			//osDelay(1000/portTICK_PERIOD_MS);
			break;

		case OK_Send_ACK:
			//				osMutexAcquire (TX_Buffer_Mutex_Handle, 0);
			//				MainCPU_Message_Maker(C_ACK, O_STATUS, "OK.", R_DONE);
			//				osThreadFlagsSet(MainCPU_Comm_TX_Task_Handle, 1);
			//				osMutexRelease (TX_Buffer_Mutex_Handle);
			break;

		case CRC_NOK:
			//
			break;

		case Invalid:
			//
			break;

		case None:
			__NOP();
			break;

		default:
			__NOP();
			break;
		}

		if(Parsed_MSG.New_MSG == 1)
		{
//			if(Parsed_MSG.Command == C_BATT_Charger)
//			{
//				osMessageQueuePut (Outputs_Queue_Handle, &Parsed_MSG, NULL, 0);
//				//Parsed_MSG.New_MSG = 0;
//			}
//
//			if(Parsed_MSG.Command == C_Siren)
//			{
//				osMessageQueuePut (Outputs_Queue_Handle, &Parsed_MSG, NULL, 0);
//				//Parsed_MSG.New_MSG = 0;
//			}
//
//			if(Parsed_MSG.Command == C_Sound_Line)
//			{
//				osMessageQueuePut (Outputs_Queue_Handle, &Parsed_MSG, NULL, 0);
//				//Parsed_MSG.New_MSG = 0;
//			}
//
//			if(Parsed_MSG.Command == C_Relay)
//			{
//				osMessageQueuePut (Outputs_Queue_Handle, &Parsed_MSG, NULL, 0);
//				//Parsed_MSG.New_MSG = 0;
//			}
//			//-------------------
//			if( (Parsed_MSG.Command == C_Battery)||(Parsed_MSG.Command == C_AC)||(Parsed_MSG.Command == C_ExtSpeaker)||(Parsed_MSG.Command == C_Siren)||(Parsed_MSG.Command == C_AUX)||(Parsed_MSG.Command == C_VDD) )
//			{
//				if(Parsed_MSG.Operation == O_STATUS)
//				{
//					osMessageQueuePut (Inputs_Queue_Handle, &Parsed_MSG, NULL, 0);
//					//Parsed_MSG.New_MSG = 0;
//					Count++;
//				}
//			}

			if(Parsed_MSG.PCKT_ID == FEUtoMIU_0)
			{
				if( (Parsed_MSG.Data1 & INJ_ON_Bit1) == INJ_ON_Bit1) {FEU_Status.FEU_INJ = ON;}
				else {FEU_Status.FEU_INJ = OFF;}

				if( (Parsed_MSG.Data1 & RF_42_63_Bit2_3) == RF_42_63_Bit2_3) {FEU_Status.FEU_RF_Filter = Filter_42_63;}
				else if( (Parsed_MSG.Data1 & RF_30_46_Bit2_3) == RF_30_46_Bit2_3) {FEU_Status.FEU_RF_Filter = Filter_30_46;}
				else if( (Parsed_MSG.Data1 & RF_20_32_Bit2_3) == RF_20_32_Bit2_3) {FEU_Status.FEU_RF_Filter = Filter_20_32;}
				else {FEU_Status.FEU_RF_Filter = Filter_16_22;}

				if( (Parsed_MSG.Data1 & RF_ON_Bit5) == RF_ON_Bit5) {FEU_Status.FEU_RF_Power = ON;}
				else {FEU_Status.FEU_RF_Power = OFF;}

				//Parsed_MSG.New_MSG = 0;
			}

			if(Parsed_MSG.PCKT_ID == IJUtoMIU_0)
			{
				if( (Parsed_MSG.Data1 & INJ_ON_Bit1) == INJ_ON_Bit1) {IJU_Status.IJU_INJ = ON;}
				else {IJU_Status.IJU_INJ = OFF;}

				if( (Parsed_MSG.Data1 & RF_42_63_Bit2_3) == RF_42_63_Bit2_3) {IJU_Status.IJU_RF_Filter = Filter_42_63;}
				else if( (Parsed_MSG.Data1 & RF_30_46_Bit2_3) == RF_30_46_Bit2_3) {IJU_Status.IJU_RF_Filter = Filter_30_46;}
				else if( (Parsed_MSG.Data1 & RF_20_32_Bit2_3) == RF_20_32_Bit2_3) {IJU_Status.IJU_RF_Filter = Filter_20_32;}
				else {IJU_Status.IJU_RF_Filter = Filter_16_22;}

				if( (Parsed_MSG.Data1 & RF_ON_Bit5) == RF_ON_Bit5) {IJU_Status.IJU_RF_Power = ON;}
				else {IJU_Status.IJU_RF_Power = OFF;}

				IJU_Status.IJU_Atten = Parsed_MSG.Data2 & 0b00111111;

				//Parsed_MSG.New_MSG = 0;
			}

			Parsed_MSG.New_MSG = 0;
		}


		//		Task_Done.MainCPU_Comm_RX_Task = 1;
		//		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
		//		Task_Done.MainCPU_Comm_RX_Task = 0;

		RX_Task_Done = 1;


	}

}
//--------------------------------------------------------------------------

void LCD_Touch_Task(void *argument)
{
	Coordinate Touch_XY;
	int Coor_X = 0;
	int Coor_Y = 0;
	//Coordinate Touch_XY_Old;
	char Str[50];
	char i = 0;
	uint16_t X = 0;
	uint16_t Y = 0;
	uint8_t Text_Line = 20;

	uint8_t Sync_MSG = 255;
	memset(Str, 0, sizeof(Str));

	LCD_Page = PRSX_Page;

	osDelay(100);

	matrix = Matrix_Default; //ts_calibrate( 240, 320 );
	getDisplayPoint(&display, Read_Value(), &matrix ) ;

	LCD_Clear(BLACK);
	Show_Str(83, 100, WHITE, BLACK, (u8 *)LCD_PRS10_Str,20,1);
	Show_Str(83, 140, WHITE, BLACK, (u8 *)LCD_PRS20_Str,20,1);
	Show_Str(83, 180, WHITE, BLACK, (u8 *)LCD_PRS30_Str,20,1);
//	Show_Str(5, 10, YELLOW, BLACK, (u8 *)LCD_FEU_Str,20,1);
//	Show_Str(5, 30, WHITE, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
//	Show_Str(5, 50, WHITE, BLACK, (u8 *)LCD_RX1_Str,20,1);
//	Show_Str(60, 50, WHITE, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
//	Show_Str(150, 50, WHITE, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
//	Show_Str(5, 70, WHITE, BLACK, (u8 *)LCD_Gain_Low_Str,20,1);
//	Show_Str(150, 70, WHITE, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
//	Show_Str(5, 90, WHITE, BLACK, (u8 *)LCD_Atten_Str,20,1);
//	LCD_DrawLine(0, 108, 239, 108, RED);
//	Show_Str(5, 110, YELLOW, BLACK, (u8 *)LCD_IJU_Str,20,1);
//	Show_Str(5, 130, WHITE, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
//	Show_Str(5, 150, WHITE, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
//	Show_Str(95, 150, WHITE, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
//	Show_Str(5, 170, WHITE, BLACK, (u8 *)LCD_Atten_Str,20,1);
//	Show_Str(150, 170, WHITE, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);

//	LL_CRC_ResetCRCCalculationUnit(CRC);
//	LL_CRC_FeedData8(CRC, 0xCA); LL_CRC_FeedData8(CRC, 0x00);
//	LL_CRC_FeedData8(CRC, 0x1F); LL_CRC_FeedData8(CRC, 0x4A); LL_CRC_FeedData8(CRC, 0x00);
//	LL_CRC_FeedData8(CRC, 0x00); LL_CRC_FeedData8(CRC, 0x00); LL_CRC_FeedData8(CRC, 0x00);
//	//CRC_Result = LL_CRC_ReadData16(CRC);
//	sprintf(Str, "CRC = %0X", LL_CRC_ReadData16(CRC));
//	Show_Str(5, 220, GBLUE, BLACK, (u8 *)Str,20,1);

//	Power27V_Switch(1);
//	osDelay(1000);
//	Power27V_Switch(0);

	for(;;)
	{
		LCD_Touch_Task_Done = 0;
		//USBPD_DPM_Run();
		//osDelay(1);
		//Ali_USB();
		if(TS_Touched() == 1)
		{
			getDisplayPoint(&display, Read_Value(), &matrix ) ;
			//---------------PRSX Select---------------
			X = 83;	Y = 140;
			if( (LCD_Page == PRSX_Page) && (X<display.x && display.x<X+(strlen(LCD_PRS20_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				LCD_Page = Modules_Page;
				LCD_Clear(BLACK);
				Show_Str(80, 100, WHITE, BLACK, (u8 *)LCD_FEU_Str,20,1);
				Show_Str(80, 140, WHITE, BLACK, (u8 *)LCD_IJU_Str,20,1);
				Show_Str(5, 300, GBLUE, BLACK, (u8 *)LCD_Back_Str,20,1);

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
//				for(;;)
//				{
//					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
//					TX_Bytes_Count ++;
//				}
			}
			//---------------Modules Select---------------
			X = 80;	Y = 100;
			if( (LCD_Page == Modules_Page) && (X<display.x && display.x<X+(strlen(LCD_FEU_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				LCD_Page = FEU_Page;
				//RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				LCD_Clear(BLACK);
				Show_Str(5, 10, YELLOW, BLACK, (u8 *)LCD_FEU_Str,20,1);
				Show_Str(5, 40, WHITE, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
				Show_Str(5, 70, WHITE, BLACK, (u8 *)LCD_RX1_Str,20,1);
				Show_Str(60, 70, WHITE, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
				Show_Str(150, 70, WHITE, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
				Show_Str(5, 100, WHITE, BLACK, (u8 *)LCD_Gain_Low_Str,20,1);
				Show_Str(150, 100, WHITE, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
				Show_Str(5, 130, WHITE, BLACK, (u8 *)LCD_Atten_Str,20,1);
				Show_Str(5, 300, GBLUE, BLACK, (u8 *)LCD_Back_Str,20,1);

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}

			X = 80;	Y = 140;
			if( (LCD_Page == Modules_Page) && (X<display.x && display.x<X+(strlen(LCD_IJU_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				LCD_Page = IJU_Page;
				//RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				LCD_Clear(BLACK);
				Show_Str(5, 10, YELLOW, BLACK, (u8 *)LCD_IJU_Str,20,1);
				Show_Str(5, 40, WHITE, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
				Show_Str(5, 70, WHITE, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
				Show_Str(95, 70, WHITE, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
				Show_Str(5, 100, WHITE, BLACK, (u8 *)LCD_Atten_Str,20,1);
				Show_Str(150, 100, WHITE, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
				Show_Str(5, 300, GBLUE, BLACK, (u8 *)LCD_Back_Str,20,1);

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}

			X = 5;	Y = 300;
			if( (LCD_Page == Modules_Page) && (X<display.x && display.x<X+(strlen(LCD_Back_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				LCD_Page = PRSX_Page;
				LCD_Clear(BLACK);
				Show_Str(83, 100, WHITE, BLACK, (u8 *)LCD_PRS10_Str,20,1);
				Show_Str(83, 140, WHITE, BLACK, (u8 *)LCD_PRS20_Str,20,1);
				Show_Str(83, 180, WHITE, BLACK, (u8 *)LCD_PRS30_Str,20,1);

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU Power Supply---------------
			X = 5;	Y = 40;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_PowerSupply_ON_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( Power27V_Status() == 0)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_PowerSupply_ON_Str,20,1);
					Power27V_Switch(1);
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_PowerSupply_ON_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
					Power27V_Switch(0);
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU RX---------------
			X = 5;	Y = 70;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_RX1_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( (MIU_FEU_MSG.PCKT_0 & RX2_Bit0) == RX2_Bit0)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RX2_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RX1_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RX_Bit0_RST, RX1_Bit0);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RX1_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RX2_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RX_Bit0_RST, RX2_Bit0);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU INJ---------------
			X = 60;	Y = 70;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_INJ_ON_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( (MIU_FEU_MSG.PCKT_0 & INJ_ON_Bit1) == INJ_ON_Bit1)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_INJ_ON_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, INJ_Bit1_RST, INJ_OFF_Bit1);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_INJ_ON_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, INJ_Bit1_RST, INJ_ON_Bit1);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU RF---------------
			X = 150;	Y = 70;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_RF_16_22_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				if( (MIU_FEU_MSG.PCKT_0 & RF_42_63_Bit2_3) == RF_42_63_Bit2_3)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_42_63_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RF_Bit2_3_RST, RF_16_22_Bit2_3);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else if( (MIU_FEU_MSG.PCKT_0 & RF_30_46_Bit2_3) == RF_30_46_Bit2_3)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_30_46_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_42_63_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RF_Bit2_3_RST, RF_42_63_Bit2_3);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else if( (MIU_FEU_MSG.PCKT_0 & RF_20_32_Bit2_3) == RF_20_32_Bit2_3)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_20_32_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_30_46_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RF_Bit2_3_RST, RF_30_46_Bit2_3);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else //RF_16_22_Bit2_3
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_20_32_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RF_Bit2_3_RST, RF_20_32_Bit2_3);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}


				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU Gain path---------------
			X = 5;	Y = 100;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_Gain_Low_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( (MIU_FEU_MSG.PCKT_0 & Gain_High_Bit4) == Gain_High_Bit4)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_Gain_High_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_Gain_Low_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, Gain_Bit4_RST, Gain_Low_Bit4);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_Gain_Low_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_Gain_High_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, Gain_Bit4_RST, Gain_High_Bit4);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU RF Power---------------
			X = 150;	Y = 100;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_RX1_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( (MIU_FEU_MSG.PCKT_0 & RF_ON_Bit5) == RF_ON_Bit5)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_ON_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RF_Bit5_RST, RF_OFF_Bit5);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_ON_Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_0, RF_Bit5_RST, RF_ON_Bit5);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU Atten---------------
			X = 5+(strlen("Atten: ")*8);	Y = 130;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen("-")*8)) && (Y<display.y && display.y<Y+15) )
			{
				if(FEU_Atten_Bit0_5 > 0)
				{
					X = 5+(strlen("Atten: -")*8);
					sprintf(Str, "%.1f", ((float)FEU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, BLACK, BLACK, (u8 *)Str,20,1);
					FEU_Atten_Bit0_5--;
					sprintf(Str, "%.1f", ((float)FEU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, WHITE, BLACK, (u8 *)Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_1, Atten_Bit0_5_RST, FEU_Atten_Bit0_5);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//----------
			X = 5+(strlen("Atten: -     ")*8);	Y = 130;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen("+")*8)) && (Y<display.y && display.y<Y+15) )
			{
				if(FEU_Atten_Bit0_5 < 63)
				{
					X = 5+(strlen("Atten: -")*8);
					sprintf(Str, "%.1f", ((float)FEU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, BLACK, BLACK, (u8 *)Str,20,1);
					FEU_Atten_Bit0_5++;
					sprintf(Str, "%.1f", ((float)FEU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, WHITE, BLACK, (u8 *)Str,20,1);
					Message_Maker(&MIU_FEU_MSG, &MIU_FEU_MSG.PCKT_1, Atten_Bit0_5_RST, FEU_Atten_Bit0_5);
					RS485_Tx(7, &MIU_FEU_MSG, MIU_FEU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------FEU Back to Modules select---------------
			X = 5;	Y = 300;
			if( (LCD_Page == FEU_Page) && (X<display.x && display.x<X+(strlen(LCD_Back_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				LCD_Page = Modules_Page;
				LCD_Clear(BLACK);
				Show_Str(80, 100, WHITE, BLACK, (u8 *)LCD_FEU_Str,20,1);
				Show_Str(80, 140, WHITE, BLACK, (u8 *)LCD_IJU_Str,20,1);
				Show_Str(5, 300, GBLUE, BLACK, (u8 *)LCD_Back_Str,20,1);

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------IJU Power Supply---------------
			X = 5;	Y = 40;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen(LCD_PowerSupply_ON_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( Power27V_Status() == 0)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_PowerSupply_ON_Str,20,1);
					Power27V_Switch(1);
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_PowerSupply_ON_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_PowerSupply_OFF_Str,20,1);
					Power27V_Switch(0);
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------IJU INJ---------------
			X = 5;	Y = 70;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen(LCD_INJ_ON_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( (MIU_IJU_MSG.PCKT_0 & INJ_ON_Bit1) == INJ_ON_Bit1)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_INJ_ON_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, INJ_Bit1_RST, INJ_OFF_Bit1);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_INJ_OFF_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_INJ_ON_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, INJ_Bit1_RST, INJ_ON_Bit1);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------IJU RF---------------
			X = 95;	Y = 70;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen(LCD_RF_16_22_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				if( (MIU_IJU_MSG.PCKT_0 & RF_42_63_Bit2_3) == RF_42_63_Bit2_3)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_42_63_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, RF_Bit2_3_RST, RF_16_22_Bit2_3);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else if( (MIU_IJU_MSG.PCKT_0 & RF_30_46_Bit2_3) == RF_30_46_Bit2_3)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_30_46_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_42_63_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, RF_Bit2_3_RST, RF_42_63_Bit2_3);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else if( (MIU_IJU_MSG.PCKT_0 & RF_20_32_Bit2_3) == RF_20_32_Bit2_3)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_20_32_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_30_46_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, RF_Bit2_3_RST, RF_30_46_Bit2_3);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else //RF_16_22_Bit2_3
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_16_22_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_20_32_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, RF_Bit2_3_RST, RF_20_32_Bit2_3);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}


				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------IJU Atten---------------
			X = 5+(strlen("Atten: ")*8);	Y = 100;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen("-")*8)) && (Y<display.y && display.y<Y+15) )
			{
				if(IJU_Atten_Bit0_5 > 0)
				{
					X = 5+(strlen("Atten: -")*8);
					sprintf(Str, "%.1f", ((float)IJU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, BLACK, BLACK, (u8 *)Str,20,1);
					IJU_Atten_Bit0_5--;
					sprintf(Str, "%.1f", ((float)IJU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, WHITE, BLACK, (u8 *)Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_1, Atten_Bit0_5_RST, IJU_Atten_Bit0_5);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//----------
			X = 5+(strlen("Atten: -     ")*8);	Y = 100;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen("+")*8)) && (Y<display.y && display.y<Y+15) )
			{
				if(IJU_Atten_Bit0_5 < 63)
				{
					X = 5+(strlen("Atten: -")*8);
					sprintf(Str, "%.1f", ((float)IJU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, BLACK, BLACK, (u8 *)Str,20,1);
					IJU_Atten_Bit0_5++;
					sprintf(Str, "%.1f", ((float)IJU_Atten_Bit0_5/2));
					Show_Str(X+2, Y, WHITE, BLACK, (u8 *)Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_1, Atten_Bit0_5_RST, IJU_Atten_Bit0_5);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------IJU RF Power---------------
			X = 150;	Y = 100;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen(LCD_RX1_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{

				if( (MIU_IJU_MSG.PCKT_0 & RF_ON_Bit5) == RF_ON_Bit5)
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_ON_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, RF_Bit5_RST, RF_OFF_Bit5);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}
				else
				{
					Show_Str(X, Y, BLACK, BLACK, (u8 *)LCD_RF_OFF_Str,20,1);
					Show_Str(X, Y, WHITE, BLACK, (u8 *)LCD_RF_ON_Str,20,1);
					Message_Maker(&MIU_IJU_MSG, &MIU_IJU_MSG.PCKT_0, RF_Bit5_RST, RF_ON_Bit5);
					RS485_Tx(7, &MIU_IJU_MSG, MIU_IJU_MSG.Length);
					RS485_Tx(5, &Sync_MSG, sizeof(Sync_MSG));
				}

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}
			//---------------IJU Back to Modules select---------------
			X = 5;	Y = 300;
			if( (LCD_Page == IJU_Page) && (X<display.x && display.x<X+(strlen(LCD_Back_Str)*8)) && (Y<display.y && display.y<Y+15) )
			{
				LCD_Page = Modules_Page;
				LCD_Clear(BLACK);
				Show_Str(80, 100, WHITE, BLACK, (u8 *)LCD_FEU_Str,20,1);
				Show_Str(80, 140, WHITE, BLACK, (u8 *)LCD_IJU_Str,20,1);
				Show_Str(5, 300, GBLUE, BLACK, (u8 *)LCD_Back_Str,20,1);

				display.x=0; display.y=0;
				while(TS_Touched() == 1)	{osDelay(10);}
			}

			//--------------- ---------------

		}

		LCD_Touch_Task_Done = 1;

	}
}
//--------------------------------------------------------------------------

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */

  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

