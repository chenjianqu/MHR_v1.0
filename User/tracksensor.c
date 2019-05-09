#include "tracksensor.h"
#include "myuart.h"
#include "led.h"

u16 carHighestSpeed=300;



u8 GetTSA_Number(void)
{
	u8 i=0;
	if(TSA4)
		i=4;
	else if(TSA5)
		i=5;
	else if(TSA3)
		i=3;
	else if(TSA6)
		i=6;
	else if(TSA2)
		i=2;
	else if(TSA7)
		i=7;
	else if(TSA1)
		i=1;
	else if(TSA8)
		i=8;
	return i;
}

u8 GetTSB_Number(void)
  {
	u8 i=0;
	if(TSB4)
		i=4;
	else if(TSB5)
		i=5;
	else if(TSB3)
		i=3;
	else if(TSB6)
		i=6;
	else if(TSB2)
		i=2;
	else if(TSB7)
		i=7;
	else if(TSB1)
		i=1;
	else if(TSB8)
		i=8;
	return i;
}

u8 GetTSC_Number(void)
{
	u8 i=0;
	if(TSC3)
		i=3	;
	else if(TSC2)
		i=2;
	else if(TSC4)
		i=4;
	else if(TSC1)
		i=1;
	return i;
}

u8 GetTSD_Number(void)
{
	u8 i=0;
	if(TSD1)
		i=1;
	else if(TSD2)
		i=2;
	else if(TSD3)
		i=3;
	else if(TSD4)
		i=4;
	return i;
}

u8 GetTSE_Number(void)
{
	u8 i=0;
	if(TSE4)
		i=4;
	else if(TSE5)
		i=5;
	else if(TSE3)
		i=3;
	else if(TSE6)
		i=6;
	else if(TSE2)
		i=2;
	else if(TSE7)
		i=7;
	else if(TSE1)
		i=1;
	else if(TSE8)
		i=8;
	return i;
}


float TrackErrForward(void)
{
	float f;
	if(TSB4&&TSB5&&TSB6)
		f=1;
	else if(TSB4&&TSB6)
		f=120;
	else if(TSB5&&TSB3)
		f=-120;
	else if(TSB4&&TSB5)
		f=1;
	else if(TSB4)
		f=-70;
	else if(TSB5)
		f=70;
	else if(TSB3)
		f=-240;
	else if(TSB6)
		f=240;
	else if(TSB2)
		f=-440;
	else if(TSB7)
		f=440;
	else if(TSB1)
		f=-670;
	else if(TSB8)
		f=670;
	else
		f=0;
	return f;
}

float TrackErrBackward(void)
{
	float f;
	if(TSA4&&TSA5&&TSA6)
		f=1;
	else if(TSA4&&TSA6)
		f=120;
	else if(TSA5&&TSA3)
		f=-120;
	else if(TSA4&&TSA5)
		f=1;
	
	else if(TSA5)
		f=70;
	else if(TSA4)
		f=-10;
	else if(TSA6)
		f=240;
	else if(TSA3)
		f=-240;
	else if(TSA7)
		f=440;
	else if(TSA2)
		f=-440;
	else if(TSA1)
		f=-670;
	else if(TSA8)
		f=670;
	else
		f=0;
	return f;
}



float TrackErrLeft_NoUse(void)
{
	float f;
	if(TSC2&&TSC3)
		f=1;
	else if(TSC1&&TSC3)
		f=-100;
	else if(TSC2&&TSC4)
		f=100;
	else if(TSC2)
		f=-100;
	else if(TSC3)
		f=100;
	else if(TSC1)
		f=-300;
	else if(TSC4)
		f=300;
	else
		f=0;
	return f;
}

float TrackErrLeft(void)
{

	float f;
	if(TSE4&&TSE5&&TSE6)
		f=1;
	else if(TSE4&&TSE6)
		f=120;
	else if(TSE5&&TSE3)
		f=-120;
	else if(TSE4&&TSE5)
		f=1;
	
	else if(TSE4)
		f=-70;
	else if(TSE5)
		f=70;
	else if(TSE3)
		f=-240;
	else if(TSE6)
		f=240;
	else if(TSE2)
		f=-440;
	else if(TSE7)
		f=440;
	else if(TSE1)
		f=-670;
	else if(TSE8)
		f=670;
	else
		f=0;
	return f;

}


