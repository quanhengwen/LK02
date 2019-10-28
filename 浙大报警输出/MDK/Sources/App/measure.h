//-----------------------------------------------------------------------------
// sys_init.h
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

#ifndef _MEASURE_H__
#define _MEASURE_H__

//--------------------------------------------------------------------------
// 1m(米) = 10dm(公分) = 100cm(厘米) = 1000mm(毫米)
//#define   C_VELOCITY           299792458 // velocity of light (m/s)
//#define   C_VELOCITY          299792.458 // velocity of light (m/ms)
//#define   C_VELOCITY          299.792458 // velocity of light (m/us)
//#define   C_VELOCITY         0.299792458 // velocity of light (m/ns)
#define C_VELOCITY            29.9792458 // velocity of light (cm/ns)
#define AGC_MIN     160 //0.16V -10DB
#define AGC_MAX     720//0.720V 20DB

#define APD_HI      380// //350 // 149V  MAX=500 176V
#define APD_MD      260 //200//96V
#define APD_LO      140 //47v //120// 50V

//#define  LK02_OLD//老版本使用该激光功率
#ifdef  LK02_OLD
  #define LD_HI      1400
  #define LD_LO      1500
#else
  #define LD_HI      1230//1100 //124V //1000 //148V //1230//100V
  #define LD_MD      1330//78V
  #define LD_LO      1450//68V
#endif

#define HIGH                     2
#define MDLL                     1
#define LOW                      0
//--------------------------------------------------------------------------
void gp22_init(void);
void gp22_init_2(void);
void tlc5618_init(void);
u16 tlc5618_execute(u16 code_a,u16 code_b);
//AGC增益调节函数
u16 tlc5618_AGC_ADJ(int value);
//LD高压调节函数
u16 tlc5618_LDV_ADJ(int value);
u16 set_LD_HV(u16 LDv);
u16 set_AGC_Gn(u16 AGCg);
u32 CalcDistance(u32 val);
void dly100ns(u32 ns);
void delay1us(u32 us);

int trigger_pulse(u32 *pDist);
u8 Slect_Gain(u8 lev);
void APDLD_GAIN_ADJ(void);
#endif

