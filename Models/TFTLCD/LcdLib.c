
/* 头文件包含 INCLUDES */
#include "prohead.h"
#include "driver.h"
#include "lcdlib.h"
#include "ASC8x16.h"
#include "GB2312.h"

/*-------------------------------------------------------------------------------------------------------
*  内部声明								 
-------------------------------------------------------------------------------------------------------*/
//lcd drivers
#define	 LCD_RESET_H  		Driver_LcdReset(1)
#define	 LCD_RESET_L  		Driver_LcdReset(0)
#define	 LCD_CS_H  				Driver_LcdCS(1)
#define	 LCD_CS_L  				Driver_LcdCS(0)
#define	 LCD_RS_H  				Driver_LcdRS(1)
#define	 LCD_RS_L  				Driver_LcdRS(0)
#define	 LCD_RD_H  				Driver_LcdRD(1)
#define	 LCD_RD_L  				Driver_LcdRD(0)
#define	 LCD_WR_H  				Driver_LcdWR(1)
#define	 LCD_WR_L  				Driver_LcdWR(0)
#define  LCD_SEND(x)    	Driver_LcdSendData((x))

typedef unsigned long       u32;
typedef signed   long       s32;


//lcd resolution 
#if LCD_DIRECT==1
	#define  LCD_ROW_NUM    320                //行数
	#define  LCD_COL_NUM    240                //列数
#else
	#define  LCD_ROW_NUM    320                //行数
	#define  LCD_COL_NUM    240                //列数
#endif

/*-------------------------------------------------------------------------------------------------------
*  资源定义											 
-------------------------------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------------------------------
*  函数声明												 
-------------------------------------------------------------------------------------------------------*/
//lcd bottom funtions
void LCD_WriteReg(u16 Index);
void LCD_WriteData(u16 Data);
void LCD_Delayms(u8 Num);
void LCD_TimerCountHandle(void);
void LCD_PortInit(void);
void LCD_Reset(void);
void LCD_Init(void);
//back light
//...
//lcd display
void LCD_OpenWin(u16 x0, u16 y0, u16 x1, u16 y1);


/*-------------------------------------------------------------------------------------------------------
*  执行代码													 
-------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************
*  Function: LCD_WriteReg				                                                           
*  Object: lcd write reg
*  Input: index
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_WriteReg(u16 Index)
{
		LCD_CS_L;
		LCD_RS_L;
		#if (LCD_BUSTYPE == 1)	
			//16位数据总线
			LCD_SEND(Index);
			LCD_WR_L;
			LCD_WR_H;
		#else 
			//8位数据总线
			LCD_SEND(Index/0x100);
			LCD_WR_L;
			LCD_WR_H;
			LCD_SEND(Index%0x100);
			LCD_WR_L;
			LCD_WR_H;
		#endif
		LCD_CS_H;
}

/********************************************************************************************************
*  Function: LCD_WriteData				                                                           
*  Object: lcd write data
*  Input: index and data
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_WriteData(u16 Data)
{
		LCD_CS_L;
		LCD_RS_H;
		#if (LCD_BUSTYPE == 1)
			//16位数据总线
			LCD_SEND(Data);
			LCD_WR_L;
			LCD_WR_H;
		#else 
			//8位数据总线
			LCD_SEND(Data/0x100);
			LCD_WR_L;
			LCD_WR_H;
			LCD_SEND(Data%0x100);
			LCD_WR_L;
			LCD_WR_H;
		#endif
		LCD_CS_H;
}

/********************************************************************************************************
*  Function: LCD_Delayms				                                                           
*  Object: lcd init wait..
*  Input: Num
*  Output: none                                  
*  brief: time = Num * 1ms
********************************************************************************************************/
void LCD_Delayms(u8 Num)
{
		u16 Timer;
		while(Num--)
		{
		 	Timer = 11500;
			while(Timer--); 
		}
}

