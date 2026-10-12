#ifndef __BEEP_H
#define __BEEP_H
#include "main.h"
void BEEP_Init(void);
#define BEEP_ON GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define BEEP_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#endif
