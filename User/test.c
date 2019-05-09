#include "test.h"
#include "car.h"
#include "tracksensor.h"
#include "motor.h"



void LeftTrackTest(void)
{
	TrackLeftNoPID(&car.speedA,&car.speedB);
	CarLeft(car.speedB,car.speedB,car.speedA,car.speedA);
}



void mainTest(void)
{/*
	CarFineTuningPro_Y_P();
	delay_ms(1000);
	CarFineTuningPro_Y_N();
	while(1)
		CarStop();
	
	*/
	/*
	CarTurnCounterClockwise();
	CarRunCounterClockwise(500);
	delay_ms(1000);
	CarCounterClockBrake_WithClock();
	*/
	/*
	CarTurnClockwise();
	CarRunClockwise(500);
	delay_ms(100);
	CarTurnLeft();
	CarRunLeft(500);
	CarTurnLeft();
	//CarClockBrake_WithCounterClock();
	while(1)
		CarStop();
	*/
	
	/*
	//循迹传感器测试
	while(1)
	{
		TrackSensorTest();
		delay_ms(5);
	}
	*/
	
	/*
	CarTurnForward();
	CarRunForward(300);
	while(1)
	{
	
			SendNumber(mc.MotorLF);
			SendNumber(mc.MotorRF);
			SendNumber(mc.MotorLR);
			SendNumber(mc.MotorRR);
			SendEndl();
		delay_ms(1000);
	}
	*/
	
	/*
	CarTurnForward();
	CarRunForward(999);
	u16 i=0;
	while(1)
	{
		i++;
		delay_ms(1);
		GET_ENCODER_DATA;
		if(i==100){
			i=0;
			SendNumber(mcn.MotorLF);
			SendNumber(mcn.MotorRF);
			SendNumber(mcn.MotorLR);
			SendNumber(mcn.MotorRR);
			SendEndl();
		}
	}
	*/
	//CarTurnBackward();
	/*
	CarTurnForward();
	CarForward(600,0,0,0);
	delay_ms(3000);
	CarForward(0,600,0,0);
	delay_ms(3000);
		CarForward(0,0,600,0);
	delay_ms(3000);
		CarForward(0,0,0,600);
	delay_ms(3000);
	*/
	
	
//	CarTurnLeft();
	
//	CarRunLeft(500);
//	delay_ms(10000);

/*
	CarTurnForward();
	CarRunForward(400);
	delay_ms(5000);
	
	CarTurnBackward();
	CarRunBackward(400);
	delay_ms(5000);
	
	
		CarTurnRight();
	CarRunRight(400);
	delay_ms(5000);
	
	
		CarTurnLeft();
	CarRunLeft(400);
	delay_ms(5000);
	*/
	/*
	CarTurnForward();
	u16 c=0;
	car.speedBase=400;
	while(1)
	{
		
		CarForwardPID();
		delay_ms(1);
		
		c++;
		if(c==500)
		{
			TrackSensorTest();
			SendNumber(msm.MotorLF);
			SendNumber(msm.MotorRF);
			SendNumber(msm.MotorLR);
			SendNumber(msm.MotorRR);
			SendEndl();
			SendEndl();
			c=0;
		}
	}
	*/
	
	/*
	CarTurnLeft();
	CarLeft(270,130,350,270);
	
	delay_ms(10000);
	
	
	*/
//	CarTurnLeft();
	
//	CarRunLeft(800);
//	delay_ms(10000);

MoveOne_Left_Y_P();
MoveOne_Left_Y_P();

	
	
	//CarTurnRight();
	u16 c=0;
	car.speedBase=500;
	while(1)
	{
		//CarRightPID();
		delay_ms(1);
		
		c++;
		if(c==20)
		{
			TrackSensorTest();
			SendNumber(msm.MotorLF);
			SendNumber(msm.MotorRF);
			SendNumber(msm.MotorLR);
			SendNumber(msm.MotorRR);
			SendEndl();
			SendEndl();
			c=0;
		}
	}
	
	
	
	
	//	CarTurnRight();
	
	/*
	while(1)
	{
		
		CarRightPID();
		delay_ms(20);
	}
	*/
	
	
	
	//CarRunBackward(400);
	//delay_ms(2000);
	
	CarTurnForward();
	car.terminalPoint=Point_QRCodeAera;
	car.speedBase=300;
	while(1)
	{
		UpdatePoint_Forward_X_N();
		
		CarForwardPID();
		if(car.currentPoint.x==car.terminalPoint.x)
		{
			while(1)
				CarStop();
		}
		delay_ms(1);
	}

		
	
//CarTurnLeft();
//CarRunForward(450);
//delay_ms(5000);
/*
i=0;
while(1)
{

CarTurnForward();
CarRunForward(400);
delay_ms(4000);

CarTurnRight();
CarRunRight(400);
delay_ms(4000);


CarTurnBackward();
CarRunBackward(400);
delay_ms(4000);

CarTurnLeft();
CarRunLeft(400);
delay_ms(4000);

CarStop();
delay_ms(2000);

*/
//CarTurnRight();
//CarFineTuning();




}





/*
void execPID(float t)
{
		if(t!=0)
			setpoint=t;
		//也就是说左边传感器得到的pid输出为负
		t=getPID(&PID,setpoint);		
		
		t/=68;//将t=(0-68)映射到(0-1)
		if(t<0){
			t=-t+1;
			//此时左边传感器被触发,应该向左转
			car.speedB=(u16)(SPEED_BASE+t*SPEED_EX_FAST);
			car.speedA=SPEED_BASE+SPEED_EX_SLOW;
		}
		else{
			t=t+1;
			car.speedB=SPEED_BASE+SPEED_EX_SLOW;
			car.speedA=(u16)(SPEED_BASE+t*SPEED_EX_FAST);
		}
		if(car.speedA>999)
			car.speedA=999;
		if(car.speedB>999)
			car.speedB=999;
}
*/