/********************************************************************************************************
*  Function: LCD_PortInit				                                                           
*  Object: lcd port init
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_PortInit(void)
{
		LCD_CS_H;
		LCD_RS_H;
		LCD_WR_H;
		LCD_RD_H;
}

/********************************************************************************************************
*  Function: LCD_Reset				                                                           
*  Object: lcd reset control
*  Input: none
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_Reset(void)
{
		LCD_RESET_L;
		LCD_Delayms(150);
		LCD_RESET_H;
		LCD_Delayms(50);
}

/********************************************************************************************************
*  Function: LCD_Init				                                                           
*  Object: lcd init
*  Input: sta
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_Init(void)
{ 
		//-- LCD PORT INIT --
		LCD_PortInit();
		//-- LCD RESET--
		LCD_Reset();
		//-------------- Initial Sequence ---------------
		//************* Start Initial Sequence **********//	
		LCD_WriteReg(0xCF);  
		LCD_WriteData(0x00); 
		LCD_WriteData(0xC1); 
		LCD_WriteData(0X30); 
		LCD_WriteReg(0xED);  
		LCD_WriteData(0x64); 
		LCD_WriteData(0x03); 
		LCD_WriteData(0X12); 
		LCD_WriteData(0X81); 
		LCD_WriteReg(0xE8);  
		LCD_WriteData(0x85); 
		LCD_WriteData(0x10); 
		LCD_WriteData(0x7A); 
		LCD_WriteReg(0xCB);  
		LCD_WriteData(0x39); 
		LCD_WriteData(0x2C); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x34); 
		LCD_WriteData(0x02); 
		LCD_WriteReg(0xF7);  
		LCD_WriteData(0x20); 
		LCD_WriteReg(0xEA);  
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 
		LCD_WriteReg(0xC0);    //Power control 
		LCD_WriteData(0x1B);   //VRH[5:0] 
		LCD_WriteReg(0xC1);    //Power control 
		LCD_WriteData(0x01);   //SAP[2:0];BT[3:0] 
		LCD_WriteReg(0xC5);    //VCM control 
		LCD_WriteData(0x30); 	 //3F
		LCD_WriteData(0x30); 	 //3C
		LCD_WriteReg(0xC7);    //VCM control2 
		LCD_WriteData(0XB7); 
		LCD_WriteReg(0x36);    // Memory Access Control 
		LCD_WriteData(0x48); 
		LCD_WriteReg(0x3A);   
		LCD_WriteData(0x55); 
		LCD_WriteReg(0xB1);   
		LCD_WriteData(0x00);   
		LCD_WriteData(0x1A); 
		LCD_WriteReg(0xB6);    // Display Function Control 
		LCD_WriteData(0x0A); 
		LCD_WriteData(0xA2); 
		LCD_WriteReg(0xF2);    // 3Gamma Function Disable 
		LCD_WriteData(0x00); 
		LCD_WriteReg(0x26);    //Gamma curve selected 
		LCD_WriteData(0x01); 
		LCD_WriteReg(0xE0);    //Set Gamma 
		LCD_WriteData(0x0F); 
		LCD_WriteData(0x2A); 
		LCD_WriteData(0x28); 
		LCD_WriteData(0x08); 
		LCD_WriteData(0x0E); 
		LCD_WriteData(0x08); 
		LCD_WriteData(0x54); 
		LCD_WriteData(0XA9); 
		LCD_WriteData(0x43); 
		LCD_WriteData(0x0A); 
		LCD_WriteData(0x0F); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x00); 		 
		LCD_WriteReg(0XE1);    //Set Gamma 
		LCD_WriteData(0x00); 
		LCD_WriteData(0x15); 
		LCD_WriteData(0x17); 
		LCD_WriteData(0x07); 
		LCD_WriteData(0x11); 
		LCD_WriteData(0x06); 
		LCD_WriteData(0x2B); 
		LCD_WriteData(0x56); 
		LCD_WriteData(0x3C); 
		LCD_WriteData(0x05); 
		LCD_WriteData(0x10); 
		LCD_WriteData(0x0F); 
		LCD_WriteData(0x3F); 
		LCD_WriteData(0x3F); 
		LCD_WriteData(0x0F); 
		LCD_WriteReg(0x2B); 
		LCD_WriteData(0x00);
		LCD_WriteData(0x00);
		LCD_WriteData(0x01);
		LCD_WriteData(0x3f);
		LCD_WriteReg(0x2A); 
		LCD_WriteData(0x00);
		LCD_WriteData(0x00);
		LCD_WriteData(0x00);
		LCD_WriteData(0xef);	 
		LCD_WriteReg(0x11); //Exit Sleep
		LCD_Delayms(120);
		LCD_WriteReg(0x29); //display on
   	LCD_WriteReg(0x36);  
		LCD_WriteData(0xC9);	  
}

