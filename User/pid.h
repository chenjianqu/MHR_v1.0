#ifndef _PID_H
#define _PID_H
#include "car.h"

typedef struct {
	float setValue;
	float current_value;
	float err;
	float last_err;
	float last_last_err;
	float Ki, Kp, Kd;//PID
	float output;
	float integral;
	float flagIntegral;
} PID_Typedef;



#define GET_ENCODER_DATA 		mcn.MotorLF=mc.MotorLF;\
		mcn.MotorRF=mc.MotorRF;\
		mcn.MotorLR=mc.MotorLR;	\
		mcn.MotorRR=mc.MotorRR;\
		mc.MotorLF=0;\
		mc.MotorLR=0;\
		mc.MotorRF=0;\
		mc.MotorRR=0;\



extern PID_Typedef PID_MLF;
extern PID_Typedef PID_MRF;
extern PID_Typedef PID_MLR;
extern PID_Typedef PID_MRR;

extern PID_Typedef PID_Car;
extern MotorSpeedManager msm;
extern MotorCounter mcn;

void PID_Init(PID_Typedef *PID);
float GetPID(float value,PID_Typedef *PID);
void PID_Init_Motor(PID_Typedef *PID);
float GetPID_Motor(float value,float current,PID_Typedef *PID);

void AvgSpeedMove(u16 speed);

void ProMotorSpeed(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear);

void AvgMotorSpeed(u16 speed);

void FixMotorSpeed_FB(u16 speedA,u16 speedB);
void FixMotorSpeed_FB2(u16 speedA,u16 speedB);
void FixMotorSpeed_LR(u16 speedA,u16 speedB);

#endif
