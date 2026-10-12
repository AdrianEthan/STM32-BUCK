#include "sw.h"

void SW_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //使能PORTB时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10;	//pin_9为IR2104s的EN引脚，pin_10为继电器的开启引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          //设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);                 //初始化6个物镜检测通道
  SW_OFF;													//关闭继电器电路准备工作
	SD_OFF; 												//关闭芯片引脚使能
}
