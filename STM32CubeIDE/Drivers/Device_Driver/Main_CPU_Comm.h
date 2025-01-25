#ifndef MAIN_CPU_COMM_H
#define MAIN_CPU_COMM_H

//#include "stm32g0xx_ll_rcc.h"
//#include "stm32g0xx_ll_bus.h"
//#include "stm32g0xx_ll_gpio.h"
//#include "stm32g0xx_ll_usart.h"
//#include "stm32g0xx_ll_dma.h"
//#include "stm32g0xx_ll_utils.h"
#include "stm32h5xx_ll_rcc.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

//#include "Outputs.h"
//#include "Utilities.h"

#define MAINCPU_RX_BUFF_SIZE			300
#define MAINCPU_TX_BUFF_SIZE			300
#define MSG_MAX_DATA_SIZE			30
#define MSG_FRAME_BUFF_SIZE		MSG_MAX_DATA_SIZE + 20

#define CoProc_Num		2

//extern char MainCPU_RX_Buffer[MAINCPU_RX_BUFF_SIZE];
//extern char MainCPU_TX_Buffer[MAINCPU_TX_BUFF_SIZE];
extern uint8_t LineX_RX_Buffer[1000];
extern uint8_t Line1_RX_Buffer[100];
extern uint8_t Line2_RX_Buffer[100];
extern uint8_t Line3_RX_Buffer[100];
extern uint8_t Line4_RX_Buffer[100];
extern uint8_t Line5_RX_Buffer[100];
extern uint8_t Line6_RX_Buffer[100];
extern uint8_t Line7_RX_Buffer[100];

typedef enum{
	N_MainCPU = 1,
	N_CoProcessor_2,
	N_CoProcessor_3
}Processor_Num_Type;

//typedef enum {
//		C_ACK = 1,
//		C_CRC,
//		C_Relay,
//    C_Analog,
//		C_Remote,
//    C_Zone,
//		C_Siren,
//		C_Sensor,
//    C_Speaker,
//		C_Sound_Line,
//		C_BATT_Charger,
//    C_RF_TX,
//    C_RF_RX,
//		C_Tel,
//    C_LoRa,
//    C_WiFi
//}CoProc1_Command_Type;

typedef enum {
		C_LED = 1,
		C_Keypad,
		C_Relay,
    C_TelLine,
		C_Remote,
    C_Zone,
		C_Tamper,
		C_Sensor,
		C_Device,
    C_Battery,//A
    C_AC,
    C_ExtSpeaker,
    C_Siren,
    C_AUX,
		C_VDD,//F
		C_Sound_Line,
		C_BATT_Charger,
    C_RF_TX,
    C_RF_RX,
		C_Tel,
    C_LoRa,
    C_WiFi
}CoProc1_Command_Type;

typedef enum {
    O_OFF = 1,
    O_ON,
    O_BLINK,
    O_STATUS,
    O_CONFIG,
		O_ARM,
    O_DISARM,
		O_Silent_Key,
    O_Alarm_Key,
    O_Trunk_Key,
		O_Zone_Open,
    O_Zone_Close,
    O_Sensor_Triggered,
		O_TAMPER,
    O_Learn,
		O_Sensor_Low_Battery,
    O_Get_Info,
		O_Command
}CoProc1_Operation_Type;

typedef enum{
    R_FAIL = 1,
    R_DONE,
    R_UNKNOWN,
		R_IN_PROGRESS
}CoProc1_Result_Type;

typedef struct MICRO_PCKT
{
    uint8_t Packet_Token;  //U
    Processor_Num_Type Co_Num; 
    CoProc1_Command_Type Command; 
    CoProc1_Operation_Type Operation;
    uint8_t data_lenght;
    uint8_t data[MSG_MAX_DATA_SIZE];
    CoProc1_Result_Type Result;
    //uint16_t crc_data;
}CoProc_MSG_Struct;

typedef enum
{
	None = 0,
	OK_Send_ACK,
	CRC_NOK,
	Invalid,
	No_Ending,
	Waiting
}MSG_RCIV_Result;

typedef enum
{
	OK,
}MSG_Parsing_Result;

typedef struct Parsed_MSG
{
    CoProc1_Command_Type Command;
		CoProc1_Operation_Type Operation;
		uint8_t data_lenght;
    uint8_t data[MSG_MAX_DATA_SIZE];
		uint8_t New_MSG;
}Parsed_MSG_Struct;

extern Parsed_MSG_Struct Parsed_MSG;

//void MainCPU_CommLine_Init(void);
MSG_RCIV_Result Message_Buffering(uint8_t *RX_Buffer, uint8_t *SOP);
Parsed_MSG_Struct MainCPU_Message_Parsing(CoProc_MSG_Struct Message);
void MainCPU_Message_Maker(CoProc1_Command_Type COM, CoProc1_Operation_Type OP, char *Data, uint8_t Data_Len, CoProc1_Result_Type Result);
void MainCPU_Message_Sender(void);

#endif
