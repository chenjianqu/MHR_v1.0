#include "pid.h"
#include "myuart.h"

PID_Typedef PID_Car;

PID_Typedef PID_MLF;
PID_Typedef PID_MRF;
PID_Typedef PID_MLR;
PID_Typedef PID_MRR;



MotorCounter mss;



MotorCounter mcn;

void PID_Init(PID_Typedef *PID)
{
	PID->current_value = 0.0;
	PID->setValue = 0.0;
	PID->err = 0.0;
	PID->last_err = 0.0;
	PID->last_last_err = 0.0;
	PID->integral = 0.0;
	PID->Kp = 0.5;
	PID->Ki = 0.3;
	PID->Kd = 0.12;
	PID->flagIntegral = 1;
}


float GetPID(float value,PID_Typedef *PID)
{
	PID->setValue = value;
	
	PID->err = PID->setValue - PID->current_value;
	PID->integral += PID->err;

	PID->current_value = PID->Kp*PID->err + PID->Ki*PID->integral/2+ PID->Kd*(PID->err-PID->last_err);

	PID->last_err = PID->err;

	return PID->current_value;
}



void PID_Init_Motor(PID_Typedef *PID)
{
	PID->current_value = 0.0;
	PID->setValue = 0.0;
	PID->err = 0.0;
	PID->last_err = 0.0;
	PID->last_last_err = 0.0;
	PID->integral = 0.0;
	PID->Kp = 0.5;
	PID->Ki = 0.3;
	PID->Kd = 0.12;
	PID->flagIntegral = 1;
}


float GetPID_Motor(float value,float current,PID_Typedef *PID)
{
	PID->setValue = value;
	PID->current_value=current;
	
	PID->err = PID->setValue - PID->current_value;
	PID->integral += PID->err;

	PID->output = PID->Kp*PID->err + PID->Ki*PID->integral/2+ PID->Kd*(PID->err-PID->last_err);

	PID->last_err = PID->err;

	return PID->output;
}


u16 counter=0;

#define FIX_COE 1

//电机比例速度
void ProMotorSpeed(u32 valLeftFront,u32 valRightFront,u32 valLeftRear,u32 valRightRear)
{
	#define FIX_SPEED_RANGE 100
	
	u16 sl=0;
	u16 sh=0;
	u16 current=0;
	
	GET_ENCODER_DATA;
	
	//测试
	msm.MotorLF=valLeftFront;
	msm.MotorRF=valRightFront;
	msm.MotorLR=valLeftRear;
	msm.MotorRR=valRightRear;
	return;
	
	
	msm.MotorLF=valLeftFront;
	
	//RF
	sl=valRightFront-FIX_SPEED_RANGE;
	sh=valRightFront+FIX_SPEED_RANGE;
	
	if(sl<1)sl=sl;else if(sl>999)sl=999;
	if(sl<1)sh=sh;else if(sl>999)sh=999;
	
	current=(u16)(mcn.MotorRF*valLeftFront/mcn.MotorLF);//归一化得到当前pwm
	int error=valRightFront-current;
	
	if(error<-FIX_SPEED_RANGE)msm.MotorRF=sl;
	else if(error>FIX_SPEED_RANGE)msm.MotorRF=sh;
	else{
		msm.MotorRF=valRightFront+FIX_COE*error;
		msm.MotorRF=msm.MotorRF>sh?sh:(msm.MotorRF<sl?sl:msm.MotorRF);
	}
	
	
	//LR
	sl=valLeftRear-FIX_SPEED_RANGE;
	sh=valLeftRear+FIX_SPEED_RANGE;
	
	current=mcn.MotorLR*valLeftFront/mcn.MotorLF;//归一化得到当前pwm
	error=valLeftRear-current;
	
	if(error<-FIX_SPEED_RANGE)msm.MotorLR=sl;
	else if(error>FIX_SPEED_RANGE)msm.MotorLR=sh;
	else{
		msm.MotorLR=valLeftRear+FIX_COE*error;
//		msm.MotorLR=msm.MotorLR>sh?sh:(msm.MotorLR<sl?sl:msm.MotorLR);
		
		if(msm.MotorLR>sh)msm.MotorLR=sh;else if(msm.MotorLR<sl)msm.MotorLR=sl;
	}
	/*
	i++;
	if(i==100)
	{
		i=0;
		SendString("test:",5);
		SendNumber(sl);
		SendNumber(sh);
		SendNumber(valLeftRear);
		SendNumber(error);
		SendNumber(current);
		SendNumber(msm.MotorLR);
		SendEndl();
	}
	//msm.MotorLR=200;
	*/
	
	//RR
	sl=valRightRear-FIX_SPEED_RANGE;
	sh=valRightRear+FIX_SPEED_RANGE;
	
	current=mcn.MotorRR*valLeftFront/mcn.MotorLF;//归一化得到当前pwm
	error=valRightRear-current;
	
	if(error<-FIX_SPEED_RANGE)msm.MotorRR=sl;
	else if(error>FIX_SPEED_RANGE)msm.MotorRR=sh;
	else{
		msm.MotorRR=valRightRear+FIX_COE*error;
		msm.MotorRR=msm.MotorRR>sh?sh:(msm.MotorRR<sl?sl:msm.MotorRR);
	}
	
	
	
	

}


