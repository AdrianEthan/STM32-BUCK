#include "encoder.h"
#include "main.h"

uchar WheelNow,WheelOld,RightCount,LeftCount;
uchar WheelRight()
{
		LeftCount=0;
		RightCount++;
		if (RightCount>=cycle)
			{
			RightCount=0;
			return(E_RIGHT);
		  }  
	else return(NULL);
}

uchar WheelLeft()
{
    RightCount=0;
    LeftCount++;
    if (LeftCount>=cycle)
			{
        LeftCount=0;
        return(E_LEFT);
      } 
			else return(NULL);
}
uchar EncoderProcess()
{
		uchar keytmp;
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		WheelNow=WheelNow<<1;
		if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1) WheelNow=WheelNow+1;  
		WheelNow=WheelNow<<1;
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == 1) WheelNow=WheelNow+1;  
		WheelNow=WheelNow & 0x03;  
		if (WheelNow==0x00) return(NULL); 
		keytmp=WheelNow;
		keytmp ^=WheelOld; 
		if (keytmp==0) return(NULL); 
												 
		if (WheelOld==0x01 && WheelNow==0x02){ 
		WheelOld=WheelNow;
		return(WheelLeft()); 
		}
		else if (WheelOld==0x02 && WheelNow==0x01){ 
		WheelOld=WheelNow;
		return(WheelRight()); 
		}
		WheelOld=WheelNow; 
		return(NULL); 
}

void inc()
{
  if(work_mode==2)pid_status=!pid_status;
	else if(work_mode==3)
	{
		if(pid_status==0)Target_V+=0.10001f;
		else Target_I+=0.10001f;	
	}
} 

void dec()
{	
  if(work_mode==2)pid_status=!pid_status;
	else if(work_mode==3)
	{
		if(pid_status==0)Target_V-=0.099999f;
		else Target_I-=0.099999f;	
	}
}
