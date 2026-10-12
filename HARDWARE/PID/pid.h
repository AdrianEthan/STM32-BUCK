#ifndef _PID_H
#define _PID_H

typedef struct
{
	float Sv;//期望值
	float Pv;//实际值
	float Ek_1;
	float Ek_2;
	float Ek;
	float T;//采样周期
	float Ti;//积分常数
	float Td;//微分常数
	float Kp_P;//系数
	float Kp_I;//系数
	float Kp_D;//系数
	float OUT_Single;
	float Pout;
	float Iout; 
	float Dout;
}PID_Struct;
float buck_pid(float NOW,float Target,float SIGNLE_ADD_NUM_LIMIT,float SUM_OUTPUT_NUM_LIMIT,float ki);
void init_buck_PID(void);
extern float OUT;
#endif

