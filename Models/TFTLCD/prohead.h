#ifndef __ProHead__
#define __ProHead__
/*--------------------------------------------------------------------------------------
*  @file     ProHead.h
*  @author   EUµç×Ó lin
*  @version  V1.0.1   
*  @date     2012.7.15
*  @brief    Project head file, must include it at first.
---------------------------------------------------------------------------------------*/
//+++++++++++++++++++++++++++ Standard C LIBS +++++++++++++++++++++++++++++++++//
#include <string.h>
#include <stdio.h>
#include <stddef.h> 

//+++++++++++++++++++++++++++ Numbers Define  ++++++++++++++++++++++++++++++++++//
#define  True  1
#define  False 0
#define  ZERO 		   	0
#define  ONE         	1
#define  TWO         	2
#define  THREE       	3
#define  FOUR        	4
#define  FIVE        	5
#define  SIX         	6
#define  SEVEN       	7
#define  EIGHT       	8
#define  NINE        	9
#define  TEN         	10
#define  HUNDRED     	100
#define  THOUSAND    	1000
#define  HALFBYTEMAX 	15
#define  ONEBYTEMAX  	255

//+++++++++++++++++++++++++++ Type Declaration ++++++++++++++++++++++++++++++++++//
//!You should modify it for different c compiler.
 typedef unsigned char       bool;
 typedef          char       ascii;
 typedef unsigned char       u8;
 typedef signed   char       s8;
 typedef unsigned short      u16;
 typedef signed   short      s16;


//+++++++++++++++++++++++++++ Bit Computing ++++++++++++++++++++++++++++++++++//


//+++++++++++++++++++++++++++++ Others ++++++++++++++++++++++++++++++++++++//
//TAST RUN STEPS.
enum
{
	STEP0 = 0,         STEP1 = 1,         STEP2 = 2,         STEP3 = 3,
	STEP4 = 4,         STEP5 = 5,         STEP6 = 6,         STEP7 = 7,
	STEP8 = 8,         STEP9 = 9,         STEP10 = 10,       STEP11 = 11,
	STEP12 = 12,       STEP13 = 13,       STEP14 = 14,       STEP15 = 15,
	STEP16 = 16,       STEP17 = 17,       STEP18 = 18,       STEP19 = 19,
	STEP20 = 20,       STEP21 = 21,       STEP22 = 22,       STEP23 = 23,
	STEP24 = 24,       STEP25 = 25,       STEP26 = 26,       STEP27 = 27,
	STEP28 = 28,       STEP29 = 29,       STEP30 = 30,       STEP31 = 31,
	STEP32 = 32,       STEP33 = 33,       STEP34 = 34,       STEP35 = 35
};


#endif



