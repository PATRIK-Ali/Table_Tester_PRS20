#include "RS485.h"


u8 RS485_SingleEnded_Network = Single_Ended;//Single_Ended;

char Line1_BUF[BUF_Size];
char Line2_BUF[BUF_Size];
char Line3_BUF[BUF_Size];
char Line4_BUF[BUF_Size];
char Line5_BUF[BUF_Size];
char Line6_BUF[BUF_Size];
char Line7_BUF[BUF_Size];
char Lines_BUF[BUF_Size];

u16 Line1_BUF_P = 0;
u16 Line2_BUF_P = 0;
u16 Line3_BUF_P = 0;
u16 Line4_BUF_P = 0;
u16 Line5_BUF_P = 0;
u16 Line6_BUF_P = 0;
u16 Line7_BUF_P = 0;

u8 Line1_BUF_Timeout = 0;
u8 Line2_BUF_Timeout = 0;
u8 Line3_BUF_Timeout = 0;
u8 Line4_BUF_Timeout = 0;
u8 Line5_BUF_Timeout = 0;
u8 Line6_BUF_Timeout = 0;
u8 Line7_BUF_Timeout = 0;

u8 Line1_Working = 0;
u8 Line2_Working = 0;
u8 Line3_Working = 0;
u8 Line4_Working = 0;
u8 Line5_Working = 0;
u8 Line6_Working = 0;
u8 Line7_Working = 0;

//------------------------------------------------------------------------------
void RS485_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	//---------------------D/R GPIO----------------------------
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	//---------------------D/R GPIO----------------------------
////    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
////	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
//
//	USART_InitStructure.USART_BaudRate = 57600;//19200
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_Init(USART1, &USART_InitStructure);
////  USART_Cmd(USART1, ENABLE);
//
//	USART_InitStructure.USART_BaudRate = 57600;//19200
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_Init(USART2, &USART_InitStructure);
////  USART_Cmd(USART2, ENABLE);
//
//	USART_InitStructure.USART_BaudRate = 57600;//19200
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//  USART_Init(USART3, &USART_InitStructure);
////  USART_Cmd(USART3, ENABLE);
//
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
////	if(UART1 == 1)
////	{
////
////	}
////
////	if(UART2 == 1)
////	{
////
////	}
////
////	if(UART3 == 1)
////	{
////
////	}
//
//	USART_Cmd(USART1, ENABLE);
//	USART_Cmd(USART2, ENABLE);
//	USART_Cmd(USART3, ENABLE);
}

//------------------------------------------------------------------------------
void RS485_Set_Line_Driver_Receiver(u8 Line, u8 D_R)
{
	delay_m(100);
	
	if(RS485_SingleEnded_Network == Single_Ended)
	{
		if(Line == 1)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line1_DR_Port, Line1_DR_Pin);
			}
			
			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
			}
		}
		
		else if(Line == 2)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line2_DR_Port, Line2_DR_Pin);
			}
			
			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
			}
		}
		
		else if(Line == 3)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line3_DR_Port, Line3_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
			}
		}

		else if(Line == 4)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line4_DR_Port, Line4_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
			}
		}

		else if(Line == 5)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line5_DR_Port, Line5_DR_Pin);
			}
			
			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
			}
		}

		else if(Line == 6)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line6_DR_Port, Line6_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
			}
		}

		else if(Line == 7)
		{
			if(D_R == Driver)
			{
				LL_GPIO_SetOutputPin(Line7_DR_Port, Line7_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
			}
		}
	}
	//------------
	if(RS485_SingleEnded_Network == Network)
	{
		if(Line == 1)
		{
			if(D_R == Driver)
			{
				//LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line1_DR_Port, Line1_DR_Pin);
			}
			
			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
			}
		}
		
		else if(Line == 2)
		{
			if(D_R == Driver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				//LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line2_DR_Port, Line2_DR_Pin);
			}
			
			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
			}
		}
		
		else if(Line == 3)
		{
			if(D_R == Driver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				//LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line3_DR_Port, Line3_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
			}
		}

		else if(Line == 4)
		{
			if(D_R == Driver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				//LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line4_DR_Port, Line4_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
			}
		}

		else if(Line == 5)
		{
			if(D_R == Driver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				//LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line5_DR_Port, Line5_DR_Pin);
			}
			
			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
			}
		}

		else if(Line == 6)
		{
			if(D_R == Driver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				//LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line6_DR_Port, Line6_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
			}
		}

		else if(Line == 7)
		{
			if(D_R == Driver)
			{
				LL_GPIO_ResetOutputPin(Line1_DR_Port, Line1_DR_Pin);
				LL_GPIO_ResetOutputPin(Line2_DR_Port, Line2_DR_Pin);
				LL_GPIO_ResetOutputPin(Line3_DR_Port, Line3_DR_Pin);
				LL_GPIO_ResetOutputPin(Line4_DR_Port, Line4_DR_Pin);
				LL_GPIO_ResetOutputPin(Line5_DR_Port, Line5_DR_Pin);
				LL_GPIO_ResetOutputPin(Line6_DR_Port, Line6_DR_Pin);
				//LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
				LL_GPIO_SetOutputPin(Line7_DR_Port, Line7_DR_Pin);
			}

			else if(D_R == Receiver)
			{
				LL_GPIO_ResetOutputPin(Line7_DR_Port, Line7_DR_Pin);
			}
		}
	}
}

