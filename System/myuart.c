#include "myuart.h"
#include "stm32f4xx_hal_uart.h"


u8 newLineArray[2]={13,10};
u8 orderSendToMV[2]={0};

 	
u8 USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA=0;//bit15,bit14,bit13~0,
u8 aRxBuffer[RXBUFFERSIZE];
UART_HandleTypeDef UART1_Handler;

u8 USART2_RX_BUF[USART2_REC_LEN];
u16 USART2_RX_STA=0;
u8 aRxBuffer2[RXBUFFERSIZE2];
UART_HandleTypeDef UART2_Handler;

u8 lenRxUSART3=0;
bool isUSART3RxFinish=false;
u8 USART3_RX_BUF[USART3_REC_LEN];
u8 aRxBuffer3[RXBUFFERSIZE3];
UART_HandleTypeDef UART3_Handler;

u8 lenRxUART5=0;
bool isUART5RxFinish=false;
u8 UART5_RX_BUF[UART5_REC_LEN];
u8 aRxBuffer5[RXBUFFERSIZE5];
UART_HandleTypeDef UART5_Handler;


u8 aRxBuffer6[RXBUFFERSIZE6];
UART_HandleTypeDef UART6_Handler;

void uart_init(u32 bound)
{	
	UART1_Handler.Instance=USART1;	
	UART1_Handler.Init.BaudRate=bound;	
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; 
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	
	UART1_Handler.Init.Parity=UART_PARITY_NONE;	
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; 
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		 
	HAL_UART_Init(&UART1_Handler);					 
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);
}

void uart2_init(u32 bound)
{	
	UART2_Handler.Instance=USART2;	
	UART2_Handler.Init.BaudRate=bound;	
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B; 
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	
	UART2_Handler.Init.Parity=UART_PARITY_NONE;	
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; 
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		 
	HAL_UART_Init(&UART2_Handler);					 
	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)aRxBuffer2, RXBUFFERSIZE2);
}

void uart3_init(u32 bound)
{	
	UART3_Handler.Instance=USART3;	
	UART3_Handler.Init.BaudRate=bound;	
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B; 
	UART3_Handler.Init.StopBits=UART_STOPBITS_1;	
	UART3_Handler.Init.Parity=UART_PARITY_NONE;	
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; 
	UART3_Handler.Init.Mode=UART_MODE_TX_RX;		 
	HAL_UART_Init(&UART3_Handler);					 
	HAL_UART_Receive_IT(&UART3_Handler, (u8 *)aRxBuffer3, RXBUFFERSIZE3);
}


void uart5_init(u32 bound)
{	
	UART5_Handler.Instance=UART5;	
	UART5_Handler.Init.BaudRate=bound;	
	UART5_Handler.Init.WordLength=UART_WORDLENGTH_8B; 
	UART5_Handler.Init.StopBits=UART_STOPBITS_1;	
	UART5_Handler.Init.Parity=UART_PARITY_NONE;	
	UART5_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; 
	UART5_Handler.Init.Mode=UART_MODE_TX_RX;		 
	HAL_UART_Init(&UART5_Handler);					 
	HAL_UART_Receive_IT(&UART5_Handler, (u8 *)aRxBuffer5,RXBUFFERSIZE5);
}

void uart6_init(u32 bound)
{	
	UART6_Handler.Instance=USART6;	
	UART6_Handler.Init.BaudRate=bound;	
	UART6_Handler.Init.WordLength=UART_WORDLENGTH_8B; 
	UART6_Handler.Init.StopBits=UART_STOPBITS_1;	
	UART6_Handler.Init.Parity=UART_PARITY_NONE;	
	UART6_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; 
	UART6_Handler.Init.Mode=UART_MODE_TX_RX;		 
	HAL_UART_Init(&UART6_Handler);					 
	HAL_UART_Receive_IT(&UART6_Handler, (u8 *)aRxBuffer6, RXBUFFERSIZE6);
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//串口1接收回调
	if(huart->Instance==USART1)
	{
		if((USART_RX_STA&0x8000)==0)
		{
			if(USART_RX_STA&0x4000)
			{
				if(aRxBuffer[0]!=0x0a)
					USART_RX_STA=0;
				else 
					USART_RX_STA|=0x8000;	
			}
			else
			{
				if(aRxBuffer[0]==0x0d)
					USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;  
				}		 
			}
		}
	}
	//串口2接收回调	
	else if(huart->Instance==USART2)
	{
		if((USART2_RX_STA&0x8000)==0)
		{
			if(USART2_RX_STA&0x4000)
			{
				if(aRxBuffer2[0]!=0x0a)
					USART2_RX_STA=0;
				else 
					USART2_RX_STA|=0x8000;	
			}
			else
			{
				if(aRxBuffer2[0]==0x0d)
					USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=aRxBuffer2[0] ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_REC_LEN-1))
						USART2_RX_STA=0;  
				}		 
			}
		}
	}
	//串口3接收回调	
	else if(huart->Instance==USART3)
	{
		if(isUSART3RxFinish==false)//the highest bit is the flag of completed
		{
			//LED2_Toggle;
				if(aRxBuffer3[0]==0x0d)//回车键
					isUSART3RxFinish=true;
				else{
					USART3_RX_BUF[lenRxUSART3]=aRxBuffer3[0] ;
					lenRxUSART3++;
					//接收缓存溢出
					if(lenRxUSART3>(USART3_REC_LEN-1))
						lenRxUSART3=0;
				}
		}
		
	}
	
		//串5接收回调	
	else if(huart->Instance==UART5)
	{
		if(isUART5RxFinish==false)//the highest bit is the flag of completed
		{
				if(aRxBuffer5[0]==0x0d)//回车键
					isUART5RxFinish=true;
				else{
					UART5_RX_BUF[lenRxUART5]=aRxBuffer5[0] ;
					lenRxUART5++;
					//接收缓存溢出
					if(lenRxUART5>(UART5_REC_LEN-1))
						lenRxUART5=0;
				}
		}
	}
	

}


