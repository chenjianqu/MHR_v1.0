#ifndef _MYUART_H
#define _MYUART_H
#include "sys.h"
//#include "stm32f4xx_hal_uart.h"
#include "delay.h"
#include "led.h"
	
#define USART_REC_LEN  			100 
#define USART2_REC_LEN  		100
#define USART3_REC_LEN  		100
#define UART5_REC_LEN  		100

#define EN_USART1_RX 			1	
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;
extern UART_HandleTypeDef UART1_Handler; 

extern u8  USART2_RX_BUF[USART2_REC_LEN]; 
extern u16 USART2_RX_STA;
extern UART_HandleTypeDef UART2_Handler; 

extern u8 lenRxUSART3;
extern bool isUSART3RxFinish;
extern u8  USART3_RX_BUF[USART3_REC_LEN]; 
extern UART_HandleTypeDef UART3_Handler; 

extern u8 lenRxUART5;
extern bool isUART5RxFinish;
extern u8  UART5_RX_BUF[UART5_REC_LEN]; 
extern UART_HandleTypeDef UART5_Handler;


extern UART_HandleTypeDef UART6_Handler; 


#define RXBUFFERSIZE   1
#define RXBUFFERSIZE2  1
#define RXBUFFERSIZE3  1
#define RXBUFFERSIZE5  1
#define RXBUFFERSIZE6  1

extern u8 aRxBuffer[RXBUFFERSIZE];
extern u8 aRxBuffer2[RXBUFFERSIZE2];
extern u8 aRxBuffer3[RXBUFFERSIZE3];
extern u8 aRxBuffer5[RXBUFFERSIZE5];
extern u8 aRxBuffer6[RXBUFFERSIZE6];

extern u8 orderSendToMV[2];
extern u8 newLineArray[2];

void uart_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void uart5_init(u32 bound);
void uart6_init(u32 bound);

void USART1_SendNumber(int num);
void USART2_SendNumber(int num);
void USART3_SendNumber(int num);
void UART5_SendNumber(int num);

//´®¿Ú1
#define SendNumber(num) USART1_SendNumber(num);
#define SendString(str,len) HAL_UART_Transmit(&UART1_Handler,(u8 *)str,len,1000);
#define SendEndl() HAL_UART_Transmit(&UART1_Handler,(uint8_t*)newLineArray,2,1000);
#define SendStringEndl(str,len) HAL_UART_Transmit(&UART1_Handler,(u8 *)str,len,1000);HAL_UART_Transmit(&UART1_Handler,(uint8_t*)newLineArray,2,1000);



//´®¿Ú3
#define SendNumber_BL(num) USART3_SendNumber(num);
#define SendString_BL(str,len) HAL_UART_Transmit(&UART3_Handler,(u8 *)str,len,1000);
#define SendEndl_BL() HAL_UART_Transmit(&UART3_Handler,(uint8_t*)newLineArray,2,1000);
#define SendStringEndl_BL(str,len) HAL_UART_Transmit(&UART3_Handler,(u8 *)str,len,1000);HAL_UART_Transmit(&UART3_Handler,(uint8_t*)newLineArray,2,1000);

//´®¿Ú6
#define SendChar_MV(order) orderSendToMV[0]=order;HAL_UART_Transmit(&UART6_Handler,(uint8_t*)orderSendToMV,1,1000);

#endif
