#include "Main_CPU_Comm.h"
#include "stdio.h"

//char MainCPU_RX_Buffer[MAINCPU_RX_BUFF_SIZE];
//char MainCPU_TX_Buffer[MAINCPU_TX_BUFF_SIZE];
Parsed_MSG_Struct Parsed_MSG;

/*
void MainCPU_CommLine_Init(void)
{

	LL_GPIO_InitTypeDef GPIO_InitStruct;
  LL_USART_InitTypeDef USART_InitStruct;
	LL_DMA_InitTypeDef DMA_InitStruct;
	
	memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
	memset(MainCPU_TX_Buffer, 0, sizeof(MainCPU_TX_Buffer));

  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;					//UART3 TX pin.
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;					//UART3 RX pin.
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	LL_USART_Disable(USART3);
	LL_USART_DisableDMAReq_RX(USART3);
	LL_USART_DisableDMAReq_TX(USART3);

  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART3, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART3, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART3, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART3);
  LL_USART_ConfigAsyncMode(USART3);
	
	LL_USART_DisableOverrunDetect(USART3);
	
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
	
	DMA_InitStruct.PeriphOrM2MSrcAddress  = LL_USART_DMA_GetRegAddr(USART3, LL_USART_DMA_REG_DATA_RECEIVE);
  DMA_InitStruct.MemoryOrM2MDstAddress  = (uint32_t) &MainCPU_RX_Buffer;
  DMA_InitStruct.Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DMA_InitStruct.Mode                   = LL_DMA_MODE_CIRCULAR; //LL_DMA_MODE_NORMAL;
  DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.NbData                 = (sizeof(MainCPU_RX_Buffer));
  DMA_InitStruct.PeriphRequest          = LL_DMAMUX_REQ_USART3_RX;
  DMA_InitStruct.Priority               = LL_DMA_PRIORITY_VERYHIGH;
	LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &DMA_InitStruct);
	
	DMA_InitStruct.PeriphOrM2MSrcAddress  = LL_USART_DMA_GetRegAddr(USART3, LL_USART_DMA_REG_DATA_TRANSMIT);
  DMA_InitStruct.MemoryOrM2MDstAddress  = (uint32_t) &MainCPU_TX_Buffer;
  DMA_InitStruct.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_InitStruct.Mode                   = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
  DMA_InitStruct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
  DMA_InitStruct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
  DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
  DMA_InitStruct.NbData                 = 20; //(sizeof(MainCPU_TX_Buffer));
  DMA_InitStruct.PeriphRequest          = LL_DMAMUX_REQ_USART3_TX; //LL_DMAMUX_REQ_GENERATOR0;
  DMA_InitStruct.Priority               = LL_DMA_PRIORITY_VERYHIGH;
	LL_DMA_Init(DMA1, LL_DMA_CHANNEL_2, &DMA_InitStruct);

  LL_USART_Enable(USART3);
	
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	//LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
	
//	LL_DMAMUX_EnableEventGeneration(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t Channel)
//	LL_DMAMUX_DisableEventGeneration(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t Channel)
//	LL_DMAMUX_IsEnabledEventGeneration(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t Channel)
//	LL_DMAMUX_EnableRequestGen(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t RequestGenChannel)
//	LL_DMAMUX_DisableRequestGen(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t RequestGenChannel)
//	LL_DMAMUX_IsEnabledRequestGen(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t RequestGenChannel)
//	LL_DMAMUX_SetRequestGenPolarity(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t RequestGenChannel,uint32_t Polarity)
//	LL_DMAMUX_SetGenRequestNb(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t RequestGenChannel,uint32_t RequestNb)
//	LL_DMAMUX_SetRequestSignalID(DMAMUX_Channel_TypeDef *DMAMUXx, uint32_t RequestGenChannel,uint32_t RequestSignalID)
	
	
	LL_USART_EnableDMAReq_RX(USART3);
	LL_USART_EnableDMAReq_TX(USART3);

  while((!(LL_USART_IsActiveFlag_TEACK(USART3))) || (!(LL_USART_IsActiveFlag_REACK(USART3))))
  {
  }

}
*/
//-------------------------------------------------------------------------------------
/*
MSG_RCIV_Result MainCPU_Message_Buffering(void)				//Version 1
{
	uint8_t *MSG_Start = 0;
	uint8_t *MSG_End = 0;
	char Main_MSG[MSG_FRAME_BUFF_SIZE];
	uint8_t Main_MSG_Len = 0;
	uint8_t MSG_Data_Len = 0;
	uint8_t MSG_Packet_Len = 0;
	uint16_t MSG_CRC = 0;
	static uint8_t *Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
	uint32_t Bytes_ToEND = 0;
	MSG_RCIV_Result Result = None;
	static uint8_t *Extra_Buffer = 0;
	CoProc_MSG_Struct Message;
	static uint8_t Wait = 0;
	
	memset(Main_MSG, 0, sizeof(Main_MSG));
	memset(&Message, 0, sizeof(Message));
	
	Bytes_ToEND = (uint32_t)&MainCPU_RX_Buffer[299] - (uint32_t)Next_Packet_SOP;
	
	//MSG_Start = (uint8_t *)strstr(MainCPU_RX_Buffer, "U\1");
	//MSG_Start = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, 'U', sizeof(MainCPU_RX_Buffer)), "U\1");
	MSG_Start = (uint8_t *)memchr(Next_Packet_SOP, 'U', Bytes_ToEND); 	//sizeof(MainCPU_RX_Buffer)		//MSG_Start = (uint8_t *)memchr(MainCPU_RX_Buffer, 'U', sizeof(MainCPU_RX_Buffer));
	if(MSG_Start != 0)
	{
		if( (uint8_t *)memchr(MSG_Start+1, CoProc_Num, 1) != 0 )
		{
			__NOP;
		}
		else 
		{
			Next_Packet_SOP = MSG_Start + 1;
			MSG_Start = 0;
		}
	}
	if(MSG_Start != 0)
	{
//		LL_mDelay(20);
		if(Wait == 0) {Wait = 1; return Waiting;}
		else if(Wait == 1) {Wait = 0;}
		
		MSG_End = (uint8_t *)strstr(memchr((char *)MSG_Start, '\r', MSG_FRAME_BUFF_SIZE), "\r\n"); //(uint8_t *)strstr((char *)MSG_Start+1, "\r\n");
		if(MSG_End == 0)
		{
			if(Bytes_ToEND < MSG_FRAME_BUFF_SIZE)
			{
				memcpy(Main_MSG, MSG_Start, Bytes_ToEND);
			}
			//memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
			Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(MainCPU_RX_Buffer));
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
			LL_mDelay(50);
			MSG_End = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, '\r', (MSG_FRAME_BUFF_SIZE-Bytes_ToEND)), "\r\n");
			if((MSG_End != 0) && (MSG_End < MSG_Start))
			{
				memcpy(Main_MSG+Bytes_ToEND, MainCPU_RX_Buffer, (MSG_FRAME_BUFF_SIZE-Bytes_ToEND));
				Next_Packet_SOP = MSG_End+2;
				MSG_Packet_Len = Bytes_ToEND + ((MSG_End+2) - (uint8_t *)MainCPU_RX_Buffer);
				memset(MSG_Start, 0, 2);
				MSG_Start = (uint8_t *)Main_MSG;
				MSG_End = (uint8_t *)strstr(memchr(Main_MSG, '\r', MSG_FRAME_BUFF_SIZE), "\r\n");
			}
			
//			Result = 0;
		}
		else
		{
			Next_Packet_SOP = MSG_End+2;
			MSG_Packet_Len = (MSG_End+2)-MSG_Start;
		}
	
		//MSG_Start = (uint8_t *)memchr((char *)MSG_Start, 1, 2); //MSG_Start = (uint8_t *)strstr((char *)MSG_Start, "U\1");
		if(memchr((char *)MSG_Start, CoProc_Num, 2) != 0)
		{
			//memset(Main_MSG, 0, sizeof(Main_MSG));
			if(MSG_End > MSG_Start)
			{
			memcpy(Main_MSG, MSG_Start, ((MSG_End - 2) - MSG_Start));
			Main_MSG_Len = (MSG_End - 2) - MSG_Start;
			MSG_Data_Len = *(MSG_Start + 4);
			MSG_CRC = *(MSG_End-2);
			MSG_CRC = MSG_CRC << 8;
			MSG_CRC |= *(MSG_End-1);
			}
			else if(MSG_End < MSG_Start)
			{
			//memcpy(Main_MSG, MSG_Start, ((MSG_End - 2) - MSG_Start));
			Main_MSG_Len = (MSG_End - 2) - MSG_Start;
			MSG_Data_Len = *(MSG_Start + 4);
			MSG_CRC = *(MSG_End-2);
			MSG_CRC = MSG_CRC << 8;
			MSG_CRC |= *(MSG_End-1);
			}
			
			//if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) == MSG_CRC)
			if(1)
			{
				Message.Packet_Token = Main_MSG[0];
				Message.Co_Num = Main_MSG[1];
				Message.Command = Main_MSG[2];
				Message.Operation = Main_MSG[3];
				Message.data_lenght = Main_MSG[4];
				memcpy(Message.data, &Main_MSG[5], Main_MSG[4]);
				//Message.Result = ;
				MainCPU_Message_Parsing(Message);
				memset(MSG_Start, 0, MSG_Packet_Len);
				Result = OK_Send_ACK; //strcpy(MainCPU_TX_Buffer, "OK.\r\n");
			}
			else if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) != MSG_CRC)
			{
				memset(MSG_Start, 0, MSG_Packet_Len);
				//strcpy(MainCPU_TX_Buffer, "CRC Failed.\r\n");
				//LL_mDelay(20);
				Result = CRC_NOK;
			}
		}
		else
		{
			memset(MSG_Start, 0, MSG_Packet_Len);
			//strcpy(MainCPU_TX_Buffer, "Wrong message.\r\n");
			//LL_mDelay(20);
			Result = Invalid;
		}
	
	}
	
	if(LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1) < 50)		// && ((Next_Packet_SOP - (uint8_t *)MainCPU_RX_Buffer) > 250)
	{
		if(strstr(MainCPU_RX_Buffer, "U\1") != 0)
		{
			Extra_Buffer = malloc(sizeof(MainCPU_RX_Buffer));
			memcpy(Extra_Buffer, MainCPU_RX_Buffer, sizeof(MainCPU_RX_Buffer));
		}
		memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(MainCPU_RX_Buffer));
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	}
	
	return Result;			
		
} */
//-------------------------------------------------------------------------------------
/*
MSG_RCIV_Result MainCPU_Message_Buffering(void)				//Version 2
{
	uint8_t *MSG_Start = 0;
	uint8_t *MSG_End = 0;
	char Main_MSG[MSG_FRAME_BUFF_SIZE];
	uint8_t Main_MSG_Len = 0;
	uint8_t MSG_Data_Len = 0;
	uint8_t MSG_Packet_Len = 0;
	uint16_t MSG_CRC = 0;
	static uint8_t *Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
	uint32_t Bytes_ToEND = 0;
	MSG_RCIV_Result Result = None;
	static uint8_t *Extra_Buffer = 0;
	CoProc_MSG_Struct Message;
	static uint8_t Wait = 0;
	
	memset(Main_MSG, 0, sizeof(Main_MSG));
	memset(&Message, 0, sizeof(Message));
	
	if((uint32_t)Next_Packet_SOP > (uint32_t)&MainCPU_RX_Buffer[299])
	{
		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
	}
	
	Bytes_ToEND = ( (uint32_t)&MainCPU_RX_Buffer[299] - (uint32_t)Next_Packet_SOP ) + 1;
	
	if(*Next_Packet_SOP!='U' && *Next_Packet_SOP!=0)
	{
		__NOP;
	}
	
	//MSG_Start = (uint8_t *)strstr(MainCPU_RX_Buffer, "U\1");
	//MSG_Start = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, 'U', sizeof(MainCPU_RX_Buffer)), "U\1");
	MSG_Start = (uint8_t *)memchr(Next_Packet_SOP, 'U', Bytes_ToEND); 	//sizeof(MainCPU_RX_Buffer)		//MSG_Start = (uint8_t *)memchr(MainCPU_RX_Buffer, 'U', sizeof(MainCPU_RX_Buffer));
	if(MSG_Start != 0)
	{
		if(MSG_Start == (uint8_t *)&MainCPU_RX_Buffer[299])
		{
			if( memchr(&MainCPU_RX_Buffer[0], CoProc_Num, 1) != 0 )
			{
				__NOP;
			}
			else 
			{
				if(Wait == 1)
				{
					Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
					MSG_Start = 0;
				}
			}
		}
		else if( memchr(MSG_Start+1, CoProc_Num, 1) != 0 )
		{
			__NOP;
		}
		else 
		{
			if(Wait == 1)
			{
				Next_Packet_SOP = MSG_Start + 1;
				MSG_Start = 0;
			}
		}
	}
	if(MSG_Start != 0)
	{
//		LL_mDelay(20);
		if(Wait == 0) {Wait = 1; return Waiting;}
		else if(Wait == 1) {Wait = 0;}
		
		MSG_End = (uint8_t *)strstr(memchr((char *)MSG_Start, '\r', MSG_FRAME_BUFF_SIZE), "\r\n"); //(uint8_t *)strstr((char *)MSG_Start+1, "\r\n");
		if(MSG_End == 0)
		{
			if(Bytes_ToEND < MSG_FRAME_BUFF_SIZE)
			{
				memcpy(Main_MSG, MSG_Start, Bytes_ToEND);
				MSG_End = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, '\r', (MSG_FRAME_BUFF_SIZE-Bytes_ToEND)), "\r\n");
			}
			//memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
			Next_Packet_SOP = MSG_Start + 1; //(uint8_t *)MainCPU_RX_Buffer;
			//LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
			//LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(MainCPU_RX_Buffer));
			//LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
			//LL_mDelay(50);
			//////MSG_End = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, '\r', (MSG_FRAME_BUFF_SIZE-Bytes_ToEND)), "\r\n");
			if((MSG_End != 0) && (MSG_End < MSG_Start))
			{
				memcpy(Main_MSG+Bytes_ToEND, MainCPU_RX_Buffer, (MSG_End-(uint8_t *)MainCPU_RX_Buffer)+2);
				Next_Packet_SOP = MSG_End+2;
				MSG_Packet_Len = Bytes_ToEND + ((MSG_End+2) - (uint8_t *)MainCPU_RX_Buffer);
				memset(MSG_Start, 0, Bytes_ToEND);
				memset(MainCPU_RX_Buffer, 0, (MSG_End-(uint8_t *)MainCPU_RX_Buffer)+2);
				MSG_Start = (uint8_t *)Main_MSG;
				MSG_End = (uint8_t *)strstr(memchr(Main_MSG, '\r', MSG_FRAME_BUFF_SIZE), "\r\n");
			}
			
//			Result = 0;
		}
		else
		{
			Next_Packet_SOP = MSG_End+2;
			MSG_Packet_Len = (MSG_End+2)-MSG_Start;
		}
	
		//MSG_Start = (uint8_t *)memchr((char *)MSG_Start, 1, 2); //MSG_Start = (uint8_t *)strstr((char *)MSG_Start, "U\1");
		if(memchr((char *)MSG_Start, CoProc_Num, 2) != 0)
		{
			//memset(Main_MSG, 0, sizeof(Main_MSG));
			if(MSG_End > MSG_Start)
			{
			memcpy(Main_MSG, MSG_Start, ((MSG_End - 2) - MSG_Start));
			Main_MSG_Len = (MSG_End - 2) - MSG_Start;
			MSG_Data_Len = *(MSG_Start + 4);
			MSG_CRC = *(MSG_End-2);
			MSG_CRC = MSG_CRC << 8;
			MSG_CRC |= *(MSG_End-1);
			}
			else if(MSG_End < MSG_Start)
			{
			//memcpy(Main_MSG, MSG_Start, ((MSG_End - 2) - MSG_Start));
			Main_MSG_Len = (MSG_End - 2) - MSG_Start;
			MSG_Data_Len = *(MSG_Start + 4);
			MSG_CRC = *(MSG_End-2);
			MSG_CRC = MSG_CRC << 8;
			MSG_CRC |= *(MSG_End-1);
			}
			
			//if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) == MSG_CRC)
			if(1)
			{
				Message.Packet_Token = Main_MSG[0];
				Message.Co_Num = Main_MSG[1];
				Message.Command = Main_MSG[2];
				Message.Operation = Main_MSG[3];
				Message.data_lenght = Main_MSG[4];
				memcpy(Message.data, &Main_MSG[5], Main_MSG[4]);
				//Message.Result = ;
				MainCPU_Message_Parsing(Message);
				memset(MSG_Start, 0, MSG_Packet_Len);
				Result = OK_Send_ACK; //strcpy(MainCPU_TX_Buffer, "OK.\r\n");
			}
			else if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) != MSG_CRC)
			{
				memset(MSG_Start, 0, MSG_Packet_Len);
				//strcpy(MainCPU_TX_Buffer, "CRC Failed.\r\n");
				//LL_mDelay(20);
				Result = CRC_NOK;
			}
		}
		else
		{
			memset(MSG_Start, 0, MSG_Packet_Len);
			//strcpy(MainCPU_TX_Buffer, "Wrong message.\r\n");
			//LL_mDelay(20);
			Result = Invalid;
		}
	
	}
	
	if(LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1) < 50)		// && ((Next_Packet_SOP - (uint8_t *)MainCPU_RX_Buffer) > 250)
	{
//		if(strstr(MainCPU_RX_Buffer, "U\3") != 0)
//		{
//			Extra_Buffer = malloc(sizeof(MainCPU_RX_Buffer));
//			memcpy(Extra_Buffer, MainCPU_RX_Buffer, sizeof(MainCPU_RX_Buffer));
//		}
//		memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
//		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
//		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
//		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(MainCPU_RX_Buffer));
//		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	}
	
//	if((uint32_t)Next_Packet_SOP > (uint32_t)&MainCPU_RX_Buffer[299])		// && ((Next_Packet_SOP - (uint8_t *)MainCPU_RX_Buffer) > 250)
//	{
//		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
//	}
	
	return Result;			
		
} */
//-------------------------------------------------------------------------------------
/*
MSG_RCIV_Result MainCPU_Message_Buffering(void)			//Version 3
{
	uint8_t *MSG_Start = 0;
	uint8_t *MSG_End = 0;
	uint8_t *MSG_Read = 0;
	char Main_MSG[MSG_FRAME_BUFF_SIZE];
	uint8_t Main_MSG_Len = 0;
	uint8_t MSG_Data_Len = 0;
	uint8_t MSG_Packet_Len = 0;
	uint16_t MSG_CRC = 0;
	static uint8_t *Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
	uint32_t Bytes_ToEND = 0;
	MSG_RCIV_Result Result = None;
	static uint8_t *Extra_Buffer = 0;
	CoProc_MSG_Struct Message;
	static uint8_t Wait = 0;
	uint8_t Copy_Loop = 0;

	memset(Main_MSG, 0, sizeof(Main_MSG));
	memset(&Message, 0, sizeof(Message));

	if((uint32_t)Next_Packet_SOP > (uint32_t)&MainCPU_RX_Buffer[299])
	{
		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
	}

	Bytes_ToEND = ( (uint32_t)&MainCPU_RX_Buffer[299] - (uint32_t)Next_Packet_SOP ) + 1;

	//MSG_Start = (uint8_t *)strstr(MainCPU_RX_Buffer, "U\1");
	//MSG_Start = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, 'U', sizeof(MainCPU_RX_Buffer)), "U\1");
	MSG_Start = (uint8_t *)memchr(Next_Packet_SOP, 'U', Bytes_ToEND); 	//sizeof(MainCPU_RX_Buffer)		//MSG_Start = (uint8_t *)memchr(MainCPU_RX_Buffer, 'U', sizeof(MainCPU_RX_Buffer));
	if(MSG_Start == 0) {MSG_Start = (uint8_t *)memchr(MainCPU_RX_Buffer, 'U', (Next_Packet_SOP-(uint8_t *)&MainCPU_RX_Buffer[0]) );}
	if(MSG_Start != 0)
	{
		LL_mDelay(1);
		if(MSG_Start == (uint8_t *)&MainCPU_RX_Buffer[299])
		{
			if( memchr(&MainCPU_RX_Buffer[0], CoProc_Num, 1) != 0 )
			{
				__NOP;
			}
			else
			{
				if(Wait == 1)
				{
					Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
					MSG_Start = 0;
				}
			}
		}
		else if( memchr(MSG_Start+1, CoProc_Num, 1) != 0 )
		{
			__NOP;
		}
		else
		{
			if(Wait == 1)
			{
				Next_Packet_SOP = MSG_Start + 1;
				MSG_Start = 0;
			}
		}
	}
	if(MSG_Start != 0)
	{
//		LL_mDelay(20);
		if(Wait == 0) {Wait = 1; return Waiting;}
		else if(Wait == 1) {Wait = 0;}

		MSG_Read = MSG_Start;

		for(Copy_Loop=0; Copy_Loop<MSG_FRAME_BUFF_SIZE; Copy_Loop++)
		{
			Main_MSG[Copy_Loop] = (char)*MSG_Read;
			MSG_Read++;
			if(MSG_Read > (uint8_t *)&MainCPU_RX_Buffer[299]) {MSG_Read = (uint8_t *)MainCPU_RX_Buffer;}
			if(*MSG_Read == '\r')
			{
				if(MSG_Read+1 > (uint8_t *)&MainCPU_RX_Buffer[299])
				{
					if(MainCPU_RX_Buffer[0] == '\n')
						{
							MSG_End=MSG_Read;
							strcpy(&Main_MSG[Copy_Loop+1], "\r\n");
							Copy_Loop = Copy_Loop + 2;
							break;
						}
				}
				else
				{
					if(*(MSG_Read+1) == '\n')
						{
							MSG_End=MSG_Read;
							strcpy(&Main_MSG[Copy_Loop+1], "\r\n");
							Copy_Loop = Copy_Loop + 2;
							break;
						}
				}
			}
		}

		if(MSG_End != 0)
		{
			if(MSG_Start < MSG_End)
			{
				memset(MSG_Start, 0, (MSG_End-MSG_Start)+2);
			}
			else if(MSG_Start > MSG_End)
			{
				memset(MSG_Start, 0, ((uint8_t *)&MainCPU_RX_Buffer[299]-MSG_Start)+1);
				memset(&MainCPU_RX_Buffer[0], 0, (MSG_End-(uint8_t *)&MainCPU_RX_Buffer[0])+2 );
			}

			Next_Packet_SOP = MSG_End+2;
			MSG_Packet_Len = Copy_Loop;
			MSG_Start = (uint8_t *)Main_MSG;
			MSG_End = (uint8_t *)strstr(memchr(Main_MSG, '\r', MSG_FRAME_BUFF_SIZE), "\r\n");
		}

		//MSG_End = (uint8_t *)strstr(memchr((char *)MSG_Start, '\r', MSG_FRAME_BUFF_SIZE), "\r\n"); //(uint8_t *)strstr((char *)MSG_Start+1, "\r\n");
		if(MSG_End == 0)
		{
			//memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
			Next_Packet_SOP = MSG_Start + 1; //(uint8_t *)MainCPU_RX_Buffer;
			//////MSG_End = (uint8_t *)strstr(memchr(MainCPU_RX_Buffer, '\r', (MSG_FRAME_BUFF_SIZE-Bytes_ToEND)), "\r\n");

//			Result = 0;
		}

		//MSG_Start = (uint8_t *)memchr((char *)MSG_Start, 1, 2); //MSG_Start = (uint8_t *)strstr((char *)MSG_Start, "U\1");
		if(memchr((char *)MSG_Start, CoProc_Num, 2) != 0)
		{
			//memset(Main_MSG, 0, sizeof(Main_MSG));
			if(MSG_End > MSG_Start)
			{
			//memcpy(Main_MSG, MSG_Start, ((MSG_End - 2) - MSG_Start));
			Main_MSG_Len = (MSG_End - 2) - MSG_Start;
			MSG_Data_Len = *(MSG_Start + 4);
			MSG_CRC = *(MSG_End-2);
			MSG_CRC = MSG_CRC << 8;
			MSG_CRC |= *(MSG_End-1);
			}


			//if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) == MSG_CRC)
			if(1)
			{
				Message.Packet_Token = Main_MSG[0];
				Message.Co_Num = Main_MSG[1];
				Message.Command = Main_MSG[2];
				Message.Operation = Main_MSG[3];
				Message.data_lenght = Main_MSG[4];
				memcpy(Message.data, &Main_MSG[5], Main_MSG[4]);
				//Message.Result = ;
				MainCPU_Message_Parsing(Message);
				memset(MSG_Start, 0, MSG_Packet_Len);
				Result = OK_Send_ACK; //strcpy(MainCPU_TX_Buffer, "OK.\r\n");
			}
			else if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) != MSG_CRC)
			{
				//memset(MSG_Start, 0, MSG_Packet_Len);
				//strcpy(MainCPU_TX_Buffer, "CRC Failed.\r\n");
				//LL_mDelay(20);
				Result = CRC_NOK;
			}
		}
		else
		{
			memset(MSG_Start, 0, MSG_Packet_Len);
			//strcpy(MainCPU_TX_Buffer, "Wrong message.\r\n");
			//LL_mDelay(20);
			Result = Invalid;
		}

	}

	if(LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1) < 50)		// && ((Next_Packet_SOP - (uint8_t *)MainCPU_RX_Buffer) > 250)
	{
//		if(strstr(MainCPU_RX_Buffer, "U\3") != 0)
//		{
//			Extra_Buffer = malloc(sizeof(MainCPU_RX_Buffer));
//			memcpy(Extra_Buffer, MainCPU_RX_Buffer, sizeof(MainCPU_RX_Buffer));
//		}
//		memset(MainCPU_RX_Buffer, 0, sizeof(MainCPU_RX_Buffer));
//		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
//		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
//		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(MainCPU_RX_Buffer));
//		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	}

//	if((uint32_t)Next_Packet_SOP > (uint32_t)&MainCPU_RX_Buffer[299])		// && ((Next_Packet_SOP - (uint8_t *)MainCPU_RX_Buffer) > 250)
//	{
//		Next_Packet_SOP = (uint8_t *)MainCPU_RX_Buffer;
//	}

	return Result;

}
*/
//-------------------------------------------------------------------------------------

