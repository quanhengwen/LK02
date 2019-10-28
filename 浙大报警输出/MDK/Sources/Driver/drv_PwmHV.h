#ifndef _DRV_PWMHV_H_
#define _DRV_PWMHV_H_

#include "stm32f10x.h"
void PwmCongfig(void);
//设置APD,PWM正脉冲宽度：
void  PWMSet_APD(int16_t Pulse);
//获取当前PWM正脉冲宽度：
int16_t  PWM_Get(void);
//调整PWM正脉冲宽度：
int16_t  PWM_Adj_APD(int16_t dPulse);

void   PWM_TEST(u8  state);//0--apd，1--ld,2--apd&&ld

#endif

