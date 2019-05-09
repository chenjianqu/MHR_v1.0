/*--------------------------------------------------------------------------
// 文件名：Driver.c
// 描述：  MCU底层驱动  
// 设计者：EU电子
// 深圳EU电子出品-版权所有-翻版必究
// EU-热爱嵌入式开发
// http://euse.taobao.com
//-------------------------------------------------------------------------*/
/* 头文件包含 INCLUDES */

#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"


/* type change */
typedef unsigned char       bool;
typedef unsigned char       u8;
typedef unsigned short      u16;
#define  True  1
#define  False 0



/* INCLUDES */
//Driver
#include "Driver.h"

/*-------------------------------------------------------------------------------------------------------
*  函数声明												 
-------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------
*  函数声明												 
-------------------------------------------------------------------------------------------------------*/
//mcu
void Driver_MCU_Init(void);
//lcd
void Driver_LcdBacklight(bool sta);
void Driver_LcdReset(bool sta);
void Driver_LcdCS(bool sta);
void Driver_LcdRS(bool sta);
void Driver_LcdRD(bool sta);
void Driver_LcdWR(bool sta);
void Driver_LcdSendData(u16 Temp);

//-------------------------------------------------------------------------------------------------------
//-------------------------------------- LCD DRIVER -----------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/********************************************************************************************************
*  Function: Driver_LcdBacklight				                                                           
*  Object: lcd backlight control
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdBacklight(bool sta)
{
		if(sta)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

/********************************************************************************************************
*  Function: Driver_LcdReset				                                                           
*  Object: lcd reset control
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdReset(bool sta)
{
		if(!sta)
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
}

/********************************************************************************************************
*  Function: Driver_LcdCS		                                                           
*  Object: lcd enable/disable control
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdCS(bool sta)
{
		if(!sta)
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);
}

/********************************************************************************************************
*  Function: Driver_LcdRS		                                                           
*  Object: lcd RS(cmd/data chose) control
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdRS(bool sta)
{
		if(!sta)
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);
}

/********************************************************************************************************
*  Function: Driver_LcdRD		                                                           
*  Object: lcd read control
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdRD(bool sta)
{

		if(!sta)
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
}

/********************************************************************************************************
*  Function: Driver_LcdWR		                                                           
*  Object: lcd write control
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void Driver_LcdWR(bool sta)
{
		if(!sta)
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
		else
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
}

/********************************************************************************************************
*  Function: Driver_LcdSendData		                                                           
*  Object: lcd data send
*  Input: Temp
*  Output: none                                  
*  brief: len is 16bits
********************************************************************************************************/
void Driver_LcdSendData(u16 Temp)
{
		//PD10 PD9 PD8    PE15 PE14 PE13 PE12 PE11 PE10 PE9 PE8 PE7     PD1 PD0 PD15 PD14

		HAL_GPIO_WritePin(GPIOD,((Temp)/0x2000)<<8 & 0x0700, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD,(~((Temp)/0x2000)<<8 & 0x0700), GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE,((Temp<<3)/0x80)<<7 & 0xff80, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,(~((Temp<<3)/0x80)<<7 & 0xff80), GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,((Temp<<12)/0x4000) & 0x0003, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD,(~((Temp<<12)/0x4000) & 0x0003), GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,((Temp<<14)/0x4000)<<14 & 0xC000, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD,(~((Temp<<14)/0x4000)<<14 & 0xC000), GPIO_PIN_RESET);
}
