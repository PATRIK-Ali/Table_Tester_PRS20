#ifndef _TABLE_TESTER_APP_H_
#define _TABLE_TESTER_APP_H_

#include "stdint.h"
#include "stm32h5xx_ll_gpio.h"

/**
 * @author  Ali Mesgari
 * @email   PATRIKAli3000@Gmail.com
 * @website
 * @link
 * @version v1.0
 * @ide     Keil uVision
 * @license
 * @brief
 *
 */

#define Power27V_Ctrl_Port		GPIOC
#define Power27V_Ctrl_Pin		LL_GPIO_PIN_13

// LCD texts
typedef enum
{
	PRSX_Page = 0,
	Modules_Page,
	FEU_Page,
	IJU_Page,
}LCD_Pages_t;

extern LCD_Pages_t LCD_Page;
extern const char LCD_Back_Str[];
extern const char LCD_PRS10_Str[];
extern const char LCD_PRS20_Str[];
extern const char LCD_PRS30_Str[];
extern const char LCD_FEU_Str[];
extern const char LCD_IJU_Str[];
extern const char LCD_PowerSupply_OFF_Str[];
extern const char LCD_PowerSupply_ON_Str[];
extern const char LCD_RX1_Str[];
extern const char LCD_RX2_Str[];
extern const char LCD_INJ_OFF_Str[];
extern const char LCD_INJ_ON_Str[];
extern const char LCD_RF_16_22_Str[];
extern const char LCD_RF_20_32_Str[];
extern const char LCD_RF_30_46_Str[];
extern const char LCD_RF_42_63_Str[];
extern const char LCD_Gain_Low_Str[];
extern const char LCD_Gain_High_Str[];
extern const char LCD_RF_OFF_Str[];
extern const char LCD_RF_ON_Str[];
extern const char LCD_Atten_Str[];
// LCD texts

//----------------------------------
extern const uint8_t RX_Bit0_RST;
extern const uint8_t RX1_Bit0; //0b11111110;
extern const uint8_t RX2_Bit0;

extern const uint8_t INJ_Bit1_RST;
extern const uint8_t INJ_OFF_Bit1; //0b11111101;
extern const uint8_t INJ_ON_Bit1;

extern const uint8_t RF_Bit2_3_RST;
extern const uint8_t RF_16_22_Bit2_3; //0b11110011;
extern const uint8_t RF_20_32_Bit2_3;
extern const uint8_t RF_30_46_Bit2_3;
extern const uint8_t RF_42_63_Bit2_3;

extern const uint8_t Gain_Bit4_RST;
extern const uint8_t Gain_Low_Bit4; //0b11101111;
extern const uint8_t Gain_High_Bit4;

extern const uint8_t RF_Bit5_RST;
extern const uint8_t RF_OFF_Bit5; //0b11011111;
extern const uint8_t RF_ON_Bit5;

extern const uint8_t Atten_Bit0_5_RST;
extern uint8_t FEU_Atten_Bit0_5;
extern uint8_t IJU_Atten_Bit0_5;
//----------------------------------

#define Start_Header	0xCA

typedef enum
{
	ID_MIU_FEU = 0,
	RES1,
	RES2,
	RES3,
	ID_MIU_IJU,
	RES5
}ID_Packet_t;

typedef struct MSG_Frame_t
{
	uint8_t Start;
	ID_Packet_t ID;
	uint8_t PCKT_0;
	uint8_t PCKT_1;
	uint8_t PCKT_2;
	uint8_t PCKT_3;
	uint8_t PCKT_4;
	uint8_t PCKT_5;
	uint8_t CRC_1;
	uint8_t CRC_2;
	uint8_t Length;
	uint8_t New;
	uint8_t Changed;
}MSG_Frame_t;

typedef enum
{
	OFF = 0,
	ON
}ON_OFF_t;

typedef enum
{
	RX_One = 1,
	RX_Two
}RX_t;

typedef enum
{
	Filter_16_22 = 0,
	Filter_20_32,
	Filter_30_46,
	Filter_42_63
}RF_Filter_t;

typedef enum
{
	Gain_Low = 0,
	Gain_High
}Gain_Path_t;

typedef struct FEU_Status_t
{
	ON_OFF_t FEU_Power_Supply;
	RX_t FEU_RX;
	ON_OFF_t FEU_INJ;
	RF_Filter_t FEU_RF_Filter;
	Gain_Path_t FEU_Gain_Path;
	ON_OFF_t FEU_RF_Power;
	uint8_t FEU_Atten;
}FEU_Status_t;

typedef struct IJU_Status_t
{
	ON_OFF_t IJU_Power_Supply;
	ON_OFF_t IJU_INJ;
	RF_Filter_t IJU_RF_Filter;
	ON_OFF_t IJU_RF_Power;
	uint8_t IJU_Atten;
}IJU_Status_t;

extern MSG_Frame_t MIU_FEU_MSG;
extern MSG_Frame_t MIU_IJU_MSG;
extern FEU_Status_t FEU_Status;
extern IJU_Status_t IJU_Status;

void Power27V_Switch(uint8_t State);
char Power27V_Status(void);
void Message_Maker(MSG_Frame_t *MSG, uint8_t *PCKT_X, uint8_t Bit_Reset_CMD, uint8_t Bit_CMD);


#endif
