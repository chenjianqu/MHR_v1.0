#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY1        HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define KEY2        HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_11)

#define KEY1_PRES 1  //KEY0按下后返回值
#define KEY2_PRES	2	//KEY1按下后返回值


u8 KEY_Scan(u8 mode); //按键扫描函数

#endif
