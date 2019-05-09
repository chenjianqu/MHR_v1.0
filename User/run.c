#include "run.h"
#include "c.h"
#include "math.h"


u8 flagResetPosition=0;

u8 flagCCW=0;

void CarBrake(void)
{
	switch(car.dir)
	{
		case DIR_X_N:
			CarForwardBrake_WithBackward();
			break;
		case DIR_X_P:
			CarBackwardBrake_WithForward();
			break;
		case DIR_Y_N:
			CarRightBrake_WithLeft();
			break;
		case DIR_Y_P:
			CarLeftBrake_WithRight();
			break;
		default:
			CarStop();
			break;
	}
}






void Clockwise90Handle(void)
{
	car.speedBase=500;
	
	if(flagCCW==0)
	{
			CarRunClockwise(650);
			delay_ms(200);
		flagCCW=1;
	}
	
	
		if(car.dir==DIR_X_N||car.dir==DIR_Y_N)
		{
			if(car.flagRotation==0 &&(TSB8)){
				car.flagRotation=1;
				car.speedBase=200;
			}
			else if(car.flagRotation==1 && (TSB6||TSB5))
			{
				car.flagRotation=0;
				car.isRotating=false;
				car.flagReadyUpdatePoint=1;
			}
		}
		if(car.dir==DIR_X_P||car.dir==DIR_Y_P)
		{
			if(car.flagRotation==0 &&(TSA8)){
				car.flagRotation=1;
				car.speedBase=200;
			}
			else if(car.flagRotation==1 && (TSA6||TSA5))
			{
				car.flagRotation=0;
				car.isRotating=false;
				car.flagReadyUpdatePoint=1;
				flagCCW=0;
			}
		}
		
		
		CarRunClockwise(car.speedBase);
		
		//CarRunClockwise(speed);
		//delay_us(100);
		//CarClockwise(400,285,367,410);
		//AvgSpeedMove(speed);
		//CarClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
		//delay_us(300);
}






void CounterClockwise90Handle(void)
{	
	car.speedBase=500;
	
	if(flagCCW==0)
	{
			CarRunCounterClockwise(650);
			delay_ms(200);
			flagCCW=1;
	}
	
		if(car.dir==DIR_X_N||car.dir==DIR_Y_N)
		{
			if(car.flagRotation==0 &&(TSB1)){
				car.speedBase=400;
				car.flagRotation=1;
			}
				else if(car.flagRotation==1 && (TSB5))
			{
				car.flagRotation=0;
				car.isRotating=false;
				car.flagReadyUpdatePoint=1;
			}
		}
		if(car.dir==DIR_X_P||car.dir==DIR_Y_P)
		{
			if(car.flagRotation==0 &&(TSA1)){
				car.flagRotation=1;
				car.speedBase=400;
			}
			else if(car.flagRotation==1 && (TSA3||TSA2))
			{
				flagCCW=0;
				car.flagRotation=0;
				car.isRotating=false;
				car.flagReadyUpdatePoint=1;
			}
		}
		
		CarRunCounterClockwise(car.speedBase);
//		CarCounterClockwise(450,450,450,450);

//		AvgMotorSpeed(400);
//		CarCounterClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
//		CarRunCounterClockwise(speed);
//		CarCounterClockwise(500,400,400,400);
}


void Clockwise180Handle(void)
{

}






void InitCarPosition2(void)
{
	static u8 flagInitPosition2=0;	
	if(flagInitPosition2==0)
	{
		CarTurnLeft();
		flagInitPosition2=1;
		CarRunLeft(500);
		delay_ms(100);
	}
	else if(flagInitPosition2==1)
	{
		AvgMotorSpeed(400);
		CarLeftSetFixedSpeed();
		delay_ms(1);
		if(TSC4){
			flagInitPosition2=2;
		}
	}
	else if(flagInitPosition2==2)
	{
		AvgMotorSpeed(400);
		CarLeftSetFixedSpeed();
		delay_ms(1);
		if(TSA4||TSA5){
			flagInitPosition2=3;
		}
		
	}
	else if(flagInitPosition2==3)
	{
		CarLeftBrake_WithRight();
		
		car.flagSetPosition=SSP_RegularMode;
		flagInitPosition2=0;
		CarTurnForward();
		SendString("Init Position OK",18);
	}
	
	//移动两格
	MoveOne_Forward_X_N();
	MoveOne_Forward_X_N();
	
	//移动一格
	MoveOne_Left_Y_P();
	
	CarTurnForward();
	car.terminalPoint.x=2;
	car.terminalPoint.y=2;
}