MSG_RCIV_Result Message_Buffering(uint8_t *RX_Buffer)			//Version 3 (Revision 1) (for this project.)
{
	uint8_t *MSG_Start = 0;
	uint8_t *MSG_End = 0;
	uint8_t *MSG_Read = 0;
	char Main_MSG[MSG_FRAME_BUFF_SIZE];
	uint8_t Main_MSG_Len = 0;
	uint8_t MSG_Data_Len = 0;
	uint8_t MSG_Packet_Len = 0;
	uint16_t MSG_CRC = 0;
//	static uint8_t *Next_Packet_SOP = (uint8_t *)RX_Buffer;
	uint8_t *Next_Packet_SOP = 0;
	uint32_t Bytes_ToEND = 0;
	MSG_RCIV_Result Result = None;
	static uint8_t *Extra_Buffer = 0;
	CoProc_MSG_Struct Message;
	static uint8_t Wait = 0;
	uint8_t Copy_Loop = 0;
	uint16_t Last_Index = sizeof(RX_Buffer)-1;
	
	*Next_Packet_SOP = RX_Buffer;

	memset(Main_MSG, 0, sizeof(Main_MSG));
	memset(&Message, 0, sizeof(Message));
	
	if((uint32_t)Next_Packet_SOP > (uint32_t)&RX_Buffer[Last_Index])
	{
		Next_Packet_SOP = (uint8_t *)RX_Buffer;
	}
	
	Bytes_ToEND = ( (uint32_t)&RX_Buffer[Last_Index] - (uint32_t)Next_Packet_SOP ) + 1;
	
	//MSG_Start = (uint8_t *)strstr(RX_Buffer, "U\1");
	//MSG_Start = (uint8_t *)strstr(memchr(RX_Buffer, 'U', sizeof(RX_Buffer)), "U\1");
	MSG_Start = (uint8_t *)memchr(Next_Packet_SOP, 'U', Bytes_ToEND); 	//sizeof(RX_Buffer)		//MSG_Start = (uint8_t *)memchr(RX_Buffer, 'U', sizeof(RX_Buffer));
	if(MSG_Start == 0) {MSG_Start = (uint8_t *)memchr(RX_Buffer, 'U', (Next_Packet_SOP-(uint8_t *)&RX_Buffer[0]) );}
	if(MSG_Start != 0)
	{
		LL_mDelay(1);
		if(MSG_Start == (uint8_t *)&RX_Buffer[Last_Index])
		{
			if( memchr(&RX_Buffer[0], CoProc_Num, 1) != 0 )
			{
				__NOP();

			}
			else 
			{
				if(Wait == 1)
				{
					Next_Packet_SOP = (uint8_t *)RX_Buffer;
					MSG_Start = 0;
				}
			}
		}
		else if( memchr(MSG_Start+1, CoProc_Num, 1) != 0 )
		{
			__NOP();
		}
		else 
		{
			if(Wait == 1)
			{
				Next_Packet_SOP = MSG_Start + 1;
				MSG_Start = 0;
			}
		}
	}
	if(MSG_Start != 0)
	{
//		LL_mDelay(20);
		if(Wait == 0) {Wait = 1; return Waiting;}
		else if(Wait == 1) {Wait = 0;}
		
		MSG_Read = MSG_Start;
		
		for(Copy_Loop=0; Copy_Loop<MSG_FRAME_BUFF_SIZE; Copy_Loop++)
		{
			Main_MSG[Copy_Loop] = (char)*MSG_Read;
			MSG_Read++;
			if(MSG_Read > (uint8_t *)&RX_Buffer[Last_Index]) {MSG_Read = (uint8_t *)RX_Buffer;}
			if(*MSG_Read == '\r')
			{
				if(MSG_Read+1 > (uint8_t *)&RX_Buffer[Last_Index])
				{
					if(RX_Buffer[0] == '\n')
						{
							MSG_End=MSG_Read;
							strcpy(&Main_MSG[Copy_Loop+1], "\r\n");
							Copy_Loop = Copy_Loop + 2;
							break;
						}
				}
				else
				{
					if(*(MSG_Read+1) == '\n')
						{
							MSG_End=MSG_Read;
							strcpy(&Main_MSG[Copy_Loop+1], "\r\n");
							Copy_Loop = Copy_Loop + 2;
							break;
						}
				}
			}
		}
		
		if(MSG_End != 0)
		{
			if(MSG_Start < MSG_End)
			{
				memset(MSG_Start, 0, (MSG_End-MSG_Start)+2);
			}
			else if(MSG_Start > MSG_End)
			{
				memset(MSG_Start, 0, ((uint8_t *)&RX_Buffer[Last_Index]-MSG_Start)+1);
				memset(&RX_Buffer[0], 0, (MSG_End-(uint8_t *)&RX_Buffer[0])+2 );
			}
			
			Next_Packet_SOP = MSG_End+2;
			MSG_Packet_Len = Copy_Loop;
			MSG_Start = (uint8_t *)Main_MSG;
			MSG_End = (uint8_t *)strstr(memchr(Main_MSG, '\r', MSG_FRAME_BUFF_SIZE), "\r\n");
		}
		
		//MSG_End = (uint8_t *)strstr(memchr((char *)MSG_Start, '\r', MSG_FRAME_BUFF_SIZE), "\r\n"); //(uint8_t *)strstr((char *)MSG_Start+1, "\r\n");
		if(MSG_End == 0)
		{
			//memset(RX_Buffer, 0, sizeof(RX_Buffer));
			Next_Packet_SOP = MSG_Start + 1; //(uint8_t *)RX_Buffer;
			//////MSG_End = (uint8_t *)strstr(memchr(RX_Buffer, '\r', (MSG_FRAME_BUFF_SIZE-Bytes_ToEND)), "\r\n");
			
//			Result = 0;
		}
	
		//MSG_Start = (uint8_t *)memchr((char *)MSG_Start, 1, 2); //MSG_Start = (uint8_t *)strstr((char *)MSG_Start, "U\1");
		if(memchr((char *)MSG_Start, CoProc_Num, 2) != 0)
		{
			//memset(Main_MSG, 0, sizeof(Main_MSG));
			if(MSG_End > MSG_Start)
			{
			//memcpy(Main_MSG, MSG_Start, ((MSG_End - 2) - MSG_Start));
			Main_MSG_Len = (MSG_End - 2) - MSG_Start;
			MSG_Data_Len = *(MSG_Start + 4);
			MSG_CRC = *(MSG_End-2);
			MSG_CRC = MSG_CRC << 8;
			MSG_CRC |= *(MSG_End-1);
			}
			
			
			//if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) == MSG_CRC)
			if(1)
			{
				Message.Packet_Token = Main_MSG[0];
				Message.Co_Num = Main_MSG[1];
				Message.Command = Main_MSG[2];
				Message.Operation = Main_MSG[3];
				Message.data_lenght = Main_MSG[4];
				memcpy(Message.data, &Main_MSG[5], Main_MSG[4]);
				//Message.Result = ;
				MainCPU_Message_Parsing(Message);
				memset(MSG_Start, 0, MSG_Packet_Len);
				Result = OK_Send_ACK; //strcpy(MainCPU_TX_Buffer, "OK.\r\n");
			}
			else if(b_CRC_16_X25_fw(Main_MSG, Main_MSG_Len) != MSG_CRC)
			{
				//memset(MSG_Start, 0, MSG_Packet_Len);
				//strcpy(MainCPU_TX_Buffer, "CRC Failed.\r\n");
				//LL_mDelay(20);
				Result = CRC_NOK;
			}
		}
		else
		{
			memset(MSG_Start, 0, MSG_Packet_Len);
			//strcpy(MainCPU_TX_Buffer, "Wrong message.\r\n");
			//LL_mDelay(20);
			Result = Invalid;
		}
	
	}
	
//	if(LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_1) < 50)		// && ((Next_Packet_SOP - (uint8_t *)RX_Buffer) > 250)
//	{
//		if(strstr(RX_Buffer, "U\3") != 0)
//		{
//			Extra_Buffer = malloc(sizeof(RX_Buffer));
//			memcpy(Extra_Buffer, RX_Buffer, sizeof(RX_Buffer));
//		}
//		memset(RX_Buffer, 0, sizeof(RX_Buffer));
//		Next_Packet_SOP = (uint8_t *)RX_Buffer;
//		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
//		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sizeof(RX_Buffer));
//		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
//	}
	
//	if((uint32_t)Next_Packet_SOP > (uint32_t)&RX_Buffer[Last_Index])		// && ((Next_Packet_SOP - (uint8_t *)RX_Buffer) > 250)
//	{
//		Next_Packet_SOP = (uint8_t *)RX_Buffer;
//	}
	
	return Result;			
		
}
//-------------------------------------------------------------------------------------

