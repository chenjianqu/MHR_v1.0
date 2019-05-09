#ifndef _MOTOR_H
#define _MOTOR_H
#include <sys.h>	 
#include "delay.h"
#include "main.h"
#include "CoordinateSystem.h"

//左前电机
#define LF1_CCR TIM2->CCR1
#define LF2_CCR TIM2->CCR2

//右前电机
#define RF1_CCR TIM2->CCR3
#define RF2_CCR TIM2->CCR4

//左后电机
#define LR1_CCR TIM3->CCR1
#define LR2_CCR TIM3->CCR2

//右后电机
#define RR1_CCR TIM3->CCR3
#define RR2_CCR TIM3->CCR4

//管脚复用设置
#define LF_GPIO_AF GPIO_AF1_TIM2
#define RF_GPIO_AF GPIO_AF1_TIM2
#define LR_GPIO_AF GPIO_AF2_TIM3
#define RR_GPIO_AF GPIO_AF2_TIM3

//定时器
#define LF_TIM htim2
#define RF_TIM htim2
#define LR_TIM htim3
#define RR_TIM htim3

//定时器通道
#define LF1_TIM_CHANNEL TIM_CHANNEL_1
#define LF2_TIM_CHANNEL TIM_CHANNEL_2
#define RF1_TIM_CHANNEL TIM_CHANNEL_3
#define RF2_TIM_CHANNEL TIM_CHANNEL_4

#define LR1_TIM_CHANNEL TIM_CHANNEL_1
#define LR2_TIM_CHANNEL TIM_CHANNEL_2
#define RR1_TIM_CHANNEL TIM_CHANNEL_3
#define RR2_TIM_CHANNEL TIM_CHANNEL_4

//电机操作
#define MOTOR_LF_F initGPIO_AF(MOTOR_LF1_GPIO_Port,MOTOR_LF1_Pin,LF_GPIO_AF);initGPIO_OUTPUT(MOTOR_LF2_GPIO_Port,MOTOR_LF2_Pin);
#define MOTOR_LF_B initGPIO_OUTPUT(MOTOR_LF1_GPIO_Port,MOTOR_LF1_Pin);initGPIO_AF(MOTOR_LF2_GPIO_Port,MOTOR_LF2_Pin,LF_GPIO_AF);
#define MOTOR_LF_S initGPIO_OUTPUT(MOTOR_LF1_GPIO_Port,MOTOR_LF1_Pin);initGPIO_OUTPUT(MOTOR_LF2_GPIO_Port,MOTOR_LF2_Pin);

#define MOTOR_RF_F initGPIO_AF(MOTOR_RF1_GPIO_Port,MOTOR_RF1_Pin,RF_GPIO_AF);initGPIO_OUTPUT(MOTOR_RF2_GPIO_Port,MOTOR_RF2_Pin);
#define MOTOR_RF_B initGPIO_OUTPUT(MOTOR_RF1_GPIO_Port,MOTOR_RF1_Pin);initGPIO_AF(MOTOR_RF2_GPIO_Port,MOTOR_RF2_Pin,RF_GPIO_AF);
#define MOTOR_RF_S initGPIO_OUTPUT(MOTOR_RF1_GPIO_Port,MOTOR_RF1_Pin);initGPIO_OUTPUT(MOTOR_RF2_GPIO_Port,MOTOR_RF2_Pin);

#define MOTOR_LR_F initGPIO_AF(MOTOR_LR1_GPIO_Port,MOTOR_LR1_Pin,LR_GPIO_AF);initGPIO_OUTPUT(MOTOR_LR2_GPIO_Port,MOTOR_LR2_Pin);
#define MOTOR_LR_B initGPIO_OUTPUT(MOTOR_LR1_GPIO_Port,MOTOR_LR1_Pin);initGPIO_AF(MOTOR_LR2_GPIO_Port,MOTOR_LR2_Pin,LR_GPIO_AF);
#define MOTOR_LR_S initGPIO_OUTPUT(MOTOR_LR1_GPIO_Port,MOTOR_LR1_Pin);initGPIO_OUTPUT(MOTOR_LR2_GPIO_Port,MOTOR_LR2_Pin);

#define MOTOR_RR_F initGPIO_AF(MOTOR_RR1_GPIO_Port,MOTOR_RR1_Pin,RR_GPIO_AF);initGPIO_OUTPUT(MOTOR_RR2_GPIO_Port,MOTOR_RR2_Pin);
#define MOTOR_RR_B initGPIO_OUTPUT(MOTOR_RR1_GPIO_Port,MOTOR_RR1_Pin);initGPIO_AF(MOTOR_RR2_GPIO_Port,MOTOR_RR2_Pin,RR_GPIO_AF);
#define MOTOR_RR_S initGPIO_OUTPUT(MOTOR_RR1_GPIO_Port,MOTOR_RR1_Pin);initGPIO_OUTPUT(MOTOR_RR2_GPIO_Port,MOTOR_RR2_Pin);

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void CarSetMotor(void);

//电机方向改变
void Motor_TIM_PWM_Stop(void);
void CarTurnForward(void);
void CarTurnBackward(void);
void CarTurnLeft(void);
void CarTurnRight(void);
void CarTurnClockwise(void);
void CarTurnCounterClockwise(void);
void CarStop(void);


//电机转速
void CarForward(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);
void CarBack(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);
void CarLeft(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);
void CarRight(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);

void CarClockwise(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);
void CarCounterClockwise(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);

//引脚复位
void initGPIO_OUTPUT(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
void initGPIO_AF(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin,uint8_t GPIO_AF);
#endif

