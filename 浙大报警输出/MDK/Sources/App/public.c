//-----------------------------------------------------------------------------
// public.c
//-----------------------------------------------------------------------------
// Copyright 2015 MC Ltd, Inc.
// http://www.mc.com
//
// Program Description:
//
// driver definitions for the pluse measuring.
//
// PRJ:            X HIGH SPEED MEASURING
// Target:         STM32F10X
// Tool chain:     IAR
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (CM)
//    -27 Oct 2015
//    -Latest release before new firmware coding standard
//

#include "global.h"

//-----------------------------------------------------------------------------

/**  
  * @brief  delay 1MS. >=5ms
  * @param  None
  * @retval None
  */
void DelayMS(u16 ms)
{
    rt_tick_t cur_tick;
    cur_tick = timer_set((ms+(SYS_TICK_MS-1))/SYS_TICK_MS);
    while(timer_expired(cur_tick)==FALSE)
    {
        FreeWatchDog(); //硬件看门狗清除
    }
}