Parsed_MSG_Struct MainCPU_Message_Parsing(CoProc_MSG_Struct Message)
{
	Parsed_MSG_Struct MSG;
	
	memset(&MSG, 0, sizeof(MSG));
	memset(&Parsed_MSG, 0, sizeof(Parsed_MSG));
	
	if(Message.Command == C_BATT_Charger)
	{
		MSG.Command = C_BATT_Charger;
		if(Message.Operation == O_ON) {MSG.Operation = O_ON;}
		else if(Message.Operation == O_OFF) {MSG.Operation = O_OFF;}
		else if(Message.Operation == O_STATUS) {MSG.Operation = O_STATUS;}
	}
	
	if(Message.Command == C_Siren)
	{
		MSG.Command = C_Siren;
		if(Message.Operation == O_ON) {MSG.Operation = O_ON;}
		else if(Message.Operation == O_OFF) {MSG.Operation = O_OFF;}
		else if(Message.Operation == O_STATUS) {MSG.Operation = O_STATUS;}
	}
	
	if(Message.Command == C_Sound_Line)
	{
		MSG.Command = C_Sound_Line;
		if(Message.Operation == O_CONFIG) {MSG.Operation = O_CONFIG;}
		else if(Message.Operation == O_STATUS) {MSG.Operation = O_STATUS;}
	}
	
	if(Message.Command == C_Relay)
	{
		MSG.Command = C_Relay;
		if(Message.Operation == O_ON) {MSG.Operation = O_ON;}
		else if(Message.Operation == O_OFF) {MSG.Operation = O_OFF;}
		else if(Message.Operation == O_STATUS) {MSG.Operation = O_STATUS;}
	}
	
	if( (Message.Command == C_Battery)||(Message.Command == C_AC)||(Message.Command == C_ExtSpeaker)||(Message.Command == C_Siren)||(Message.Command == C_AUX)||(Message.Command == C_VDD) )
	{
		MSG.Command = Message.Command;
		if(Message.Operation == O_STATUS) {MSG.Operation = O_STATUS;}
	}
	
	MSG.data_lenght = Message.data_lenght;
	memcpy(MSG.data, Message.data, sizeof(MSG.data));
	
	MSG.New_MSG = 1;
	Parsed_MSG = MSG;
	return MSG;
}
	
