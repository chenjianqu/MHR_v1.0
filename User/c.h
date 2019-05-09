#ifndef __C_H
#define __C_H

#include "CoordinateSystem.h"
#include "pid.h"
#include "motor.h"
#include "delay.h"
#include "sys.h"
#include "tracksensor.h"
#include "key.h"
#include "led.h"
#include "myuart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "car.h"
#include "task.h"
#include "run.h"
#include "lcd.h"

//MV命令
#define ORDER_RESET 0
//接收
#define ORDER_RGB 'a'
#define ORDER_RBG 'b'
#define ORDER_GRB 'c'
#define ORDER_GBR 'd'
#define ORDER_BRG 'e'
#define ORDER_BGR 'f'
#define ORDER_START 'g'
#define ORDER_STOP 'h'

#define ORDER_TRUE 'h'
#define ORDER_FALSE 'g'

#define ORDER_NO_REC 'n'

//发送
#define ORDER_QRCODE 'i'
#define ORDER_CARRYUP 'j'

#define ORDER_CARRYUP_LOW 'm'

#define ORDER_PUTDOWN 'k'
#define ORDER_SCANCOLOR 'l'
#define ORDER_SCANOBJECT 'o'


#define ORDER_RPF 'p'
#define ORDER_RFP 'q'
#define ORDER_PRF 'r'
#define ORDER_PFR 's'
#define ORDER_FRP 't'
#define ORDER_FPR 'u'




//前进等级

#define SPEED_LEVEL_0 500
#define SPEED_LEVEL_1 350
#define SPEED_LEVEL_2 250
#define SPEED_LEVEL_3 250
#define SPEED_LEVEL_4 100
  
#define SPEED_LEVEL_LESS_N 500
#define SPEED_LEVEL_LESS2 450
#define SPEED_LEVEL_LESS1 450
#define SPEED_LEVEL_LESS0 400

//时间
#define One_Sec 1000
#define One_Min 60*One_Sec
#define Five_Min 5*One_Min


#define Limited_Time 7*One_Min+One_Sec*45



//
#define GRID_TIME_COF 80 //过了一个点后 下一条黑线被探测的时间 200 ms

#define BLOCK_DELAY_TIME 100//阻塞前进时间

#define INTERVAL_SEND_INF 1000


#define SPEED_LEFT_LEVEL_N 500
#define SPEED_LEFT_LEVEL_0 700
#define SPEED_LEFT_LEVEL_1 500
#define SPEED_LEFT_LEVEL_2 400
#define SPEED_LEFT_LEVEL_3 300
#define SPEED_LEFT_LEVEL_4 200


#endif
