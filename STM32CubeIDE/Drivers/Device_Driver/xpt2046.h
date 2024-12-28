/****************************************Copyright (c)****************************************************
**                                      
**                        http://www.powermcu.com & http://www.hotmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               xpt2046.c
** Descriptions:            resistive touch screen, compatible ads7843
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             AVRman
** Modified date:           2015-7-2
** Version:                 V1.1
** Descriptions:            add english description
**
*********************************************************************************************************/

#ifndef _XPT2046_H_
#define _XPT2046_H_

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
//#include "GLCD.h"
#include "stm32h5xx_ll_gpio.h"
#include "stm32h5xx_ll_spi.h"
#include "lcd.h"
#include "gui.h"

typedef struct Matrix 
{
	/* This arrangement of values facilitates  calculations within getDisplayPoint() */
	int  
	An,     /* A = An/Divider */
	Bn,     /* B = Bn/Divider */   
	Cn,     /* C = Cn/Divider */   
	Dn,     /* D = Dn/Divider */   
	En,     /* E = En/Divider */   
	Fn,     /* F = Fn/Divider */   
	Divider ;   
} Matrix ;

typedef struct {
      int x[5], xfb[5];
      int y[5], yfb[5];
      int a[7];
} calibration;

typedef	struct POINT 
{
   int x;
   int y;
}Coordinate;

extern Matrix matrix ;
extern Coordinate  display ;
extern Matrix Matrix_Default;

/* Private define ------------------------------------------------------------*/
/* AD channel selection command */
#define	CHX 	        0x90 	/* Channel X+ command*/	
#define	CHY 	        0xd0	/* Channel Y+ command* */

#define TP_CS(x)	((x) ? (LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1)) : (LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1)) ) //((x) ? (GPIO_SetBits(GPIOC, GPIO_Pin_13)) : (GPIO_ResetBits(GPIOC, GPIO_Pin_13) ) )

#define TP_INT_IN   (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_2)) //(GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_8))

/* Private function prototypes -----------------------------------------------*/				
void xpt2046_init(void);	
Coordinate *Read_Value(void);
int getDisplayPoint(Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr );
int setCalibrationMatrix( Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr);
void ts_draw_point(int x,int y,int color);
void ts_draw_cross(int Xpos,int Ypos);
uint8_t TS_Touched(void);
#endif

/************************ (C) COPYRIGHT HAOYU Electronics *****END OF FILE****/
