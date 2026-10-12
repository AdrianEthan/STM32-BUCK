/*-------------------------------------------------*/
/*            超纬电子STM32系列开发板              */
/*-------------------------------------------------*/
/*                                                 */
/*            实现定时器1功能的头文件              */
/*                                                 */
/*-------------------------------------------------*/

#ifndef _TIMER1_H
#define _TIMER1_H
extern float ADC_ConvertedValueLocal; 
extern float ADC_ConvertedValueLoca2;
void TIM1_Time_Init(u16 arr,u16 psc);

#endif