float TrackErrRight_NoUse(void)
{
	float f;
	if(TSD2&&TSD3)
		f=1;
	else if(TSD1&&TSD3)
		f=-200;
	else if(TSD2&&TSD4)
		f=200;
	else if(TSD2)
		f=-100;
	else if(TSD3)
		f=100;
	else if(TSD1)
		f=-300;
	else if(TSD4)
		f=300;
	else
		f=0;
	return f;

}





float TrackErrRight(void)
{

	float f;
	if(TSE4&&TSE5&&TSE6)
		f=1;
	else if(TSE4&&TSE6)
		f=-120;
	else if(TSE5&&TSE3)
		f=120;
	else if(TSE4&&TSE5)
		f=1;
	else if(TSE4)
		f=70;
	else if(TSE5)
		f=-70;
	else if(TSE3)
		f=240;
	else if(TSE6)
		f=-240;
	else if(TSE2)
		f=440;
	else if(TSE7)
		f=-440;
	else if(TSE1)
		f=670;
	else if(TSE8)
		f=-670;
	else
		f=0;
	return f;

}




void TrackForwardNoPID(u16 *speedA,u16 *speedB)
{
	u16 A=0;
	u16 B=0;
	if(TSB4&&TSB5&&TSB6)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSB4&&TSB6)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-50;
	}
	else if(TSB5&&TSB3)
	{
		A=carHighestSpeed-50;//因为看到小车老是靠左边偏,
		B=carHighestSpeed;
	}
	else if(TSB4&&TSB5)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSB4)
	{
		A=carHighestSpeed-50;
		B=carHighestSpeed;
	}
	else if(TSB5)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-50;
	}
	else if(TSB3)
	{
		A=carHighestSpeed-200;
		B=carHighestSpeed;
	}
	else if(TSB6)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-200;
	}
	else if(TSB2)
	{
		A=carHighestSpeed-300;
		B=carHighestSpeed;
	}
	else if(TSB7)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-300;
	}
	else if(TSB1)
	{
		A=carHighestSpeed-400;
		B=carHighestSpeed;
	}
	else if(TSB8)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-400;
	}
	if(A!=0)
	{
		*speedA=A;
		*speedB=B;
	}

}


void TrackBackwardNoPID(u16 *speedA,u16 *speedB)
{
	u16 A=0;
	u16 B=0;
	
	if(TSA4&&TSA5&&TSA6)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSA4&&TSA6)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-50;
	}
	else if(TSA5&&TSA3)
	{
		A=carHighestSpeed-50;
		B=carHighestSpeed;
	}
	else if(TSA4&&TSA5)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	
	//会单独跳TSA4
	else if(TSA4)
	{
		A=900;
		B=950;
	}
	else if(TSA5)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-50;
	}
	else if(TSA3)
	{
		A=carHighestSpeed-200;
		B=carHighestSpeed;
	}
	else if(TSA6)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-200;
	}
	else if(TSA2)
	{
		A=carHighestSpeed-300;
		B=carHighestSpeed;
	}
	else if(TSA7)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-300;
	}
	else if(TSA1)
	{
		A=carHighestSpeed-400;
		B=carHighestSpeed;
	}
	else if(TSA8)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-400;
	}
	if(A!=0)
	{
		*speedA=A;
		*speedB=B;
	}


}