void InitCarPosition3(void)
{
	static u8 flag=0;	
	if(flag==0)
	{
		CarTurnForward();
		flag=1;
	}
	else if(flag==1)
	{
		AvgMotorSpeed(350);
		CarForwardSetFixedSpeed();
		
		delay_ms(1);
		if(TSC4){																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											
			flag=2;
		}
	}
	
	else if(flag==2)
	{
		AvgMotorSpeed(350);
		CarForwardSetFixedSpeed();
		
		delay_ms(1);
		if(TSC2){																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											
			flag=3;
			CarForwardBrake_WithBackward();
			CarTurnLeft();
		}
	}
	else if(flag==3)
	{
		AvgMotorSpeed(400);
		CarLeftSetFixedSpeed();
		
		if(TSB5){
			flag=0;
//			CarLeftBrake_WithRight();
			car.flagSetPosition=SSP_RegularMode;
//			CarTurnForward();
			if(car.pm==PM_RFP ||car.pm==PM_RPF)
				MoveOne_Left_Y_P();
						
	CarTurnForward();
		}
	}
	
	
}








void ResetCarPosition(void)
{
	if(flagResetPosition==0 && car.dir==DIR_Y_N)
	{
		flagResetPosition=13;
	}
	
	if(flagResetPosition==0 && car.dir==DIR_X_P)
	{
		CarTurnCounterClockwise();
		car.isRotating=true;
		flagResetPosition=11;
	}
	
	if(flagResetPosition==13){
		car.dir=DIR_Y_N;
		CarSetMotor();
		flagResetPosition=14;
	}
	else if(flagResetPosition==14)
	{
		CarRunBackward(700);
		if((TSB8&&TSB7)||(TSB1&&TSB2)){
			delay_ms(100);
			flagResetPosition=15;
		}
	}
	else if(flagResetPosition==15)
	{
		flagResetPosition=16;
	}
	else if(flagResetPosition==16)
	{
		CarRunBackward(700);
		if((!TSB8&&!TSB1))
			flagResetPosition=17;
	}
	else if(flagResetPosition==17)
	{
		CarTurnLeft();
		flagResetPosition=18;
	}
	else if(flagResetPosition==18)
	{
		CarLeft(999,999,999,999);
		delay_ms(400);
//		if(!TSA1){
			CarStop();
			flagResetPosition=0;
			car.flagSetPosition=SSP_RegularMode;
			delay_ms(5000);
			InitCar();
//		}
	}

}


void MoveToRawPosition(void)
{
	static u8 flagMoveToRawPosition=0;
	
	car.speedBase=500;
	
	if(flagMoveToRawPosition==0)
	{
		CarTurnClockwise();
		CarRunClockwise(650);
		delay_ms(200);
		flagMoveToRawPosition=1;
	}
	else if(flagMoveToRawPosition==1)
	{
		AvgMotorSpeed(500);
		CarClockwiseSetFixedSpeed();
		if(TSB8)
			flagMoveToRawPosition=2;
	}
	else if(flagMoveToRawPosition==2)
	{
		AvgMotorSpeed(300);
		CarClockwiseSetFixedSpeed();
		if(TSD1)
			flagMoveToRawPosition=3;
	}
	else if(flagMoveToRawPosition==3)
	{
		AvgMotorSpeed(300);
		CarClockwiseSetFixedSpeed();
		if(TSD3){
			flagMoveToRawPosition=4;
			CarTurnRight();
			CarRunRight(500);
			delay_ms(100);
		}
	}
	else if(flagMoveToRawPosition==4)
	{
		CarRightPID();
		if(TSB8)
			flagMoveToRawPosition=5;
	}
	else if(flagMoveToRawPosition==5)
	{
		CarRightPID();
		if(TSB4)
			flagMoveToRawPosition=6;
	}
	else if(flagMoveToRawPosition==6)
	{
		CarRightPID();
		if(TSB8)
			flagMoveToRawPosition=7;
	}
	else if(flagMoveToRawPosition==7)
	{
		CarRightPID();
		if(TSB5)
			flagMoveToRawPosition=8;
	}
	else if(flagMoveToRawPosition==8)
	{
		flagMoveToRawPosition=0;
		car.flagSetPosition=SSP_RegularMode;
		while(1)
			CarStop();
	}
}










