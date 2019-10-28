//-----------------------------------------------------------------------------
// public.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PUBLIC_H
#define __PUBLIC_H

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void delay100ns(void *arg);
void delay100us(void *arg);
void DelayMS(u16 ms);

#endif /* __PUBLIC_H */