void TrackLeftNoPID(u16 *speedA,u16 *speedB)
{
	u16 A=0;
	u16 B=0;
	
	if(TSC1&&TSC2&&TSC3&&TSC4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSC1&&TSC2&&TSC3)
	{
		A=carHighestSpeed-50;
		B=carHighestSpeed;
	}
	else if(TSC2&&TSC3&&TSC4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-50;
	}
	else if(TSC2&&TSC3)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSC1&&TSC3)
	{
		A=carHighestSpeed-100;
		B=carHighestSpeed;
	}
	else if(TSC2&&TSC4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-100;
	}
	else if(TSC2)
	{
		A=carHighestSpeed-150;
		B=carHighestSpeed;
	}
	else if(TSC3)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-150;
	}
	else if(TSC1)
	{
		A=carHighestSpeed-300;
		B=carHighestSpeed;
	}
	else if(TSC4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-300;
	}

	if(A!=0)
	{
		*speedA=A;
		*speedB=B;
	}
}


void TrackRightNoPID(u16 *speedA,u16 *speedB)
{
	u16 A=0;
	u16 B=0;
	
	if(TSD1&&TSD2&&TSD3&&TSD4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSD1&&TSD2&&TSD3)
	{
		A=carHighestSpeed-50;
		B=carHighestSpeed;
	}
	else if(TSD2&&TSD3&&TSD4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-50;
	}
	else if(TSD2&&TSD3)
	{
		A=carHighestSpeed;
		B=carHighestSpeed;
	}
	else if(TSD1&&TSD3)
	{
		A=carHighestSpeed-100;
		B=carHighestSpeed;
	}
	else if(TSD2&&TSD4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-100;
	}
	else if(TSD2)
	{
		A=carHighestSpeed-150;
		B=carHighestSpeed;
	}
	else if(TSD3)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-150;
	}
	else if(TSD1)
	{
		A=carHighestSpeed-300;
		B=carHighestSpeed;
	}
	else if(TSD4)
	{
		A=carHighestSpeed;
		B=carHighestSpeed-300;
	}

	if(A!=0)
	{
		*speedA=A;
		*speedB=B;
	}
}

void TrackSensorTest(void)
{
	if(TSA4){
		SendStringEndl("TSA4",4);
	}
	if(TSA5){
		SendStringEndl("TSA5",4);
	}
	if(TSA3){
		SendStringEndl("TSA3",4);
	}
	if(TSA6){
		SendStringEndl("TSA6",5);
	}
	if(TSA2){
		SendStringEndl("TSA2",4);
	}
	if(TSA7){
		SendStringEndl("TSA7",4);
	}
	if(TSA1){
		SendStringEndl("TSA1",4);
	}
	if(TSA8){
		SendStringEndl("TSA8",4);
	}
	
	if(TSB4){
		SendStringEndl("TSB4",4);
	}
	if(TSB5){
		SendStringEndl("TSB5",4);
	}
	if(TSB3){
		SendStringEndl("TSB3",4);
	}
	if(TSB6){
		SendStringEndl("TSB6",4);
	}
	if(TSB2){
		SendStringEndl("TSB2",4);
	}
	if(TSB7){
		SendStringEndl("TSB7",4);
	}
	if(TSB1){
		SendStringEndl("TSB1",4);
	}
	if(TSB8){
		SendStringEndl("TSB8",4);
	}
	
	if(TSC2){
		SendStringEndl("TSC2",4);
	}
	if(TSC3){
		SendStringEndl("TSC3",4);
	}
	if(TSC1){
		SendStringEndl("TSC1",4);
	}
	if(TSC4){
		SendStringEndl("TSC4",4);
	}
	
	if(TSD1){
		SendStringEndl("TSD1",4);
	}
	if(TSD2){
		SendStringEndl("TSD2",4);
	}
	if(TSD3){
		SendStringEndl("TSD3",4);
	}
	if(TSD4){
		SendStringEndl("TSD4",4);
	}
	
	if(TSE4){
		SendStringEndl("TSE4",4);
	}
	if(TSE5){
		SendStringEndl("TSE5",4);
	}
	if(TSE3){
		SendStringEndl("TSE3",4);
	}
	if(TSE6){
		SendStringEndl("TSE6",4);
	}
	if(TSE2){
		SendStringEndl("TSE2",4);
	}
	if(TSE7){
		SendStringEndl("TSE7",4);
	}
	if(TSE1){
		SendStringEndl("TSE1",4);
	}
	if(TSE8){
		SendStringEndl("TSE8",4);
	}
}


