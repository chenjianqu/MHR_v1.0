#include "main_func.h"
#include "lcd.h"
#include "run.h"
#include "handle.h"



float setValue=0;
float lastSetValue=0;
float pidValue=0;

u16 tick=0;


u16 t=0;

void SetPID_Speed(void);



void SetPID_Speed(void)
{	
	//初始速度
	if(car.flagHighSpeedDelay>0)
		car.speedBase=SPEED_LEVEL_0;
	//距离为2的时候
	else if((car.dir==DIR_X_N&&car.terminalPoint.x-car.currentPoint.x==-2)
				||(car.dir==DIR_X_P&&car.terminalPoint.x-car.currentPoint.x==2)
				||(car.dir==DIR_Y_N&&car.terminalPoint.y-car.currentPoint.y==-2)
				||(car.dir==DIR_Y_P&&car.terminalPoint.y-car.currentPoint.y==2)
		)
		car.speedBase=SPEED_LEVEL_2;
	//距离为1的时候
	else if((car.dir==DIR_X_N&&car.terminalPoint.x-car.currentPoint.x==-1)
				||(car.dir==DIR_X_P&&car.terminalPoint.x-car.currentPoint.x==1)
				||(car.dir==DIR_Y_N&&car.terminalPoint.y-car.currentPoint.y==-1)
				||(car.dir==DIR_Y_P&&car.terminalPoint.y-car.currentPoint.y==1)
	)
	{
		if(car.flagUpdatePoint==0)
			car.speedBase=SPEED_LEVEL_3;
		else//车的前面的传感器前到达
			car.speedBase=SPEED_LEVEL_4;
	}
	else
		car.speedBase=SPEED_LEVEL_1;//正常速度
}




void SendInformationToPC(void)
{
		//TrackSensorTest();
		SendString("dir:",4);
		SendNumber(car.dir);
	/*
		SendString("dir_r:",6);
		SendNumber(car.dir_r);*/
		SendEndl();
	
		SendString("cp:(",4);
		SendNumber(car.currentPoint.x);
		SendString(",",1);
		SendNumber(car.currentPoint.y);
		SendStringEndl(")",1);
		SendEndl();
		SendString("tp:(",4);
		SendNumber(car.terminalPoint.x);
		SendString(",",1);
		SendNumber(car.terminalPoint.y);
		SendStringEndl(")",1);
		SendEndl();
		SendString("up:",3);
		SendNumber(car.flagUpdatePoint);
		SendEndl();
		SendEndl();
}

void SendInformationToBL(void)
{
//		SendString_BL("dir=",4);
//		SendNumber_BL(car.dir);
/*		SendString_BL("A=",2);
		SendNumber_BL(car.speedA);
		SendString_BL("B=",2);
		SendNumber_BL(car.speedB);
		SendEndl_BL();
	*/
		SendString_BL("pos=",4);
		SendNumber_BL(car.pos);
		SendNumber_BL(car.currentPoint.x);
		SendNumber_BL(car.currentPoint.y);
		SendEndl_BL();

		SendEndl_BL();
}


