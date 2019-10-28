/*******************************************************************
*file name:     meas_current.c
*project:        s5
*Description:  flash read write
*Platform: 	 stm32f10x
*firmware:      v1.0
*Author:         cwd
*data:		  2013.1.25
*note:            null
*******************************************************************/
#ifndef _MEAS_CURRENT_H_
#define _MEAS_CURRENT_H_
#include "global.h"

//=====================================================================================
bool ExDAC_Init(void);
void ExDAC_WriteDat(u16 dat);
//void ExDAC_AddDemarOutput(u16 dat);
//=====================================================================================
#endif



