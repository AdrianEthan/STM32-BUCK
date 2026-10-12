/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板              */
/*-------------------------------------------------*/
/*                                                 */
/*            实现定时器1功能的源文件              */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f10x.h"  //包含需要的头文件
#include "adc.h"
#include "main.h"
/*-------------------------------------------------*/
/*函数名：定时器1使能1分钟定时                     */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM1_Time_Init(u16 arr,u16 psc)
{
		//TIM1_Init(4999,7199);
	  //计数频率=Tclk/7200=72000000/7200=10000Hz  计一个数用时1/10000s  计数5000次=5000/10000s=500ms
	  //Tout(溢出时间)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //允许更新中断

		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  

		TIM_Cmd(TIM1, ENABLE);  
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ; 
void TIM1_UP_IRQHandler(void)   
{	
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIMx更新中断标志 
	}
}