void MoveToProcessPosition(void)
{
	static u8 flag=0;
	
	car.speedBase=500;
	
	if(flag==0)
	{
		CarTurnCounterClockwise();
		CarRunCounterClockwise(650);
		delay_ms(200);
		flag=1;
	}
	else if(flag==1)
	{
		AvgMotorSpeed(450);
		CarCounterClockwiseSetFixedSpeed();
		if(TSB1)
			flag=2;
	}
	else if(flag==2)
	{
//		CarClockwise(400,400,400,400);
		AvgMotorSpeed(450);
		CarCounterClockwiseSetFixedSpeed();
		if(TSB5||TSB4){
			CarTurnClockwise();
			CarRunClockwise(500);
			delay_ms(100);
			CarStop();
			flag=3;
			CarTurnForward();
		}
	}
	else if(flag==3)
	{
		CarForwardPID();
		if(TSB6&&TSB7&&TSB8){
			flag=100;
		}
	}
	else if(flag==100)
	{
		CarForwardPID();
		if(TSC4){
			flag=4;
			CarTurnBackward();
		}
	}
	else if(flag==4)
	{
		CarBackwardPID();
		if(TSC1)
			flag=5;
	}
	else if(flag==5)
	{
		CarBackwardPID();
		if(TSC4)
			flag=6;
	}
	else if(flag==6)
	{
		CarBackwardPID();
		if(TSC1){
			flag=7;
			CarTurnForward();
		}
	}
	else if(flag==7)
	{
		CarForwardPID();
		if(TSB6&&TSB7&&TSB8)
				flag=101;
	}
	else if(flag==101)
	{
		CarForwardPID();
		if(TSC4){
			flag=8;
			CarForwardBrake_WithBackward();
			CarTurnCounterClockwise();
		}
	}
	else if(flag==8)
	{
		CarRunCounterClockwise(400);
		if(TSB8){
			flag=9;
		}
	}
		else if(flag==9)
	{
		CarRunCounterClockwise(400);
		if(TSB1){
			flag=10;
		}
	}
	else if(flag==10)
	{
		CarRunCounterClockwise(400);
		if(TSB4||TSB5){
			flag=11;
			
			
		}
	}
	
	else if(flag==11)
	{
		flag=0;
		car.flagSetPosition=SSP_RegularMode;
		CarStop();
	}
}


void CarFineTuning(void)
{
	u8 c=0;
	while(1)
	{
		c++;
		if(c>20){
			CarStop();
			return;
		}
		if(TSB4&&TSB5 && TSA4&&TSA5 && TSC3&&TSC4 && TSD1&&TSD2){
			CarStop();
			return;
		}
		CarTurnClockwise();
		if((TSB6||TSB7||TSB8)||(TSA6||TSA7||TSA8))//小车此时偏向左边,需要往右偏一点
		{
			CarRunClockwise(450);
			delay_ms(200);
		}
		CarTurnCounterClockwise();
		if((TSB1||TSB2||TSB3)||(TSA1||TSA2||TSA3))
		{
			CarRunCounterClockwise(450);
			delay_ms(200);
		}
		CarTurnLeft();
		if((TSB6||TSB7||TSB8)||(TSA1||TSA2||TSA3))
		{
			CarRunLeft(450);
			delay_ms(200);
		}
		CarTurnRight();
		if((TSB1||TSB2||TSB3)||(TSA6||TSA7||TSA8))
		{
			CarRunRight(450);
			delay_ms(200);
		}
		/*
		CarTurnForward();
		while(TSD1&&!TSD2)
		{
			CarRunForward(400);
			delay_ms(100);
		}
		CarTurnBackward();
		while(!TSD1&&TSD2)
		{
			
			CarRunBackward(400);
			delay_ms(100);
		}
		*/
	
	}


}

void MoveToRawPosition2(void)
{
	static u8 flagMoveToRawPosition=0;
	
	car.speedBase=500;
	
	if(flagMoveToRawPosition==0)
	{
		CarTurnClockwise();
		CarRunClockwise(650);
		delay_ms(200);
		flagMoveToRawPosition=1;
	}
	else if(flagMoveToRawPosition==1)
	{
		AvgMotorSpeed(500);
		CarClockwiseSetFixedSpeed();
		if(TSA8)
			flagMoveToRawPosition=2;
	}
	else if(flagMoveToRawPosition==2)
	{
		AvgMotorSpeed(450);
		CarClockwiseSetFixedSpeed();
		u8 a=GetTSA_Number();
		u8 b=GetTSB_Number();
		
		if(Abs((a-b))<=1 && a<=5){
				CarTurnCounterClockwise();
				CarRunCounterClockwise(500);
				delay_ms(100);
			while(1)
				CarStop();
				flagMoveToRawPosition=0;
				car.flagSetPosition=SSP_RegularMode;
				car.dir=DIR_Y_P;
		}
	}

}



