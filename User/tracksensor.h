#ifndef _TRACKSENSOR_H
#define _TRACKSENSOR_H
#include <sys.h>	  
#include "main.h"
#include "myuart.h"

#define TSA1 HAL_GPIO_ReadPin(TSA1_GPIO_Port,TSA1_Pin)
#define TSA2 HAL_GPIO_ReadPin(TSA2_GPIO_Port,TSA2_Pin)
#define TSA3 HAL_GPIO_ReadPin(TSA3_GPIO_Port,TSA3_Pin)
#define TSA4 HAL_GPIO_ReadPin(TSA4_GPIO_Port,TSA4_Pin)
#define TSA5 HAL_GPIO_ReadPin(TSA5_GPIO_Port,TSA5_Pin)
#define TSA6 HAL_GPIO_ReadPin(TSA6_GPIO_Port,TSA6_Pin)
#define TSA7 HAL_GPIO_ReadPin(TSA7_GPIO_Port,TSA7_Pin)
#define TSA8 HAL_GPIO_ReadPin(TSA8_GPIO_Port,TSA8_Pin)

#define TSB1 HAL_GPIO_ReadPin(TSB1_GPIO_Port,TSB1_Pin)
#define TSB2 HAL_GPIO_ReadPin(TSB2_GPIO_Port,TSB2_Pin)
#define TSB3 HAL_GPIO_ReadPin(TSB3_GPIO_Port,TSB3_Pin)
#define TSB4 HAL_GPIO_ReadPin(TSB4_GPIO_Port,TSB4_Pin)
#define TSB5 HAL_GPIO_ReadPin(TSB5_GPIO_Port,TSB5_Pin)
#define TSB6 HAL_GPIO_ReadPin(TSB6_GPIO_Port,TSB6_Pin)
#define TSB7 HAL_GPIO_ReadPin(TSB7_GPIO_Port,TSB7_Pin)
#define TSB8 HAL_GPIO_ReadPin(TSB8_GPIO_Port,TSB8_Pin)


#define TSC1 HAL_GPIO_ReadPin(TSC1_GPIO_Port,TSC1_Pin)
#define TSC2 HAL_GPIO_ReadPin(TSC2_GPIO_Port,TSC2_Pin)
#define TSC3 HAL_GPIO_ReadPin(TSC3_GPIO_Port,TSC3_Pin)
#define TSC4 HAL_GPIO_ReadPin(TSC4_GPIO_Port,TSC4_Pin)

#define TSD1 HAL_GPIO_ReadPin(TSD1_GPIO_Port,TSD1_Pin)
#define TSD2 HAL_GPIO_ReadPin(TSD2_GPIO_Port,TSD2_Pin)
#define TSD3 HAL_GPIO_ReadPin(TSD3_GPIO_Port,TSD3_Pin)
#define TSD4 HAL_GPIO_ReadPin(TSD4_GPIO_Port,TSD4_Pin)


#define TSE1 HAL_GPIO_ReadPin(TSE1_GPIO_Port,TSE1_Pin)
#define TSE2 HAL_GPIO_ReadPin(TSE2_GPIO_Port,TSE2_Pin)
#define TSE3 HAL_GPIO_ReadPin(TSE3_GPIO_Port,TSE3_Pin)
#define TSE4 HAL_GPIO_ReadPin(TSE4_GPIO_Port,TSE4_Pin)
#define TSE5 HAL_GPIO_ReadPin(TSE5_GPIO_Port,TSE5_Pin)
#define TSE6 HAL_GPIO_ReadPin(TSE6_GPIO_Port,TSE6_Pin)
#define TSE7 HAL_GPIO_ReadPin(TSE7_GPIO_Port,TSE7_Pin)
#define TSE8 HAL_GPIO_ReadPin(TSE8_GPIO_Port,TSE8_Pin)


extern u8 newLineArray[2];
extern u16 carHighestSpeed;

float TrackErrBackward(void);
float TrackErrForward(void);
float TrackErrLeft(void);
float TrackErrRight(void);

void TrackForwardNoPID(u16 *speedA,u16 *speedB);
void TrackBackwardNoPID(u16 *speedA,u16 *speedB);
void TrackRightNoPID(u16 *speedA,u16 *speedB);
void TrackLeftNoPID(u16 *speedA,u16 *speedB);


u8 GetTSA_Number(void);
u8 GetTSB_Number(void);
u8 GetTSC_Number(void);
u8 GetTSD_Number(void);
u8 GetTSE_Number(void);

void TrackSensorTest(void);

#endif

