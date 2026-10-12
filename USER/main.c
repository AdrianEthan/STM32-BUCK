#include "stm32f10x.h" 
#include "main.h"      
#include "delay.h"      
#include "timer.h"     
#include "timer3.h"         
#include "oled.h"      
#include "show.h"         
#include "adc.h"            
#include "sw.h"
#include "key.h"
 

u8 pid_mode=0;//稳压算法使能（控制用）=0不工作，失能，=1工作，使能
u8 pid_status=0;//=0为电压环，=1为电流环
u16 buck_pwm=500;//BOOST电路的PWM

float DC_V=0.0f;//电压数据
float Target_V=10.00f;//追踪的电压数据
float DC_I=0.0f;//电流数据

float V_yuzhi=13.00f;//保护的电压阈值
float I_yuzhi=3.00f;//保护的电流阈值

u8 protect_status=0;//保护状态（保护触发标志）=0未触发保护，=1触发保护。
u8 sw_status=0;//开关状态
/************************************************************
电压电流检测:电压PA0，电流PA1
PWM波驱动引脚:PA8
芯片使能引脚:PA9
OLED屏幕:SCL:PB1,SDA:PB0
继电器控制位:PA10
按键:ADD:PB12 REDUCE:PB13 SET:PB14 MODE:PB15
************************************************************/
int main(void) 
 {
	u8 key;	   
	Delay_Init();                   //延时功能初始化           
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级	

	BUCK_PWM_Init();                //BUCK电路初始化，20KHz工作频率，带中断。
	Init_adc();                     //ADC初始化	 
	SW_Init( );                     //继电器初始化
	KEY_Init();                     //按键初始化
 
	TIM3_ENABLE_30S();	            //开启定时器3工作，实现电压电流数据采集，5ms一次
	OLED_Init();			              //初始化OLED  
	 
	loop:
	SW_OFF;
	SD_OFF;
	sw_status=0;
	pid_mode=0;//失能PID
	OLED_Clear();                   //OLED清零 
	canshu_view();                  //启动界面	
	while(1)
	{	
		key=KEY_Scan(0);              //扫描按键
		if(key==SW_PRES)
		{
			SD_ON;                      //打开芯片引脚使能
			SW_ON;                      //打开继电器电路准备工作 
			Delay_Ms(500);			
			break;
		}
	  OLED_ShowNum(72,0,DC_V,2,16);
	  OLED_ShowNum(96,0,(u16)(DC_V*100)%100,2,16);	
	  OLED_ShowNum(72,2,DC_I,2,16);
	  OLED_ShowNum(96,2,(u16)(DC_I*100)%100,2,16);	
	  OLED_ShowNum(72,4,Target_V,2,16);
	  OLED_ShowNum(96,4,(u16)(Target_V*100)%100,2,16);
		if(sw_status==0)
		{
			OLED_ShowCHinese(84,6,13);OLED_ShowCHinese(100,6,14);
		}
		else
		{
			OLED_ShowCHinese(84,6,11);OLED_ShowCHinese(100,6,12);			
		}
		Delay_Ms(50);
	}	
	while(1)
	{
	  key=KEY_Scan(0);
	  OLED_ShowNum(72,0,DC_V,2,16);
	  OLED_ShowNum(96,0,(u16)(DC_V*100)%100,2,16);	
	  OLED_ShowNum(72,2,DC_I,2,16);
	  OLED_ShowNum(96,2,(u16)(DC_I*100)%100,2,16);	
	  OLED_ShowNum(72,4,Target_V,2,16);
	  OLED_ShowNum(96,4,(u16)(Target_V*100)%100,2,16);
		if(sw_status==0)
		{
			OLED_ShowCHinese(84,6,13);OLED_ShowCHinese(100,6,14);
		}
		else
		{
			OLED_ShowCHinese(84,6,11);OLED_ShowCHinese(100,6,12);			
		}

    if(key==SW_PRES)
	  {
	  	pid_mode=1;
			sw_status=1;
	  }
    else if(key==ADD_PRES)
		{
			Target_V=Target_V+0.100001f;
		}		
    else if(key==REDUCE_PRES)
		{
			Target_V=Target_V-0.099999f;
		}			
		else if(key==CHOICE_PRES)
		{
	    SW_OFF;
			SD_OFF;
	    sw_status=0;
	    pid_mode=0;//失能PID
	    goto loop;			
		}
		
    if((DC_V>V_yuzhi)||(DC_I>I_yuzhi))
	  {
	    SW_OFF;
			SD_OFF;
	    protect_status=1;	//记录"保护发生了"
	    sw_status=0;		//输出状态标志也归 0
	    pid_mode=0;			//稳压失能PID
	    goto loop;			//回待机界面
	  }				
	}
}