//-------------------------------------------------------------------------------------

void MainCPU_Message_Maker(CoProc1_Command_Type COM, CoProc1_Operation_Type OP, char *Data, uint8_t Data_Len, CoProc1_Result_Type Result)
{/*
	int CRC_Calc = 0;
	uint8_t CRC_Len = 0;
	
	memset(MainCPU_TX_Buffer, 0, sizeof(MainCPU_TX_Buffer));
	MainCPU_TX_Buffer[0] = 'U';
	MainCPU_TX_Buffer[1] = CoProc_Num;
	MainCPU_TX_Buffer[2] = COM;
	MainCPU_TX_Buffer[3] = OP;
	//MainCPU_TX_Buffer[4] = sprintf(&MainCPU_TX_Buffer[5], "%s", Data);
	MainCPU_TX_Buffer[4] = Data_Len;
	memcpy(&MainCPU_TX_Buffer[5], Data, Data_Len);
	MainCPU_TX_Buffer[4 + MainCPU_TX_Buffer[4] + 1] = Result;
	CRC_Len = 5 + MainCPU_TX_Buffer[4] + 1;
	CRC_Calc = b_CRC_16_X25_fw(MainCPU_TX_Buffer, CRC_Len);
	MainCPU_TX_Buffer[CRC_Len] = CRC_Calc>>8;
	MainCPU_TX_Buffer[CRC_Len+1] = CRC_Calc;
	MainCPU_TX_Buffer[CRC_Len+2] = '\r';
	MainCPU_TX_Buffer[CRC_Len+3] = '\n';
	*/
}
//-------------------------------------------------------------------------------------

