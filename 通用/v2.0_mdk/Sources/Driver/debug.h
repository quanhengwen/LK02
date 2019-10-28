/*******************************************************************
*file name:     meas_measure.c
*project:        s5
*Description:  i2c read write
*Platform:    MT6250A
*firmware:      v1.0
*Author:         cwd
*data:        2013.1.25
*note:            null
*******************************************************************/
#ifndef _SYS_DEBUG_
#define _SYS_DEBUG_

#ifdef CWD_DEBUG
#define Printf              mPrintf
#else
#define Printf(fmt, ...)    do{}while(0)
#endif


char *printf_dec(char *buf, s32 hex, u32 div);//整数转换成字符串
int mPrintf(const char *fmt, ...);
int sPrintf(char *buf, const char *fmt, ...);

#endif

