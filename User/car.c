#include "car.h"
#include "motor.h"

//小车
MyCar car;

TaskInf taskInf;

MotorCounter mc;

MotorCounter mc_test;

MotorSpeedManager msm;


//原料区
Point Point_RawMaterialArea;
Point Point_RawMaterialAreaFar;
Point Point_RawMaterialAreaStartMV;
Point Point_RawMaterialAreaEndMV;


//完成区
Point Point_FinishedAeraRed;
Point Point_FinishedAeraGreen;
Point Point_FinishedAeraBlue;

Point Point_FinishedAeraA;
Point Point_FinishedAeraB;
Point Point_FinishedAeraC;


//加工区
Point Point_ProcessingAeraRed;
Point Point_ProcessingAeraGreen;
Point Point_ProcessingAeraBlue;

Point Point_ProcessingAeraA;
Point Point_ProcessingAeraB;
Point Point_ProcessingAeraC;





 //二维码区
Point Point_QRCodeAera={2,1};
Point Point_QRCodeAeraFar={2,2};

//出发区
Point Point_InitAera={8,1};
Point Point_InitAeraEnd={7,1};
Point Point_InitAeraStart={7,0};



Point Point_BaseYN_C={5,2};
Point Point_BaseYN_B={4,2};
Point Point_BaseYN_A={3,2};

Point Point_BaseYP_A={3,6};
Point Point_BaseYP_B={4,6};
Point Point_BaseYP_C={5,6};


Point Point_BaseXN_A={2,3};
Point Point_BaseXN_B={2,4};
Point Point_BaseXN_C={2,5};


