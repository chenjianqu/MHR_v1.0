#include "CoordinateSystem.h"
#include "pid.h"
#include "math.h"


void UpdateCoordinatePointNoRotation(void)
{
	switch(car.dir)
	{
		case DIR_X_N:
		{
			UpdatePoint_Forward_X_N();
		}
		break;
		case DIR_X_P:
		{
			UpdatePoint_Backward_X_P();
		}
		break;
		case DIR_Y_P:
		{
			UpdatePoint_Left_Y_P();
		}
		break;
		case DIR_Y_N:
		{
			UpdatePoint_Right_Y_N();
		}
		break;
		default:
			break;
	}
}









void UpdateCoordinatePoint(void)
{
	
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}

	
	switch(car.dir)
	{
		case DIR_X_N:
		{
				if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7&&TSB8)||(TSB1&&TSB2)))
					car.flagUpdatePoint=1;
				if(car.flagUpdatePoint==1 && (TSC4||TSC3)){
					car.flagUpdatePoint=2;
					car.currentPoint.x--;
					LED2_Toggle;
					car.flagReadyUpdatePoint=1;
				}
		}
		break;
		case DIR_X_P:
		{
				if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSA7&&TSA8)||(TSA1&&TSA2)))
					car.flagUpdatePoint=1;
				if(car.flagUpdatePoint==1 &&(TSC1||TSC2)){
					car.flagUpdatePoint=2;
					car.currentPoint.x++;
					LED2_Toggle;
					car.flagReadyUpdatePoint=1;
				}
		}
		break;
		case DIR_Y_P:
		{
				if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSA7&&TSA8)||(TSA1&&TSA2)))
					car.flagUpdatePoint=1;
				if(car.flagUpdatePoint==1 && (TSC4||TSC3)){
					car.flagUpdatePoint=2;
					car.currentPoint.y++;
					LED2_Toggle;
					car.flagReadyUpdatePoint=1;
				}
		}
		break;
		case DIR_Y_N:
		{
				if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7&&TSB8)||(TSB1&&TSB2)))
					car.flagUpdatePoint=1;
				if(car.flagUpdatePoint==1 &&(TSC1||TSC2)){
					car.flagUpdatePoint=2;
					car.currentPoint.y--;
					LED2_Toggle;
					car.flagReadyUpdatePoint=1;
				}
		}
		break;
		default:
			break;
	}
}






void UpdatePoint_Backward_X_P(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=20;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSA8)||(TSA1)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 &&(TSC3||TSC2||TSD2||TSD3)){
		car.flagUpdatePoint=2;
		car.currentPoint.x++;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
	
}

void UpdatePoint_Backward_X_N(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSA7&&TSA8)||(TSA1&&TSA2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 &&(TSC3||TSC2||TSD2||TSD3)){
		car.flagUpdatePoint=2;
		car.currentPoint.x--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
	
}

void UpdatePoint_Backward_Y_P(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSA7&&TSA8)||(TSA1&&TSA2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 &&(TSC1||TSC2)){
		car.flagUpdatePoint=2;
		car.currentPoint.y++;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
}

void UpdatePoint_Backward_Y_N(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSA7&&TSA8)||(TSA1&&TSA2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 &&(TSC1||TSC2)){
		car.flagUpdatePoint=2;
		car.currentPoint.y--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
}

void UpdatePoint_Forward_Y_P(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7&&TSB8)||(TSB1&&TSB2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSC4||TSC3))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.y++;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
	
}

void UpdatePoint_Forward_Y_N(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7&&TSB8)||(TSB1&&TSB2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSC4||TSC3))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.y--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
	
}	
	
void UpdatePoint_Forward_X_P(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7)||(TSB1)||TSB2))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSC2||TSC3||TSD2||TSD3))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.x++;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}

}

void UpdatePoint_Forward_X_N(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=20;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7&&TSB8)||(TSB1&&TSB2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSC2||TSC3||TSD2||TSD3))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.x--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
}

void UpdatePoint_Forward_X_N_QRC(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSC1&&!TSC4&&!TSC2&&!TSC3)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB7&&TSB8)||(TSB1&&TSB2)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSC1))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.x--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
	
	car.speedBase=SPEED_LEVEL_LESS_N;
	if(car.terminalPoint.x-car.currentPoint.x==-2)
		car.speedBase=SPEED_LEVEL_LESS2;
	else if(car.terminalPoint.x-car.currentPoint.x==-1)
	{
		
		if(car.flagUpdatePoint==1)
			car.speedBase=SPEED_LEVEL_LESS0;
		else 
			car.speedBase=SPEED_LEVEL_LESS1;
	}
	
	
}



void UpdatePoint_Left_Y_P(void)
{
	if(car.flagReadyUpdatePoint>0)
	{
		car.flagUpdatePoint=20;
		if((!TSB1&&!TSB2&&!TSB3&&!TSB4&&!TSB5&&!TSB6&&!TSB7&&!TSB8)&&(!TSA3&&!TSA4&&!TSA5&&!TSA6))
			car.flagReadyUpdatePoint=0;
	}
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&(TSA8||TSB1))
	{
		car.flagUpdatePoint=1;
	}
	if(car.flagUpdatePoint==1&&((TSA3||TSA4)))
	{	
		car.flagUpdatePoint=2;
		car.currentPoint.y++;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
}








void UpdatePoint_Left_X_N(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=2;
		if(!TSB1&&!TSB2&&!TSB3&&!TSB4&&!TSB5&&!TSB6&&!TSB7&&!TSB8)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSC1&&TSC3)||(TSC2&&TSC4)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSB6||TSB5))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.x--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
}









void UpdatePoint_Right_Y_N(void)
{
	if(car.flagReadyUpdatePoint==1 && car.flagUpdatePoint==0)
	{
		car.flagUpdatePoint=20;
		if(!TSB1&&!TSB2&&!TSB3&&!TSB4&&!TSB5&&!TSB6&&!TSB7&&!TSB8)
			car.flagReadyUpdatePoint=0;
	}
	
	if(car.flagReadyUpdatePoint==0&&car.flagUpdatePoint==0&&((TSB8)||(TSA1)))
		car.flagUpdatePoint=1;
	if(car.flagUpdatePoint==1 && (TSB4||TSB3))
	{
		car.flagUpdatePoint=2;
		car.currentPoint.y--;
		LED2_Toggle;
		car.flagReadyUpdatePoint=1;
	}
}
