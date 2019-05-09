#include "lcd.h"
#include "prohead.h"
#include "driver.h" 
#include "lcdlib.h"
#include "qqImage.h"
#include "gpio.h"
#include "car.h"
#include "c.h"




void DIS_Delayms(u16 Num)
{
   	u16 Timer;
		while(Num--)
		{
		 	Timer = 60000;
			while(Timer--); 
		}
}

u8* GetTaskString(char t)
{
	u8 *str;
	switch(t)
	{
		case ORDER_RGB:
			str="R->G->B";
		break;
		case ORDER_RBG:
			str="R->B->G";
		break;
		case ORDER_GRB:
			str="G->R->B";
		break;
		case ORDER_GBR:
			str="G->B->R";
		break;
		case ORDER_BGR:
			str="B->G->R";
		break;
		case ORDER_BRG:
			str="B->R->G";
		break;	
	}
	return str;
}

u8* GetTaskNumber(char t)
{
	u8 *str;
	switch(t)
	{
		case ORDER_RGB:
			str="123";
		break;
		case ORDER_RBG:
			str="132";
		break;
		case ORDER_GRB:
			str="213";
		break;
		case ORDER_GBR:
			str="231";
		break;
		case ORDER_BGR:
			str="321";
		break;
		case ORDER_BRG:
			str="312";
		break;	
	}
	return str;
}




void LCDShowTaskNumber(void)
{
	LCD_ClrScr(WHITE);
	
	u16 x=10;//定义游标
	u16 y=10;
	u8 cw=8,ch=16;
	
	
	
	LCD_DisALine(y,0,1,240,BLUE);
	y+=2;
	LCD_DisASCString16x8(y,x, "Task List:", BLUE, WHITE);
	y+=ch;
	LCD_DisALine(y,0,1,240,BLUE);
	u16 startY=y;
	
	y+=2;
	u16 xs=x+cw+8;
	
	u8 numStr[2];
	for(u8 i=0;i<taskInf.currentPoint;i++)
	{
		numStr[0]=i+48;
		LCD_DisASCString16x8(y,xs,GetTaskNumber(taskInf.list[i]), BLUE, WHITE);
		
		y+=ch;
		//画横线
		LCD_DisALine(y,0,1,240,BLUE);
		y+=2;
	}
	
	//画第一条竖线
	LCD_DisALine(startY,x+10,2,y-startY-2,BLUE);
		//画中间的第二条竖线
	u16 startX=xs+cw*7+2;
	LCD_DisALine(startY,startX,2,y-startY-2,BLUE);
	
	y+=10;
	
	LCD_DisASCString16x8(y,x+2,"Current Task:", BLUE, WHITE);
	
	u16 x0=120,y0=y+62+ch;
	
	LCD_DisALoop(y0,x0,60,RED);
	LCD_DisALoop(y0,x0,55,GREEN);
	LCD_DisALoop(y0,x0,50,BLUE);
	
	if(taskInf.currentPoint!=0)LCD_DisASCString16x8(y0-ch/2,x0-cw*4+cw/2,GetTaskString(taskInf.list[taskInf.currentPoint-1]), BLUE, GREEN);
	
	//在x0,y0 ~ x1,y1位置处,显示一个颜色为Color的长方形
	LCD_DisABorder(y,x,y0+60+18,240-10,BLACK);
	
}



void LCDShowTask(void)
{
	LCD_ClrScr(WHITE);
	
	u16 x=10;//定义游标
	u16 y=10;
	u8 cw=8,ch=16;
	
	
	
	LCD_DisALine(y,0,1,240,BLUE);
	y+=2;
	LCD_DisASCString16x8(y,x, "Task List:", BLUE, WHITE);
	y+=ch;
	LCD_DisALine(y,0,1,240,BLUE);
	u16 startY=y;
	
	y+=2;
	u16 xs=x+cw+8;
	
	u8 numStr[2];
	for(u8 i=0;i<taskInf.currentPoint;i++)
	{
		numStr[0]=i+48;
		LCD_DisASCString16x8(y,x,numStr, BLUE, WHITE);
		LCD_DisASCString16x8(y,xs,GetTaskString(taskInf.list[i]), BLUE, WHITE);
		
		if(i%2==0)
			LCD_DisASCString16x8(y,xs+cw*7+4,"Raw To Process",BLUE,WHITE);
		else
			LCD_DisASCString16x8(y,xs+cw*7+4,"Process To Finish",BLUE,WHITE);
		
		
		y+=ch;
		//画横线
		LCD_DisALine(y,0,1,240,BLUE);
		y+=2;
	}
	//画第一条竖线
	LCD_DisALine(startY,x+10,2,y-startY-2,BLUE);
		//画中间的第二条竖线
	u16 startX=xs+cw*7+2;
	LCD_DisALine(startY,startX,2,y-startY-2,BLUE);
	
	y+=10;
	
	LCD_DisASCString16x8(y,x+2,"Current Task:", BLUE, WHITE);
	
	u16 x0=120,y0=y+62+ch;
	
	LCD_DisALoop(y0,x0,60,RED);
	LCD_DisALoop(y0,x0,55,GREEN);
	LCD_DisALoop(y0,x0,50,BLUE);
	LCD_DisASCString16x8(y0-ch/2,x0-cw*4+cw/2,GetTaskString(taskInf.list[taskInf.currentPoint-1]), BLUE, GREEN);
	
	//在x0,y0 ~ x1,y1位置处,显示一个颜色为Color的长方形
	LCD_DisABorder(y,x,y0+60+18,240-10,BLACK);
	
}



void LCD(void)
{
		//TFT初始化
	LCD_Init();
	//开背光 清屏
	Driver_LcdBacklight(True);
	LCD_ClrScr(WHITE);
	//开机LOGO
	LCD_DisARectangular(70+46, 20+29, 70+30+46, 10+60+29-20, YELLOW);
	LCD_DisARectangular(63+46, 28+29, 63+32+46, 28+50+29-20, GREEN);
	DIS_Delayms(100);
	LCD_DisABorder(63+46, 28+29, 63+32+46, 28+50+29, WHITE);
	LCD_DisASCString16x8(72+46, 31+29, "MHR", WHITE, GREEN);
	DIS_Delayms(100);
	LCD_DisASCString16x8(72+46-8, 28+50+29-10, "No.1 Team", YELLOW, WHITE);
	DIS_Delayms(100);
	LCD_DisALoop(72+46,28+50+29-10+2*8,35,GREEN);
	DIS_Delayms(100);
	LCD_DisASCString16x8(72+46+16+4+20, 31, "Engineering Training Center", WHITE, GREEN);
	LCD_DisASCString16x8(72+46+16+4+16+20, 40, "From Shanghai University", WHITE, GREEN);
	DIS_Delayms(100);
	LCD_DisABorder(70+26, 20,72+46+16+4+16+40,240-10,YELLOW);
	
}


