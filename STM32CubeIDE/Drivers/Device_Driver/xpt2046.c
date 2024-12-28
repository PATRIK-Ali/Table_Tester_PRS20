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

/* Includes ------------------------------------------------------------------*/
//#include "GLCD.h"
#include "xpt2046.h"

/* Private define ------------------------------------------------------------*/
#define THRESHOLD 2   /* The bigger of the value, the lower the sensitivity */

static Coordinate ts_position[5];
static Coordinate display_position[5];
static calibration cal;

Matrix matrix ;
Coordinate display ;
Matrix Matrix_Default;
//--------------------------------------------------------------------------------delay
static void delay_nus(int cnt)
{
	int i,us;
	for(i = 0;i<cnt;i++)
	{
		us = 40;
		while (us--)     /* delay	*/
		{
		}
	}
}
 //----------------------------------------------------------------------------XPT2046 SPI initialization
void xpt2046_init(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	SPI_InitTypeDef  SPI_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB| RCC_AHB1Periph_GPIOC
//	| RCC_AHB1Periph_GPIOD| RCC_AHB1Periph_GPIOI, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_SPI2);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//
//	/* xpt2046  CS */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	/* xpt2046  IRQ */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//	GPIO_Init(GPIOI, &GPIO_InitStructure);
//
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 7;
//	SPI_Init(SPI2, &SPI_InitStructure);
//	SPI_Cmd(SPI2, ENABLE);
	Matrix_Default.An = 52;
	Matrix_Default.Bn = 4360;
	Matrix_Default.Cn = -979832;
	Matrix_Default.Dn = -5923;
	Matrix_Default.En = 5;
	Matrix_Default.Fn = 23070954;
	Matrix_Default.Divider = 65536;
}
//------------------------------------------------------------------------------delay function
int getDisplayPoint(Coordinate * displayPtr, Coordinate * screenPtr, Matrix * matrixPtr )
{
	/* Operation order is important since we are doing integer math. 
	   Make sure you add all terms together before dividing, so that 
	   the remainder is not rounded off prematurely. */
	if(screenPtr == 0) {return -1;}
  if( matrixPtr->Divider != 0 )
  {
    /* XD = AX+BY+C */        
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;
	/* YD = DX+EY+F */        
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;
  }
  else
  {
    return -1;
  }
  return 0;
} 
//------------------------------------------------------------------------------------------------------------------------------
int perform_calibration(calibration *cal) 
{
	int j;
	float n, x, y, x2, y2, xy, z, zx, zy;
	float det, a, b, c, e, f, i;
	float scaling = 65536.0;

	/* Get sums for matrix */
	n = x = y = x2 = y2 = xy = 0;
	for(j=0;j<5;j++) {
		n += 1.0;
		x += (float)cal->x[j];
		y += (float)cal->y[j];
		x2 += (float)(cal->x[j]*cal->x[j]);
		y2 += (float)(cal->y[j]*cal->y[j]);
		xy += (float)(cal->x[j]*cal->y[j]);
	}

	/* Get determinant of matrix -- check if determinant is too small */
	det = n*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
	if(det < 0.1 && det > -0.1) {
		/* ts_calibrate determinant is too small */
		return 0;
	}

	/* Get elements of inverse matrix */
	a = (x2*y2 - xy*xy)/det;
	b = (xy*y - x*y2)/det;
	c = (x*xy - y*x2)/det;
	e = (n*y2 - y*y)/det;
	f = (x*y - n*xy)/det;
	i = (n*x2 - x*x)/det;

	/* Get sums for x calibration */
	z = zx = zy = 0;
	for(j=0;j<5;j++) {
		z += (float)cal->xfb[j];
		zx += (float)(cal->xfb[j]*cal->x[j]);
		zy += (float)(cal->xfb[j]*cal->y[j]);
	}
	/* Now multiply out to get the calibration for framebuffer x coord */
	cal->a[2] = (int)((a*z + b*zx + c*zy)*(scaling));
	cal->a[0] = (int)((b*z + e*zx + f*zy)*(scaling));
	cal->a[1] = (int)((c*z + f*zx + i*zy)*(scaling));

	/* Get sums for y calibration */
	z = zx = zy = 0;
	for(j=0;j<5;j++) {
		z += (float)cal->yfb[j];
		zx += (float)(cal->yfb[j]*cal->x[j]);
		zy += (float)(cal->yfb[j]*cal->y[j]);
	}
	/* Now multiply out to get the calibration for framebuffer y coord */
	cal->a[5] = (int)((a*z + b*zx + c*zy)*(scaling));
	cal->a[3] = (int)((b*z + e*zx + f*zy)*(scaling));
	cal->a[4] = (int)((c*z + f*zx + i*zy)*(scaling));

	/* assign scaling */
	cal->a[6] = (int)scaling;
	return 1;
}
//------------------------------------------------------------------------------------------------------------------------------
void ts_calibrate( int x_size, int y_size )
{
	unsigned char i;
	int count;
	Coordinate * Ptr;
	//Coordinate Ptr;

	display_position[0].x = 20;              display_position[0].y = 20;
	display_position[1].x = x_size - 20;     display_position[1].y = 20;
	display_position[2].x = x_size - 20;     display_position[2].y = y_size - 20;
	display_position[3].x = 20;              display_position[3].y = y_size - 20;
	display_position[4].x = x_size / 2;      display_position[4].y = y_size / 2;

	for( i=0; i<5; i++ )
	{
		LCD_Clear(BLACK);

		for( count=0; count<1000*10000; count++ );   /* delay */

		ts_draw_cross(display_position[i].x,display_position[i].y);
		do
		{
			Ptr = Read_Value();
		}
		while( Ptr == (void*)0 );
		//while( Ptr.x == 65535 );
		ts_position[i].x= Ptr->x; ts_position[i].y= Ptr->y;
	}

	LCD_Clear(BLACK);

	cal.xfb[0] = display_position[0].x;
	cal.yfb[0] = display_position[0].y;

	cal.x[0] = ts_position[0].x;
	cal.y[0] = ts_position[0].y;

	cal.xfb[1] = display_position[1].x;
	cal.yfb[1] = display_position[1].y;

	cal.x[1] = ts_position[1].x;
	cal.y[1] = ts_position[1].y;

	cal.xfb[2] = display_position[2].x;
	cal.yfb[2] = display_position[2].y;

	cal.x[2] = ts_position[2].x;
	cal.y[2] = ts_position[2].y;

	cal.xfb[3] = display_position[3].x;
	cal.yfb[3] = display_position[3].y;

	cal.x[3] = ts_position[3].x;
	cal.y[3] = ts_position[3].y;

	cal.xfb[4] = display_position[4].x;
	cal.yfb[4] = display_position[4].y;

	cal.x[4] = ts_position[4].x;
	cal.y[4] = ts_position[4].y;

	perform_calibration(&cal);

	matrix.An = cal.a[0];
	matrix.Bn = cal.a[1];
	matrix.Cn = cal.a[2];
	matrix.Dn = cal.a[3];
	matrix.En = cal.a[4];
	matrix.Fn = cal.a[5];
	matrix.Divider = cal.a[6];
}
//------------------------------------------------------------------------------------------------------------------------------
void ts_draw_cross(int xpos, int ypos)
{
//	LCD_DrawLine(xpos-15, ypos, xpos-2, ypos, 0xffff);
//	LCD_DrawLine(xpos+2, ypos, xpos+15, ypos, 0xffff);
//	LCD_DrawLine(xpos, ypos-15, xpos, ypos-2, 0xffff);
//	LCD_DrawLine(xpos, ypos+2, xpos, ypos+15, 0xffff);
//
//	LCD_DrawLine(xpos-15, ypos+15, xpos-7, ypos+15, RGB565CONVERT(184,158,131));
//	LCD_DrawLine(xpos-15, ypos+7, xpos-15, ypos+15, RGB565CONVERT(184,158,131));
//
//	LCD_DrawLine(xpos-15, ypos-15, xpos-7, ypos-15, RGB565CONVERT(184,158,131));
//	LCD_DrawLine(xpos-15, ypos-7, xpos-15, ypos-15, RGB565CONVERT(184,158,131));
//
//	LCD_DrawLine(xpos+7, ypos+15, xpos+15, ypos+15, RGB565CONVERT(184,158,131));
//	LCD_DrawLine(xpos+15, ypos+7, xpos+15, ypos+15, RGB565CONVERT(184,158,131));
//
//	LCD_DrawLine(xpos+7, ypos-15, xpos+15, ypos-15, RGB565CONVERT(184,158,131));
//	LCD_DrawLine(xpos+15, ypos-15, xpos+15, ypos-7, RGB565CONVERT(184,158,131));



	LCD_DrawLine(xpos-15, ypos, xpos-2, ypos, 0xffff);
	LCD_DrawLine(xpos+2, ypos, xpos+15, ypos, 0xffff);
	LCD_DrawLine(xpos, ypos-15, xpos, ypos-2, 0xffff);
	LCD_DrawLine(xpos, ypos+2, xpos, ypos+15, 0xffff);

	LCD_DrawLine(xpos-15, ypos+15, xpos-7, ypos+15, RED);
	LCD_DrawLine(xpos-15, ypos+7, xpos-15, ypos+15, RED);

	LCD_DrawLine(xpos-15, ypos-15, xpos-7, ypos-15, RED);
	LCD_DrawLine(xpos-15, ypos-7, xpos-15, ypos-15, RED);

	LCD_DrawLine(xpos+7, ypos+15, xpos+15, ypos+15, RED);
	LCD_DrawLine(xpos+15, ypos+7, xpos+15, ypos+15, RED);

	LCD_DrawLine(xpos+7, ypos-15, xpos+15, ypos-15, RED);
	LCD_DrawLine(xpos+15, ypos-15, xpos+15, ypos-7, RED);
}
//------------------------------------------------------------------------------------------------------------------------------
void ts_draw_point(int x, int y, int color)
{
	//if( x >= LCD_X_SIZE || y >= LCD_Y_SIZE )
	if( x >= LCD_W || y >= LCD_H )
	{
		return;
	}

	if( x == 0 || y == 0 )
	{
		return;
	}

//	LCD_SetPixel_16bpp(x,y,color);
//	LCD_SetPixel_16bpp(x-1,y,color);
//	LCD_SetPixel_16bpp(x,y-1,color);
//	LCD_SetPixel_16bpp(x-1,y-1,color);
//	LCD_SetPixel_16bpp(x+1,y-1,color);
//	LCD_SetPixel_16bpp(x,y+1,color);
//	LCD_SetPixel_16bpp(x-1,y+1,color);
//	LCD_SetPixel_16bpp(x+1,y+1,color);
//	LCD_SetPixel_16bpp(x+1,y,color);

	GUI_DrawPoint(x,y,color);
	GUI_DrawPoint(x-1,y,color);
	GUI_DrawPoint(x,y-1,color);
	GUI_DrawPoint(x-1,y-1,color);
	GUI_DrawPoint(x+1,y-1,color);
	GUI_DrawPoint(x,y+1,color);
	GUI_DrawPoint(x-1,y+1,color);
	GUI_DrawPoint(x+1,y+1,color);
	GUI_DrawPoint(x+1,y,color);
}
//------------------------------------------------------------------------SPI bus transmit and receive data
unsigned char WR_CMD (unsigned char cmd)
{
	unsigned char Ret = 0;
//	/* Wait for SPI Tx buffer empty */
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
//	/* Send SPI data */
//	SPI_I2S_SendData(SPI2,cmd);
//	/* Wait for SPI data reception */
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//	/* Read SPI received data */
//	return SPI_I2S_ReceiveData(SPI2);

	LL_SPI_SetDataWidth(SPI6, LL_SPI_DATAWIDTH_8BIT);
	LL_SPI_Enable(SPI6);
	if(LL_SPI_IsActiveFlag_TXP(SPI6) == 1)
	{
		LL_SPI_TransmitData8(SPI6, cmd);
	}
	LL_SPI_StartMasterTransfer(SPI6);
	while( !( /*LL_SPI_IsActiveFlag_EOT(SPI6) &&*/ LL_SPI_IsActiveFlag_TXC(SPI6) ) )
	{
		__NOP();
	}
	LL_SPI_ClearFlag_EOT(SPI6);
	while( !( LL_SPI_IsActiveFlag_RXP(SPI6) ) )
	{
		__NOP();
	}
	Ret = LL_SPI_ReceiveData8(SPI6);
	LL_SPI_Disable(SPI6);
	return Ret;
} 
//-------------------------------------------------------------------------read xpt2046 adc value
unsigned short RD_AD(void)
{ 
	unsigned short buf,temp;
	//int buf,temp;
	buf = 0;
	temp = 0;

	temp = WR_CMD(0x00);
	buf = temp << 8; 
	delay_nus(1); 
	temp = WR_CMD(0x00);
	buf |= temp; 
	buf >>= 4;
	buf &= 0xfff;
	return buf;
}
//------------------------------------------------------------------------read xpt2046 channel X+ adc value
unsigned short Read_X(void)
{
	unsigned short temp = 0;
	//int temp = 0;
	TP_CS(0); 
	delay_nus(1); 
	WR_CMD(CHX); 
	delay_nus(1); 
	temp = RD_AD(); 
	TP_CS(1); 
	return temp;    
}  
//-----------------------------------------------------------------------read xpt2046 channel Y+ adc value
unsigned short Read_Y(void)
{  
	unsigned short temp = 0;
	//int temp = 0;
	TP_CS(0);
	delay_nus(1);
	WR_CMD(CHY);
	delay_nus(1);
	temp = RD_AD();
	TP_CS(1); 
	return temp;
} 
//----------------------------------------------------------------read xpt2046 channel X+ channel Y+ adc value
void TP_GetAdXY(int *x,int *y)  
{
	int adx,ady;
	adx = 0;
	ady = 0;
	adx = Read_X(); 
	delay_nus(1); 
	ady = Read_Y(); 
	*x = adx;
	*y = ady;
}
//-------------------------------------------get xpt2046 channel X+ channel Y+ adc filtering value, some interference values can be excluded
Coordinate *Read_Value(void)
{
	static Coordinate screen;
	Coordinate screen_fail;
	int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
	unsigned char count=0;
	int buffer[2][9]={{0},{0}};  /* channel X+ Y+ for sampling buffer */
	TP_X[0] = 0; TP_Y[0] = 0;
	screen.x=0; screen.y=0;
	screen_fail.x=65535; screen_fail.y=65535;
	do                           /* 9 sampling times */
	{
		TP_GetAdXY(TP_X,TP_Y);
		buffer[0][count]=TP_X[0];
		buffer[1][count]=TP_Y[0];
		count++;
	}
	while(!TP_INT_IN&& count<9);  /* TP_INT_IN interrupt pin for the touch screen, when the user clicks on the touch screen��
	                                 TP_INT_IN Low level */
//TP_GetAdXY(&TP_X[0],&TP_Y[0]);
//screen.x=0; screen.y=0;
//screen.x=TP_X[0]; screen.y=TP_Y[0];
	if(count==9)   /* sampled 9 times, then filtering some interference values can be excluded*/
		{
			/* average value of the 3 groups */
			temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
			temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
			temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;
			/* D-value between the 3 groups */
			m0=temp[0]-temp[1];
			m1=temp[1]-temp[2];
			m2=temp[2]-temp[0];
			/* absolute value of D-value */
			m0=m0>0?m0:(-m0);
			m1=m1>0?m1:(-m1);
			m2=m2>0?m2:(-m2);

			/* judging Whether the absolute value of D-value is more than threshold, if three absolute value of D-value is
			   more than threshold value, then determine the sampling point for the interference, ignore the sampling point,
			   the threshold value is setting to 2, in this example */
			if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;
			/* calculate channel X+ average values,then assign them to screen */
			if(m0<m1)
			{
				if(m2<m0)
				screen.x=(temp[0]+temp[2])/2;
				else
				screen.x=(temp[0]+temp[1])/2;
			}
			else if(m2<m1)
				screen.x=(temp[0]+temp[2])/2;
			else
				screen.x=(temp[1]+temp[2])/2;

			/* same as above, this is channel Y+ */
			temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3;
			temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3;
			temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3;
			m0=temp[0]-temp[1];
			m1=temp[1]-temp[2];
			m2=temp[2]-temp[0];
			m0=m0>0?m0:(-m0);
			m1=m1>0?m1:(-m1);
			m2=m2>0?m2:(-m2);
			if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

			if(m0<m1)
			{
				if(m2<m0)
					screen.y=(temp[0]+temp[2])/2;
				else
					screen.y=(temp[0]+temp[1])/2;
			}
			else if(m2<m1)
				screen.y=(temp[0]+temp[2])/2;
			else
				screen.y=(temp[1]+temp[2])/2;

			return &screen;
		}
		return 0;
}
//-------------------------------------------------------------------------------------------
uint8_t TS_Touched(void)
{
//	return 1;
	return !LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_2);
}
