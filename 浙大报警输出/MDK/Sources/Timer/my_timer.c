/*******************************************************************
*file name:    my_timer.c
*project:      s2x
*Description:  dynamic timer
*Platform: 	   stm32
*firmware:     v1.0
*Author:       cwd
*data:		   2015.12.26
*note:         null
*******************************************************************/
#include "global.h"
#include "my_timer.h"

//-----------------------------------------------------------------------------
volatile rt_tick_t rt_tick = 0;

u8 g_TimerNbr = 0;  /* the numbers of current timer */

TimerFuncPtr g_TimerFuncTab[MAX_TIMER_NUM];/* timer function table */
rt_tick_t g_TimerTickTab[MAX_TIMER_NUM];  /* timer tick table */

OutputTimeStr_t OutputTimeStr;
/*---------------------------------------------------------------------------*/
/**
 * Set a timer.
 *
 * This function is used to set a timer for a time sometime in the
 * future. The function timer_expired() will evaluate to true after
 * the timer has expired.
 *
 * param t A pointer to the timer
 * param interval The interval before the timer expires.
 *
 */
rt_tick_t timer_set(s16 interval)
{
    return (rt_tick + interval);
}

/*---------------------------------------------------------------------------*/
/**
 * Check if a timer has expired.
 *
 * This function tests if a timer has expired and returns true or
 * false depending on its status.
 *
 * param t A pointer to the timer
 *
 * return Non-zero if the timer has expired, zero otherwise.
 *
 */
bool timer_expired(rt_tick_t t)
{
    if ((rt_tick_t)(rt_tick - t) >= 0)
        return TRUE;
    else
        return FALSE;
}
/*
描述:   定时器处理机
输入:   必须放在while(1)里面跑
输出:   无
*/
void SoftTimerHandler(void)
{
    TimerFuncPtr func;
    rt_tick_t tick;
    int i;

    if(g_TimerNbr==0)
        return;

    tick = rt_tick;
    
    /* Find one time slot */
    for(i=0; i<MAX_TIMER_NUM; i++)
    {
        if((g_TimerFuncTab[i]!=NULL) && ((rt_tick_t)(tick-g_TimerTickTab[i])>=0))
        {
            func = g_TimerFuncTab[i];

            /* delete the timer slot */
            g_TimerFuncTab[i] = NULL;
            g_TimerNbr--;

            /* execute function */
            func();
        }
    }
}

/*
描述:   定时器开始
输入:   FuncPtr:超时函数句柄,ms:多少ms,不要超过 32768*SYS_TICK_MS = 32768*5 = 163840ms
输出:   无
*/
int TimerStart(TimerFuncPtr FuncPtr,int ms)
{
    int i,number;
    rt_tick_t tick;
    
    if(ms==0)
        return -1;
    
    if(g_TimerNbr>=MAX_TIMER_NUM)
        return -1;
    
    tick = rt_tick + (rt_tick_t)(ms/SYS_TICK_MS);
    number = -1;
    
    /* Find an empty time slot */
    for(i=0; i<MAX_TIMER_NUM; i++)
    {
        if(g_TimerFuncTab[i] != NULL)
        {
            if(g_TimerFuncTab[i] == FuncPtr)
            {
                g_TimerTickTab[i] = tick;
                return 0;
            }
        }
        else if(number==-1)
        {
            number = i;
        }
    }
    if(number==-1)
        return -1;
    
    g_TimerFuncTab[number] = FuncPtr;
    g_TimerTickTab[number] = tick;
    g_TimerNbr++;

    return 1;
}

/*
描述:   定时器停止
输入:   timeout:超时函数句柄
输出:   无
*/
int TimerStop(TimerFuncPtr FuncPtr)
{
    int i;

    if(g_TimerNbr==0)
        return -1;
    
    for(i=0; i<MAX_TIMER_NUM; i++)
    {
        /* Find one time slot */
        if(FuncPtr == g_TimerFuncTab[i])
        {
            g_TimerFuncTab[i] = NULL; /* delete the timer slot */
            g_TimerNbr--;
            return 1;
        }
    }
    
    return 0;
}



void hr_TimerBaseInit(TIM_TypeDef* TIMX, uint16_t pre, uint16_t period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_DeInit(TIMX);                               
		 
	/* TIM2 configuration */						
	TIM_TimeBaseStructure.TIM_Period = period;         
	TIM_TimeBaseStructure.TIM_Prescaler = pre;     
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);
	/* Clear   update pending flag */
	TIM_ClearFlag(TIMX, TIM_FLAG_Update); 
	/* Enable   Update interrupt */
	TIM_ITConfig(TIMX, TIM_IT_Update, ENABLE); 
	/*  enable counter */
	TIM_Cmd(TIMX, ENABLE);
}

