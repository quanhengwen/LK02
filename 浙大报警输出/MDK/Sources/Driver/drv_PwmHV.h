#ifndef _DRV_PWMHV_H_
#define _DRV_PWMHV_H_

#include "stm32f10x.h"
void PwmCongfig(void);
//����APD,PWM�������ȣ�
void  PWMSet_APD(int16_t Pulse);
//��ȡ��ǰPWM�������ȣ�
int16_t  PWM_Get(void);
//����PWM�������ȣ�
int16_t  PWM_Adj_APD(int16_t dPulse);

void   PWM_TEST(u8  state);//0--apd��1--ld,2--apd&&ld

#endif