void SetAeraCoordinate(void)
{
	switch(car.pm)
	{
		//初赛
		case PM_RPF:
		{
			Point_RawMaterialArea=Point_BaseYN_B;
			Point_RawMaterialAreaStartMV=Point_BaseYN_C;
			Point_RawMaterialAreaEndMV=Point_BaseYN_A;
			Point_RawMaterialAreaFar=Point_BaseYN_B;
			
			
			Point_RawMaterialArea.y-=1;
			Point_RawMaterialAreaStartMV.y-=1;
			Point_RawMaterialAreaEndMV.y-=1;
			
			Point_FinishedAeraRed=Point_BaseXN_B;
			Point_FinishedAeraGreen=Point_BaseXN_B;
			Point_FinishedAeraBlue=Point_BaseXN_B;
			
			Point_FinishedAeraA=Point_BaseXN_A;
			Point_FinishedAeraB=Point_BaseXN_B;
			Point_FinishedAeraC=Point_BaseXN_C;
			
			Point_ProcessingAeraRed=Point_BaseYP_B;
			Point_ProcessingAeraGreen=Point_BaseYP_B;
			Point_ProcessingAeraBlue=Point_BaseYP_B;
			
			Point_ProcessingAeraA=Point_BaseYP_A;
			Point_ProcessingAeraB=Point_BaseYP_B;
			Point_ProcessingAeraC=Point_BaseYP_C;
		}
		break;
		case PM_RFP:
		{
			Point_RawMaterialArea=Point_BaseYN_B;
			Point_RawMaterialAreaStartMV=Point_BaseYN_C;
			Point_RawMaterialAreaEndMV=Point_BaseYN_A;
			Point_RawMaterialAreaFar=Point_BaseYN_B;
			
			Point_RawMaterialArea.y-=1;
			Point_RawMaterialAreaStartMV.y-=1;
			Point_RawMaterialAreaEndMV.y-=1;
			
			Point_FinishedAeraRed=Point_BaseYP_B;
			Point_FinishedAeraGreen=Point_BaseYP_B;
			Point_FinishedAeraBlue=Point_BaseYP_B;
			
			Point_FinishedAeraA=Point_BaseYP_A;
			Point_FinishedAeraB=Point_BaseYP_B;
			Point_FinishedAeraC=Point_BaseYP_C;
			
			Point_ProcessingAeraRed=Point_BaseXN_B;
			Point_ProcessingAeraGreen=Point_BaseXN_B;
			Point_ProcessingAeraBlue=Point_BaseXN_B;
			
			Point_ProcessingAeraA=Point_BaseXN_A;
			Point_ProcessingAeraB=Point_BaseXN_B;
			Point_ProcessingAeraC=Point_BaseXN_C;
		}
			break;
		case PM_FPR:
		{
			Point_RawMaterialArea=Point_BaseXN_B;
			Point_RawMaterialAreaStartMV=Point_BaseXN_B;
			Point_RawMaterialAreaEndMV=Point_BaseXN_C;
			
			Point_RawMaterialAreaFar=Point_BaseXN_B;
			
			Point_FinishedAeraRed=Point_BaseYN_B;
			Point_FinishedAeraGreen=Point_BaseYN_B;
			Point_FinishedAeraBlue=Point_BaseYN_B;
			
			Point_FinishedAeraA=Point_BaseYN_A;
			Point_FinishedAeraB=Point_BaseYN_B;
			Point_FinishedAeraC=Point_BaseYN_C;
			
			Point_ProcessingAeraRed=Point_BaseYP_B;
			Point_ProcessingAeraGreen=Point_BaseYP_B;
			Point_ProcessingAeraBlue=Point_BaseYP_B;
			
			Point_ProcessingAeraA=Point_BaseYP_A;
			Point_ProcessingAeraB=Point_BaseYP_B;
			Point_ProcessingAeraC=Point_BaseYP_C;
		}
			break;
		case PM_FRP:
		{
			Point_RawMaterialArea=Point_BaseYP_B;
			Point_RawMaterialAreaStartMV=Point_BaseYP_C;
			Point_RawMaterialAreaEndMV=Point_BaseYP_C;
			Point_RawMaterialAreaFar=Point_BaseYP_B;
			
			Point_RawMaterialArea.y+=1;
			Point_RawMaterialAreaStartMV.y+=1;
			Point_RawMaterialAreaEndMV.y-=1;
			
			Point_FinishedAeraRed=Point_BaseYN_B;
			Point_FinishedAeraGreen=Point_BaseYN_B;
			Point_FinishedAeraBlue=Point_BaseYN_B;
			
			Point_FinishedAeraA=Point_BaseYN_A;
			Point_FinishedAeraB=Point_BaseYN_B;
			Point_FinishedAeraC=Point_BaseYN_C;
			
			Point_ProcessingAeraRed=Point_BaseXN_B;
			Point_ProcessingAeraGreen=Point_BaseXN_B;
			Point_ProcessingAeraBlue=Point_BaseXN_B;
			
			Point_ProcessingAeraA=Point_BaseXN_A;
			Point_ProcessingAeraB=Point_BaseXN_B;
			Point_ProcessingAeraC=Point_BaseXN_C;
		}
			break;
		case PM_PFR:
		{
			Point_RawMaterialArea=Point_BaseXN_B;
			Point_RawMaterialAreaStartMV=Point_BaseXN_B;			
			Point_RawMaterialAreaEndMV=Point_BaseXN_C;
			Point_RawMaterialAreaFar=Point_BaseXN_B;
			
			Point_FinishedAeraRed=Point_BaseYP_B;
			Point_FinishedAeraGreen=Point_BaseYP_B;
			Point_FinishedAeraBlue=Point_BaseYP_B;
			
			Point_FinishedAeraA=Point_BaseYP_A;
			Point_FinishedAeraB=Point_BaseYP_B;
			Point_FinishedAeraC=Point_BaseYP_C;
			
			Point_ProcessingAeraRed=Point_BaseYN_B;
			Point_ProcessingAeraGreen=Point_BaseYN_B;
			Point_ProcessingAeraBlue=Point_BaseYN_B;
			
			Point_ProcessingAeraA=Point_BaseYN_A;
			Point_ProcessingAeraB=Point_BaseYN_B;
			Point_ProcessingAeraC=Point_BaseYN_C;
		}
			break;
		case PM_PRF:
		{
			Point_RawMaterialArea=Point_BaseYP_B;
			Point_RawMaterialAreaStartMV=Point_BaseYP_C;
			Point_RawMaterialAreaEndMV=Point_BaseYP_C;
			Point_RawMaterialAreaFar=Point_BaseYP_B;
			
			Point_RawMaterialArea.y+=1;
			Point_RawMaterialAreaStartMV.y+=1;
			Point_RawMaterialAreaEndMV.y-=1;
			
			Point_FinishedAeraRed=Point_BaseXN_B;
			Point_FinishedAeraGreen=Point_BaseXN_B;
			Point_FinishedAeraBlue=Point_BaseXN_B;
			
			Point_FinishedAeraA=Point_BaseXN_A;
			Point_FinishedAeraB=Point_BaseXN_B;
			Point_FinishedAeraC=Point_BaseXN_C;
			
			Point_ProcessingAeraRed=Point_BaseYN_B;
			Point_ProcessingAeraGreen=Point_BaseYN_B;
			Point_ProcessingAeraBlue=Point_BaseYN_B;
			
			Point_ProcessingAeraA=Point_BaseYN_A;
			Point_ProcessingAeraB=Point_BaseYN_B;
			Point_ProcessingAeraC=Point_BaseYN_C;
		}
			break;
	}


}


float pitch,roll,yaw;


void InitCar(void)
{
	
	//初始化小车
	//设置目标坐标
	car.currentPoint=Point_InitAeraEnd;
	//car.terminalPoint=Point_QRCodeAera;
	car.terminalPoint=Point_RawMaterialAreaFar;
	car.lastPoint=Point_InitAeraEnd;
	//设置方向
	car.dir=DIR_X_N;
	car.last_dir=car.dir;
	//设置状态
	car.isRotating=false;//旋转关闭
	car.isRun=true;//运行启动
	car.flagSetPosition=SSP_InitPosition;//初始化位置
//	car.flagSetPosition=SSP_RegularMode;
	car.flagBlockForward=0;//不阻塞
	car.flagRotation=0;
	car.flagUpdatePoint=0;
	car.flagReadyUpdatePoint=0;
	car.order=0;
	car.pos=0;
	
	CarSetMotor();//根据方向设置电机
	car.flagHighSpeedDelay=0;
	taskInf.currentPoint=0;
	
	car.cp=CP_InitToQRC;
	car.pm=PM_RPF;
	
	mc.MotorLF=0;
	mc.MotorRF=0;
	mc.MotorLR=0;
	mc.MotorRR=0;
	
	car.isSendScanObj=false;
	
	taskInf.currentPoint=1;
	
}









