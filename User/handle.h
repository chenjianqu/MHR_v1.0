#ifndef __HANDLE_H
#define __HANDLE_H
#include "CoordinateSystem.h"
#include "pid.h"
#include "motor.h"
#include "delay.h"
#include "sys.h"
#include "tracksensor.h"
#include "key.h"
#include "led.h"
#include "myuart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "c.h"
#include "car.h"


void KeyHandle(void);
void Usart1Handle(void);
void Usart2Handle(void);
void Usart3Handle(void);
void Uart5Handle(void);
void getPosture(void);

#endif