/********************************************************************************************************
*  Function: LCD_OpenWin				                                                           
*  Object: lcd open window for display
*  Input: x0,y0, x1, y1
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_OpenWin(u16 x0, u16 y0, u16 x1, u16 y1)
{
		/*
		#if (LCD_DIRECT == 1)
			LCD_WriteReg(0x0044);
			LCD_WriteData((x1<<8)+x0);
			LCD_WriteReg(0x0045);
			LCD_WriteData((y1<<8)+y0);	
			LCD_WriteReg(0x0021);
			LCD_WriteData((y0<<8)+x0); 
		#else
			LCD_WriteReg(0x0045);
			LCD_WriteData((x1<<8)+x0);
			LCD_WriteReg(0x0044);
			LCD_WriteData((y1<<8)+y0);
			LCD_WriteReg(0x0021);
			LCD_WriteData((x0<<8)+y0); 
		#endif
			LCD_WriteReg(0x0022);
		//S_DogFeed();
		*/
		LCD_WriteReg(0x2A);	
		LCD_WriteData(y0>>8);
		LCD_WriteData(0x00FF&y0);		
		LCD_WriteData(y1>>8);
		LCD_WriteData(0x00FF&y1);
		LCD_WriteReg(0x2B);	
		LCD_WriteData(x0>>8);
		LCD_WriteData(0x00FF&x0);		
		LCD_WriteData(x1>>8);
		LCD_WriteData(0x00FF&x1);
		LCD_WriteReg(0x2C);
}

