#ifndef __ENCODER_H
#define __ENCODER_H	 
#include "sys.h"
#define cycle       1     //定义动作周期，转多少格有效        
#define NULL        0     //编码器不动作时的返回值
#define E_RIGHT     0x0e  //右转返回值      
#define E_LEFT      0x0f  //左转返回值
typedef unsigned char uchar;
uchar WheelRight(void);
uchar WheelLeft(void);
uchar EncoderProcess(void);
void inc(void);
void dec(void);
#define SCENE_KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//读取按键X_A
#define SCENE_KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键X_B
#endif