//------------------------------------------------------------------------------
void RS485_Tx(u8 Line, char *MSG, u16 MSG_Length)
{
	//char Str[100] = "...";
	const char Header_MSG[110] = "\r\n-----\r\nMessage from MPM controller on %s.\r\nMessage length: %u bytes\r\nCRC-32: %u\r\n\r\n\0\0";
	char Header[200] = ".";
	char *Pointer = Header;
	//unsigned int CRC_MSG = CRC_Message_Calculator(MSG, MSG_Length);
	unsigned int CRC_MSG = 65535; //crc32_check (MSG, MSG_Length);
	unsigned int Checksum = 0;
	//memset(Header, 0, 110);
	//Text = &Str[0];
	//Str[0] = '.';
	
//		while(MSG_Length)
//		{
//			Checksum
//			MSG++;
//			MSG_Length--;
//		}

		if(Line == 1)
		{
			if(Line1_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(1, Driver);
			sprintf(Header, Header_MSG, "Line1 (RS485-1)", MSG_Length, CRC_MSG);
			//sprintf(Str, "Allllllllli");
//			memset(Header, 0, 200);
//			strcpy(Header, "SALAM AZ KHATE 1");
			
//			while(*Pointer != 0)
//			{
//				while(LL_USART_IsActiveFlag_TXE(Line1_UART) == RESET) {__NOP();}
//				LL_USART_TransmitData8(Line1_UART, *Pointer);//'1'
//				while(LL_USART_IsActiveFlag_TC(Line1_UART) == RESET) {__NOP();}
//				LL_USART_ClearFlag_TC(Line1_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_USART_IsActiveFlag_TXE(Line1_UART) == RESET) {__NOP();}
				LL_USART_TransmitData8(Line1_UART, *MSG);//'A'
				while(LL_USART_IsActiveFlag_TC(Line1_UART) == RESET) {__NOP();}
				LL_USART_ClearFlag_TC(Line1_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_USART_IsActiveFlag_TXE(Line1_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		//------------
		else if(Line == 2)
		{
			if(Line2_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(2, Driver);
			sprintf(Header, Header_MSG, "Line2 (RS485-2)", MSG_Length, CRC_MSG);
			
//			while(*Pointer != 0)
//			{
//				while(LL_USART_IsActiveFlag_TXE(Line2_UART) == RESET) {__NOP();}
//				LL_USART_TransmitData8(Line2_UART, *Pointer);//'2'
//				while(LL_USART_IsActiveFlag_TC(Line2_UART) == RESET) {__NOP();}
//				LL_USART_ClearFlag_TC(Line2_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_USART_IsActiveFlag_TXE(Line2_UART) == RESET) {__NOP();}
				LL_USART_TransmitData8(Line2_UART, *MSG);//'B'
				while(LL_USART_IsActiveFlag_TC(Line2_UART) == RESET) {__NOP();}
				LL_USART_ClearFlag_TC(Line2_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_USART_IsActiveFlag_TXE(Line2_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		//------------
		else if(Line == 3)
		{
			if(Line3_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(3, Driver);
			sprintf(Header, Header_MSG, "HV Line (RS485-3)", MSG_Length, CRC_MSG);
			
//			while(*Pointer != 0)
//			{
//				while(LL_USART_IsActiveFlag_TXE(Line3_UART) == RESET) {__NOP();}
//				LL_USART_TransmitData8(Line3_UART, *Pointer);//'3'
//				while(LL_USART_IsActiveFlag_TC(Line3_UART) == RESET) {__NOP();}
//				LL_USART_ClearFlag_TC(Line3_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_USART_IsActiveFlag_TXE(Line3_UART) == RESET) {__NOP();}
				LL_USART_TransmitData8(Line3_UART, *MSG);//'C'
				while(LL_USART_IsActiveFlag_TC(Line3_UART) == RESET) {__NOP();}
				LL_USART_ClearFlag_TC(Line3_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_USART_IsActiveFlag_TXE(Line3_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		//------------
		else if(Line == 4)
		{
			if(Line4_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(4, Driver);
			sprintf(Header, Header_MSG, "Line4 (RS485-4)", MSG_Length, CRC_MSG);

//			while(*Pointer != 0)
//			{
//				while(LL_USART_IsActiveFlag_TXE(Line4_UART) == RESET) {__NOP();}
//				LL_USART_TransmitData8(Line4_UART, '4');//*Pointer
//				while(LL_USART_IsActiveFlag_TC(Line4_UART) == RESET) {__NOP();}
//				LL_USART_ClearFlag_TC(Line4_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_USART_IsActiveFlag_TXE(Line4_UART) == RESET) {__NOP();}
				LL_USART_TransmitData8(Line4_UART, 'D');//*MSG
				while(LL_USART_IsActiveFlag_TC(Line4_UART) == RESET) {__NOP();}
				LL_USART_ClearFlag_TC(Line4_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_USART_IsActiveFlag_TXE(Line4_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		//------------
		else if(Line == 5)
		{
			if(Line5_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(5, Driver);
			sprintf(Header, Header_MSG, "Line5 (RS485-5)", MSG_Length, CRC_MSG);

//			while(*Pointer != 0)
//			{
//				while(LL_LPUART_IsActiveFlag_TXE(Line5_UART) == RESET) {__NOP();}
//				LL_LPUART_TransmitData8(Line5_UART, '5');//*Pointer
//				while(LL_LPUART_IsActiveFlag_TC(Line5_UART) == RESET) {__NOP();}
//				LL_LPUART_ClearFlag_TC(Line5_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_LPUART_IsActiveFlag_TXE(Line5_UART) == RESET) {__NOP();}
				LL_LPUART_TransmitData8(Line5_UART, 'E');//*MSG
				while(LL_LPUART_IsActiveFlag_TC(Line5_UART) == RESET) {__NOP();}
				LL_LPUART_ClearFlag_TC(Line5_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_LPUART_IsActiveFlag_TXE(Line5_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		//------------
		else if(Line == 6)
		{
			if(Line6_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(6, Driver);
			sprintf(Header, Header_MSG, "Line6 (RS485-6)", MSG_Length, CRC_MSG);

//			while(*Pointer != 0)
//			{
//				while(LL_LPUART_IsActiveFlag_TXE(Line6_UART) == RESET) {__NOP();}
//				LL_LPUART_TransmitData8(Line6_UART, *Pointer);//'6'
//				while(LL_LPUART_IsActiveFlag_TC(Line6_UART) == RESET) {__NOP();}
//				LL_LPUART_ClearFlag_TC(Line6_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_LPUART_IsActiveFlag_TXE(Line6_UART) == RESET) {__NOP();}
				LL_USART_TransmitData8(Line6_UART, *MSG);//'F'
				while(LL_LPUART_IsActiveFlag_TC(Line6_UART) == RESET) {__NOP();}
				LL_LPUART_ClearFlag_TC(Line6_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_LPUART_IsActiveFlag_TXE(Line6_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		//------------
		else if(Line == 7)
		{
			if(Line7_Working == 1) {return;}
			RS485_Set_Line_Driver_Receiver(7, Driver);
			sprintf(Header, Header_MSG, "Line7 (RS485-7)", MSG_Length, CRC_MSG);

//			while(*Pointer != 0)
//			{
//				while(LL_LPUART_IsActiveFlag_TXE(Line7_UART) == RESET) {__NOP();}
//				LL_LPUART_TransmitData8(Line7_UART, *Pointer);//'7'
//				while(LL_LPUART_IsActiveFlag_TC(Line7_UART) == RESET) {__NOP();}
//				LL_LPUART_ClearFlag_TC(Line7_UART);
//				Pointer++;
//			}

			while(MSG_Length)
			{
				while(LL_LPUART_IsActiveFlag_TXE(Line7_UART) == RESET) {__NOP();}
				LL_USART_TransmitData8(Line7_UART, *MSG);//'G'
				while(LL_LPUART_IsActiveFlag_TC(Line7_UART) == RESET) {__NOP();}
				LL_LPUART_ClearFlag_TC(Line7_UART);
				MSG++;
				MSG_Length--;
			}

			while(LL_LPUART_IsActiveFlag_TXE(Line7_UART) == RESET) {__NOP();}
			//delay_m(10);
		}
		
}
//------------------------------------------------------------------------------
void RS485_Rx(u8 Line, char *MSG, u16 MSG_Length)
{
	//char Str[100] = "...";
	char Header_MSG[110] = "\r\n-----\r\nMessage from user on %s.\r\nMessage length: %u bytes\r\nCRC-32: %u\r\n\r\n\0\0";
	char Header[200] = ".";
	char *Pointer = Header;
	//unsigned int CRC_MSG = CRC_Message_Calculator(MSG, MSG_Length);
	//unsigned int CRC_MSG = crc32_check (MSG, MSG_Length);
	//unsigned int Checksum = 0;
	//memset(Header, 0, 100);
	//Text = &Str[0];
	//Str[0] = '.';
	
//		while(MSG_Length)
//		{
//			Checksum
//			MSG++;
//			MSG_Length--;
//		}

		if(Line == 1)
		{
			MSG[Line1_BUF_P] = LL_USART_ReceiveData8(Line1_UART);
			Line1_BUF_P++;
			Line1_Working = 1;
			Line1_BUF_Timeout = 0;
		}
		//------------
		else if(Line == 2)
		{
			MSG[Line2_BUF_P] = LL_USART_ReceiveData8(Line2_UART);
			Line2_BUF_P++;
			Line2_Working = 1;
			Line2_BUF_Timeout = 0;
		}
		//------------
		else if(Line == 3)
		{
			MSG[Line3_BUF_P] = LL_USART_ReceiveData8(Line3_UART);
			Line3_BUF_P++;
			Line3_Working = 1;
			Line3_BUF_Timeout = 0;
		}
		//------------
		else if(Line == 4)
		{
			MSG[Line4_BUF_P] = LL_USART_ReceiveData8(Line4_UART);
			Line4_BUF_P++;
			Line4_Working = 1;
			Line4_BUF_Timeout = 0;
		}
		//------------
		else if(Line == 5)
		{
			MSG[Line5_BUF_P] = LL_LPUART_ReceiveData8(Line5_UART);
			Line5_BUF_P++;
			Line5_Working = 1;
			Line5_BUF_Timeout = 0;
		}
		//------------
		else if(Line == 6)
		{
			MSG[Line6_BUF_P] = LL_LPUART_ReceiveData8(Line6_UART);
			Line6_BUF_P++;
			Line6_Working = 1;
			Line6_BUF_Timeout = 0;
		}
		//------------
		else if(Line == 7)
		{
			MSG[Line7_BUF_P] = LL_LPUART_ReceiveData8(Line7_UART);
			Line7_BUF_P++;
			Line7_Working = 1;
			Line7_BUF_Timeout = 0;
		}
		
}
