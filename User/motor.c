#include "motor.h"

GPIO_InitTypeDef GPIO_InitStruct_InitMotor;

void CarSetMotor(void)
{
		switch(car.dir)
		{
			case DIR_X_N:
				CarTurnForward();
				break;
			case DIR_X_P:
				CarTurnBackward();
				break;
			case DIR_Y_P:
				CarTurnLeft();
				break;
			case DIR_Y_N:
				CarTurnRight();
				break;
			default:
				CarStop();
			break;
		}
}




void initGPIO_OUTPUT(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	GPIO_InitStruct_InitMotor.Pin = GPIO_Pin;
	GPIO_InitStruct_InitMotor.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct_InitMotor.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct_InitMotor.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct_InitMotor);
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_RESET);
}




void initGPIO_AF(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin,uint8_t GPIO_AF)
{
	GPIO_InitStruct_InitMotor.Pin = GPIO_Pin;
	GPIO_InitStruct_InitMotor.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct_InitMotor.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct_InitMotor.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct_InitMotor.Alternate = GPIO_AF;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct_InitMotor);
}


void Motor_TIM_PWM_Stop(void)
{
	HAL_TIM_PWM_Stop(&LF_TIM,LF1_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&LF_TIM,LF2_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&RF_TIM,RF1_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&RF_TIM,RF2_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&LR_TIM,LR1_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&LR_TIM,LR2_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&RR_TIM,RR1_TIM_CHANNEL);
	HAL_TIM_PWM_Stop(&RR_TIM,RR2_TIM_CHANNEL);
}


void CarForward(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	//所有的轮子都前向转动
	LF1_CCR=valLeftFront;//通道设置比较值
	RF1_CCR=valRightFront;
	LR1_CCR=valLeftRear;
	RR1_CCR=valRightRear;
}


void CarBack(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	//所有的轮子都向后转动
	LF2_CCR=valLeftFront;
	RF2_CCR=valRightFront;
	LR2_CCR=valLeftRear;
	RR2_CCR=valRightRear;
}


void CarRight(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	//LF RR back,RF LR forward
	LF1_CCR=valLeftFront;//通道设置比较值
	RF2_CCR=valRightFront;
	LR2_CCR=valLeftRear;
	RR1_CCR=valRightRear;
}


void CarLeft(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	//左前右后向后转动,又前左后向前转动
	LF2_CCR=valLeftFront;
	RF1_CCR=valRightFront;
	LR1_CCR=valLeftRear;
	RR2_CCR=valRightRear;
}


void CarClockwise(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	LF1_CCR=valLeftFront;
	RF2_CCR=valRightFront;
	LR1_CCR=valLeftRear;
	RR2_CCR=valRightRear;
}



void CarCounterClockwise(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	LF2_CCR=valLeftFront;
	RF1_CCR=valRightFront;
	LR2_CCR=valLeftRear;
	RR1_CCR=valRightRear;
}

void CarStop(void)
{
	Motor_TIM_PWM_Stop();
	MOTOR_LF_S
	MOTOR_RF_S
	MOTOR_LR_S
	MOTOR_RR_S
}

void CarTurnForward()
{
	Motor_TIM_PWM_Stop();
	MOTOR_LF_F
	MOTOR_RF_F
	MOTOR_LR_F
	MOTOR_RR_F
	HAL_TIM_PWM_Start(&LF_TIM,LF1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RF_TIM,RF1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&LR_TIM,LR1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RR_TIM,RR1_TIM_CHANNEL);
}

void CarTurnBackward()
{
	Motor_TIM_PWM_Stop();
	MOTOR_LF_B
	MOTOR_RF_B
	MOTOR_LR_B
	MOTOR_RR_B
	HAL_TIM_PWM_Start(&LF_TIM,LF2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RF_TIM,RF2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&LR_TIM,LR2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RR_TIM,RR2_TIM_CHANNEL);
}

//LF RR反转 RF LR正转
void CarTurnRight()
{
	Motor_TIM_PWM_Stop();
	
	MOTOR_LF_F
	MOTOR_RF_B
	MOTOR_LR_B
	MOTOR_RR_F
	
	HAL_TIM_PWM_Start(&LF_TIM,LF1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RF_TIM,RF2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&LR_TIM,LR2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RR_TIM,RR1_TIM_CHANNEL);
}


//LF RR forward RF LR backward
void CarTurnLeft()
{
	Motor_TIM_PWM_Stop();

	MOTOR_LF_B
	MOTOR_RF_F
	MOTOR_LR_F
	MOTOR_RR_B
	
	HAL_TIM_PWM_Start(&LF_TIM,LF2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RF_TIM,RF1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&LR_TIM,LR1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RR_TIM,RR2_TIM_CHANNEL);
}

void CarTurnClockwise(void)
{
	Motor_TIM_PWM_Stop();
	
	MOTOR_LF_F
	MOTOR_RF_B
	MOTOR_LR_F
	MOTOR_RR_B
	
	HAL_TIM_PWM_Start(&LF_TIM,LF1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RF_TIM,RF2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&LR_TIM,LR1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RR_TIM,RR2_TIM_CHANNEL);
}

void CarTurnCounterClockwise(void)
{
	Motor_TIM_PWM_Stop();
	
	MOTOR_LF_B
	MOTOR_RF_F
	MOTOR_LR_B
	MOTOR_RR_F
	
	HAL_TIM_PWM_Start(&LF_TIM,LF2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RF_TIM,RF1_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&LR_TIM,LR2_TIM_CHANNEL);
	HAL_TIM_PWM_Start(&RR_TIM,RR1_TIM_CHANNEL);
}