void MainCPU_Message_Sender(void)
{/*
	uint8_t *MSG_Start = 0;
	uint8_t *MSG_End = 0;
	uint8_t MSG_Packet_Len = 0;
	
	MSG_Start = (uint8_t *)memchr(MainCPU_TX_Buffer, 'U', sizeof(MainCPU_TX_Buffer));
	if(MSG_Start != 0)
	{
		MSG_End = (uint8_t *)strstr(memchr((char *)MSG_Start, '\r', MSG_FRAME_BUFF_SIZE), "\r\n");
	}
	if(MSG_End != 0)
	{
		MSG_Packet_Len = (MSG_End+2)-MSG_Start;
	}
	
	if(MSG_Packet_Len != 0)
	{
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
		//LL_DMA_SetMemoryAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress);
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, MSG_Packet_Len);
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
		LL_mDelay(20);
		memset(MainCPU_TX_Buffer, 0, sizeof(MainCPU_TX_Buffer));
	}
	*/
//	if(strlen(MainCPU_TX_Buffer) != 0)
//	{
//		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
//		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, strlen(MainCPU_TX_Buffer));
//		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
//		LL_mDelay(20);
//		memset(MainCPU_TX_Buffer, 0, sizeof(MainCPU_TX_Buffer));
//	}
	
	
}
//-------------------------------------------------------------------------------------


