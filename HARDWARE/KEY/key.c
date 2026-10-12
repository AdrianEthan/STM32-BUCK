#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure; 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //使能PORTB时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;            //SW
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);                 //初始化PB14
}
//按键处理函数
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(SW==0||CHOICE==0||ADD==0||REDUCE==0))
	{
		Delay_Ms(10);//去抖动 
		key_up=0;
		if(SW==0)return SW_PRES;
		else if(CHOICE==0)return CHOICE_PRES;
		else if(ADD==0)return ADD_PRES;
		else if(REDUCE==0)return REDUCE_PRES;
	}else if(SW==1&&CHOICE==1&&ADD==1&&REDUCE==1)key_up=1; 	    
 	return 0;// 无按键按下
}
