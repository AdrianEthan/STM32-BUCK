#include "pid.h"
#include "main.h"
PID_Struct pid1;

float OUT=50;
float buck_pid(float NOW,float Target,float SIGNLE_ADD_NUM_LIMIT,float SUM_OUTPUT_NUM_LIMIT,float ki)//SIGNLE_ADD_NUM_LIMIT是单次增加最大值 如100即为单次转换输出不能超过+-100
{
	//SUM_OUTPUT_NUM_LIMIT 是总输出限位 如100 即总输出不能超出+-100的范围 防止长时间低于或高于 对于突变反应不及时

	pid1.Pv=NOW;
	pid1.Ek=Target-pid1.Pv;
	pid1.Pout=pid1.Kp_P*(pid1.Ek-pid1.Ek_1);
	pid1.Iout=ki*pid1.Ek*pid1.T/pid1.Ti;
	pid1.Dout=pid1.Kp_D*pid1.Td*(pid1.Ek-pid1.Ek_1-pid1.Ek_1+pid1.Ek_2)/pid1.T;
	pid1.OUT_Single=pid1.Pout+pid1.Iout+pid1.Dout;
	if(pid1.OUT_Single>SIGNLE_ADD_NUM_LIMIT)pid1.OUT_Single=SIGNLE_ADD_NUM_LIMIT;
	else if(pid1.OUT_Single<-SIGNLE_ADD_NUM_LIMIT)pid1.OUT_Single=-SIGNLE_ADD_NUM_LIMIT;
	OUT+=pid1.OUT_Single;
	if(OUT>SUM_OUTPUT_NUM_LIMIT)OUT=SUM_OUTPUT_NUM_LIMIT;
	else if(OUT<0)OUT=0;
	pid1.Ek_2=pid1.Ek_1;
	pid1.Ek_1=pid1.Ek;
	return OUT;
}

void init_buck_PID()
{
	pid1.Kp_P=0;
	pid1.Kp_I=1;
	pid1.Kp_D=0;
	pid1.T=1;//Ms
	pid1.Td=2.5;
	pid1.Ti=150;
	pid1.Pv=1000;
	pid1.Ek_2=0;
	pid1.Ek_1=0;
	pid1.Ek=0;
}
