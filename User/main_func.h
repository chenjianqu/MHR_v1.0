#ifndef __MAIN_FUNC_H
#define __MAIN_FUNC_H
#include "c.h"

extern u8 flagReadyUpdatePoint;


void CarRunTrack(void);
bool DecideWetherRotation(void);
bool DecideWetherSlowDown(void);

void CarRunTrackPID2(void);
void CarRightPID(void);
void CarLeftPID(void);
void CarForwardPID(void);
void CarBackwardPID(void);


void SendInformationToBL(void);
void SendInformationToPC(void);

#endif