void USART1_IRQHandler(void)                	
{ 
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_3);
	u32 timeout=0;
    u32 maxDelay=0x1FFFF;
#if SYSTEM_SUPPORT_OS	
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART1_Handler);
	
	timeout=0;
    while (HAL_UART_GetState(&UART1_Handler)!=HAL_UART_STATE_READY)
	{
        timeout++;
        if(timeout>maxDelay) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler,(u8 *)aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//????????,?????????RxXferCount?1
	{
        timeout++;
        if(timeout>maxDelay) break;	
	}
#if SYSTEM_SUPPORT_OS	
	OSIntExit();  											 
#endif

}



void USART2_IRQHandler(void)                	
{ 
	u32 timeout=0;
  u32 maxDelay=0x1FFFF;	
	HAL_UART_IRQHandler(&UART2_Handler);
  while (HAL_UART_GetState(&UART2_Handler)!=HAL_UART_STATE_READY)
	{
			timeout++;
			if(timeout>maxDelay) 
				break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler,(u8 *)aRxBuffer2, RXBUFFERSIZE2)!=HAL_OK)
	{
			timeout++;
			if(timeout>maxDelay)
				break;	
	}
}

void USART3_IRQHandler(void)                	
{
	u32 timeout=0;
  u32 maxDelay=0x1FFFF;	
	HAL_UART_IRQHandler(&UART3_Handler);
  while (HAL_UART_GetState(&UART3_Handler)!=HAL_UART_STATE_READY)
	{
			timeout++;
			if(timeout>maxDelay) 
				break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART3_Handler,(u8 *)aRxBuffer3, RXBUFFERSIZE3)!=HAL_OK)
	{
			timeout++;
			if(timeout>maxDelay)
				break;	
	}
	//测试
//		HAL_UART_Transmit(&UART3_Handler,(uint8_t*)aRxBuffer3,1,1000);
}


void UART5_IRQHandler(void)                	
{ 
	u32 timeout=0;
  u32 maxDelay=0x1FFFF;	
	HAL_UART_IRQHandler(&UART5_Handler);
  while (HAL_UART_GetState(&UART5_Handler)!=HAL_UART_STATE_READY)
	{
			timeout++;
			if(timeout>maxDelay) 
				break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART5_Handler,(u8 *)aRxBuffer5, RXBUFFERSIZE5)!=HAL_OK)
	{
			timeout++;
			if(timeout>maxDelay)
				break;	
	}
}


u8 numArr[30];
void USART1_SendNumber(int num)
{
	int i=0;
	u8 stringLen=0;
	if(num<=0){//?????
		if(num==0)
		{
			USART_RX_BUF[0]='0';
			USART_RX_BUF[1]=' ';
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,2,1000);
			return;
		}
		num=-num;
		USART_RX_BUF[0]='-';
		HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,1,1000);
	}
	
	for(;num>0;i++){
		USART_RX_BUF[i]=num%10+'0';
		num=num/10;
	}
	i--;
	stringLen=i;
	for(;i>=0;i--){
		numArr[stringLen-i]=USART_RX_BUF[i];
	}
	numArr[stringLen+1]=32;
	
	USART_RX_BUF[i]=32;//??
	HAL_UART_Transmit(&UART1_Handler,(uint8_t*)numArr,stringLen+2,1000);
}


u8 numArr2[30];
void USART2_SendNumber(int num)
{
	int i=0;
	u8 stringLen=0;
	if(num<=0){//?????
		if(num==0)
		{
			USART_RX_BUF[0]='0';
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,1,1000);
			return;
		}
		num=-num;
		USART_RX_BUF[0]='-';
		HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,1,1000);
	}
	
	for(;num>0;i++){
		USART_RX_BUF[i]=num%10+'0';
		num=num/10;
	}
	i--;
	stringLen=i;
	for(;i>=0;i--){
		numArr[stringLen-i]=USART_RX_BUF[i];
	}
	numArr[stringLen+1]=32;
	
	USART_RX_BUF[i]=32;//??
	HAL_UART_Transmit(&UART1_Handler,(uint8_t*)numArr,stringLen+2,1000);
}

u8 numArr3[30];
void USART3_SendNumber(int num)
{
	int i=0;
	u8 stringLen=0;
	if(num<=0){//?????
		if(num==0)
		{
			USART3_RX_BUF[0]='0';
			HAL_UART_Transmit(&UART3_Handler,(uint8_t*)USART3_RX_BUF,1,1000);
			return;
		}
		num=-num;
		USART3_RX_BUF[0]='-';
		HAL_UART_Transmit(&UART3_Handler,(uint8_t*)USART3_RX_BUF,1,1000);
	}
	
	for(;num>0;i++){
		USART3_RX_BUF[i]=num%10+'0';
		num=num/10;
	}
	i--;
	stringLen=i;
	for(;i>=0;i--){
		numArr3[stringLen-i]=USART3_RX_BUF[i];
	}
	numArr3[stringLen+1]=32;
	
	USART3_RX_BUF[i]=32;//??
	HAL_UART_Transmit(&UART3_Handler,(uint8_t*)numArr3,stringLen+2,1000);
}


