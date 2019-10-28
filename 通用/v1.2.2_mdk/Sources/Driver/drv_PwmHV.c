/*******************************************************************
*file name:     drv_PwmHV.c
*project:        c2_new
*Description:   PWM ADJ
*Platform: 	  uCOSII2.86
*firmware:      v1.0
*Author:         cwd
*data:		  2013.1.25
*note:            null
*******************************************************************/
#include "global.h"
//PB1--TIM3-CH4
//PA3--TIM2-CH4
static u16  PWM_pulse_APD,PWM_pulse_LD;
static u16  PWM_max=500;

void PwmCongfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                          //GPIO�ṹ������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;								//��ʱ���ṹ������
	TIM_OCInitTypeDef TIM_OCInitStructure;												//OC����
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM2,ENABLE);						//ʹ��TIM3ϵͳʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    
    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM3|GPIO_FullRemap_TIM2,ENABLE);	
	/*
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
    */
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
    /*
	TIM_TimeBaseStructure.TIM_Prescaler=0x0; //ʱ��Ԥ��Ƶֵ=72M/(0+1)=72M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseStructure.TIM_Period=1999;//1439; 2879//�Զ���װֵ    PWMƵ��=72000000/(7199+1)=10K
	TIM_TimeBaseStructure.TIM_ClockDivision=0;//ʱ��ָ�ֵ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
    */
    TIM_TimeBaseStructure.TIM_Prescaler=0x0; //ʱ��Ԥ��Ƶֵ=64M/(0+1)=64M
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseStructure.TIM_Period=1999;//32khz;//1439; 2879//�Զ���װֵ    PWMƵ��=64000000/(1999+1)=32K
	TIM_TimeBaseStructure.TIM_ClockDivision=0;//ʱ��ָ�ֵ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	
	/*
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse =0;                                  //Ĭ��ռ�ձ�Ϊ0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse =0;                                  //Ĭ��ռ�ձ�Ϊ0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    
	//TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);

  	/*
	TIM_ARRPreloadConfig(TIM3, ENABLE);	
	TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
    */
    TIM_ARRPreloadConfig(TIM2, ENABLE);	
	TIM_Cmd(TIM2, ENABLE);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
	
	PWM_pulse_APD=0;
    PWM_pulse_LD=0;
	PWM_max = 500;	
}

//����APD,PWM�������ȣ�
void  PWMSet_APD(int16_t Pulse)
{
	if(Pulse > PWM_max)
		PWM_pulse_APD = PWM_max;
	else if(Pulse < 0)
		PWM_pulse_APD = 0;
	else
        PWM_pulse_APD= Pulse;
	
    TIM_SetCompare4(TIM2, PWM_pulse_APD);
}

//����LD,PWM�������ȣ�
void  PWMSet_LD(int16_t Pulse)
{
	if(Pulse > PWM_max)
		PWM_pulse_LD = PWM_max;
	else if(Pulse < 0)
		PWM_pulse_LD = 0;
	else
        PWM_pulse_LD= Pulse;
	
    TIM_SetCompare4(TIM3, PWM_pulse_LD);
}

//��ȡ��ǰPWM�������ȣ�
int16_t  PWM_Get(void)
{
	return PWM_pulse_APD;
}

//����PWM�������ȣ�APD
int16_t  PWM_Adj_APD(int16_t dPulse)
{
	PWMSet_APD(PWM_pulse_APD + dPulse);
	
	if(PWM_pulse_APD==0 || PWM_pulse_APD==PWM_max)
	{
		//���ڳ�����Χ������0
	  return 0;
	}
	else
	{
		//���ص�ǰPWM��������
		return PWM_pulse_APD;
	}
}

//����PWM�������ȣ�LD
int16_t  PWM_Adj_LD(int16_t dPulse)
{
	PWMSet_LD(PWM_pulse_LD + dPulse);
	
	if(PWM_pulse_LD==0 || PWM_pulse_LD==PWM_max)
	{
		//���ڳ�����Χ������0
	  return 0;
	}
	else
	{
		//���ص�ǰPWM��������
		return PWM_pulse_LD;
	}
}

void   PWM_TEST(u8  state)//0--apd��1--ld,2--apd&&ld
{
  if(state==0)
  {
    do
    {
    if(PWM_Adj_APD(10)>800){PWMSet_APD(100);}//���ڵ�����С
    delay1us(1000000);
    }while(1);
  }
  else if(state==1)
  {
    do
    {
    if(PWM_Adj_LD(10)>800){PWMSet_LD(100);}//���ڵ�����С
    delay1us(1000000);
    }while(1);
  }
  else
  {
    do
    {
    if((PWM_Adj_APD(10)>800)||(PWM_Adj_LD(10)>800)){PWMSet_APD(100);PWMSet_LD(100);}//���ڵ�����С
    delay1us(1000000);
    }while(1);
  }
}