/********************************************************************************************************
*  Function: LCD_ClrScr				                                                           
*  Object: lcd clear screen
*  Input: backcolor
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_ClrScr(u16 BackColor)
{
		u16 i,j;
		LCD_OpenWin(0, 0, LCD_ROW_NUM-1, LCD_COL_NUM-1);
		for(i = 0; i < LCD_ROW_NUM; i++)
			 for(j =0; j < LCD_COL_NUM; j++)
					 LCD_WriteData(BackColor);
}

/********************************************************************************************************
*  Function: LCD_DisAPoint				                                                           
*  Object: Display a point at screen
*  Input: site and color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisAPoint(u16 x0, u16 y0, u16 Color)
{
		LCD_DisASquare(x0, y0, 1, Color);
}

/********************************************************************************************************
*  Function: LCD_DisALine				                                                           
*  Object: Display a line
*  Input: site dir lenth wide color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisALine(u16 x0, u16 y0, u8 dir, u16 lenth, u16 color)
{
		u16 x1,y1;
		x1 = x0;
		y1 = y0;
		if(dir == 1)
			y1 = y1 + lenth;
		else
			x1 = x1 + lenth;
		LCD_DisARectangular(x0, y0, x1, y1, color);
}

/********************************************************************************************************
*  Function: LCD_DisABorder				                                                           
*  Object: Display a border
*  Input: x0, y0, x1, y1, color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisABorder(u16 x0, u16 y0, u16 x1, u16 y1, u16 Color)
{
		LCD_DisALine(x0, y0, 1, y1-y0, Color);
		LCD_DisALine(x1, y0, 1, y1-y0, Color);
		LCD_DisALine(x0, y0, 2, x1-x0, Color);
		LCD_DisALine(x0, y1, 2, x1-x0, Color);
}

/********************************************************************************************************
*  Function: LCD_DisALoop				                                                           
*  Object: Display a loop
*  Input: site,radius and color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisALoop(u16 x0, u16 y0, u8 r, u16 Color)
{
		s16 a,b,next;
		a	=	0;
		b = r;	  
		next = 3 - (r<<1);            
		while(a <= b)
		{
				LCD_DisAPoint(x0+a, y0-b, Color);             
				LCD_DisAPoint(x0+b, y0-a, Color);                      
				LCD_DisAPoint(x0+b, y0+a, Color);                          
				LCD_DisAPoint(x0+a, y0+b, Color);             
				LCD_DisAPoint(x0-a, y0+b, Color);                  
				LCD_DisAPoint(x0-b, y0+a, Color);             
				LCD_DisAPoint(x0-a, y0-b, Color);                          
				LCD_DisAPoint(x0-b, y0-a, Color);              	         
				a++;
				//use the bresenham    
				if(next<0)
					next += 4*a+6;	  
				else
				{
						next += 10+4*(a-b);   
						b--;
				} 						    
		}
} 

/********************************************************************************************************
*  Function: LCD_DisASquare				                                                           
*  Object: Display a square
*  Input: start point, wide, color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisASquare(u16 x0, u16 y0, u16 wide, u16 Color)
{
		u16 i,j;
		LCD_OpenWin(x0, y0, x0+wide-1, y0+wide-1);
		for(i = 0; i < wide; i++)
			for(j = 0; j < wide; j++)
					 LCD_WriteData(Color);
}

/********************************************************************************************************
*  Function: LCD_DisARectangular				                                                           
*  Object: Display a rectangular
*  Input: start point, end point, color
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisARectangular(u16 x0, u16 y0, u16 x1, u16 y1, u16 Color)
{
		u16 i,j;
		LCD_OpenWin(x0, y0, x1, y1);
		for(i = 0; i <= x1-x0; i++)
			 for(j = 0; j <= y1-y0; j++)
					 LCD_WriteData(Color);
}

/********************************************************************************************************
*  Function: LCD_DisASC8x16				                                                           
*  Object: Display a ASC(16*8)
*  Input: site, char, fColor, bColor
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisASCString16x8(u16 x0, u16 y0, u8 *s, u16 fColor, u16 bColor)
{
		u16 i,j,l = 1;
		while(*s)
		{
				LCD_OpenWin(x0, y0+(8-1)*(l-1), x0+16-1, y0+(8-1)*l);
				for(i=0; i<16; i++) 
				{
						u8 m = InforCode_Font8x16[(*s)*16+i];
						for(j=0; j<8; j++) 
						{
								if(m&CHSBIT7)
									LCD_WriteData(fColor);
								else 
									LCD_WriteData(bColor);
								m <<= 1;
						}
				}
				s++;
				l++;
		}
}

/********************************************************************************************************
*  Function: LCD_DisGB2312String16x16				                                                           
*  Object: display a chinese string
*  Input: site, char, fColor, bColor
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisGB2312String16x16(u16 x0, u16 y0, u8 *s, u16 fColor, u16 bColor)
{
		u16 Num;
		u8 i,j,m,l = 1;
		while(*s)
		{
				LCD_OpenWin(x0, y0+(16-1)*(l-1), x0+16-1, y0+(16-1)*l);
				for(Num = 0; Num < sizeof(GB2312Code16x16)/35; Num++)
				{
						if((GB2312Code16x16[Num].Head[0] == *s) && (GB2312Code16x16[Num].Head[1] == *(s+1)))
						{ 
								for(i = 0; i < 32; i++) 
								{
										m = GB2312Code16x16[Num].Infor[i];
										for(j = 0; j<8; j++) 
										{
												if(m&CHSBIT7)
													LCD_WriteData(fColor);
												else 
													LCD_WriteData(bColor);
												m<<=1;
										} 
								}
						}  
				}
				s+=2;
				l++;
		}
}

/********************************************************************************************************
*  Function: LCD_DisGB2312String32x32				                                                           
*  Object: display a chinese string
*  Input: site, char, fColor, bColor
*  Output: none                                  
*  brief: none
********************************************************************************************************/
/*
void LCD_DisGB2312String32x32(u16 x0, u16 y0, u8 *s, u16 fColor, u16 bColor)
{
		u16 Num;
		u8 i,j,m,l = 1;
		while(*s)
		{
				LCD_OpenWin(x0, y0+(32-1)*(l-1), x0+32-1, y0+(32-1)*l);
				for(Num = 0; Num < sizeof(GB2312Code32x32)/131; Num++)
				{
						if((GB2312Code32x32[Num].Head[0] == *s) && (GB2312Code32x32[Num].Head[1] == *(s+1)))
						{ 
								for(i = 0; i < 128; i++) 
								{
										m = GB2312Code32x32[Num].Infor[i];
										for(j = 0; j<8; j++) 
										{
												if(m&CHSBIT7)
													LCD_WriteData(fColor);
												else 
													LCD_WriteData(bColor);
												m<<=1;
										} 
								}
						}  
				}
				s+=2;
				l++;
		}
}
*/

/********************************************************************************************************
*  Function: LCD_DisAPhoto				                                                           
*  Object: display a photo
*  Input: Site(x0,y0), high and wide, pData
*  Output: none                                  
*  brief: none
********************************************************************************************************/
void LCD_DisAPhoto(u16 x0, u16 y0, u16 high, u16 wide, u8 *pData)
{
		u32 i,lenth;
		lenth = high * wide * 2;  		//RGB565 每一像素点占用两个字节
		LCD_OpenWin(x0, y0, x0+high-1, y0+wide-1);
		for(i = 0; i < lenth; i+=2)
			LCD_WriteData((*(pData+i))*0x100 + (*(pData+i+1)));
}


