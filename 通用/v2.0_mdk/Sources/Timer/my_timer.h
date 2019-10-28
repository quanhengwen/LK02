/*******************************************************************
*file name:    my_timer.h
*project:      s2x
*Description:  dynamic timer
*Platform: 	   stm32
*firmware:     v1.0
*Author:       cwd
*data:		   2015.12.26
*note:         null
*******************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_


//-----------------------------------------------------------------------------
#define MAX_TIMER_NUM  8   //最多16个
#define NEW_TIMER

//-----------------------------------------------------------------------------
typedef s16 rt_tick_t;      /* Type for tick count */

typedef void (*TimerFuncPtr)(void);

typedef struct
{
    TimerFuncPtr timeout_func;  /* timeout function */
    rt_tick_t    timeout_tick;  /* timeout tick */
}rt_timer_t;

//-----------------------------------------------------------------------------
#define SoftTimerInit() do{}while(0)
#define TimerRestart    TimerStart

rt_tick_t timer_set(s16 interval);
bool timer_expired(rt_tick_t t);

int TimerStart(TimerFuncPtr FuncPtr,int ms);
int TimerStop(TimerFuncPtr FuncPtr);

void SoftTimerHandler(void);

typedef struct OutputTimeStr_s
{
  unsigned short OutputTimeCnt;//输出计数
  unsigned short SuposOutputHzCnt;//期望输出频率对应的设置值
}OutputTimeStr_t;


extern OutputTimeStr_t OutputTimeStr;

void TimerBoard_Init( void );

#endif

