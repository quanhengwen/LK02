//-----------------------------------------------------------------------------
// my_io_defs.h
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

#ifndef _MY_IO_DEFS_H_
#define _MY_IO_DEFS_H_

#include "stm32_io_action.h"

/*
*********************************************************************************************************
*      IO Initialization

* GPIOX_PP, GPIOX_AF_PP     --> Push-pull, AF, Multiplexed output
* GPIOX_OD, GPIOX_AF_OD     --> Open drain
* GPIOX_IPU, GPIOX_IPD      --> input up, input down
* GPIOX_IFLOAT, GPIOX_AIN   --> input float, Analog input
*********************************************************************************************************
*/
//----------------------GPIOA--------------------------------------------
#define GPIOA_PP   		(GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_15)  
#define GPIOA_IPU       (GPIO_Pin_12)
#define GPIOA_AIN       (GPIO_Pin_0|GPIO_Pin_1)

//----------------------GPIOB--------------------------------------------
#define GPIOB_PP		(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12)                       
//#define GPIOB_OD		(GPIO_Pin_8)

//----------------------GPIOC--------------------------------------------
#define GPIOC_PP	    (GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
//#define GPIOC_PP	    (GPIO_Pin_14)
//#define GPIOC_PP	    (GPIO_Pin_15)
//----------------------GPIOD--------------------------------------------
#define GPIOD_PP	    (GPIO_Pin_0|GPIO_Pin_1)
/*
***************************************************************************
* IO define
***************************************************************************
*/
//-POWER-----------------------------------------------------------

//-LCD-------------------------------------------------------------

//-KEY-------------------------------------------------------------

//-IIC-------------------------------------------------------------

#define	RS485_CTRL_Recieve		SetPortB8Low//DE为低时，接收
#define	RS485_CTRL_DRIVER		SetPortB8High//DE为高时，发送

//#define IIC_SET_SCL_HIGH          SetPortB8High
//#define IIC_SET_SCL_LOW           SetPortB8Low
#define IIC_SET_SDA_HIGH          SetPortB9High
#define IIC_SET_SDA_LOW           SetPortB9Low
#define IIC_CHK_SDA               CheckPortB9

//-TLC5618----------------------------------------------------------
#define TLC5618_SPI_CS_DISABLE    SetPortB12High
#define TLC5618_SPI_CS_ENABLE     SetPortB12Low

//-GP22-------------------------------------------------------------
#define GP22_SPI_CS_DISABLE       SetPortA4High
#define GP22_SPI_CS_ENABLE        SetPortA4Low
#define GP22_START_ENABLE         SetPortB5High
#define GP22_START_DISABLE        SetPortB5Low
#define GP22_STOP1_ENABLE         SetPortB4High
#define GP22_STOP1_DISABLE        SetPortB4Low
#define GP22_RSTN_ENABLE          SetPortC13Low
#define GP22_RSTN_DISABLE         SetPortC13High
#define GP22_CHK_INTN             CheckPortA12

//------------------------------------------------------------------
#define AGC_CTRL_HIGH             SetPortB11High
#define AGC_CTRL_LOW              SetPortB11Low

#define TX_PULSE_HIGH             SetPortB0High
#define TX_PULSE_LOW              SetPortB0Low

//-TSTx-------------------------------------------------------------
#define T10_HIGH                  SetPortA2High
#define T10_LOW                   SetPortA2Low
#define T10_Reserve               SetPortA2Reserve

#define T13_HIGH                  SetPortA15High
#define T13_LOW                   SetPortA15Low
#define T13_Reserve               SetPortA15Reserve

#define T16_HIGH                  SetPortB3High
#define T16_LOW                   SetPortB3Low
#define T16_Reserve               SetPortB3Reserve

#define	CTL_LD635_H				  SetPortB10High
#define	CTL_LD635_L				  SetPortB10Low

#endif

