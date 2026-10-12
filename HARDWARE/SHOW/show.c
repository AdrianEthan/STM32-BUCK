#include "show.h"
#include "sys.h"
#include "delay.h"
#include "oled.h"
#include "main.h"

void qidong_view()//启动界面，按下choice按键
{
	OLED_Clear();
	OLED_ShowCHinese(32,0,0);OLED_ShowCHinese(48,0,1);OLED_ShowCHinese(64,0,2);OLED_ShowCHinese(80,0,3);//启动界面
	OLED_ShowString(12,3,"press--choice",16);
  OLED_ShowString(40,5,"start!!",16);
}
void canshu_view()                                                                                                                                                         //OLED显示的参数界面，用来显示测量的输出电压参数
{
	OLED_Clear();
	//输出电压	
	OLED_ShowCHinese(0,0,14);OLED_ShowCHinese(16,0,15);OLED_ShowCHinese(32,0,13);OLED_ShowCHinese(48,0,9);
	OLED_ShowString(64,0,":",16);
	OLED_ShowString(88,0,".",16);OLED_ShowString(112,0,"V",16);
	//输出电流
	OLED_ShowCHinese(0,2,14);OLED_ShowCHinese(16,2,15);OLED_ShowCHinese(32,2,13);OLED_ShowCHinese(48,2,10);
	OLED_ShowString(64,2,":",16);
	OLED_ShowString(88,2,".",16);OLED_ShowString(112,2,"A",16);
	//输出功率
	OLED_ShowCHinese(0,4,14);OLED_ShowCHinese(16,4,15);OLED_ShowCHinese(32,4,16);OLED_ShowCHinese(48,4,17);
	OLED_ShowString(64,4,":",16);
	OLED_ShowString(88,4,".",16);OLED_ShowString(112,4,"W",16);
	//负载温度
	OLED_ShowCHinese(0,6,18);OLED_ShowCHinese(16,6,19);OLED_ShowCHinese(32,6,20);OLED_ShowCHinese(48,6,21);//负载温度
	OLED_ShowString(64,6,":",16);
	OLED_ShowString(88,6,".",16);OLED_ShowString(104,6      ,"*C",16);
}
void moshi_view()//OLED显示的参数界面，用来显示测量的输出电压参数
{
	OLED_Clear();
	//模式选择
	OLED_ShowCHinese(32,0,4);OLED_ShowCHinese(48,0,5);OLED_ShowCHinese(64,0,6);OLED_ShowCHinese(80,0,7);
	//恒压模式	
  OLED_ShowCHinese(0,3,8);OLED_ShowCHinese(16,3,9);OLED_ShowCHinese(32,3,4);OLED_ShowCHinese(48,3,5);
	//恒流模式	
  OLED_ShowCHinese(0,5,8);OLED_ShowCHinese(16,5,10);OLED_ShowCHinese(32,5,4);OLED_ShowCHinese(48,5,5);
}

void hengya_view()//OLED显示的参数界面，用来显示测量的输出电压参数
{
	OLED_Clear();
	//目标电压
	OLED_ShowCHinese(0,3,11);OLED_ShowCHinese(16,3,12);OLED_ShowCHinese(32,3,13);OLED_ShowCHinese(48,3,9);
	OLED_ShowString(64,3,":",16);
	OLED_ShowString(88,3,".",16);OLED_ShowString(112,3,"V",16);
}
void hengliu_view()//OLED显示的参数界面，用来显示测量的输出电压参数
{
	OLED_Clear();
	//目标电流
	OLED_ShowCHinese(0,3,11);OLED_ShowCHinese(16,3,12);OLED_ShowCHinese(32,3,13);OLED_ShowCHinese(48,3,10);
	OLED_ShowString(64,3,":",16);
	OLED_ShowString(88,3,".",16);OLED_ShowString(112,3,"A",16);
}