//电机平均速度
void AvgMotorSpeed(u16 speed)
{
	#define AVG_FIX_SPEED_RANGE 200
	
	u16 sl=speed-AVG_FIX_SPEED_RANGE;
	u16 sh=speed+AVG_FIX_SPEED_RANGE;
	int error=0;
	
	u32 avg=0;

	GET_ENCODER_DATA;
	
	if(counter==100)
	{
		SendNumber(mcn.MotorLF);
		SendNumber(mcn.MotorRF);
		SendNumber(mcn.MotorLR);
		SendNumber(mcn.MotorRR);
		
	}
	/*
	
		//测试
	msm.MotorLF=speed;
	msm.MotorRF=speed;
	msm.MotorLR=speed;
	msm.MotorRR=speed;
	return;
	*/
	
	avg=mcn.MotorLF;
	msm.MotorLF=speed;
		
	error=speed-(int)(speed*mcn.MotorRF/avg);//归一化到speed 得到误差 .如果LF比RF大 则大于0
	if(error<-AVG_FIX_SPEED_RANGE)msm.MotorRF=sl;
	else if(error>AVG_FIX_SPEED_RANGE)msm.MotorRF=sh;
	else{
		msm.MotorRF=speed+FIX_COE*error;
		msm.MotorRF=msm.MotorRF>sh?sh:(msm.MotorRF<sl?sl:msm.MotorRF);
	}
	
	error=speed-(int)(speed*mcn.MotorLR/avg);
	if(error<-AVG_FIX_SPEED_RANGE)msm.MotorLR=sl;
	else if(error>AVG_FIX_SPEED_RANGE)msm.MotorLR=sh;
	else{
		msm.MotorLR=speed+FIX_COE*error;
		msm.MotorLR=msm.MotorLR>sh?sh:(msm.MotorLR<sl?sl:msm.MotorLR);
	}
	
	if(error<-AVG_FIX_SPEED_RANGE)msm.MotorRR=sl;
	else if(error>AVG_FIX_SPEED_RANGE)msm.MotorRR=sh;
	else{
		error=speed-(int)(speed*mcn.MotorRR/avg);
		msm.MotorRR=speed+FIX_COE*error;
	}
		
	if(counter==100)
	{
		SendNumber(msm.MotorRR);
	}
	msm.MotorRR=msm.MotorRR>sh?sh:(msm.MotorRR<sl?sl:msm.MotorRR);

	if(counter==100)
	{
		/*
		SendNumber(error);
		SendNumber(msm.MotorLF);
		SendNumber(msm.MotorRF);
		SendNumber(msm.MotorLR);
		SendNumber(msm.MotorRR);
		SendEndl();
		*/

	}
	
	counter++;
	
	if(counter<10)
	{
		msm.MotorLF=speed;
		msm.MotorRF=speed;
		msm.MotorLR=speed;
		msm.MotorRR=speed;
	}

}