u16 i=0;
void MoveToRawPosition3(void)
{
	static u8 flagMoveToRawPosition=0;
	
	car.speedBase=500;
	
	if(flagMoveToRawPosition==0)
	{
		CarTurnClockwise();
		CarRunClockwise(850);
		delay_ms(200);
		flagMoveToRawPosition=1;
	}
	else if(flagMoveToRawPosition==1)
	{
//		AvgMotorSpeed(500);
//		CarClockwiseSetFixedSpeed();
		//CarRunClockwise(500);
		CarClockwise(700,700,700,730);
		if((!TSC1&&!TSC2&&!TSC3&&!TSC4))
			flagMoveToRawPosition=2;
	}
	else if(flagMoveToRawPosition==2)
	{
//		AvgMotorSpeed(400);
//		CarClockwiseSetFixedSpeed();
		CarClockwise(500,500,500,550);
		
		if((TSA4||TSA5)||(TSA7&&TSB2)||(TSA6&&TSB3)){
				CarTurnCounterClockwise();
				CarRunCounterClockwise(500);
				delay_ms(100);
			//while(1)
				CarStop();
				flagMoveToRawPosition=0;
				car.flagSetPosition=SSP_RegularMode;
				car.dir=DIR_Y_P;
		}
	}
	GET_ENCODER_DATA;
	i++;
	if(i==100)
	{
		i=0;
		SendNumber(mcn.MotorLF);
		SendNumber(mcn.MotorRF);
		SendNumber(mcn.MotorLR);
		SendNumber(mcn.MotorRR);
		SendNumber(flagMoveToRawPosition);
		SendEndl();
		SendEndl();
	}
	delay_ms(1);

}
















void Clockwise90Handle2(void)
{
	car.speedBase=450;
	
	if(flagCCW==0)
	{
		CarRunClockwise(650);
		delay_ms(200);
		flagCCW=1;
	}

	if(car.flagRotation==0 &&(TSB8)){
		car.flagRotation=1;
		car.speedBase=200;
	}
	else if(car.flagRotation==1 && (TSB4||TSB5))
	{
		car.flagRotation=0;
		car.isRotating=false;
		car.flagReadyUpdatePoint=1;
	}
		
	CarRunClockwise(car.speedBase);
		
		//CarRunClockwise(speed);
		//delay_us(100);
		//CarClockwise(400,285,367,410);
		//AvgSpeedMove(speed);
		//CarClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
		//delay_us(300);
}












void Clockwise90Handle3(void)
{
	car.speedBase=450;
	
	if(flagCCW==0)
	{
		CarRunClockwise(550);
		delay_ms(200);
		flagCCW=1;
	}

	if(car.flagRotation==0 &&(TSB8)){
		car.flagRotation=1;
		car.speedBase=300;
	}
	else if(car.flagRotation==1 && (TSB4||TSB5))
	{
		car.flagRotation=0;
		car.isRotating=false;
		car.flagReadyUpdatePoint=1;
		flagCCW=1;
	}
		
	CarRunClockwise(car.speedBase);
		
		//CarRunClockwise(speed);
		//delay_us(100);
		//CarClockwise(400,285,367,410);
		//AvgSpeedMove(speed);
		//CarClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
		//delay_us(300);
}













void CounterClockwise90Handle2(void)
{	
	car.speedBase=450;
	
		if(flagCCW==0)
		{
				CarRunCounterClockwise(650);
				delay_ms(200);
				flagCCW=1;
		}
	
		if(car.dir==DIR_X_N||car.dir==DIR_Y_N)
		{
			if(car.flagRotation==0 &&(TSB1)){
				car.speedBase=300;
				car.flagRotation=1;
			}
				else if(car.flagRotation==1 && (TSB5))
			{
				car.flagRotation=0;
				car.isRotating=false;
				car.flagReadyUpdatePoint=1;
				flagCCW=0;
			}
		}
		
		CarRunCounterClockwise(car.speedBase);
//		CarCounterClockwise(450,450,450,450);

//		AvgMotorSpeed(400);
//		CarCounterClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
//		CarRunCounterClockwise(speed);
//		CarCounterClockwise(500,400,400,400);
}




void MoveOne_Forward_X_N(void)
{
		CarTurnForward();
		car.terminalPoint.x=car.currentPoint.x-1;
		car.speedBase=500;
		while(car.currentPoint.x!=car.terminalPoint.x)
		{
			UpdatePoint_Forward_X_N();
			CarForwardPID();
			if(car.flagUpdatePoint==1)
				car.speedBase=400;
			delay_ms(2);
		}
		CarForwardBrake_WithBackward();
}