void CarRunTrackPID2(void)
{
	#define TS_LIMITE_1 180
	#define TS_LIMITE_2 400
	#define ERRER_COE 2.5f
		
	switch(car.dir)
	{
		case DIR_X_N:
				SetPID_Speed();
		
			setValue=TrackErrForward();
			if(setValue<0.1f && setValue>-0.1f)
				setValue=lastSetValue;
			else
				lastSetValue=setValue;
			pidValue=GetPID(setValue,&PID_Car)/ERRER_COE;
			
			
			if(TSB1){
				pidValue=-TS_LIMITE_2;
			}
			else if(TSB8){
				pidValue=TS_LIMITE_2;
			}
			else if(TSB2){
				pidValue=-TS_LIMITE_1;
			}
			else if(TSB7){
				pidValue=TS_LIMITE_1;
			}
			if(pidValue<-TS_LIMITE_2)pidValue=-TS_LIMITE_2;
			else if(pidValue>TS_LIMITE_2)pidValue=TS_LIMITE_2;
			
			pidValue/=1.5f;
			
			
			
			car.speedA=car.speedBase+pidValue;
			car.speedB=car.speedBase-pidValue;
			
			if(pidValue<0){
				car.speedC=car.speedBase-pidValue;
				ProMotorSpeed(car.speedB,car.speedC,car.speedA,car.speedB);
				CarForwardSetFixedSpeed();
			}
			else{
				car.speedC=car.speedBase+pidValue;
				ProMotorSpeed(car.speedC,car.speedA,car.speedA,car.speedB);
				CarForwardSetFixedSpeed();
			}
			
		/*	
					tick++;
		if(tick==100)
		{
			tick=0;
			SendNumber(msm.MotorLF);
			SendNumber(msm.MotorRF);
			SendNumber(msm.MotorLR);
			SendNumber(msm.MotorRR);
			SendEndl();
			SendNumber(mcn.MotorLF);
			SendNumber(mcn.MotorRF);
			SendNumber(mcn.MotorLR);
			SendNumber(mcn.MotorRR);
			SendEndl();
			
			SendNumber(car.speedA);
			SendNumber(car.speedB);
			SendNumber(car.speedC);
			SendEndl();
			SendEndl();
			delay_ms(10);
		}
		*/
			break;
			
		
		case DIR_X_P:			
			SetPID_Speed();
			setValue=TrackErrBackward();
			if(setValue<0.1f && setValue>-0.1f)
				setValue=lastSetValue;
			else
				lastSetValue=setValue;
			pidValue=GetPID(setValue,&PID_Car)/ERRER_COE;
				
			if(TSA1)
				pidValue=-TS_LIMITE_2;
			else if(TSA8)
				pidValue=TS_LIMITE_2;
			if(TSA2)
				pidValue=-TS_LIMITE_1;
			else if(TSA7)
				pidValue=TS_LIMITE_1;
			
			car.speedA=car.speedBase+pidValue;
			car.speedB=car.speedBase-pidValue;
			
			if(pidValue<0){
				car.speedC=car.speedBase-pidValue;
				ProMotorSpeed(car.speedB,car.speedA,car.speedC,car.speedB);
				CarBackwardSetFixedSpeed();
			}
			else{
				car.speedC=car.speedBase+pidValue;
				ProMotorSpeed(car.speedB,car.speedA,car.speedA,car.speedC);
				CarBackwardSetFixedSpeed();
				//CarBack(car.speedB,car.speedA,car.speedA,car.speedC);
			}			
			//测试
			if(t==100)
			{
				t=0;
				SendNumber(car.speedA);
				SendNumber(car.speedC);
				SendNumber(car.speedB);
				SendNumber((int)pidValue);
				SendEndl();
			}
			
			t++;
			
			break;
			
		case DIR_Y_N:
			SetPID_Speed();
			
			setValue=TrackErrForward();
			if(setValue<0.1f && setValue>-0.1f)
				setValue=lastSetValue;
			else
				lastSetValue=setValue;
			pidValue=GetPID(setValue,&PID_Car)/ERRER_COE;
			
			if(TSB1)
				pidValue=-TS_LIMITE_2;
			else if(TSB8)
				pidValue=TS_LIMITE_2;
			else if(TSB2)
				pidValue=-TS_LIMITE_1;
			else if(TSB7)
				pidValue=TS_LIMITE_1;
			
			pidValue/=2.0f;
			
			car.speedA=car.speedBase+pidValue;
			car.speedB=car.speedBase-pidValue;
			
			if(pidValue<0){
				car.speedC=car.speedBase-pidValue;
				ProMotorSpeed(car.speedB,car.speedC,car.speedA,car.speedB);
				CarForwardSetFixedSpeed();
//				CarForward(car.speedB,car.speedC,car.speedA,car.speedB);
			}
			else{
				car.speedC=car.speedBase+pidValue;
				//CarForward(car.speedC,car.speedA,car.speedA,car.speedB);
				ProMotorSpeed(car.speedC,car.speedA,car.speedA,car.speedB);
				CarForwardSetFixedSpeed();
			}
			break;
			
			
		case DIR_Y_P:
			SetPID_Speed();
			
			setValue=TrackErrBackward();
			if(setValue<0.1f && setValue>-0.1f)
				setValue=lastSetValue;
			else
				lastSetValue=setValue;
			pidValue=GetPID(setValue,&PID_Car)/ERRER_COE;
			
			
			if(TSA1)
				pidValue=-TS_LIMITE_2;
			else if(TSA8)
				pidValue=TS_LIMITE_2;
			if(TSA2)
				pidValue=-TS_LIMITE_1;
			else if(TSA7)
				pidValue=TS_LIMITE_1;
			
			pidValue/=2.0f;
			
			car.speedA=car.speedBase+pidValue;
			car.speedB=car.speedBase-pidValue;
			
			if(pidValue<0){
				car.speedC=car.speedBase-pidValue;
				ProMotorSpeed(car.speedB,car.speedA,car.speedC,car.speedB);
				CarBackwardSetFixedSpeed();
			}
			else{
				car.speedC=car.speedBase+pidValue;
				ProMotorSpeed(car.speedB,car.speedA,car.speedA,car.speedC);
				CarBackwardSetFixedSpeed();
				//CarBack(car.speedB,car.speedA,car.speedA,car.speedC);
			}
			
			break;
		default:
			break;
	}
}