#define FIX_COE_FB 2
void FixMotorSpeed_FB(u16 speedA,u16 speedB)
{
	u16 SL_A=speedA-100;
	u16 SH_A=speedA+100;
	u16 SL_B=speedB-100;
	u16 SH_B=speedB+100;
	int error=0;
	
	float avgA=0,avgB=0;

	GET_ENCODER_DATA;
	
			
		avgA=(mcn.MotorLF+mcn.MotorLR)/2;
		avgB=(mcn.MotorRF+mcn.MotorRR)/2;
		
		mcn.MotorLF=(u32)(speedA*mcn.MotorLF/avgA);
		error=speedA-mcn.MotorLF;
		msm.MotorLF=speedA+FIX_COE_FB*error;
		if(msm.MotorLF>SH_A)msm.MotorLF=SH_A;
		else if(msm.MotorLF<SL_A)msm.MotorLF=SL_A;
		
		
		mcn.MotorRF=(u32)(speedB*mcn.MotorRF/avgB);
		error=speedB-mcn.MotorRF;
		msm.MotorRF=speedB+FIX_COE_FB*error;
		if(msm.MotorRF>SH_B)msm.MotorRF=SH_B;
		else if(msm.MotorRF<SL_B)msm.MotorRF=SL_B;
		
		mcn.MotorLR=(u32)(speedA*mcn.MotorLR/avgA);
		error=speedA-mcn.MotorLR;
		msm.MotorLR=speedA+FIX_COE_FB*error;
		if(msm.MotorLR>SH_A)msm.MotorLR=SH_A;
		else if(msm.MotorLR<SL_A)msm.MotorLR=SL_A;
		
		mcn.MotorRR=(u32)(speedB*mcn.MotorRR/avgB);
		error=speedB-mcn.MotorRR;
		msm.MotorRR=speedB+FIX_COE_FB*error;
		if(msm.MotorRR>SH_B)msm.MotorRR=SH_B;
		else if(msm.MotorRR<SL_B)msm.MotorRR=SL_B;
}


void FixMotorSpeed_FB2(u16 speedA,u16 speedB)
{
	u16 SL_A=speedA-100;
	u16 SH_A=speedA+100;
	u16 SL_B=speedB-100;
	u16 SH_B=speedB+100;
	int error=0;
	
	GET_ENCODER_DATA;
					
		msm.MotorLF=speedA;		
		msm.MotorRF=speedB;
		
		mcn.MotorLR=(u32)(speedA*mcn.MotorLR/mcn.MotorLF);
		error=speedA-mcn.MotorLR;
		msm.MotorLR=speedA+FIX_COE_FB*error;
		if(msm.MotorLR>SH_A)msm.MotorLR=SH_A;
		else if(msm.MotorLR<SL_A)msm.MotorLR=SL_A;
		
		mcn.MotorRR=(u32)(speedB*mcn.MotorRR/mcn.MotorRF);
		error=speedB-mcn.MotorRR;
		msm.MotorRR=speedB+FIX_COE_FB*error;
		if(msm.MotorRR>SH_B)msm.MotorRR=SH_B;
		else if(msm.MotorRR<SL_B)msm.MotorRR=SL_B;
}