void MoveOne_Forward_X_P(void)
{
	//往X_P/移一格
	CarTurnForward();
	car.terminalPoint.x=car.currentPoint.x+1;
	car.speedBase=300;
	while(car.currentPoint.x!=car.terminalPoint.x)
	{
		UpdatePoint_Forward_X_P();
		CarForwardPID();
		if(car.flagUpdatePoint==1)
			car.speedBase=200;
		delay_ms(2);
	}
	CarForwardBrake_WithBackward();
}

void MoveOne_Forward_Y_N(void)
{
		//往Y_N/移一格
	CarTurnForward();
	car.terminalPoint.y=car.currentPoint.y-1;
	car.speedBase=300;
	while(car.currentPoint.y!=car.terminalPoint.y)
	{
		UpdatePoint_Forward_Y_N();
		CarForwardPID();
		if(car.flagUpdatePoint==1)
			car.speedBase=200;
		delay_ms(2);
	}
	CarForwardBrake_WithBackward();
	
}

void MoveOne_Forward_Y_P(void)
{
	
}

void MoveOne_Left_X_N(void)
{
		CarTurnLeft();
		car.terminalPoint.x=car.currentPoint.x-1;
		car.speedBase=300;
		while(car.currentPoint.x!=car.terminalPoint.x)
		{
			UpdatePoint_Left_X_N();
			CarLeftPID();
			if(car.flagUpdatePoint==1)
				car.speedBase=200;
			delay_ms(2);
		}
		CarLeftBrake_WithRight();
}






void MoveOne_Backward_X_N(void)
{
		CarTurnBackward();
		car.terminalPoint.x=car.currentPoint.x-1;
		car.speedBase=400;
		while(car.currentPoint.x!=car.terminalPoint.x)
		{
			UpdatePoint_Backward_X_N();
			CarBackwardPID();
			if(car.flagUpdatePoint==1)
				car.speedBase=300;
			delay_ms(2);
		}
		CarBackwardBrake_WithForward();
}




void MoveOne_Backward_X_P(void)
{
		CarTurnBackward();
		car.terminalPoint.x=car.currentPoint.x+1;
		car.speedBase=500;
		while(car.currentPoint.x!=car.terminalPoint.x)
		{
			UpdatePoint_Backward_X_P();
			CarBackwardPID();
			if(car.flagUpdatePoint==1)
				car.speedBase=400;
			delay_ms(2);
		}
		CarBackwardBrake_WithForward();

}

void MoveOne_Backward_Y_N(void)
{
		//往Y_N/移一格
	CarTurnBackward();
	car.terminalPoint.y=car.currentPoint.y-1;
	car.speedBase=400;
	while(car.currentPoint.y!=car.terminalPoint.y)
	{
		UpdatePoint_Backward_Y_N();
		CarBackwardPID();
		if(car.flagUpdatePoint==1)
			car.speedBase=300;
		delay_ms(2);
	}
	CarBackwardBrake_WithForward();
}

void MoveOne_Backward_Y_P(void)
{
		//往Y_N/移一格
	CarTurnBackward();
	car.terminalPoint.y=car.currentPoint.y+1;
	car.speedBase=300;
	while(car.currentPoint.y!=car.terminalPoint.y)
	{
		UpdatePoint_Backward_Y_P();
		CarBackwardPID();
		if(car.flagUpdatePoint==1)
			car.speedBase=200;
		delay_ms(2);
	}
	CarBackwardBrake_WithForward();
}







void MoveOne_Right_Y_N(void)
{
		//往Y_N/移一格
	CarTurnRight();
	car.terminalPoint.y=car.currentPoint.y-1;
	car.speedBase=500;
	while(car.currentPoint.y!=car.terminalPoint.y)
	{
		UpdatePoint_Right_Y_N();
		CarRightPID();
		if(car.flagUpdatePoint==1)
			car.speedBase=400;
		delay_ms(2);
	}
	CarRightBrake_WithLeft();
}

void MoveOne_Left_Y_P(void)
{
		//往Y_N/移一格

	CarTurnLeft();
	car.terminalPoint.y=car.currentPoint.y+1;
	car.speedBase=500;
	while(car.currentPoint.y!=car.terminalPoint.y)
	{
		UpdatePoint_Left_Y_P();
		CarLeftPID();
		if(car.flagUpdatePoint==1)
			car.speedBase=400;
		delay_ms(2);
	}
	CarLeftBrake_WithRight();
}







