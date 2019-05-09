#include "handle.h"

u8 len;
u8 key;//按键标志位



//MPU6050的数据变量
short aacx,aacy,aacz;			//加速度传感器原始数据
short gyrox,gyroy,gyroz;		//陀螺仪原始数据
short temp;						//温度



void KeyHandle()
{
	key=KEY_Scan(0);
	if(key)
	{								
		switch(key)
		{				 
			case KEY1_PRES:	
				HAL_UART_Transmit(&UART1_Handler,(u8 *)"KEY1",5,1000);
				if(car.isRun==false){
					car.isRun=true;
					SendStringEndl("run start",10);
				}
				else{
					car.isRun=false;
					SendStringEndl("run stop",9);
				}
				break;
			case KEY2_PRES: 
				HAL_UART_Transmit(&UART1_Handler,(u8 *)"KEY2",5,1000);
				//USART1_SendNumber(123);					
				break;
		}
	}
}


void Usart1Handle()
{
	if(USART_RX_STA&0x8000)
	{					   
		len=USART_RX_STA&0x3fff;
		HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);
		while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);
		USART_RX_STA=0;
	}
}

void Usart3Handle(void)
{
	if(isUSART3RxFinish)
	{
		HAL_UART_Transmit(&UART3_Handler,(uint8_t*)USART3_RX_BUF,lenRxUSART3,1000);
		while(__HAL_UART_GET_FLAG(&UART3_Handler,UART_FLAG_TC)!=SET);
		isUSART3RxFinish=false;
		lenRxUSART3=0;
	}
}


void Uart5Handle()
{
	if(isUART5RxFinish==true)
	{
		HAL_UART_Transmit(&UART5_Handler,(uint8_t*)UART5_RX_BUF,lenRxUART5,1000);
		while(__HAL_UART_GET_FLAG(&UART5_Handler,UART_FLAG_TC)!=SET);
		isUART5RxFinish=false;
		lenRxUART5=0;
	}
}



void getPosture(void)
{
		int dataPitch=0;
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		SendString("Pitch:",7);
		dataPitch=(int)pitch;
		SendNumber(dataPitch);
		SendString(" Roll:",7);
		dataPitch=(int)roll;
		SendNumber(dataPitch);
		SendString(" Yaw:",6);
		dataPitch=(int)yaw;
		SendNumber(dataPitch);
		SendEndl();
}



void USART6_IRQHandler(void)                	
{
	u32 timeout=0;
  u32 maxDelay=0x1FFFF;	
	HAL_UART_IRQHandler(&UART6_Handler);
  while (HAL_UART_GetState(&UART6_Handler)!=HAL_UART_STATE_READY)
	{
			timeout++;
			if(timeout>maxDelay) 
				break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART6_Handler,(u8 *)aRxBuffer6, RXBUFFERSIZE6)!=HAL_OK)
	{
			timeout++;
			if(timeout>maxDelay)
				break;	
	}
	
	//测试
//	HAL_UART_Transmit(&UART6_Handler,(uint8_t*)aRxBuffer6,1,1000);
	car.order=aRxBuffer6[0];
}


