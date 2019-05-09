#include "key.h"
#include "delay.h"

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //按键松开标志
    if(mode==1)
			key_up=1;    //支持连按
    if(key_up&&(KEY1==1||KEY2==1))
    {
        delay_ms(20);
        key_up=0;
        if(KEY1==1)  
					return KEY1_PRES;
        else if(KEY2==1)  
					return KEY2_PRES;
    }
		else if(KEY1==0&&KEY2==0)
			key_up=1;
    return 0;   //无按键按下
}
