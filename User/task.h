#ifndef _TASK_H
#define _TASK_H
#include "car.h"
#include "c.h"


extern Point ppc[6];

void SendAndWaitMV(u8 order);


void CarSetPipelinePoint_A(void);
void CarSetPipelinePoint_B(void);


void CarSetProcessPoint(void);
void CarSetFinishedPoint(void);

void WaitOrder(void);
void WaitOrderTest(void);

void TernimalHandle(void);
void RunTask(void);
bool equal(Point A,Point B);


void CarFineTuningFhd_X_N(void);
void CarFineTuningFhd_X_P(void);

void CarFineTuningRaw_X_N(void);
void CarFineTuningRaw_X_P(void);

void TernimalHandleNoRotation(void);
void TernimalHandleNoRotationTest(void);

void TernimalHandleNoRotationRPF(void);
void TernimalHandleNoRotationRFP(void);
void TernimalHandleNoRotationPRF(void);
void TernimalHandleNoRotationPFR(void);
void TernimalHandleNoRotationFPR(void);
void TernimalHandleNoRotationFRP(void);

void TernimalHandleNoRotationRPF_Test(void);
void TernimalHandleNoRotationRFP_Test(void);
void TernimalHandleNoRotationPRF_Test(void);
void TernimalHandleNoRotationPFR_Test(void);
void TernimalHandleNoRotationFPR_Test(void);
void TernimalHandleNoRotationFRP_Test(void);

void CarFineTuningPro(void);
void CarFineTuningPro_Y_P(void);
void CarFineTuningPro_Y_N(void);
void CarFineTuningRaw_Y_N(void);
void CarFineTuningRaw_Y_P(void);

#endif
