#ifndef _RS485_H_
#define _RS485_H_

/**
 * @author  Ali Mesgari
 * @email   PATRIKAli3000@Gmail.com
 * @website 
 * @link    
 * @version v1.0
 * @ide     Keil uVision
 * @license 
 * @brief   Library for RS485 communication through UART and MAX485 in MPM project.
 *	
 */

//#include "stm32f10x_conf.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
//#include "CRC.h"
#include "stm32h5xx_ll_gpio.h"
#include "stm32h5xx_ll_usart.h"
#include "stm32h5xx_ll_lpuart.h"

#define Line1_DR_Port		GPIOB
#define Line1_DR_Pin		LL_GPIO_PIN_0

#define Line2_DR_Port		GPIOC
#define Line2_DR_Pin		LL_GPIO_PIN_8

#define Line3_DR_Port		GPIOB
#define Line3_DR_Pin		LL_GPIO_PIN_14

#define Line4_DR_Port		GPIOB
#define Line4_DR_Pin		LL_GPIO_PIN_15

#define Line5_DR_Port		GPIOC
#define Line5_DR_Pin		LL_GPIO_PIN_9

#define Line6_DR_Port		GPIOB
#define Line6_DR_Pin		LL_GPIO_PIN_1

#define Line7_DR_Port		GPIOB
#define Line7_DR_Pin		LL_GPIO_PIN_2

#define Line1_UART			USART3
#define Line2_UART			UART5
#define Line3_UART			UART4
#define Line4_UART			USART6
#define Line5_UART			LPUART1
#define Line6_UART			USART11
#define Line7_UART			UART7

#define BUF_Size			512

#define Line1_BUF_Index		0
#define Line2_BUF_Index		100
#define Line3_BUF_Index		200
#define Line4_BUF_Index		300
#define Line5_BUF_Index		400
#define Line6_BUF_Index		500
#define Line7_BUF_Index		600

#define Line_BUF_Size		100

typedef enum
{
	Single_Ended = 0,
	Network = 1
}RS_485_SingleEnded_Network;

typedef enum
{
	Receiver = 0,
	Driver = 1
}RS_485_Driver_Receiver;

typedef enum
{
	Line1 = 1,
	Line2 = 2,
	Line3 = 3
}Lines;

extern char Line1_BUF[BUF_Size];
extern char Line2_BUF[BUF_Size];
extern char Line3_BUF[BUF_Size];
extern char Line4_BUF[BUF_Size];
extern char Line5_BUF[BUF_Size];
extern char Line6_BUF[BUF_Size];
extern char Line7_BUF[BUF_Size];
extern char Lines_BUF[BUF_Size];

extern u16 Line1_BUF_P;
extern u16 Line2_BUF_P;
extern u16 Line3_BUF_P;
extern u16 Line4_BUF_P;
extern u16 Line5_BUF_P;
extern u16 Line6_BUF_P;
extern u16 Line7_BUF_P;

extern u8 Line1_BUF_Timeout;
extern u8 Line2_BUF_Timeout;
extern u8 Line3_BUF_Timeout;
extern u8 Line4_BUF_Timeout;
extern u8 Line5_BUF_Timeout;
extern u8 Line6_BUF_Timeout;
extern u8 Line7_BUF_Timeout;

extern u8 Line1_Working;
extern u8 Line2_Working;
extern u8 Line3_Working;
extern u8 Line4_Working;
extern u8 Line5_Working;
extern u8 Line6_Working;
extern u8 Line7_Working;

void RS485_Init(void);
void RS485_Set_Line_Driver_Receiver(u8 Line, u8 D_R);
void RS485_Tx(u8 Line, char *MSG, u16 MSG_Length);
void RS485_Rx(u8 Line, char *MSG, u16 MSG_Length);

#endif
