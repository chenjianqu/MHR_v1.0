/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main_func.h"
#include "lcd.h"
#include "car.h"
#include "handle.h"
#include "test.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
u32 sysCounter=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	u32 cycleTimer=0;
	int deltaX=0;
	int deltaY=0;
	

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	delay_init(168);	
	uart_init(115200);
	uart3_init(9600);
	//uart5_init(115200);
	uart6_init(115200);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
 // MX_USART1_UART_Init();`
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
 // MX_USART3_UART_Init();
 // MX_UART5_Init();
  //MX_USART6_UART_Init();
  //MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
//	while(mpu_dmp_init())
//	{
//		LED1_Toggle;
//		delay_ms(100);
//8	}
	
	LCD();
	PID_Init(&PID_Car);
              
	
	SendStringEndl("System Launch Succeed",22);
	SendStringEndl_BL("Connected BL",12);
	SendStringEndl("waitKey...",11);
	
	delay_ms(1500);
	
  //	while(KEY_Scan(0)!=KEY1_PRES)delay_ms(1);//等待key1
	sysCounter=0;//系统计数器
	
	LCDShowTaskNumber();
	
	InitCar();
	
	//car.pm=PM_RPF;
	car.pm=PM_RFP;
	//car.pm=PM_PRF;
	//car.pm=PM_FRP;
	
	//car.pm=PM_PFR;
	//car.pm=PM_FPR;
	
	CarTurnForward();
	CarRunForward(300);
	delay_ms(300);
	
	SetAeraCoordinate();
	/*
	Point_RawMaterialAreaFar.y+=1;
	car.terminalPoint.x=4;
	car.terminalPoint.y=2;
	*/
	
	if(car.pm==PM_RFP || car.pm==PM_RPF)
	{
		car.terminalPoint=Point_RawMaterialAreaFar;	
	}
	else{
		car.terminalPoint=Point_QRCodeAera;
	}
	switch(car.pm)
	{
		case PM_RPF:
			SendChar_MV(ORDER_RPF);
			break;
		case PM_RFP:
			SendChar_MV(ORDER_RFP);
			break;
		case PM_PRF:
			SendChar_MV(ORDER_PRF);
			break;
		case PM_PFR:
			SendChar_MV(ORDER_PFR);
			break;
		case PM_FPR:
			SendChar_MV(ORDER_FPR);
			break;
		case PM_FRP:
			SendChar_MV(ORDER_FRP);
			break;
	}
	
  SendStringEndl("Run Start",9);
	
	CarStop();
	
	//测试
	//mainTest();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
		delay_us(100);

		cycleTimer++;
		//按键和串口监测
		KeyHandle();
		Usart1Handle();//usart connect to computer
		Usart3Handle();//connect to BL
		
		
		//send usart every time
		if(cycleTimer==INTERVAL_SEND_INF){//串口发送状态信息
			cycleTimer=0;
			//SendInformationToBL();
			SendInformationToPC();
			//LED1_Toggle;
			//delay_ms(50);
		}
		
		//时间到某一时刻就回去
		if(sysCounter>Limited_Time)//go back to init area
		{
			LED1_Toggle;
			LED2_Toggle;
			car.terminalPoint=Point_InitAera;
		}

		//小车停止跑动
		if(car.isRun==false)
  	{
			CarStop();
			LED1(true);
			LED2(true);
			if(cycleTimer==INTERVAL_SEND_INF-1){
				SendStringEndl("Wait",4);
			}
			continue;
		}
		
		//特殊区域处理
		if(car.flagSetPosition!=SSP_RegularMode)
		{
			switch(car.flagSetPosition)
			{
				case SSP_InitPosition:
					//InitCarPosition();
					//InitCarPosition2();	
					InitCarPosition3();
				break;
				case SSP_ResetPosition:
					//ResetCarPosition();
					break;
				case SSP_RawPosition:
					break;
				case SSP_MoveToRawPosition:
				//MoveToRawPosition3();
					break;
				default:
					break;
			}
			delay_ms(1);
			continue;
		}		
		
		car.last_dir=car.dir;
		
		//坐标更新
		UpdateCoordinatePointNoRotation();
		
		//根据坐标值设置方向
		deltaX=car.terminalPoint.x-car.currentPoint.x;
		deltaY=car.terminalPoint.y-car.currentPoint.y;			
		
		if(deltaY>0)
			car.dir=DIR_Y_P;
		else if(deltaY<0)
			car.dir=DIR_Y_N;
		else if(deltaX>0)
			car.dir=DIR_X_P;
		else if(deltaX<0)
			car.dir=DIR_X_N;
		else
		{//当到达目标时，dir不被赋值，故在此轮循环不执行旋转操作
			CarStop();
			car.pos++;
			car.lastPoint=car.terminalPoint;
			CarBrake();
			
			switch(car.pm)
			{
				case PM_RPF:
					TernimalHandleNoRotationRPF();
				break;
				case PM_RFP:
					TernimalHandleNoRotationRFP();
					break;
				case PM_FRP:
					TernimalHandleNoRotationFRP();
					break;
				case PM_FPR:
					TernimalHandleNoRotationFPR();
					break;
				case PM_PRF:
					TernimalHandleNoRotationPRF();
					break;
				case PM_PFR:
					TernimalHandleNoRotationPFR();
					break;
				default:
					break;
			}
			
			
			
			//显示任务
			if(equal(car.currentPoint,Point_QRCodeAera))
			{
				taskInf.list[taskInf.currentPoint]=car.order;
				taskInf.currentPoint++;
				LCDShowTaskNumber();
			}
			
			car.dir=DIR_NONE;
		}
		
		if(car.dir!=car.last_dir)//电机转向
			CarSetMotor();
		
		//速度设置
		if(deltaY>2||deltaY<-2)
			car.speedBase=SPEED_LEVEL_LESS_N;
		else if(deltaY==2 || deltaY==-2)
			car.speedBase=SPEED_LEVEL_LESS2;
		else if(deltaY==1 ||deltaY==-1)
		{
		 if(car.flagUpdatePoint==0)
			 car.speedBase=SPEED_LEVEL_LESS1;
		 if(car.flagUpdatePoint>1)
			 car.speedBase=SPEED_LEVEL_LESS0;
		}
		else if(deltaX>2||deltaX<-2)
			car.speedBase=SPEED_LEVEL_LESS_N;
		else if(deltaX==2 ||deltaX ==-2)
			car.speedBase=SPEED_LEVEL_LESS2;
		else if(deltaX==1 || deltaX ==-1)
		{
			if(car.flagUpdatePoint==0)
				car.speedBase=SPEED_LEVEL_LESS1;
			if(car.flagUpdatePoint>1)
				car.speedBase=SPEED_LEVEL_LESS0;
		}
		
		
		
		//让MV识别物块
		if(car.isSendScanObj==false && equal(car.currentPoint,Point_RawMaterialAreaStartMV)){
				if(car.pm==PM_RPF && car.pos==0)
				{
					SendChar_MV(ORDER_SCANOBJECT);
					car.isSendScanObj=true;
				}		
		}
		
		switch(car.dir)
		{
			case DIR_X_N:
				CarForwardPID();
				break;
			case DIR_X_P:
				CarBackwardPID();
				break;
			case DIR_Y_N:
				CarRightPID();
				break;
			case DIR_Y_P:
				CarLeftPID();
				break;
			default:
				CarStop();
				break;
		}

}
		
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==(&htim6))
	{
		sysCounter++;

		if(car.flagUpdatePoint>1)
			car.flagUpdatePoint++;
		if(car.flagUpdatePoint==GRID_TIME_COF)
			car.flagUpdatePoint=0;
		
		if(car.flagBlockForward>=2)
			car.flagBlockForward++;
		if(car.flagBlockForward>car.delayBlockForward)
			car.flagBlockForward=0;	
		
		if(car.flagHighSpeedDelay>0)
			car.flagHighSpeedDelay--;
	}
}




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:
		break;
		case GPIO_PIN_1:
		break;
		case GPIO_PIN_2:
		break;
		case GPIO_PIN_3:
			mc.MotorLR++;
		break;
		case GPIO_PIN_4:
			mc.MotorLR++;
		break;
		case GPIO_PIN_5:
			mc.MotorRR++;
		break;
		case GPIO_PIN_6:
			mc.MotorRR++;
		break;
		case GPIO_PIN_7:
		break;
		case GPIO_PIN_8:
		break;
		case GPIO_PIN_9:
		break;
		case GPIO_PIN_10:
			mc.MotorRF++;
		break;
		case GPIO_PIN_11:
			mc.MotorRF++;
		break;
		case GPIO_PIN_12:
		break;
		case GPIO_PIN_13:
		mc.MotorLF++;
		break;
		case GPIO_PIN_14:
			mc.MotorLF++;
		break;
		case GPIO_PIN_15:
			
		break;
	}
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