void HwTimer_InterrtpyInit()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
    
  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
 
}
extern T_SysParam SysSeting;

extern unsigned char Packet(unsigned char* pGetBuf,unsigned int distres);
extern u8  FreeRun;


void TimerBoard_Init()
{
  unsigned short tmv_set = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    //SysSeting.CurMol = 1;
    //GPIO_SetBits(GPIOB,GPIO_Pin_8);
	hr_TimerBaseInit(TIM3,63,999);
	HwTimer_InterrtpyInit();
    if(SysSeting.CurMol == 255){//new eerom sectors(without system params)
      SysSeting.CurMol = 0; 
      DefaultSetting(); 
      SettingSave();
      sprintf(UsartDatStr.TxBuffer,"当前为标定模式，请标定!\r\n");
      UsartDatStr.TxSize=strlen(UsartDatStr.TxBuffer);
    }else if(SysSeting.CurMol == 1){//has be calibrated 
      SysSeting.CurMol = 2;//directly update to realease
      if(SysSeting.OutputHZ > 1000){
        SysSeting.OutputHZ = 1000;
        tmv_set = 999;
      }else{
        if(SysSeting.OutputHZ <= 15){
          tmv_set = 999;
          OutputTimeStr.SuposOutputHzCnt = 1000/SysSeting.OutputHZ;//1000 = 1秒
        }else{
          OutputTimeStr.SuposOutputHzCnt = 0;
          tmv_set = 1000000/SysSeting.OutputHZ - 1;
        }
      }
      //Printf("hz:%d t%d cnt%d\r\n",SysSeting.OutputHZ,tmv_set,OutputTimeStr.SuposOutputHzCnt);
      hr_TimerBaseInit(TIM3,63,tmv_set);
       UsartDatStr.FinishedTxFlag = 1;
      //UsartDatStr.TxSize = Packet(UsartDatStr.TxBuffer,0x00);
       UsartDatStr.TxSize = Packet(UsartDatStr.TxBuffer,0x00);
      UsartDatStr.TxSize=strlen(UsartDatStr.TxBuffer);
    }else if(SysSeting.CurMol == 2){
      UsartDatStr.TxSize = Packet(UsartDatStr.TxBuffer,0x00);
      UsartDatStr.TxSize=strlen(UsartDatStr.TxBuffer);
    }else{
      //sprintf(UsartDatStr.TxBuffer,"当前为标定模式，请标定!\r\n");
      //UsartDatStr.TxSize=strlen(UsartDatStr.TxBuffer);
      Printf("当前为标定模式，请标定!\r\n");
      
    }
    

    Uart1_DMASendOutOnce(UsartDatStr.TxBuffer,UsartDatStr.TxSize);
 
}


extern u32 dist_final;
extern u8  Flag_Cal;
extern E_MEAS_STATE MeasStatus ;
void TIM3_IRQHandler()
{
  (OutputTimeStr.OutputTimeCnt > 0) ? (OutputTimeStr.OutputTimeCnt--) : 0;

  if((MeasStatus||FreeRun)  && !Flag_Cal){
      if(UsartDatStr.FinishedTxFlag){
        if(OutputTimeStr.OutputTimeCnt == 0){
          OutputTimeStr.OutputTimeCnt = OutputTimeStr.SuposOutputHzCnt;
          if(SysSeting.CurMol != 0){
            GPIO_SetBits(GPIOB,GPIO_Pin_8);
            if(dist_final == 0){
              sprintf(UsartDatStr.TxBuffer,"---\r\n");
            }else{
              sprintf(UsartDatStr.TxBuffer,"%.2fm\r\n",dist_final/100.0);
            }
            //GPIO_WriteBit(GPIOB,GPIO_Pin_8,!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8));
            UsartDatStr.TxSize = strlen(UsartDatStr.TxBuffer);
            //UsartDatStr.TxSize = Packet(UsartDatStr.TxBuffer,dist_final);
            UsartDatStr.FinishedTxFlag = 0;
            Uart1_DMASendOutOnce(UsartDatStr.TxBuffer,UsartDatStr.TxSize);
          }
        }
      }
    }
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
