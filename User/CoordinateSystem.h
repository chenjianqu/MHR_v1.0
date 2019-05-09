#ifndef __COORDINATESYSTEM_H
#define __COORDINATESYSTEM_H
#include "sys.h"
#include "motor.h"
#include "tracksensor.h"
#include "main_func.h"
#include "car.h"


//×ø±ê¸üÐÂ
void UpdateCoordinatePoint(void);

void UpdatePoint_Backward_X_P(void);
void UpdatePoint_Backward_X_N(void);
void UpdatePoint_Backward_Y_P(void);
void UpdatePoint_Backward_Y_N(void);

void UpdatePoint_Forward_Y_P(void);
void UpdatePoint_Forward_Y_N(void);
void UpdatePoint_Forward_X_P(void);
void UpdatePoint_Forward_X_N(void);
void UpdatePoint_Forward_X_N_QRC(void);

void UpdatePoint_Left_Y_P(void);
void UpdatePoint_Left_X_N(void);

void UpdatePoint_Right_Y_N(void);

void UpdateCoordinatePointNoRotation(void);


#endif
