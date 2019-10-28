/*******************************************************************
*file name:     meas_current.c
*project:        s5
*Description:  demarcate distance
*Platform: 	  MT6250A
*firmware:      v1.0
*Author:         cwd
*data:		  2013.1.25
*note:            null
*******************************************************************/
#include "global.h"

#define ENABLE_OUT_CURRENT

#ifdef ENABLE_OUT_CURRENT

#define SetDacSclLow()      SetPortC15Low() 
#define SetDacSclHigh()     SetPortC15High() 

#define SetDacSdaHigh()     SetPortB9High()
#define SetDacSdaLow()      SetPortB9Low()

#define SetDacCsEnable()    SetPortD1High()
#define SetDacCsDisable()   SetPortD1Low()
//=====================================================================================
//描述:	存储参数
//输入:	地址,数据长度,指针
//输出:	无
//=====================================================================================
void ExDAC_Delay(void)
{
	u8 i=60;
	while(--i);
}

//=====================================================================================
//描述:	ExDAC写入数据
//输入:	16bit数据
//输出:	无
//=====================================================================================
void AD5420_Write(u32 dat)
{
	u8 i = 24;
	SetDacCsEnable();
	do
	{
		SetDacSclLow();
		if(dat&0x800000)
		{
			SetDacSdaHigh();
		}
		else
		{
			SetDacSdaLow();
		}
		ExDAC_Delay();
		SetDacSclHigh();
		dat <<= 1;
		ExDAC_Delay();
	}while(--i);
	SetDacSclLow();
	ExDAC_Delay();
	SetDacCsDisable();
	ExDAC_Delay();
}
//=====================================================================================
void ExDAC_WriteDat(u16 dat)
{
#ifdef ENABLE_OUT_CURRENT
	AD5420_Write(0x010000|(u32)dat);
#endif
}

//=====================================================================================
bool ExDAC_Init(void)
{
#ifdef ENABLE_OUT_CURRENT
	AD5420_Write(0x553007);    //分别写0x55,0x30,0x07
	AD5420_Write(0x020002);    //分别写0x02,0x00,0x02
	ExDAC_WriteDat(0x100);
#endif
	return TRUE;
}

//=====================================================================================
#endif

