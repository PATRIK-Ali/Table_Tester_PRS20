#include "Table_Tester_App.h"
#include "stm32h5xx_ll_crc.h"

// LCD texts
LCD_Pages_t LCD_Page = PRSX_Page;
const char LCD_Back_Str[] = "< Back >";
const char LCD_PRS10_Str[] = "< PRS10 >";
const char LCD_PRS20_Str[] = "< PRS20 >";
const char LCD_PRS30_Str[] = "< PRS30 >";
const char LCD_FEU_Str[] = "FEU Status:";
const char LCD_IJU_Str[] = "IJU Status:";
const char LCD_PowerSupply_OFF_Str[] = "Power Supply OFF";
const char LCD_PowerSupply_ON_Str[] = "Power Supply ON";
const char LCD_RX1_Str[] = "RX 1";
const char LCD_RX2_Str[] = "RX 2";
const char LCD_INJ_OFF_Str[] = "INJ OFF";
const char LCD_INJ_ON_Str[] = "INJ ON";
const char LCD_RF_16_22_Str[] = "RF 1.6-2.2";
const char LCD_RF_20_32_Str[] = "RF 2.0-3.2";
const char LCD_RF_30_46_Str[] = "RF 3.0-4.6";
const char LCD_RF_42_63_Str[] = "RF 4.2-6.3";
const char LCD_Gain_Low_Str[] = "Low gain path";
const char LCD_Gain_High_Str[] = "High gain path";
const char LCD_RF_OFF_Str[] = "RF OFF";
const char LCD_RF_ON_Str[] = "RF_ON";
const char LCD_Atten_Str[] = "Atten: -     +";
// LCD texts

//----------------------------------
const uint8_t RX_Bit0_RST = 0b11111110;
const uint8_t RX1_Bit0 = 0b00000000; //0b11111110;
const uint8_t RX2_Bit0 = 0b00000001;

const uint8_t INJ_Bit1_RST = 0b11111101;
const uint8_t INJ_OFF_Bit1 = 0b00000000; //0b11111101;
const uint8_t INJ_ON_Bit1 = 0b00000010;

const uint8_t RF_Bit2_3_RST = 0b11110011;
const uint8_t RF_16_22_Bit2_3 = 0b00000000; //0b11110011;
const uint8_t RF_20_32_Bit2_3 = 0b00000100;
const uint8_t RF_30_46_Bit2_3 = 0b00001000;
const uint8_t RF_42_63_Bit2_3 = 0b00001100;

const uint8_t Gain_Bit4_RST = 0b11101111;
const uint8_t Gain_Low_Bit4 = 0b00000000; //0b11101111;
const uint8_t Gain_High_Bit4 = 0b00010000;

const uint8_t RF_Bit5_RST = 0b11011111;
const uint8_t RF_OFF_Bit5 = 0b00000000; //0b11011111;
const uint8_t RF_ON_Bit5 = 0b00100000;

const uint8_t Atten_Bit0_5_RST = 0b11000000;
uint8_t FEU_Atten_Bit0_5 = 0b00000000;
uint8_t IJU_Atten_Bit0_5 = 0b00000000;
//----------------------------------

MSG_Frame_t MIU_FEU_MSG =
{
		.Start = Start_Header,
		.ID = ID_MIU_FEU,
		.PCKT_0 = 0, //ID = 00
		.PCKT_1 = 0b01000000, //ID = 01
		.PCKT_2 = 0,
		.PCKT_3 = 0,
		.PCKT_4 = 0,
		.PCKT_5 = 0,
		.CRC_1 = 0,
		.CRC_2 = 0,
		.Length = 0,
		.New = 0,
		.Changed = 0
};

MSG_Frame_t MIU_IJU_MSG =
{
		.Start = Start_Header,
		.ID = ID_MIU_IJU,
		.PCKT_0 = 0, //ID = 00
		.PCKT_1 = 0b01000000, //ID = 01,
		.PCKT_2 = 0,
		.PCKT_3 = 0,
		.PCKT_4 = 0,
		.PCKT_5 = 0,
		.CRC_1 = 0,
		.CRC_2 = 0,
		.Length = 0,
		.New = 0,
		.Changed = 0
};

FEU_Status_t FEU_Status;
IJU_Status_t IJU_Status;

void Power27V_Switch(uint8_t State)
{
	if(State == 0) {LL_GPIO_ResetOutputPin(Power27V_Ctrl_Port, Power27V_Ctrl_Pin);}
	else {LL_GPIO_SetOutputPin(Power27V_Ctrl_Port, Power27V_Ctrl_Pin);}
}

char Power27V_Status(void)
{
	return LL_GPIO_IsOutputPinSet(Power27V_Ctrl_Port, Power27V_Ctrl_Pin);
}

void Message_Maker(MSG_Frame_t *MSG, uint8_t *PCKT_X, uint8_t Bit_Reset_CMD, uint8_t Bit_CMD)
{
	uint16_t L = 0;
	uint16_t CRC_Result = 0;
	uint8_t *P = (uint8_t *)&MSG;
	uint16_t X = 0;

	MSG->Length = 0;

	*PCKT_X = *PCKT_X & Bit_Reset_CMD;
	*PCKT_X = *PCKT_X | Bit_CMD;

	LL_CRC_ResetCRCCalculationUnit(CRC);
//	for(L=0; L<sizeof(MSG)-5; L++)
//	{
//		LL_CRC_FeedData8(CRC, *P);
//		MSG->Length++;
//		P++;
//	}

//	X = MSG->ID; X=X<<8; X = X | MSG->Start;
//	LL_CRC_FeedData16(CRC, X);
//	X = MSG->PCKT_1; X=X<<8; X = X | MSG->PCKT_0;
//	LL_CRC_FeedData16(CRC, X);
//	X = MSG->PCKT_3; X=X<<8; X = X | MSG->PCKT_2;
//	LL_CRC_FeedData16(CRC, X);
//	X = MSG->PCKT_5; X=X<<8; X = X | MSG->PCKT_4;
//	LL_CRC_FeedData16(CRC, X);

	LL_CRC_FeedData8(CRC, MSG->Start); LL_CRC_FeedData8(CRC, MSG->ID);
	LL_CRC_FeedData8(CRC, MSG->PCKT_0); LL_CRC_FeedData8(CRC, MSG->PCKT_1); LL_CRC_FeedData8(CRC, MSG->PCKT_2);
	LL_CRC_FeedData8(CRC, MSG->PCKT_3); LL_CRC_FeedData8(CRC, MSG->PCKT_4); LL_CRC_FeedData8(CRC, MSG->PCKT_5);

	CRC_Result = LL_CRC_ReadData16(CRC);

	MSG->CRC_2 = (uint8_t)CRC_Result;
	MSG->CRC_1 = (uint8_t)(CRC_Result>>8);

	MSG->Length = sizeof(MSG->Start) + sizeof(MSG->ID) +
	sizeof(MSG->PCKT_0) + sizeof(MSG->PCKT_1) + sizeof(MSG->PCKT_2) +
	sizeof(MSG->PCKT_3) + sizeof(MSG->PCKT_4) + sizeof(MSG->PCKT_5) +
	sizeof(MSG->CRC_1) + sizeof(MSG->CRC_2);

	MSG->New = 1;

}