#define SPEED_FIX_RANGE 100
void FixMotorSpeed_FB3(u16 speedA,u16 speedB)
{
	u16 SL_A=speedA-SPEED_FIX_RANGE;
	u16 SH_A=speedA+SPEED_FIX_RANGE;
	u16 SL_B=speedB-SPEED_FIX_RANGE;
	u16 SH_B=speedB+SPEED_FIX_RANGE;
	int error=0;
	
	GET_ENCODER_DATA;
					
		msm.MotorLF=speedA;		
		msm.MotorRF=speedB;
	
	/*
				//测试
	msm.MotorLF=speedA;
	msm.MotorRF=speedB;
	msm.MotorLR=speedA;
	msm.MotorRR=speedB;
	return;
	
	*/
	
		
		mcn.MotorLR=(u32)(speedB*mcn.MotorLR/mcn.MotorRF);
		error=speedB-mcn.MotorLR;
		msm.MotorLR=speedB+FIX_COE_FB*error;
		if(msm.MotorLR>SH_B)msm.MotorLR=SH_B;
		else if(msm.MotorLR<SL_B)msm.MotorLR=SL_B;
		
		mcn.MotorRR=(u32)(speedA*mcn.MotorRR/mcn.MotorLF);
		error=speedA-mcn.MotorRR;
		msm.MotorRR=speedA+FIX_COE_FB*error;
		if(msm.MotorRR>SH_A)msm.MotorRR=SH_A;
		else if(msm.MotorRR<SL_A)msm.MotorRR=SL_A;
}





void FixMotorSpeed_LR(u16 speedA,u16 speedB)
{
	u16 SL_A=speedA-100;
	u16 SH_A=speedA+100;
	u16 SL_B=speedB-100;
	u16 SH_B=speedB+100;
	int error=0;
	
	GET_ENCODER_DATA;
					
		msm.MotorLF=speedA;		
		msm.MotorLR=speedB;
		
		mcn.MotorRF=(u32)(speedA*mcn.MotorRF/mcn.MotorLF);
		error=speedA-mcn.MotorRF;
		msm.MotorRF=speedA+FIX_COE_FB*error;
		if(msm.MotorRF>SH_A)msm.MotorRF=SH_A;
		else if(msm.MotorRF<SL_A)msm.MotorRF=SL_A;
		
		mcn.MotorRR=(u32)(speedB*mcn.MotorRR/mcn.MotorLR);
		error=speedB-mcn.MotorRR;
		msm.MotorRR=speedB+FIX_COE_FB*error;
		if(msm.MotorRR>SH_B)msm.MotorRR=SH_B;
		else if(msm.MotorRR<SL_B)msm.MotorRR=SL_B;
}




void FixMotorSpeed_LR2(u16 speedA,u16 speedB)
{
	u16 SL_A=speedA-SPEED_FIX_RANGE;
	u16 SH_A=speedA+SPEED_FIX_RANGE;
	u16 SL_B=speedB-SPEED_FIX_RANGE;
	u16 SH_B=speedB+SPEED_FIX_RANGE;
	int error=0;
	
	GET_ENCODER_DATA;
	/*
	
			//测试
	msm.MotorLF=speedA;
	msm.MotorRF=speedB;
	msm.MotorLR=speedB;
	msm.MotorRR=speedA;
	return;
	*/
	
					
	msm.MotorLF=speedA;		
	msm.MotorLR=speedB;
	
	mcn.MotorRF=(u32)(speedB*mcn.MotorRF/mcn.MotorLR);
	error=speedB-mcn.MotorRF;
	msm.MotorRF=speedB+FIX_COE_FB*error;
	if(msm.MotorRF>SH_B)msm.MotorRF=SH_B;
	else if(msm.MotorRF<SL_B)msm.MotorRF=SL_B;
	
	mcn.MotorRR=(u32)(speedA*mcn.MotorRR/mcn.MotorLF);
	error=speedA-mcn.MotorRR;
	msm.MotorRR=speedA+FIX_COE_FB*error;
	if(msm.MotorRR>SH_A)msm.MotorRR=SH_A;
	else if(msm.MotorRR<SL_A)msm.MotorRR=SL_A;
}