void CarLeftPID(void)
{
	#define ERROR_COE_LEFT 2.0f
	#define TS_LIMITE_1_L 250
	
	#define TS_LIMITE_2_L 350
		
		setValue=TrackErrLeft();
		if(setValue<0.1f && setValue>-0.1f)
			setValue=lastSetValue;
		else
			lastSetValue=setValue;
		pidValue=GetPID(setValue,&PID_Car)/ERROR_COE_LEFT;
		
		
		if(TSE1){
			pidValue=-TS_LIMITE_2_L;
		}
		else if(TSE8){
			pidValue=TS_LIMITE_2_L;
		}
		else if(TSE2){
			pidValue=-TS_LIMITE_1_L;
		}
		else if(TSE7){
			pidValue=TS_LIMITE_1_L;
		}
		
		if(pidValue<-TS_LIMITE_2_L)pidValue=-TS_LIMITE_2_L;
		else if(pidValue>TS_LIMITE_2_L)pidValue=TS_LIMITE_2_L;
		else if(pidValue<-TS_LIMITE_1_L)pidValue=-TS_LIMITE_1_L;
		else if(pidValue>TS_LIMITE_1_L)pidValue=TS_LIMITE_1_L;
		
		pidValue/=2.0f;
		
		
		car.speedA=car.speedBase+pidValue*2;
		car.speedB=car.speedBase-pidValue*2;
		
		if(pidValue<0){
			ProMotorSpeed(car.speedB,car.speedBase,car.speedA,car.speedBase);
			CarLeftSetFixedSpeed();
		}
		else{
			//顺时针旋转 通过向左平动
			ProMotorSpeed(car.speedB,car.speedBase,car.speedA,car.speedBase);
			CarLeftSetFixedSpeed();
		}
}


void CarRightPID(void)
{
	#define ERROR_COE_RIGHT 2.0f
	#define TS_LIMITE_1_R 150
	
	#define TS_LIMITE_2_R 250
		
		setValue=TrackErrRight();
		if(setValue<0.1f && setValue>-0.1f)
			setValue=lastSetValue;
		else
			lastSetValue=setValue;
		pidValue=GetPID(setValue,&PID_Car)/ERROR_COE_RIGHT;
		
		
		if(TSE1){
			pidValue=TS_LIMITE_2_R;
		}
		else if(TSE8){
			pidValue=-TS_LIMITE_2_R;
		}
		else if(TSE2){
			pidValue=TS_LIMITE_1_R;
		}
		else if(TSE7){
			pidValue=-TS_LIMITE_1_R;
		}
		
		if(pidValue<-TS_LIMITE_2_R)pidValue=-TS_LIMITE_2_R;
		else if(pidValue>TS_LIMITE_2_R)pidValue=TS_LIMITE_2_R;
		else if(pidValue<-TS_LIMITE_1_R)pidValue=-TS_LIMITE_1_R;
		else if(pidValue>TS_LIMITE_1_R)pidValue=TS_LIMITE_1_R;
		
		
		pidValue/=2.0f;
		
		
		car.speedA=car.speedBase+pidValue*2;
		car.speedB=car.speedBase-pidValue*2;
		
		if(pidValue<0){
			ProMotorSpeed(car.speedBase,car.speedA,car.speedBase,car.speedB);
			CarRightSetFixedSpeed();
		}
		else{
			//顺时针旋转 通过向左平动
			ProMotorSpeed(car.speedBase,car.speedA,car.speedBase,car.speedB);
			CarRightSetFixedSpeed();
		}
}





void CarForwardPID(void)
{
	#define ERROR_COE_FORWARD 3.0f
	#define TS_LIMITE_1_F 200
	#define TS_LIMITE_2_F 300

		setValue=TrackErrForward();
		if(setValue<0.1f && setValue>-0.1f)
			setValue=lastSetValue;
		else
			lastSetValue=setValue;
		pidValue=GetPID(setValue,&PID_Car)/ERROR_COE_FORWARD;
		
		
		if(TSB1){
			pidValue=-TS_LIMITE_2_F;
		}
		else if(TSB8){
			pidValue=TS_LIMITE_2_F;
		}
		else if(TSB2){
			pidValue=-TS_LIMITE_1_F;
		}
		else if(TSB7){
			pidValue=TS_LIMITE_1_F;
		}
		
		if(pidValue<-TS_LIMITE_2)pidValue=-TS_LIMITE_2;
		else if(pidValue>TS_LIMITE_2)pidValue=TS_LIMITE_2;
		
		pidValue/=2.0f;
		
		
		car.speedA=car.speedBase+pidValue;
		car.speedB=car.speedBase-pidValue;
		
		
		if(pidValue<0){
			float t=pidValue/4;
			ProMotorSpeed(car.speedBase+4*t,car.speedBase-4*t,car.speedBase+2*t,car.speedBase-2*t);
			CarForwardSetFixedSpeed();
		}
		else{
			float t=pidValue/4;
			ProMotorSpeed(car.speedBase+4*t,car.speedBase-4*t,car.speedBase+2*t,car.speedBase-2*t);
			CarForwardSetFixedSpeed();
		}
}

void CarBackwardPID(void)
{
	#define ERROR_COE_BACKWARD 3.0f
	#define TS_LIMITE_1_B 200
	#define TS_LIMITE_2_B 300
		
	static u16 i=0;

		setValue=TrackErrBackward();
		if(setValue<0.1f && setValue>-0.1f)
			setValue=lastSetValue;
		else
			lastSetValue=setValue;
		pidValue=GetPID(setValue,&PID_Car)/ERROR_COE_BACKWARD;
		
		
		if(TSA1){
			pidValue=-TS_LIMITE_2_B;
		}
		else if(TSA8){
			pidValue=TS_LIMITE_2_B;
		}
		else if(TSA2){
			pidValue=-TS_LIMITE_1_B;
		}
		else if(TSA7){
			pidValue=TS_LIMITE_1_B;
		}
		
		if(pidValue<-TS_LIMITE_2_B)pidValue=-TS_LIMITE_2_B;
		else if(pidValue>TS_LIMITE_2_B)pidValue=TS_LIMITE_2_B;
		else if(pidValue<-TS_LIMITE_1_B)pidValue=-TS_LIMITE_1_B;
		else if(pidValue>TS_LIMITE_1_B)pidValue=TS_LIMITE_1_B;
		
		pidValue/=2.0f;
		
		
		if(pidValue<0){
			float t=pidValue/4;
			ProMotorSpeed(car.speedBase-2*t,car.speedBase+2*t,car.speedBase-4*t,car.speedBase+4*t);
			CarBackwardSetFixedSpeed();
		}
		else{
			float t=pidValue/4;
			ProMotorSpeed(car.speedBase-2*t,car.speedBase+2*t,car.speedBase-4*t,car.speedBase+4*t);
			CarBackwardSetFixedSpeed();
		}
}
bool DecideWetherRotation(void)
{
	bool isNeedRotation=false;
	switch(car.dir)
	{
		case DIR_X_P:
			if(car.last_dir==DIR_Y_N){
				car.dir_r=R_CW90;
				isNeedRotation=true;
			}
			else if(car.last_dir==DIR_Y_P){
				car.dir_r=R_CW90;
				isNeedRotation=true;
			}
			break;
		case DIR_X_N:
			if(car.last_dir==DIR_Y_N){
				car.dir_r=R_CW90;
				isNeedRotation=true;
			}
			else if(car.last_dir==DIR_Y_P){
				car.dir_r=R_CW90;
				isNeedRotation=true;
			}
			break;
		case DIR_Y_P:
			if(car.last_dir==DIR_X_N){
				car.dir_r=R_CCW90;
				isNeedRotation=true;
			}
			else if(car.last_dir==DIR_X_P){
				car.dir_r=R_CCW90;
				isNeedRotation=true;
			}
			break;
		case DIR_Y_N:
			if(car.last_dir==DIR_X_N){
				car.dir_r=R_CCW90;
				isNeedRotation=true;
			}
			else if(car.last_dir==DIR_X_P){
				car.dir_r=R_CCW90;
				isNeedRotation=true;
			}
			break;
		default:
			break;
	}
	return isNeedRotation;
}
