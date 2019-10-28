//-----------------------------------------------------------------------------
// stm32fx_io_action.h
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

#ifndef __STM32FX_IO_ACTION_H_
#define __STM32FX_IO_ACTION_H_

#define SetPortA0AsInputAnalog()	{GPIOA->CRL &= CLB0300;}
#define SetPortA0AsInputFloating()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT02;}
#define SetPortA0AsInputPullDown()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT03; GPIOA->BRR = BIT00;}
#define SetPortA0AsInputPullUp()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT03; GPIOA->BSRR = BIT00;}
#define SetPortA0AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortA0AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT03 + BIT01;}
#define SetPortA0AsOutputOpenDrain()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT02 + BIT01;}
#define SetPortA0AsOutputPushPull()	{GPIOA->CRL &= CLB0300; GPIOA->CRL |= BIT01;}
#define SetPortA0High()	{GPIOA->BSRR = BIT00;}
#define SetPortA0Low()	{GPIOA->BRR = BIT00;}
#define SetPortA0Reserve()	{GPIOA->ODR ^= BIT00;}
#define CheckPortA0()	(GPIOA->IDR & BIT00)

#define SetPortA1AsInputAnalog()	{GPIOA->CRL &= CLB0704;}
#define SetPortA1AsInputFloating()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT06;}
#define SetPortA1AsInputPullDown()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT07; GPIOA->BRR = BIT04;}
#define SetPortA1AsInputPullUp()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT07; GPIOA->BSRR = BIT04;}
#define SetPortA1AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortA1AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT07 + BIT05;}
#define SetPortA1AsOutputOpenDrain()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT06 + BIT05;}
#define SetPortA1AsOutputPushPull()	{GPIOA->CRL &= CLB0704; GPIOA->CRL |= BIT05;}
#define SetPortA1High()	{GPIOA->BSRR = BIT01;}
#define SetPortA1Low()	{GPIOA->BRR = BIT01;}
#define SetPortA1Reserve()	{GPIOA->ODR ^= BIT01;}
#define CheckPortA1()	(GPIOA->IDR & BIT01)

#define SetPortA2AsInputAnalog()	{GPIOA->CRL &= CLB1108;}
#define SetPortA2AsInputFloating()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT10;}
#define SetPortA2AsInputPullDown()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT11; GPIOA->BRR = BIT08;}
#define SetPortA2AsInputPullUp()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT11; GPIOA->BSRR = BIT08;}
#define SetPortA2AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortA2AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT11 + BIT09;}
#define SetPortA2AsOutputOpenDrain()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT10 + BIT09;}
#define SetPortA2AsOutputPushPull()	{GPIOA->CRL &= CLB1108; GPIOA->CRL |= BIT09;}
#define SetPortA2High()	{GPIOA->BSRR = BIT02;}
#define SetPortA2Low()	{GPIOA->BRR = BIT02;}
#define SetPortA2Reserve()	{GPIOA->ODR ^= BIT02;}
#define CheckPortA2()	(GPIOA->IDR & BIT02)

#define SetPortA3AsInputAnalog()	{GPIOA->CRL &= CLB1512;}
#define SetPortA3AsInputFloating()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT14;}
#define SetPortA3AsInputPullDown()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT15; GPIOA->BRR = BIT12;}
#define SetPortA3AsInputPullUp()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT15; GPIOA->BSRR = BIT12;}
#define SetPortA3AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortA3AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT15 + BIT13;}
#define SetPortA3AsOutputOpenDrain()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT14 + BIT13;}
#define SetPortA3AsOutputPushPull()	{GPIOA->CRL &= CLB1512; GPIOA->CRL |= BIT13;}
#define SetPortA3High()	{GPIOA->BSRR = BIT03;}
#define SetPortA3Low()	{GPIOA->BRR = BIT03;}
#define SetPortA3Reserve()	{GPIOA->ODR ^= BIT03;}
#define CheckPortA3()	(GPIOA->IDR & BIT03)

#define SetPortA4AsInputAnalog()	{GPIOA->CRL &= CLB1916;}
#define SetPortA4AsInputFloating()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT18;}
#define SetPortA4AsInputPullDown()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT19; GPIOA->BRR = BIT16;}
#define SetPortA4AsInputPullUp()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT19; GPIOA->BSRR = BIT16;}
#define SetPortA4AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortA4AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT19 + BIT17;}
#define SetPortA4AsOutputOpenDrain()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT18 + BIT17;}
#define SetPortA4AsOutputPushPull()	{GPIOA->CRL &= CLB1916; GPIOA->CRL |= BIT17;}
#define SetPortA4High()	{GPIOA->BSRR = BIT04;}
#define SetPortA4Low()	{GPIOA->BRR = BIT04;}
#define SetPortA4Reserve()	{GPIOA->ODR ^= BIT04;}
#define CheckPortA4()	(GPIOA->IDR & BIT04)

#define SetPortA5AsInputAnalog()	{GPIOA->CRL &= CLB2320;}
#define SetPortA5AsInputFloating()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT22;}
#define SetPortA5AsInputPullDown()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT23; GPIOA->BRR = BIT20;}
#define SetPortA5AsInputPullUp()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT23; GPIOA->BSRR = BIT20;}
#define SetPortA5AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortA5AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT23 + BIT21;}
#define SetPortA5AsOutputOpenDrain()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT22 + BIT21;}
#define SetPortA5AsOutputPushPull()	{GPIOA->CRL &= CLB2320; GPIOA->CRL |= BIT21;}
#define SetPortA5High()	{GPIOA->BSRR = BIT05;}
#define SetPortA5Low()	{GPIOA->BRR = BIT05;}
#define SetPortA5Reserve()	{GPIOA->ODR ^= BIT05;}
#define CheckPortA5()	(GPIOA->IDR & BIT05)

#define SetPortA6AsInputAnalog()	{GPIOA->CRL &= CLB2724;}
#define SetPortA6AsInputFloating()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT26;}
#define SetPortA6AsInputPullDown()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT27; GPIOA->BRR = BIT24;}
#define SetPortA6AsInputPullUp()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT27; GPIOA->BSRR = BIT24;}
#define SetPortA6AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortA6AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT27 + BIT25;}
#define SetPortA6AsOutputOpenDrain()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT26 + BIT25;}
#define SetPortA6AsOutputPushPull()	{GPIOA->CRL &= CLB2724; GPIOA->CRL |= BIT25;}
#define SetPortA6High()	{GPIOA->BSRR = BIT06;}
#define SetPortA6Low()	{GPIOA->BRR = BIT06;}
#define SetPortA6Reserve()	{GPIOA->ODR ^= BIT06;}
#define CheckPortA6()	(GPIOA->IDR & BIT06)

#define SetPortA7AsInputAnalog()	{GPIOA->CRL &= CLB3128;}
#define SetPortA7AsInputFloating()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT30;}
#define SetPortA7AsInputPullDown()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT31; GPIOA->BRR = BIT28;}
#define SetPortA7AsInputPullUp()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT31; GPIOA->BSRR = BIT28;}
#define SetPortA7AsOutputAlternateOpenDrain()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortA7AsOutputAlternatePushPull()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT31 + BIT29;}
#define SetPortA7AsOutputOpenDrain()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT30 + BIT29;}
#define SetPortA7AsOutputPushPull()	{GPIOA->CRL &= CLB3128; GPIOA->CRL |= BIT29;}
#define SetPortA7High()	{GPIOA->BSRR = BIT07;}
#define SetPortA7Low()	{GPIOA->BRR = BIT07;}
#define SetPortA7Reserve()	{GPIOA->ODR ^= BIT07;}
#define CheckPortA7()	(GPIOA->IDR & BIT07)

#define SetPortA8AsInputAnalog()	{GPIOA->CRH &= CLB0300;}
#define SetPortA8AsInputFloating()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT02;}
#define SetPortA8AsInputPullDown()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT03; GPIOA->BRR = BIT00;}
#define SetPortA8AsInputPullUp()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT03; GPIOA->BSRR = BIT00;}
#define SetPortA8AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortA8AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT03 + BIT01;}
#define SetPortA8AsOutputOpenDrain()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT02 + BIT01;}
#define SetPortA8AsOutputPushPull()	{GPIOA->CRH &= CLB0300; GPIOA->CRH |= BIT01;}
#define SetPortA8High()	{GPIOA->BSRR = BIT08;}
#define SetPortA8Low()	{GPIOA->BRR = BIT08;}
#define SetPortA8Reserve()	{GPIOA->ODR ^= BIT08;}
#define CheckPortA8()	(GPIOA->IDR & BIT08)

#define SetPortA9AsInputAnalog()	{GPIOA->CRH &= CLB0704;}
#define SetPortA9AsInputFloating()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT06;}
#define SetPortA9AsInputPullDown()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT07; GPIOA->BRR = BIT04;}
#define SetPortA9AsInputPullUp()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT07; GPIOA->BSRR = BIT04;}
#define SetPortA9AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortA9AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT07 + BIT05;}
#define SetPortA9AsOutputOpenDrain()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT06 + BIT05;}
#define SetPortA9AsOutputPushPull()	{GPIOA->CRH &= CLB0704; GPIOA->CRH |= BIT05;}
#define SetPortA9High()	{GPIOA->BSRR = BIT09;}
#define SetPortA9Low()	{GPIOA->BRR = BIT09;}
#define SetPortA9Reserve()	{GPIOA->ODR ^= BIT09;}
#define CheckPortA9()	(GPIOA->IDR & BIT09)

#define SetPortA10AsInputAnalog()	{GPIOA->CRH &= CLB1108;}
#define SetPortA10AsInputFloating()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT10;}
#define SetPortA10AsInputPullDown()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT11; GPIOA->BRR = BIT08;}
#define SetPortA10AsInputPullUp()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT11; GPIOA->BSRR = BIT08;}
#define SetPortA10AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortA10AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT11 + BIT09;}
#define SetPortA10AsOutputOpenDrain()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT10 + BIT09;}
#define SetPortA10AsOutputPushPull()	{GPIOA->CRH &= CLB1108; GPIOA->CRH |= BIT09;}
#define SetPortA10High()	{GPIOA->BSRR = BIT10;}
#define SetPortA10Low()	{GPIOA->BRR = BIT10;}
#define SetPortA10Reserve()	{GPIOA->ODR ^= BIT10;}
#define CheckPortA10()	(GPIOA->IDR & BIT10)

#define SetPortA11AsInputAnalog()	{GPIOA->CRH &= CLB1512;}
#define SetPortA11AsInputFloating()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT14;}
#define SetPortA11AsInputPullDown()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT15; GPIOA->BRR = BIT12;}
#define SetPortA11AsInputPullUp()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT15; GPIOA->BSRR = BIT12;}
#define SetPortA11AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortA11AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT15 + BIT13;}
#define SetPortA11AsOutputOpenDrain()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT14 + BIT13;}
#define SetPortA11AsOutputPushPull()	{GPIOA->CRH &= CLB1512; GPIOA->CRH |= BIT13;}
#define SetPortA11High()	{GPIOA->BSRR = BIT11;}
#define SetPortA11Low()	{GPIOA->BRR = BIT11;}
#define SetPortA11Reserve()	{GPIOA->ODR ^= BIT11;}
#define CheckPortA11()	(GPIOA->IDR & BIT11)

#define SetPortA12AsInputAnalog()	{GPIOA->CRH &= CLB1916;}
#define SetPortA12AsInputFloating()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT18;}
#define SetPortA12AsInputPullDown()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT19; GPIOA->BRR = BIT16;}
#define SetPortA12AsInputPullUp()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT19; GPIOA->BSRR = BIT16;}
#define SetPortA12AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortA12AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT19 + BIT17;}
#define SetPortA12AsOutputOpenDrain()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT18 + BIT17;}
#define SetPortA12AsOutputPushPull()	{GPIOA->CRH &= CLB1916; GPIOA->CRH |= BIT17;}
#define SetPortA12High()	{GPIOA->BSRR = BIT12;}
#define SetPortA12Low()	{GPIOA->BRR = BIT12;}
#define SetPortA12Reserve()	{GPIOA->ODR ^= BIT12;}
#define CheckPortA12()	(GPIOA->IDR & BIT12)

#define SetPortA13AsInputAnalog()	{GPIOA->CRH &= CLB2320;}
#define SetPortA13AsInputFloating()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT22;}
#define SetPortA13AsInputPullDown()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT23; GPIOA->BRR = BIT20;}
#define SetPortA13AsInputPullUp()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT23; GPIOA->BSRR = BIT20;}
#define SetPortA13AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortA13AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT23 + BIT21;}
#define SetPortA13AsOutputOpenDrain()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT22 + BIT21;}
#define SetPortA13AsOutputPushPull()	{GPIOA->CRH &= CLB2320; GPIOA->CRH |= BIT21;}
#define SetPortA13High()	{GPIOA->BSRR = BIT13;}
#define SetPortA13Low()	{GPIOA->BRR = BIT13;}
#define SetPortA13Reserve()	{GPIOA->ODR ^= BIT13;}
#define CheckPortA13()	(GPIOA->IDR & BIT13)

#define SetPortA14AsInputAnalog()	{GPIOA->CRH &= CLB2724;}
#define SetPortA14AsInputFloating()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT26;}
#define SetPortA14AsInputPullDown()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT27; GPIOA->BRR = BIT24;}
#define SetPortA14AsInputPullUp()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT27; GPIOA->BSRR = BIT24;}
#define SetPortA14AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortA14AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT27 + BIT25;}
#define SetPortA14AsOutputOpenDrain()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT26 + BIT25;}
#define SetPortA14AsOutputPushPull()	{GPIOA->CRH &= CLB2724; GPIOA->CRH |= BIT25;}
#define SetPortA14High()	{GPIOA->BSRR = BIT14;}
#define SetPortA14Low()	{GPIOA->BRR = BIT14;}
#define SetPortA14Reserve()	{GPIOA->ODR ^= BIT14;}
#define CheckPortA14()	(GPIOA->IDR & BIT14)

#define SetPortA15AsInputAnalog()	{GPIOA->CRH &= CLB3128;}
#define SetPortA15AsInputFloating()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT30;}
#define SetPortA15AsInputPullDown()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT31; GPIOA->BRR = BIT28;}
#define SetPortA15AsInputPullUp()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT31; GPIOA->BSRR = BIT28;}
#define SetPortA15AsOutputAlternateOpenDrain()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortA15AsOutputAlternatePushPull()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT31 + BIT29;}
#define SetPortA15AsOutputOpenDrain()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT30 + BIT29;}
#define SetPortA15AsOutputPushPull()	{GPIOA->CRH &= CLB3128; GPIOA->CRH |= BIT29;}
#define SetPortA15High()	{GPIOA->BSRR = BIT15;}
#define SetPortA15Low()	{GPIOA->BRR = BIT15;}
#define SetPortA15Reserve()	{GPIOA->ODR ^= BIT15;}
#define CheckPortA15()	(GPIOA->IDR & BIT15)

//只有LQFP48	LQFP64	LQFP100	LQFP144有PortB口,VFQFPN36只有PortB0,1,2,3,4,5,6,7口
#define SetPortB0AsInputAnalog()	{GPIOB->CRL &= CLB0300;}
#define SetPortB0AsInputFloating()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT02;}
#define SetPortB0AsInputPullDown()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT03; GPIOB->BRR = BIT00;}
#define SetPortB0AsInputPullUp()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT03; GPIOB->BSRR = BIT00;}
#define SetPortB0AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortB0AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT03 + BIT01;}
#define SetPortB0AsOutputOpenDrain()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT02 + BIT01;}
#define SetPortB0AsOutputPushPull()	{GPIOB->CRL &= CLB0300; GPIOB->CRL |= BIT01;}
#define SetPortB0High()	{GPIOB->BSRR = BIT00;}
#define SetPortB0Low()	{GPIOB->BRR = BIT00;}
#define SetPortB0Reserve()	{GPIOB->ODR ^= BIT00;}
#define CheckPortB0()	(GPIOB->IDR & BIT00)

#define SetPortB1AsInputAnalog()	{GPIOB->CRL &= CLB0704;}
#define SetPortB1AsInputFloating()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT06;}
#define SetPortB1AsInputPullDown()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT07; GPIOB->BRR = BIT04;}
#define SetPortB1AsInputPullUp()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT07; GPIOB->BSRR = BIT04;}
#define SetPortB1AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortB1AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT07 + BIT05;}
#define SetPortB1AsOutputOpenDrain()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT06 + BIT05;}
#define SetPortB1AsOutputPushPull()	{GPIOB->CRL &= CLB0704; GPIOB->CRL |= BIT05;}
#define SetPortB1High()	{GPIOB->BSRR = BIT01;}
#define SetPortB1Low()	{GPIOB->BRR = BIT01;}
#define SetPortB1Reserve()	{GPIOB->ODR ^= BIT01;}
#define CheckPortB1()	(GPIOB->IDR & BIT01)

#define SetPortB2AsInputAnalog()	{GPIOB->CRL &= CLB1108;}
#define SetPortB2AsInputFloating()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT10;}
#define SetPortB2AsInputPullDown()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT11; GPIOB->BRR = BIT08;}
#define SetPortB2AsInputPullUp()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT11; GPIOB->BSRR = BIT08;}
#define SetPortB2AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortB2AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT11 + BIT09;}
#define SetPortB2AsOutputOpenDrain()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT10 + BIT09;}
#define SetPortB2AsOutputPushPull()	{GPIOB->CRL &= CLB1108; GPIOB->CRL |= BIT09;}
#define SetPortB2High()	{GPIOB->BSRR = BIT02;}
#define SetPortB2Low()	{GPIOB->BRR = BIT02;}
#define SetPortB2Reserve()	{GPIOB->ODR ^= BIT02;}
#define CheckPortB2()	(GPIOB->IDR & BIT02)

#define SetPortB3AsInputAnalog()	{GPIOB->CRL &= CLB1512;}
#define SetPortB3AsInputFloating()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT14;}
#define SetPortB3AsInputPullDown()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT15; GPIOB->BRR = BIT12;}
#define SetPortB3AsInputPullUp()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT15; GPIOB->BSRR = BIT12;}
#define SetPortB3AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortB3AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT15 + BIT13;}
#define SetPortB3AsOutputOpenDrain()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT14 + BIT13;}
#define SetPortB3AsOutputPushPull()	{GPIOB->CRL &= CLB1512; GPIOB->CRL |= BIT13;}
#define SetPortB3High()	{GPIOB->BSRR = BIT03;}
#define SetPortB3Low()	{GPIOB->BRR = BIT03;}
#define SetPortB3Reserve()	{GPIOB->ODR ^= BIT03;}
#define CheckPortB3()	(GPIOB->IDR & BIT03)

#define SetPortB4AsInputAnalog()	{GPIOB->CRL &= CLB1916;}
#define SetPortB4AsInputFloating()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT18;}
#define SetPortB4AsInputPullDown()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT19; GPIOB->BRR = BIT16;}
#define SetPortB4AsInputPullUp()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT19; GPIOB->BSRR = BIT16;}
#define SetPortB4AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortB4AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT19 + BIT17;}
#define SetPortB4AsOutputOpenDrain()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT18 + BIT17;}
#define SetPortB4AsOutputPushPull()	{GPIOB->CRL &= CLB1916; GPIOB->CRL |= BIT17;}
#define SetPortB4High()	{GPIOB->BSRR = BIT04;}
#define SetPortB4Low()	{GPIOB->BRR = BIT04;}
#define SetPortB4Reserve()	{GPIOB->ODR ^= BIT04;}
#define CheckPortB4()	(GPIOB->IDR & BIT04)

#define SetPortB5AsInputAnalog()	{GPIOB->CRL &= CLB2320;}
#define SetPortB5AsInputFloating()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT22;}
#define SetPortB5AsInputPullDown()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT23; GPIOB->BRR = BIT20;}
#define SetPortB5AsInputPullUp()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT23; GPIOB->BSRR = BIT20;}
#define SetPortB5AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortB5AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT23 + BIT21;}
#define SetPortB5AsOutputOpenDrain()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT22 + BIT21;}
#define SetPortB5AsOutputPushPull()	{GPIOB->CRL &= CLB2320; GPIOB->CRL |= BIT21;}
#define SetPortB5High()	{GPIOB->BSRR = BIT05;}
#define SetPortB5Low()	{GPIOB->BRR = BIT05;}
#define SetPortB5Reserve()	{GPIOB->ODR ^= BIT05;}
#define CheckPortB5()	(GPIOB->IDR & BIT05)

#define SetPortB6AsInputAnalog()	{GPIOB->CRL &= CLB2724;}
#define SetPortB6AsInputFloating()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT26;}
#define SetPortB6AsInputPullDown()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT27; GPIOB->BRR = BIT24;}
#define SetPortB6AsInputPullUp()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT27; GPIOB->BSRR = BIT24;}
#define SetPortB6AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortB6AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT27 + BIT25;}
#define SetPortB6AsOutputOpenDrain()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT26 + BIT25;}
#define SetPortB6AsOutputPushPull()	{GPIOB->CRL &= CLB2724; GPIOB->CRL |= BIT25;}
#define SetPortB6High()	{GPIOB->BSRR = BIT06;}
#define SetPortB6Low()	{GPIOB->BRR = BIT06;}
#define SetPortB6Reserve()	{GPIOB->ODR ^= BIT06;}
#define CheckPortB6()	(GPIOB->IDR & BIT06)

#define SetPortB7AsInputAnalog()	{GPIOB->CRL &= CLB3128;}
#define SetPortB7AsInputFloating()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT30;}
#define SetPortB7AsInputPullDown()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT31; GPIOB->BRR = BIT28;}
#define SetPortB7AsInputPullUp()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT31; GPIOB->BSRR = BIT28;}
#define SetPortB7AsOutputAlternateOpenDrain()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortB7AsOutputAlternatePushPull()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT31 + BIT29;}
#define SetPortB7AsOutputOpenDrain()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT30 + BIT29;}
#define SetPortB7AsOutputPushPull()	{GPIOB->CRL &= CLB3128; GPIOB->CRL |= BIT29;}
#define SetPortB7High()	{GPIOB->BSRR = BIT07;}
#define SetPortB7Low()	{GPIOB->BRR = BIT07;}
#define SetPortB7Reserve()	{GPIOB->ODR ^= BIT07;}
#define CheckPortB7()	(GPIOB->IDR & BIT07)

#define SetPortB8AsInputAnalog()	{GPIOB->CRH &= CLB0300;}
#define SetPortB8AsInputFloating()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT02;}
#define SetPortB8AsInputPullDown()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT03; GPIOB->BRR = BIT00;}
#define SetPortB8AsInputPullUp()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT03; GPIOB->BSRR = BIT00;}
#define SetPortB8AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortB8AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT03 + BIT01;}
#define SetPortB8AsOutputOpenDrain()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT02 + BIT01;}
#define SetPortB8AsOutputPushPull()	{GPIOB->CRH &= CLB0300; GPIOB->CRH |= BIT01;}
#define SetPortB8High()	{GPIOB->BSRR = BIT08;}
#define SetPortB8Low()	{GPIOB->BRR = BIT08;}
#define SetPortB8Reserve()	{GPIOB->ODR ^= BIT08;}
#define CheckPortB8()	(GPIOB->IDR & BIT08)

#define SetPortB9AsInputAnalog()	{GPIOB->CRH &= CLB0704;}
#define SetPortB9AsInputFloating()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT06;}
#define SetPortB9AsInputPullDown()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT07; GPIOB->BRR = BIT04;}
#define SetPortB9AsInputPullUp()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT07; GPIOB->BSRR = BIT04;}
#define SetPortB9AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortB9AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT07 + BIT05;}
#define SetPortB9AsOutputOpenDrain()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT06 + BIT05;}
#define SetPortB9AsOutputPushPull()	{GPIOB->CRH &= CLB0704; GPIOB->CRH |= BIT05;}
#define SetPortB9High()	{GPIOB->BSRR = BIT09;}
#define SetPortB9Low()	{GPIOB->BRR = BIT09;}
#define SetPortB9Reserve()	{GPIOB->ODR ^= BIT09;}
#define CheckPortB9()	(GPIOB->IDR & BIT09)

#define SetPortB10AsInputAnalog()	{GPIOB->CRH &= CLB1108;}
#define SetPortB10AsInputFloating()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT10;}
#define SetPortB10AsInputPullDown()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT11; GPIOB->BRR = BIT08;}
#define SetPortB10AsInputPullUp()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT11; GPIOB->BSRR = BIT08;}
#define SetPortB10AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortB10AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT11 + BIT09;}
#define SetPortB10AsOutputOpenDrain()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT10 + BIT09;}
#define SetPortB10AsOutputPushPull()	{GPIOB->CRH &= CLB1108; GPIOB->CRH |= BIT09;}
#define SetPortB10High()	{GPIOB->BSRR = BIT10;}
#define SetPortB10Low()	{GPIOB->BRR = BIT10;}
#define SetPortB10Reserve()	{GPIOB->ODR ^= BIT10;}
#define CheckPortB10()	(GPIOB->IDR & BIT10)

#define SetPortB11AsInputAnalog()	{GPIOB->CRH &= CLB1512;}
#define SetPortB11AsInputFloating()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT14;}
#define SetPortB11AsInputPullDown()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT15; GPIOB->BRR = BIT12;}
#define SetPortB11AsInputPullUp()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT15; GPIOB->BSRR = BIT12;}
#define SetPortB11AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortB11AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT15 + BIT13;}
#define SetPortB11AsOutputOpenDrain()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT14 + BIT13;}
#define SetPortB11AsOutputPushPull()	{GPIOB->CRH &= CLB1512; GPIOB->CRH |= BIT13;}
#define SetPortB11High()	{GPIOB->BSRR = BIT11;}
#define SetPortB11Low()	{GPIOB->BRR = BIT11;}
#define SetPortB11Reserve()	{GPIOB->ODR ^= BIT11;}
#define CheckPortB11()	(GPIOB->IDR & BIT11)

#define SetPortB12AsInputAnalog()	{GPIOB->CRH &= CLB1916;}
#define SetPortB12AsInputFloating()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT18;}
#define SetPortB12AsInputPullDown()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT19; GPIOB->BRR = BIT16;}
#define SetPortB12AsInputPullUp()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT19; GPIOB->BSRR = BIT16;}
#define SetPortB12AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortB12AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT19 + BIT17;}
#define SetPortB12AsOutputOpenDrain()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT18 + BIT17;}
#define SetPortB12AsOutputPushPull()	{GPIOB->CRH &= CLB1916; GPIOB->CRH |= BIT17;}
#define SetPortB12High()	{GPIOB->BSRR = BIT12;}
#define SetPortB12Low()	{GPIOB->BRR = BIT12;}
#define SetPortB12Reserve()	{GPIOB->ODR ^= BIT12;}
#define CheckPortB12()	(GPIOB->IDR & BIT12)

#define SetPortB13AsInputAnalog()	{GPIOB->CRH &= CLB2320;}
#define SetPortB13AsInputFloating()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT22;}
#define SetPortB13AsInputPullDown()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT23; GPIOB->BRR = BIT20;}
#define SetPortB13AsInputPullUp()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT23; GPIOB->BSRR = BIT20;}
#define SetPortB13AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortB13AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT23 + BIT21;}
#define SetPortB13AsOutputOpenDrain()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT22 + BIT21;}
#define SetPortB13AsOutputPushPull()	{GPIOB->CRH &= CLB2320; GPIOB->CRH |= BIT21;}
#define SetPortB13High()	{GPIOB->BSRR = BIT13;}
#define SetPortB13Low()	{GPIOB->BRR = BIT13;}
#define SetPortB13Reserve()	{GPIOB->ODR ^= BIT13;}
#define CheckPortB13()	(GPIOB->IDR & BIT13)

#define SetPortB14AsInputAnalog()	{GPIOB->CRH &= CLB2724;}
#define SetPortB14AsInputFloating()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT26;}
#define SetPortB14AsInputPullDown()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT27; GPIOB->BRR = BIT24;}
#define SetPortB14AsInputPullUp()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT27; GPIOB->BSRR = BIT24;}
#define SetPortB14AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortB14AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT27 + BIT25;}
#define SetPortB14AsOutputOpenDrain()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT26 + BIT25;}
#define SetPortB14AsOutputPushPull()	{GPIOB->CRH &= CLB2724; GPIOB->CRH |= BIT25;}
#define SetPortB14High()	{GPIOB->BSRR = BIT14;}
#define SetPortB14Low()	{GPIOB->BRR = BIT14;}
#define SetPortB14Reserve()	{GPIOB->ODR ^= BIT14;}
#define CheckPortB14()	(GPIOB->IDR & BIT14)

#define SetPortB15AsInputAnalog()	{GPIOB->CRH &= CLB3128;}
#define SetPortB15AsInputFloating()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT30;}
#define SetPortB15AsInputPullDown()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT31; GPIOB->BRR = BIT28;}
#define SetPortB15AsInputPullUp()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT31; GPIOB->BSRR = BIT28;}
#define SetPortB15AsOutputAlternateOpenDrain()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortB15AsOutputAlternatePushPull()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT31 + BIT29;}
#define SetPortB15AsOutputOpenDrain()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT30 + BIT29;}
#define SetPortB15AsOutputPushPull()	{GPIOB->CRH &= CLB3128; GPIOB->CRH |= BIT29;}
#define SetPortB15High()	{GPIOB->BSRR = BIT15;}
#define SetPortB15Low()	{GPIOB->BRR = BIT15;}
#define SetPortB15Reserve()	{GPIOB->ODR ^= BIT15;}
#define CheckPortB15()	(GPIOB->IDR & BIT15)

//只有LQFP64	LQFP100	LQFP144有PortC口,LQFP48只有PortC13,14,15口
#define SetPortC0AsInputAnalog()	{GPIOC->CRL &= CLB0300;}
#define SetPortC0AsInputFloating()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT02;}
#define SetPortC0AsInputPullDown()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT03; GPIOC->BRR = BIT00;}
#define SetPortC0AsInputPullUp()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT03; GPIOC->BSRR = BIT00;}
#define SetPortC0AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortC0AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT03 + BIT01;}
#define SetPortC0AsOutputOpenDrain()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT02 + BIT01;}
#define SetPortC0AsOutputPushPull()	{GPIOC->CRL &= CLB0300; GPIOC->CRL |= BIT01;}
#define SetPortC0High()	{GPIOC->BSRR = BIT00;}
#define SetPortC0Low()	{GPIOC->BRR = BIT00;}
#define SetPortC0Reserve()	{GPIOC->ODR ^= BIT00;}
#define CheckPortC0()	(GPIOC->IDR & BIT00)

#define SetPortC1AsInputAnalog()	{GPIOC->CRL &= CLB0704;}
#define SetPortC1AsInputFloating()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT06;}
#define SetPortC1AsInputPullDown()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT07; GPIOC->BRR = BIT04;}
#define SetPortC1AsInputPullUp()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT07; GPIOC->BSRR = BIT04;}
#define SetPortC1AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortC1AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT07 + BIT05;}
#define SetPortC1AsOutputOpenDrain()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT06 + BIT05;}
#define SetPortC1AsOutputPushPull()	{GPIOC->CRL &= CLB0704; GPIOC->CRL |= BIT05;}
#define SetPortC1High()	{GPIOC->BSRR = BIT01;}
#define SetPortC1Low()	{GPIOC->BRR = BIT01;}
#define SetPortC1Reserve()	{GPIOC->ODR ^= BIT01;}
#define CheckPortC1()	(GPIOC->IDR & BIT01)

#define SetPortC2AsInputAnalog()	{GPIOC->CRL &= CLB1108;}
#define SetPortC2AsInputFloating()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT10;}
#define SetPortC2AsInputPullDown()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT11; GPIOC->BRR = BIT08;}
#define SetPortC2AsInputPullUp()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT11; GPIOC->BSRR = BIT08;}
#define SetPortC2AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortC2AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT11 + BIT09;}
#define SetPortC2AsOutputOpenDrain()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT10 + BIT09;}
#define SetPortC2AsOutputPushPull()	{GPIOC->CRL &= CLB1108; GPIOC->CRL |= BIT09;}
#define SetPortC2High()	{GPIOC->BSRR = BIT02;}
#define SetPortC2Low()	{GPIOC->BRR = BIT02;}
#define SetPortC2Reserve()	{GPIOC->ODR ^= BIT02;}
#define CheckPortC2()	(GPIOC->IDR & BIT02)

#define SetPortC3AsInputAnalog()	{GPIOC->CRL &= CLB1512;}
#define SetPortC3AsInputFloating()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT14;}
#define SetPortC3AsInputPullDown()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT15; GPIOC->BRR = BIT12;}
#define SetPortC3AsInputPullUp()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT15; GPIOC->BSRR = BIT12;}
#define SetPortC3AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortC3AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT15 + BIT13;}
#define SetPortC3AsOutputOpenDrain()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT14 + BIT13;}
#define SetPortC3AsOutputPushPull()	{GPIOC->CRL &= CLB1512; GPIOC->CRL |= BIT13;}
#define SetPortC3High()	{GPIOC->BSRR = BIT03;}
#define SetPortC3Low()	{GPIOC->BRR = BIT03;}
#define SetPortC3Reserve()	{GPIOC->ODR ^= BIT03;}
#define CheckPortC3()	(GPIOC->IDR & BIT03)

#define SetPortC4AsInputAnalog()	{GPIOC->CRL &= CLB1916;}
#define SetPortC4AsInputFloating()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT18;}
#define SetPortC4AsInputPullDown()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT19; GPIOC->BRR = BIT16;}
#define SetPortC4AsInputPullUp()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT19; GPIOC->BSRR = BIT16;}
#define SetPortC4AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortC4AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT19 + BIT17;}
#define SetPortC4AsOutputOpenDrain()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT18 + BIT17;}
#define SetPortC4AsOutputPushPull()	{GPIOC->CRL &= CLB1916; GPIOC->CRL |= BIT17;}
#define SetPortC4High()	{GPIOC->BSRR = BIT04;}
#define SetPortC4Low()	{GPIOC->BRR = BIT04;}
#define SetPortC4Reserve()	{GPIOC->ODR ^= BIT04;}
#define CheckPortC4()	(GPIOC->IDR & BIT04)

#define SetPortC5AsInputAnalog()	{GPIOC->CRL &= CLB2320;}
#define SetPortC5AsInputFloating()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT22;}
#define SetPortC5AsInputPullDown()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT23; GPIOC->BRR = BIT20;}
#define SetPortC5AsInputPullUp()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT23; GPIOC->BSRR = BIT20;}
#define SetPortC5AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortC5AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT23 + BIT21;}
#define SetPortC5AsOutputOpenDrain()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT22 + BIT21;}
#define SetPortC5AsOutputPushPull()	{GPIOC->CRL &= CLB2320; GPIOC->CRL |= BIT21;}
#define SetPortC5High()	{GPIOC->BSRR = BIT05;}
#define SetPortC5Low()	{GPIOC->BRR = BIT05;}
#define SetPortC5Reserve()	{GPIOC->ODR ^= BIT05;}
#define CheckPortC5()	(GPIOC->IDR & BIT05)

#define SetPortC6AsInputAnalog()	{GPIOC->CRL &= CLB2724;}
#define SetPortC6AsInputFloating()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT26;}
#define SetPortC6AsInputPullDown()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT27; GPIOC->BRR = BIT24;}
#define SetPortC6AsInputPullUp()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT27; GPIOC->BSRR = BIT24;}
#define SetPortC6AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortC6AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT27 + BIT25;}
#define SetPortC6AsOutputOpenDrain()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT26 + BIT25;}
#define SetPortC6AsOutputPushPull()	{GPIOC->CRL &= CLB2724; GPIOC->CRL |= BIT25;}
#define SetPortC6High()	{GPIOC->BSRR = BIT06;}
#define SetPortC6Low()	{GPIOC->BRR = BIT06;}
#define SetPortC6Reserve()	{GPIOC->ODR ^= BIT06;}
#define CheckPortC6()	(GPIOC->IDR & BIT06)

#define SetPortC7AsInputAnalog()	{GPIOC->CRL &= CLB3128;}
#define SetPortC7AsInputFloating()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT30;}
#define SetPortC7AsInputPullDown()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT31; GPIOC->BRR = BIT28;}
#define SetPortC7AsInputPullUp()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT31; GPIOC->BSRR = BIT28;}
#define SetPortC7AsOutputAlternateOpenDrain()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortC7AsOutputAlternatePushPull()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT31 + BIT29;}
#define SetPortC7AsOutputOpenDrain()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT30 + BIT29;}
#define SetPortC7AsOutputPushPull()	{GPIOC->CRL &= CLB3128; GPIOC->CRL |= BIT29;}
#define SetPortC7High()	{GPIOC->BSRR = BIT07;}
#define SetPortC7Low()	{GPIOC->BRR = BIT07;}
#define SetPortC7Reserve()	{GPIOC->ODR ^= BIT07;}
#define CheckPortC7()	(GPIOC->IDR & BIT07)

#define SetPortC8AsInputAnalog()	{GPIOC->CRH &= CLB0300;}
#define SetPortC8AsInputFloating()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT02;}
#define SetPortC8AsInputPullDown()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT03; GPIOC->BRR = BIT00;}
#define SetPortC8AsInputPullUp()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT03; GPIOC->BSRR = BIT00;}
#define SetPortC8AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortC8AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT03 + BIT01;}
#define SetPortC8AsOutputOpenDrain()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT02 + BIT01;}
#define SetPortC8AsOutputPushPull()	{GPIOC->CRH &= CLB0300; GPIOC->CRH |= BIT01;}
#define SetPortC8High()	{GPIOC->BSRR = BIT08;}
#define SetPortC8Low()	{GPIOC->BRR = BIT08;}
#define SetPortC8Reserve()	{GPIOC->ODR ^= BIT08;}
#define CheckPortC8()	(GPIOC->IDR & BIT08)

#define SetPortC9AsInputAnalog()	{GPIOC->CRH &= CLB0704;}
#define SetPortC9AsInputFloating()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT06;}
#define SetPortC9AsInputPullDown()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT07; GPIOC->BRR = BIT04;}
#define SetPortC9AsInputPullUp()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT07; GPIOC->BSRR = BIT04;}
#define SetPortC9AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortC9AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT07 + BIT05;}
#define SetPortC9AsOutputOpenDrain()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT06 + BIT05;}
#define SetPortC9AsOutputPushPull()	{GPIOC->CRH &= CLB0704; GPIOC->CRH |= BIT05;}
#define SetPortC9High()	{GPIOC->BSRR = BIT09;}
#define SetPortC9Low()	{GPIOC->BRR = BIT09;}
#define SetPortC9Reserve()	{GPIOC->ODR ^= BIT09;}
#define CheckPortC9()	(GPIOC->IDR & BIT09)

#define SetPortC10AsInputAnalog()	{GPIOC->CRH &= CLB1108;}
#define SetPortC10AsInputFloating()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT10;}
#define SetPortC10AsInputPullDown()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT11; GPIOC->BRR = BIT08;}
#define SetPortC10AsInputPullUp()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT11; GPIOC->BSRR = BIT08;}
#define SetPortC10AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortC10AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT11 + BIT09;}
#define SetPortC10AsOutputOpenDrain()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT10 + BIT09;}
#define SetPortC10AsOutputPushPull()	{GPIOC->CRH &= CLB1108; GPIOC->CRH |= BIT09;}
#define SetPortC10High()	{GPIOC->BSRR = BIT10;}
#define SetPortC10Low()	{GPIOC->BRR = BIT10;}
#define SetPortC10Reserve()	{GPIOC->ODR ^= BIT10;}
#define CheckPortC10()	(GPIOC->IDR & BIT10)

#define SetPortC11AsInputAnalog()	{GPIOC->CRH &= CLB1512;}
#define SetPortC11AsInputFloating()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT14;}
#define SetPortC11AsInputPullDown()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT15; GPIOC->BRR = BIT12;}
#define SetPortC11AsInputPullUp()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT15; GPIOC->BSRR = BIT12;}
#define SetPortC11AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortC11AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT15 + BIT13;}
#define SetPortC11AsOutputOpenDrain()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT14 + BIT13;}
#define SetPortC11AsOutputPushPull()	{GPIOC->CRH &= CLB1512; GPIOC->CRH |= BIT13;}
#define SetPortC11High()	{GPIOC->BSRR = BIT11;}
#define SetPortC11Low()	{GPIOC->BRR = BIT11;}
#define SetPortC11Reserve()	{GPIOC->ODR ^= BIT11;}
#define CheckPortC11()	(GPIOC->IDR & BIT11)

#define SetPortC12AsInputAnalog()	{GPIOC->CRH &= CLB1916;}
#define SetPortC12AsInputFloating()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT18;}
#define SetPortC12AsInputPullDown()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT19; GPIOC->BRR = BIT16;}
#define SetPortC12AsInputPullUp()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT19; GPIOC->BSRR = BIT16;}
#define SetPortC12AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortC12AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT19 + BIT17;}
#define SetPortC12AsOutputOpenDrain()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT18 + BIT17;}
#define SetPortC12AsOutputPushPull()	{GPIOC->CRH &= CLB1916; GPIOC->CRH |= BIT17;}
#define SetPortC12High()	{GPIOC->BSRR = BIT12;}
#define SetPortC12Low()	{GPIOC->BRR = BIT12;}
#define SetPortC12Reserve()	{GPIOC->ODR ^= BIT12;}
#define CheckPortC12()	(GPIOC->IDR & BIT12)

#define SetPortC13AsInputAnalog()	{GPIOC->CRH &= CLB2320;}
#define SetPortC13AsInputFloating()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT22;}
#define SetPortC13AsInputPullDown()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT23; GPIOC->BRR = BIT20;}
#define SetPortC13AsInputPullUp()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT23; GPIOC->BSRR = BIT20;}
#define SetPortC13AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortC13AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT23 + BIT21;}
#define SetPortC13AsOutputOpenDrain()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT22 + BIT21;}
#define SetPortC13AsOutputPushPull()	{GPIOC->CRH &= CLB2320; GPIOC->CRH |= BIT21;}
#define SetPortC13High()	{GPIOC->BSRR = BIT13;}
#define SetPortC13Low()	{GPIOC->BRR = BIT13;}
#define SetPortC13Reserve()	{GPIOC->ODR ^= BIT13;}
#define CheckPortC13()	(GPIOC->IDR & BIT13)

#define SetPortC14AsInputAnalog()	{GPIOC->CRH &= CLB2724;}
#define SetPortC14AsInputFloating()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT26;}
#define SetPortC14AsInputPullDown()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT27; GPIOC->BRR = BIT24;}
#define SetPortC14AsInputPullUp()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT27; GPIOC->BSRR = BIT24;}
#define SetPortC14AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortC14AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT27 + BIT25;}
#define SetPortC14AsOutputOpenDrain()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT26 + BIT25;}
#define SetPortC14AsOutputPushPull()	{GPIOC->CRH &= CLB2724; GPIOC->CRH |= BIT25;}
#define SetPortC14High()	{GPIOC->BSRR = BIT14;}
#define SetPortC14Low()	{GPIOC->BRR = BIT14;}
#define SetPortC14Reserve()	{GPIOC->ODR ^= BIT14;}
#define CheckPortC14()	(GPIOC->IDR & BIT14)

#define SetPortC15AsInputAnalog()	{GPIOC->CRH &= CLB3128;}
#define SetPortC15AsInputFloating()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT30;}
#define SetPortC15AsInputPullDown()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT31; GPIOC->BRR = BIT28;}
#define SetPortC15AsInputPullUp()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT31; GPIOC->BSRR = BIT28;}
#define SetPortC15AsOutputAlternateOpenDrain()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortC15AsOutputAlternatePushPull()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT31 + BIT29;}
#define SetPortC15AsOutputOpenDrain()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT30 + BIT29;}
#define SetPortC15AsOutputPushPull()	{GPIOC->CRH &= CLB3128; GPIOC->CRH |= BIT29;}
#define SetPortC15High()	{GPIOC->BSRR = BIT15;}
#define SetPortC15Low()	{GPIOC->BRR = BIT15;}
#define SetPortC15Reserve()	{GPIOC->ODR ^= BIT15;}
#define CheckPortC15()	(GPIOC->IDR & BIT15)

//只有LQFP100	LQFP144有PortD口,LQFP64只有PortD2口
#define SetPortD0AsInputAnalog()	{GPIOD->CRL &= CLB0300;}
#define SetPortD0AsInputFloating()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT02;}
#define SetPortD0AsInputPullDown()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT03; GPIOD->BRR = BIT00;}
#define SetPortD0AsInputPullUp()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT03; GPIOD->BSRR = BIT00;}
#define SetPortD0AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortD0AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT03 + BIT01;}
#define SetPortD0AsOutputOpenDrain()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT02 + BIT01;}
#define SetPortD0AsOutputPushPull()	{GPIOD->CRL &= CLB0300; GPIOD->CRL |= BIT01;}
#define SetPortD0High()	{GPIOD->BSRR = BIT00;}
#define SetPortD0Low()	{GPIOD->BRR = BIT00;}
#define SetPortD0Reserve()	{GPIOD->ODR ^= BIT00;}
#define CheckPortD0()	(GPIOD->IDR & BIT00)

#define SetPortD1AsInputAnalog()	{GPIOD->CRL &= CLB0704;}
#define SetPortD1AsInputFloating()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT06;}
#define SetPortD1AsInputPullDown()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT07; GPIOD->BRR = BIT04;}
#define SetPortD1AsInputPullUp()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT07; GPIOD->BSRR = BIT04;}
#define SetPortD1AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortD1AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT07 + BIT05;}
#define SetPortD1AsOutputOpenDrain()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT06 + BIT05;}
#define SetPortD1AsOutputPushPull()	{GPIOD->CRL &= CLB0704; GPIOD->CRL |= BIT05;}
#define SetPortD1High()	{GPIOD->BSRR = BIT01;}
#define SetPortD1Low()	{GPIOD->BRR = BIT01;}
#define SetPortD1Reserve()	{GPIOD->ODR ^= BIT01;}
#define CheckPortD1()	(GPIOD->IDR & BIT01)

#define SetPortD2AsInputAnalog()	{GPIOD->CRL &= CLB1108;}
#define SetPortD2AsInputFloating()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT10;}
#define SetPortD2AsInputPullDown()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT11; GPIOD->BRR = BIT08;}
#define SetPortD2AsInputPullUp()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT11; GPIOD->BSRR = BIT08;}
#define SetPortD2AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortD2AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT11 + BIT09;}
#define SetPortD2AsOutputOpenDrain()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT10 + BIT09;}
#define SetPortD2AsOutputPushPull()	{GPIOD->CRL &= CLB1108; GPIOD->CRL |= BIT09;}
#define SetPortD2High()	{GPIOD->BSRR = BIT02;}
#define SetPortD2Low()	{GPIOD->BRR = BIT02;}
#define SetPortD2Reserve()	{GPIOD->ODR ^= BIT02;}
#define CheckPortD2()	(GPIOD->IDR & BIT02)

#define SetPortD3AsInputAnalog()	{GPIOD->CRL &= CLB1512;}
#define SetPortD3AsInputFloating()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT14;}
#define SetPortD3AsInputPullDown()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT15; GPIOD->BRR = BIT12;}
#define SetPortD3AsInputPullUp()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT15; GPIOD->BSRR = BIT12;}
#define SetPortD3AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortD3AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT15 + BIT13;}
#define SetPortD3AsOutputOpenDrain()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT14 + BIT13;}
#define SetPortD3AsOutputPushPull()	{GPIOD->CRL &= CLB1512; GPIOD->CRL |= BIT13;}
#define SetPortD3High()	{GPIOD->BSRR = BIT03;}
#define SetPortD3Low()	{GPIOD->BRR = BIT03;}
#define SetPortD3Reserve()	{GPIOD->ODR ^= BIT03;}
#define CheckPortD3()	(GPIOD->IDR & BIT03)

#define SetPortD4AsInputAnalog()	{GPIOD->CRL &= CLB1916;}
#define SetPortD4AsInputFloating()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT18;}
#define SetPortD4AsInputPullDown()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT19; GPIOD->BRR = BIT16;}
#define SetPortD4AsInputPullUp()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT19; GPIOD->BSRR = BIT16;}
#define SetPortD4AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortD4AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT19 + BIT17;}
#define SetPortD4AsOutputOpenDrain()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT18 + BIT17;}
#define SetPortD4AsOutputPushPull()	{GPIOD->CRL &= CLB1916; GPIOD->CRL |= BIT17;}
#define SetPortD4High()	{GPIOD->BSRR = BIT04;}
#define SetPortD4Low()	{GPIOD->BRR = BIT04;}
#define SetPortD4Reserve()	{GPIOD->ODR ^= BIT04;}
#define CheckPortD4()	(GPIOD->IDR & BIT04)

#define SetPortD5AsInputAnalog()	{GPIOD->CRL &= CLB2320;}
#define SetPortD5AsInputFloating()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT22;}
#define SetPortD5AsInputPullDown()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT23; GPIOD->BRR = BIT20;}
#define SetPortD5AsInputPullUp()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT23; GPIOD->BSRR = BIT20;}
#define SetPortD5AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortD5AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT23 + BIT21;}
#define SetPortD5AsOutputOpenDrain()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT22 + BIT21;}
#define SetPortD5AsOutputPushPull()	{GPIOD->CRL &= CLB2320; GPIOD->CRL |= BIT21;}
#define SetPortD5High()	{GPIOD->BSRR = BIT05;}
#define SetPortD5Low()	{GPIOD->BRR = BIT05;}
#define SetPortD5Reserve()	{GPIOD->ODR ^= BIT05;}
#define CheckPortD5()	(GPIOD->IDR & BIT05)

#define SetPortD6AsInputAnalog()	{GPIOD->CRL &= CLB2724;}
#define SetPortD6AsInputFloating()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT26;}
#define SetPortD6AsInputPullDown()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT27; GPIOD->BRR = BIT24;}
#define SetPortD6AsInputPullUp()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT27; GPIOD->BSRR = BIT24;}
#define SetPortD6AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortD6AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT27 + BIT25;}
#define SetPortD6AsOutputOpenDrain()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT26 + BIT25;}
#define SetPortD6AsOutputPushPull()	{GPIOD->CRL &= CLB2724; GPIOD->CRL |= BIT25;}
#define SetPortD6High()	{GPIOD->BSRR = BIT06;}
#define SetPortD6Low()	{GPIOD->BRR = BIT06;}
#define SetPortD6Reserve()	{GPIOD->ODR ^= BIT06;}
#define CheckPortD6()	(GPIOD->IDR & BIT06)

#define SetPortD7AsInputAnalog()	{GPIOD->CRL &= CLB3128;}
#define SetPortD7AsInputFloating()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT30;}
#define SetPortD7AsInputPullDown()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT31; GPIOD->BRR = BIT28;}
#define SetPortD7AsInputPullUp()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT31; GPIOD->BSRR = BIT28;}
#define SetPortD7AsOutputAlternateOpenDrain()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortD7AsOutputAlternatePushPull()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT31 + BIT29;}
#define SetPortD7AsOutputOpenDrain()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT30 + BIT29;}
#define SetPortD7AsOutputPushPull()	{GPIOD->CRL &= CLB3128; GPIOD->CRL |= BIT29;}
#define SetPortD7High()	{GPIOD->BSRR = BIT07;}
#define SetPortD7Low()	{GPIOD->BRR = BIT07;}
#define SetPortD7Reserve()	{GPIOD->ODR ^= BIT07;}
#define CheckPortD7()	(GPIOD->IDR & BIT07)

#define SetPortD8AsInputAnalog()	{GPIOD->CRH &= CLB0300;}
#define SetPortD8AsInputFloating()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT02;}
#define SetPortD8AsInputPullDown()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT03; GPIOD->BRR = BIT00;}
#define SetPortD8AsInputPullUp()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT03; GPIOD->BSRR = BIT00;}
#define SetPortD8AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortD8AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT03 + BIT01;}
#define SetPortD8AsOutputOpenDrain()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT02 + BIT01;}
#define SetPortD8AsOutputPushPull()	{GPIOD->CRH &= CLB0300; GPIOD->CRH |= BIT01;}
#define SetPortD8High()	{GPIOD->BSRR = BIT08;}
#define SetPortD8Low()	{GPIOD->BRR = BIT08;}
#define SetPortD8Reserve()	{GPIOD->ODR ^= BIT08;}
#define CheckPortD8()	(GPIOD->IDR & BIT08)

#define SetPortD9AsInputAnalog()	{GPIOD->CRH &= CLB0704;}
#define SetPortD9AsInputFloating()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT06;}
#define SetPortD9AsInputPullDown()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT07; GPIOD->BRR = BIT04;}
#define SetPortD9AsInputPullUp()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT07; GPIOD->BSRR = BIT04;}
#define SetPortD9AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortD9AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT07 + BIT05;}
#define SetPortD9AsOutputOpenDrain()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT06 + BIT05;}
#define SetPortD9AsOutputPushPull()	{GPIOD->CRH &= CLB0704; GPIOD->CRH |= BIT05;}
#define SetPortD9High()	{GPIOD->BSRR = BIT09;}
#define SetPortD9Low()	{GPIOD->BRR = BIT09;}
#define SetPortD9Reserve()	{GPIOD->ODR ^= BIT09;}
#define CheckPortD9()	(GPIOD->IDR & BIT09)

#define SetPortD10AsInputAnalog()	{GPIOD->CRH &= CLB1108;}
#define SetPortD10AsInputFloating()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT10;}
#define SetPortD10AsInputPullDown()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT11; GPIOD->BRR = BIT08;}
#define SetPortD10AsInputPullUp()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT11; GPIOD->BSRR = BIT08;}
#define SetPortD10AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortD10AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT11 + BIT09;}
#define SetPortD10AsOutputOpenDrain()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT10 + BIT09;}
#define SetPortD10AsOutputPushPull()	{GPIOD->CRH &= CLB1108; GPIOD->CRH |= BIT09;}
#define SetPortD10High()	{GPIOD->BSRR = BIT10;}
#define SetPortD10Low()	{GPIOD->BRR = BIT10;}
#define SetPortD10Reserve()	{GPIOD->ODR ^= BIT10;}
#define CheckPortD10()	(GPIOD->IDR & BIT10)

#define SetPortD11AsInputAnalog()	{GPIOD->CRH &= CLB1512;}
#define SetPortD11AsInputFloating()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT14;}
#define SetPortD11AsInputPullDown()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT15; GPIOD->BRR = BIT12;}
#define SetPortD11AsInputPullUp()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT15; GPIOD->BSRR = BIT12;}
#define SetPortD11AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortD11AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT15 + BIT13;}
#define SetPortD11AsOutputOpenDrain()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT14 + BIT13;}
#define SetPortD11AsOutputPushPull()	{GPIOD->CRH &= CLB1512; GPIOD->CRH |= BIT13;}
#define SetPortD11High()	{GPIOD->BSRR = BIT11;}
#define SetPortD11Low()	{GPIOD->BRR = BIT11;}
#define SetPortD11Reserve()	{GPIOD->ODR ^= BIT11;}
#define CheckPortD11()	(GPIOD->IDR & BIT11)

#define SetPortD12AsInputAnalog()	{GPIOD->CRH &= CLB1916;}
#define SetPortD12AsInputFloating()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT18;}
#define SetPortD12AsInputPullDown()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT19; GPIOD->BRR = BIT16;}
#define SetPortD12AsInputPullUp()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT19; GPIOD->BSRR = BIT16;}
#define SetPortD12AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortD12AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT19 + BIT17;}
#define SetPortD12AsOutputOpenDrain()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT18 + BIT17;}
#define SetPortD12AsOutputPushPull()	{GPIOD->CRH &= CLB1916; GPIOD->CRH |= BIT17;}
#define SetPortD12High()	{GPIOD->BSRR = BIT12;}
#define SetPortD12Low()	{GPIOD->BRR = BIT12;}
#define SetPortD12Reserve()	{GPIOD->ODR ^= BIT12;}
#define CheckPortD12()	(GPIOD->IDR & BIT12)

#define SetPortD13AsInputAnalog()	{GPIOD->CRH &= CLB2320;}
#define SetPortD13AsInputFloating()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT22;}
#define SetPortD13AsInputPullDown()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT23; GPIOD->BRR = BIT20;}
#define SetPortD13AsInputPullUp()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT23; GPIOD->BSRR = BIT20;}
#define SetPortD13AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortD13AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT23 + BIT21;}
#define SetPortD13AsOutputOpenDrain()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT22 + BIT21;}
#define SetPortD13AsOutputPushPull()	{GPIOD->CRH &= CLB2320; GPIOD->CRH |= BIT21;}
#define SetPortD13High()	{GPIOD->BSRR = BIT13;}
#define SetPortD13Low()	{GPIOD->BRR = BIT13;}
#define SetPortD13Reserve()	{GPIOD->ODR ^= BIT13;}
#define CheckPortD13()	(GPIOD->IDR & BIT13)

#define SetPortD14AsInputAnalog()	{GPIOD->CRH &= CLB2724;}
#define SetPortD14AsInputFloating()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT26;}
#define SetPortD14AsInputPullDown()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT27; GPIOD->BRR = BIT24;}
#define SetPortD14AsInputPullUp()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT27; GPIOD->BSRR = BIT24;}
#define SetPortD14AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortD14AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT27 + BIT25;}
#define SetPortD14AsOutputOpenDrain()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT26 + BIT25;}
#define SetPortD14AsOutputPushPull()	{GPIOD->CRH &= CLB2724; GPIOD->CRH |= BIT25;}
#define SetPortD14High()	{GPIOD->BSRR = BIT14;}
#define SetPortD14Low()	{GPIOD->BRR = BIT14;}
#define SetPortD14Reserve()	{GPIOD->ODR ^= BIT14;}
#define CheckPortD14()	(GPIOD->IDR & BIT14)

#define SetPortD15AsInputAnalog()	{GPIOD->CRH &= CLB3128;}
#define SetPortD15AsInputFloating()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT30;}
#define SetPortD15AsInputPullDown()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT31; GPIOD->BRR = BIT28;}
#define SetPortD15AsInputPullUp()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT31; GPIOD->BSRR = BIT28;}
#define SetPortD15AsOutputAlternateOpenDrain()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortD15AsOutputAlternatePushPull()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT31 + BIT29;}
#define SetPortD15AsOutputOpenDrain()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT30 + BIT29;}
#define SetPortD15AsOutputPushPull()	{GPIOD->CRH &= CLB3128; GPIOD->CRH |= BIT29;}
#define SetPortD15High()	{GPIOD->BSRR = BIT15;}
#define SetPortD15Low()	{GPIOD->BRR = BIT15;}
#define SetPortD15Reserve()	{GPIOD->ODR ^= BIT15;}
#define CheckPortD15()	(GPIOD->IDR & BIT15)

//只有LQFP100	LQFP144有PortE口
#define SetPortE0AsInputAnalog()	{GPIOE->CRL &= CLB0300;}
#define SetPortE0AsInputFloating()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT02;}
#define SetPortE0AsInputPullDown()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT03; GPIOE->BRR = BIT00;}
#define SetPortE0AsInputPullUp()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT03; GPIOE->BSRR = BIT00;}
#define SetPortE0AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortE0AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT03 + BIT01;}
#define SetPortE0AsOutputOpenDrain()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT02 + BIT01;}
#define SetPortE0AsOutputPushPull()	{GPIOE->CRL &= CLB0300; GPIOE->CRL |= BIT01;}
#define SetPortE0High()	{GPIOE->BSRR = BIT00;}
#define SetPortE0Low()	{GPIOE->BRR = BIT00;}
#define SetPortE0Reserve()	{GPIOE->ODR ^= BIT00;}
#define CheckPortE0()	(GPIOE->IDR & BIT00)

#define SetPortE1AsInputAnalog()	{GPIOE->CRL &= CLB0704;}
#define SetPortE1AsInputFloating()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT06;}
#define SetPortE1AsInputPullDown()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT07; GPIOE->BRR = BIT04;}
#define SetPortE1AsInputPullUp()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT07; GPIOE->BSRR = BIT04;}
#define SetPortE1AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortE1AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT07 + BIT05;}
#define SetPortE1AsOutputOpenDrain()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT06 + BIT05;}
#define SetPortE1AsOutputPushPull()	{GPIOE->CRL &= CLB0704; GPIOE->CRL |= BIT05;}
#define SetPortE1High()	{GPIOE->BSRR = BIT01;}
#define SetPortE1Low()	{GPIOE->BRR = BIT01;}
#define SetPortE1Reserve()	{GPIOE->ODR ^= BIT01;}
#define CheckPortE1()	(GPIOE->IDR & BIT01)

#define SetPortE2AsInputAnalog()	{GPIOE->CRL &= CLB1108;}
#define SetPortE2AsInputFloating()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT10;}
#define SetPortE2AsInputPullDown()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT11; GPIOE->BRR = BIT08;}
#define SetPortE2AsInputPullUp()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT11; GPIOE->BSRR = BIT08;}
#define SetPortE2AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortE2AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT11 + BIT09;}
#define SetPortE2AsOutputOpenDrain()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT10 + BIT09;}
#define SetPortE2AsOutputPushPull()	{GPIOE->CRL &= CLB1108; GPIOE->CRL |= BIT09;}
#define SetPortE2High()	{GPIOE->BSRR = BIT02;}
#define SetPortE2Low()	{GPIOE->BRR = BIT02;}
#define SetPortE2Reserve()	{GPIOE->ODR ^= BIT02;}
#define CheckPortE2()	(GPIOE->IDR & BIT02)

#define SetPortE3AsInputAnalog()	{GPIOE->CRL &= CLB1512;}
#define SetPortE3AsInputFloating()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT14;}
#define SetPortE3AsInputPullDown()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT15; GPIOE->BRR = BIT12;}
#define SetPortE3AsInputPullUp()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT15; GPIOE->BSRR = BIT12;}
#define SetPortE3AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortE3AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT15 + BIT13;}
#define SetPortE3AsOutputOpenDrain()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT14 + BIT13;}
#define SetPortE3AsOutputPushPull()	{GPIOE->CRL &= CLB1512; GPIOE->CRL |= BIT13;}
#define SetPortE3High()	{GPIOE->BSRR = BIT03;}
#define SetPortE3Low()	{GPIOE->BRR = BIT03;}
#define SetPortE3Reserve()	{GPIOE->ODR ^= BIT03;}
#define CheckPortE3()	(GPIOE->IDR & BIT03)

#define SetPortE4AsInputAnalog()	{GPIOE->CRL &= CLB1916;}
#define SetPortE4AsInputFloating()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT18;}
#define SetPortE4AsInputPullDown()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT19; GPIOE->BRR = BIT16;}
#define SetPortE4AsInputPullUp()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT19; GPIOE->BSRR = BIT16;}
#define SetPortE4AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortE4AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT19 + BIT17;}
#define SetPortE4AsOutputOpenDrain()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT18 + BIT17;}
#define SetPortE4AsOutputPushPull()	{GPIOE->CRL &= CLB1916; GPIOE->CRL |= BIT17;}
#define SetPortE4High()	{GPIOE->BSRR = BIT04;}
#define SetPortE4Low()	{GPIOE->BRR = BIT04;}
#define SetPortE4Reserve()	{GPIOE->ODR ^= BIT04;}
#define CheckPortE4()	(GPIOE->IDR & BIT04)

#define SetPortE5AsInputAnalog()	{GPIOE->CRL &= CLB2320;}
#define SetPortE5AsInputFloating()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT22;}
#define SetPortE5AsInputPullDown()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT23; GPIOE->BRR = BIT20;}
#define SetPortE5AsInputPullUp()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT23; GPIOE->BSRR = BIT20;}
#define SetPortE5AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortE5AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT23 + BIT21;}
#define SetPortE5AsOutputOpenDrain()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT22 + BIT21;}
#define SetPortE5AsOutputPushPull()	{GPIOE->CRL &= CLB2320; GPIOE->CRL |= BIT21;}
#define SetPortE5High()	{GPIOE->BSRR = BIT05;}
#define SetPortE5Low()	{GPIOE->BRR = BIT05;}
#define SetPortE5Reserve()	{GPIOE->ODR ^= BIT05;}
#define CheckPortE5()	(GPIOE->IDR & BIT05)

#define SetPortE6AsInputAnalog()	{GPIOE->CRL &= CLB2724;}
#define SetPortE6AsInputFloating()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT26;}
#define SetPortE6AsInputPullDown()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT27; GPIOE->BRR = BIT24;}
#define SetPortE6AsInputPullUp()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT27; GPIOE->BSRR = BIT24;}
#define SetPortE6AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortE6AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT27 + BIT25;}
#define SetPortE6AsOutputOpenDrain()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT26 + BIT25;}
#define SetPortE6AsOutputPushPull()	{GPIOE->CRL &= CLB2724; GPIOE->CRL |= BIT25;}
#define SetPortE6High()	{GPIOE->BSRR = BIT06;}
#define SetPortE6Low()	{GPIOE->BRR = BIT06;}
#define SetPortE6Reserve()	{GPIOE->ODR ^= BIT06;}
#define CheckPortE6()	(GPIOE->IDR & BIT06)

#define SetPortE7AsInputAnalog()	{GPIOE->CRL &= CLB3128;}
#define SetPortE7AsInputFloating()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT30;}
#define SetPortE7AsInputPullDown()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT31; GPIOE->BRR = BIT28;}
#define SetPortE7AsInputPullUp()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT31; GPIOE->BSRR = BIT28;}
#define SetPortE7AsOutputAlternateOpenDrain()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortE7AsOutputAlternatePushPull()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT31 + BIT29;}
#define SetPortE7AsOutputOpenDrain()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT30 + BIT29;}
#define SetPortE7AsOutputPushPull()	{GPIOE->CRL &= CLB3128; GPIOE->CRL |= BIT29;}
#define SetPortE7High()	{GPIOE->BSRR = BIT07;}
#define SetPortE7Low()	{GPIOE->BRR = BIT07;}
#define SetPortE7Reserve()	{GPIOE->ODR ^= BIT07;}
#define CheckPortE7()	(GPIOE->IDR & BIT07)

#define SetPortE8AsInputAnalog()	{GPIOE->CRH &= CLB0300;}
#define SetPortE8AsInputFloating()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT02;}
#define SetPortE8AsInputPullDown()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT03; GPIOE->BRR = BIT00;}
#define SetPortE8AsInputPullUp()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT03; GPIOE->BSRR = BIT00;}
#define SetPortE8AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortE8AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT03 + BIT01;}
#define SetPortE8AsOutputOpenDrain()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT02 + BIT01;}
#define SetPortE8AsOutputPushPull()	{GPIOE->CRH &= CLB0300; GPIOE->CRH |= BIT01;}
#define SetPortE8High()	{GPIOE->BSRR = BIT08;}
#define SetPortE8Low()	{GPIOE->BRR = BIT08;}
#define SetPortE8Reserve()	{GPIOE->ODR ^= BIT08;}
#define CheckPortE8()	(GPIOE->IDR & BIT08)

#define SetPortE9AsInputAnalog()	{GPIOE->CRH &= CLB0704;}
#define SetPortE9AsInputFloating()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT06;}
#define SetPortE9AsInputPullDown()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT07; GPIOE->BRR = BIT04;}
#define SetPortE9AsInputPullUp()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT07; GPIOE->BSRR = BIT04;}
#define SetPortE9AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortE9AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT07 + BIT05;}
#define SetPortE9AsOutputOpenDrain()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT06 + BIT05;}
#define SetPortE9AsOutputPushPull()	{GPIOE->CRH &= CLB0704; GPIOE->CRH |= BIT05;}
#define SetPortE9High()	{GPIOE->BSRR = BIT09;}
#define SetPortE9Low()	{GPIOE->BRR = BIT09;}
#define SetPortE9Reserve()	{GPIOE->ODR ^= BIT09;}
#define CheckPortE9()	(GPIOE->IDR & BIT09)

#define SetPortE10AsInputAnalog()	{GPIOE->CRH &= CLB1108;}
#define SetPortE10AsInputFloating()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT10;}
#define SetPortE10AsInputPullDown()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT11; GPIOE->BRR = BIT08;}
#define SetPortE10AsInputPullUp()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT11; GPIOE->BSRR = BIT08;}
#define SetPortE10AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortE10AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT11 + BIT09;}
#define SetPortE10AsOutputOpenDrain()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT10 + BIT09;}
#define SetPortE10AsOutputPushPull()	{GPIOE->CRH &= CLB1108; GPIOE->CRH |= BIT09;}
#define SetPortE10High()	{GPIOE->BSRR = BIT10;}
#define SetPortE10Low()	{GPIOE->BRR = BIT10;}
#define SetPortE10Reserve()	{GPIOE->ODR ^= BIT10;}
#define CheckPortE10()	(GPIOE->IDR & BIT10)

#define SetPortE11AsInputAnalog()	{GPIOE->CRH &= CLB1512;}
#define SetPortE11AsInputFloating()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT14;}
#define SetPortE11AsInputPullDown()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT15; GPIOE->BRR = BIT12;}
#define SetPortE11AsInputPullUp()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT15; GPIOE->BSRR = BIT12;}
#define SetPortE11AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortE11AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT15 + BIT13;}
#define SetPortE11AsOutputOpenDrain()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT14 + BIT13;}
#define SetPortE11AsOutputPushPull()	{GPIOE->CRH &= CLB1512; GPIOE->CRH |= BIT13;}
#define SetPortE11High()	{GPIOE->BSRR = BIT11;}
#define SetPortE11Low()	{GPIOE->BRR = BIT11;}
#define SetPortE11Reserve()	{GPIOE->ODR ^= BIT11;}
#define CheckPortE11()	(GPIOE->IDR & BIT11)

#define SetPortE12AsInputAnalog()	{GPIOE->CRH &= CLB1916;}
#define SetPortE12AsInputFloating()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT18;}
#define SetPortE12AsInputPullDown()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT19; GPIOE->BRR = BIT16;}
#define SetPortE12AsInputPullUp()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT19; GPIOE->BSRR = BIT16;}
#define SetPortE12AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortE12AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT19 + BIT17;}
#define SetPortE12AsOutputOpenDrain()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT18 + BIT17;}
#define SetPortE12AsOutputPushPull()	{GPIOE->CRH &= CLB1916; GPIOE->CRH |= BIT17;}
#define SetPortE12High()	{GPIOE->BSRR = BIT12;}
#define SetPortE12Low()	{GPIOE->BRR = BIT12;}
#define SetPortE12Reserve()	{GPIOE->ODR ^= BIT12;}
#define CheckPortE12()	(GPIOE->IDR & BIT12)

#define SetPortE13AsInputAnalog()	{GPIOE->CRH &= CLB2320;}
#define SetPortE13AsInputFloating()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT22;}
#define SetPortE13AsInputPullDown()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT23; GPIOE->BRR = BIT20;}
#define SetPortE13AsInputPullUp()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT23; GPIOE->BSRR = BIT20;}
#define SetPortE13AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortE13AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT23 + BIT21;}
#define SetPortE13AsOutputOpenDrain()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT22 + BIT21;}
#define SetPortE13AsOutputPushPull()	{GPIOE->CRH &= CLB2320; GPIOE->CRH |= BIT21;}
#define SetPortE13High()	{GPIOE->BSRR = BIT13;}
#define SetPortE13Low()	{GPIOE->BRR = BIT13;}
#define SetPortE13Reserve()	{GPIOE->ODR ^= BIT13;}
#define CheckPortE13()	(GPIOE->IDR & BIT13)

#define SetPortE14AsInputAnalog()	{GPIOE->CRH &= CLB2724;}
#define SetPortE14AsInputFloating()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT26;}
#define SetPortE14AsInputPullDown()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT27; GPIOE->BRR = BIT24;}
#define SetPortE14AsInputPullUp()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT27; GPIOE->BSRR = BIT24;}
#define SetPortE14AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortE14AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT27 + BIT25;}
#define SetPortE14AsOutputOpenDrain()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT26 + BIT25;}
#define SetPortE14AsOutputPushPull()	{GPIOE->CRH &= CLB2724; GPIOE->CRH |= BIT25;}
#define SetPortE14High()	{GPIOE->BSRR = BIT14;}
#define SetPortE14Low()	{GPIOE->BRR = BIT14;}
#define SetPortE14Reserve()	{GPIOE->ODR ^= BIT14;}
#define CheckPortE14()	(GPIOE->IDR & BIT14)

#define SetPortE15AsInputAnalog()	{GPIOE->CRH &= CLB3128;}
#define SetPortE15AsInputFloating()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT30;}
#define SetPortE15AsInputPullDown()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT31; GPIOE->BRR = BIT28;}
#define SetPortE15AsInputPullUp()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT31; GPIOE->BSRR = BIT28;}
#define SetPortE15AsOutputAlternateOpenDrain()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortE15AsOutputAlternatePushPull()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT31 + BIT29;}
#define SetPortE15AsOutputOpenDrain()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT30 + BIT29;}
#define SetPortE15AsOutputPushPull()	{GPIOE->CRH &= CLB3128; GPIOE->CRH |= BIT29;}
#define SetPortE15High()	{GPIOE->BSRR = BIT15;}
#define SetPortE15Low()	{GPIOE->BRR = BIT15;}
#define SetPortE15Reserve()	{GPIOE->ODR ^= BIT15;}
#define CheckPortE15()	(GPIOE->IDR & BIT15)

//只有LQFP144 有PortF,PortG口
#define SetPortF0AsInputAnalog()	{GPIOF->CRL &= CLB0300;}
#define SetPortF0AsInputFloating()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT02;}
#define SetPortF0AsInputPullDown()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT03; GPIOF->BRR = BIT00;}
#define SetPortF0AsInputPullUp()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT03; GPIOF->BSRR = BIT00;}
#define SetPortF0AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortF0AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT03 + BIT01;}
#define SetPortF0AsOutputOpenDrain()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT02 + BIT01;}
#define SetPortF0AsOutputPushPull()	{GPIOF->CRL &= CLB0300; GPIOF->CRL |= BIT01;}
#define SetPortF0High()	{GPIOF->BSRR = BIT00;}
#define SetPortF0Low()	{GPIOF->BRR = BIT00;}
#define SetPortF0Reserve()	{GPIOF->ODR ^= BIT00;}
#define CheckPortF0()	(GPIOF->IDR & BIT00)

#define SetPortF1AsInputAnalog()	{GPIOF->CRL &= CLB0704;}
#define SetPortF1AsInputFloating()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT06;}
#define SetPortF1AsInputPullDown()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT07; GPIOF->BRR = BIT04;}
#define SetPortF1AsInputPullUp()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT07; GPIOF->BSRR = BIT04;}
#define SetPortF1AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortF1AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT07 + BIT05;}
#define SetPortF1AsOutputOpenDrain()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT06 + BIT05;}
#define SetPortF1AsOutputPushPull()	{GPIOF->CRL &= CLB0704; GPIOF->CRL |= BIT05;}
#define SetPortF1High()	{GPIOF->BSRR = BIT01;}
#define SetPortF1Low()	{GPIOF->BRR = BIT01;}
#define SetPortF1Reserve()	{GPIOF->ODR ^= BIT01;}
#define CheckPortF1()	(GPIOF->IDR & BIT01)

#define SetPortF2AsInputAnalog()	{GPIOF->CRL &= CLB1108;}
#define SetPortF2AsInputFloating()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT10;}
#define SetPortF2AsInputPullDown()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT11; GPIOF->BRR = BIT08;}
#define SetPortF2AsInputPullUp()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT11; GPIOF->BSRR = BIT08;}
#define SetPortF2AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortF2AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT11 + BIT09;}
#define SetPortF2AsOutputOpenDrain()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT10 + BIT09;}
#define SetPortF2AsOutputPushPull()	{GPIOF->CRL &= CLB1108; GPIOF->CRL |= BIT09;}
#define SetPortF2High()	{GPIOF->BSRR = BIT02;}
#define SetPortF2Low()	{GPIOF->BRR = BIT02;}
#define SetPortF2Reserve()	{GPIOF->ODR ^= BIT02;}
#define CheckPortF2()	(GPIOF->IDR & BIT02)

#define SetPortF3AsInputAnalog()	{GPIOF->CRL &= CLB1512;}
#define SetPortF3AsInputFloating()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT14;}
#define SetPortF3AsInputPullDown()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT15; GPIOF->BRR = BIT12;}
#define SetPortF3AsInputPullUp()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT15; GPIOF->BSRR = BIT12;}
#define SetPortF3AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortF3AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT15 + BIT13;}
#define SetPortF3AsOutputOpenDrain()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT14 + BIT13;}
#define SetPortF3AsOutputPushPull()	{GPIOF->CRL &= CLB1512; GPIOF->CRL |= BIT13;}
#define SetPortF3High()	{GPIOF->BSRR = BIT03;}
#define SetPortF3Low()	{GPIOF->BRR = BIT03;}
#define SetPortF3Reserve()	{GPIOF->ODR ^= BIT03;}
#define CheckPortF3()	(GPIOF->IDR & BIT03)

#define SetPortF4AsInputAnalog()	{GPIOF->CRL &= CLB1916;}
#define SetPortF4AsInputFloating()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT18;}
#define SetPortF4AsInputPullDown()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT19; GPIOF->BRR = BIT16;}
#define SetPortF4AsInputPullUp()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT19; GPIOF->BSRR = BIT16;}
#define SetPortF4AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortF4AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT19 + BIT17;}
#define SetPortF4AsOutputOpenDrain()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT18 + BIT17;}
#define SetPortF4AsOutputPushPull()	{GPIOF->CRL &= CLB1916; GPIOF->CRL |= BIT17;}
#define SetPortF4High()	{GPIOF->BSRR = BIT04;}
#define SetPortF4Low()	{GPIOF->BRR = BIT04;}
#define SetPortF4Reserve()	{GPIOF->ODR ^= BIT04;}
#define CheckPortF4()	(GPIOF->IDR & BIT04)

#define SetPortF5AsInputAnalog()	{GPIOF->CRL &= CLB2320;}
#define SetPortF5AsInputFloating()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT22;}
#define SetPortF5AsInputPullDown()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT23; GPIOF->BRR = BIT20;}
#define SetPortF5AsInputPullUp()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT23; GPIOF->BSRR = BIT20;}
#define SetPortF5AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortF5AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT23 + BIT21;}
#define SetPortF5AsOutputOpenDrain()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT22 + BIT21;}
#define SetPortF5AsOutputPushPull()	{GPIOF->CRL &= CLB2320; GPIOF->CRL |= BIT21;}
#define SetPortF5High()	{GPIOF->BSRR = BIT05;}
#define SetPortF5Low()	{GPIOF->BRR = BIT05;}
#define SetPortF5Reserve()	{GPIOF->ODR ^= BIT05;}
#define CheckPortF5()	(GPIOF->IDR & BIT05)

#define SetPortF6AsInputAnalog()	{GPIOF->CRL &= CLB2724;}
#define SetPortF6AsInputFloating()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT26;}
#define SetPortF6AsInputPullDown()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT27; GPIOF->BRR = BIT24;}
#define SetPortF6AsInputPullUp()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT27; GPIOF->BSRR = BIT24;}
#define SetPortF6AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortF6AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT27 + BIT25;}
#define SetPortF6AsOutputOpenDrain()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT26 + BIT25;}
#define SetPortF6AsOutputPushPull()	{GPIOF->CRL &= CLB2724; GPIOF->CRL |= BIT25;}
#define SetPortF6High()	{GPIOF->BSRR = BIT06;}
#define SetPortF6Low()	{GPIOF->BRR = BIT06;}
#define SetPortF6Reserve()	{GPIOF->ODR ^= BIT06;}
#define CheckPortF6()	(GPIOF->IDR & BIT06)

#define SetPortF7AsInputAnalog()	{GPIOF->CRL &= CLB3128;}
#define SetPortF7AsInputFloating()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT30;}
#define SetPortF7AsInputPullDown()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT31; GPIOF->BRR = BIT28;}
#define SetPortF7AsInputPullUp()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT31; GPIOF->BSRR = BIT28;}
#define SetPortF7AsOutputAlternateOpenDrain()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortF7AsOutputAlternatePushPull()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT31 + BIT29;}
#define SetPortF7AsOutputOpenDrain()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT30 + BIT29;}
#define SetPortF7AsOutputPushPull()	{GPIOF->CRL &= CLB3128; GPIOF->CRL |= BIT29;}
#define SetPortF7High()	{GPIOF->BSRR = BIT07;}
#define SetPortF7Low()	{GPIOF->BRR = BIT07;}
#define SetPortF7Reserve()	{GPIOF->ODR ^= BIT07;}
#define CheckPortF7()	(GPIOF->IDR & BIT07)

#define SetPortF8AsInputAnalog()	{GPIOF->CRH &= CLB0300;}
#define SetPortF8AsInputFloating()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT02;}
#define SetPortF8AsInputPullDown()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT03; GPIOF->BRR = BIT00;}
#define SetPortF8AsInputPullUp()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT03; GPIOF->BSRR = BIT00;}
#define SetPortF8AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortF8AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT03 + BIT01;}
#define SetPortF8AsOutputOpenDrain()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT02 + BIT01;}
#define SetPortF8AsOutputPushPull()	{GPIOF->CRH &= CLB0300; GPIOF->CRH |= BIT01;}
#define SetPortF8High()	{GPIOF->BSRR = BIT08;}
#define SetPortF8Low()	{GPIOF->BRR = BIT08;}
#define SetPortF8Reserve()	{GPIOF->ODR ^= BIT08;}
#define CheckPortF8()	(GPIOF->IDR & BIT08)

#define SetPortF9AsInputAnalog()	{GPIOF->CRH &= CLB0704;}
#define SetPortF9AsInputFloating()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT06;}
#define SetPortF9AsInputPullDown()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT07; GPIOF->BRR = BIT04;}
#define SetPortF9AsInputPullUp()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT07; GPIOF->BSRR = BIT04;}
#define SetPortF9AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortF9AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT07 + BIT05;}
#define SetPortF9AsOutputOpenDrain()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT06 + BIT05;}
#define SetPortF9AsOutputPushPull()	{GPIOF->CRH &= CLB0704; GPIOF->CRH |= BIT05;}
#define SetPortF9High()	{GPIOF->BSRR = BIT09;}
#define SetPortF9Low()	{GPIOF->BRR = BIT09;}
#define SetPortF9Reserve()	{GPIOF->ODR ^= BIT09;}
#define CheckPortF9()	(GPIOF->IDR & BIT09)

#define SetPortF10AsInputAnalog()	{GPIOF->CRH &= CLB1108;}
#define SetPortF10AsInputFloating()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT10;}
#define SetPortF10AsInputPullDown()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT11; GPIOF->BRR = BIT08;}
#define SetPortF10AsInputPullUp()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT11; GPIOF->BSRR = BIT08;}
#define SetPortF10AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortF10AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT11 + BIT09;}
#define SetPortF10AsOutputOpenDrain()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT10 + BIT09;}
#define SetPortF10AsOutputPushPull()	{GPIOF->CRH &= CLB1108; GPIOF->CRH |= BIT09;}
#define SetPortF10High()	{GPIOF->BSRR = BIT10;}
#define SetPortF10Low()	{GPIOF->BRR = BIT10;}
#define SetPortF10Reserve()	{GPIOF->ODR ^= BIT10;}
#define CheckPortF10()	(GPIOF->IDR & BIT10)

#define SetPortF11AsInputAnalog()	{GPIOF->CRH &= CLB1512;}
#define SetPortF11AsInputFloating()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT14;}
#define SetPortF11AsInputPullDown()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT15; GPIOF->BRR = BIT12;}
#define SetPortF11AsInputPullUp()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT15; GPIOF->BSRR = BIT12;}
#define SetPortF11AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortF11AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT15 + BIT13;}
#define SetPortF11AsOutputOpenDrain()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT14 + BIT13;}
#define SetPortF11AsOutputPushPull()	{GPIOF->CRH &= CLB1512; GPIOF->CRH |= BIT13;}
#define SetPortF11High()	{GPIOF->BSRR = BIT11;}
#define SetPortF11Low()	{GPIOF->BRR = BIT11;}
#define SetPortF11Reserve()	{GPIOF->ODR ^= BIT11;}
#define CheckPortF11()	(GPIOF->IDR & BIT11)

#define SetPortF12AsInputAnalog()	{GPIOF->CRH &= CLB1916;}
#define SetPortF12AsInputFloating()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT18;}
#define SetPortF12AsInputPullDown()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT19; GPIOF->BRR = BIT16;}
#define SetPortF12AsInputPullUp()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT19; GPIOF->BSRR = BIT16;}
#define SetPortF12AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortF12AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT19 + BIT17;}
#define SetPortF12AsOutputOpenDrain()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT18 + BIT17;}
#define SetPortF12AsOutputPushPull()	{GPIOF->CRH &= CLB1916; GPIOF->CRH |= BIT17;}
#define SetPortF12High()	{GPIOF->BSRR = BIT12;}
#define SetPortF12Low()	{GPIOF->BRR = BIT12;}
#define SetPortF12Reserve()	{GPIOF->ODR ^= BIT12;}
#define CheckPortF12()	(GPIOF->IDR & BIT12)

#define SetPortF13AsInputAnalog()	{GPIOF->CRH &= CLB2320;}
#define SetPortF13AsInputFloating()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT22;}
#define SetPortF13AsInputPullDown()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT23; GPIOF->BRR = BIT20;}
#define SetPortF13AsInputPullUp()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT23; GPIOF->BSRR = BIT20;}
#define SetPortF13AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortF13AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT23 + BIT21;}
#define SetPortF13AsOutputOpenDrain()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT22 + BIT21;}
#define SetPortF13AsOutputPushPull()	{GPIOF->CRH &= CLB2320; GPIOF->CRH |= BIT21;}
#define SetPortF13High()	{GPIOF->BSRR = BIT13;}
#define SetPortF13Low()	{GPIOF->BRR = BIT13;}
#define SetPortF13Reserve()	{GPIOF->ODR ^= BIT13;}
#define CheckPortF13()	(GPIOF->IDR & BIT13)

#define SetPortF14AsInputAnalog()	{GPIOF->CRH &= CLB2724;}
#define SetPortF14AsInputFloating()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT26;}
#define SetPortF14AsInputPullDown()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT27; GPIOF->BRR = BIT24;}
#define SetPortF14AsInputPullUp()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT27; GPIOF->BSRR = BIT24;}
#define SetPortF14AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortF14AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT27 + BIT25;}
#define SetPortF14AsOutputOpenDrain()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT26 + BIT25;}
#define SetPortF14AsOutputPushPull()	{GPIOF->CRH &= CLB2724; GPIOF->CRH |= BIT25;}
#define SetPortF14High()	{GPIOF->BSRR = BIT14;}
#define SetPortF14Low()	{GPIOF->BRR = BIT14;}
#define SetPortF14Reserve()	{GPIOF->ODR ^= BIT14;}
#define CheckPortF14()	(GPIOF->IDR & BIT14)

#define SetPortF15AsInputAnalog()	{GPIOF->CRH &= CLB3128;}
#define SetPortF15AsInputFloating()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT30;}
#define SetPortF15AsInputPullDown()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT31; GPIOF->BRR = BIT28;}
#define SetPortF15AsInputPullUp()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT31; GPIOF->BSRR = BIT28;}
#define SetPortF15AsOutputAlternateOpenDrain()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortF15AsOutputAlternatePushPull()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT31 + BIT29;}
#define SetPortF15AsOutputOpenDrain()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT30 + BIT29;}
#define SetPortF15AsOutputPushPull()	{GPIOF->CRH &= CLB3128; GPIOF->CRH |= BIT29;}
#define SetPortF15High()	{GPIOF->BSRR = BIT15;}
#define SetPortF15Low()	{GPIOF->BRR = BIT15;}
#define SetPortF15Reserve()	{GPIOF->ODR ^= BIT15;}
#define CheckPortF15()	(GPIOF->IDR & BIT15)

#define SetPortG0AsInputAnalog()	{GPIOG->CRL &= CLB0300;}
#define SetPortG0AsInputFloating()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT02;}
#define SetPortG0AsInputPullDown()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT03; GPIOG->BRR = BIT00;}
#define SetPortG0AsInputPullUp()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT03; GPIOG->BSRR = BIT00;}
#define SetPortG0AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT03 + BIT02 + BIT01;}
#define SetPortG0AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT03 + BIT01;}
#define SetPortG0AsOutputOpenDrain()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT02 + BIT01;}
#define SetPortG0AsOutputPushPull()	{GPIOG->CRL &= CLB0300; GPIOG->CRL |= BIT01;}
#define SetPortG0High()	{GPIOG->BSRR = BIT00;}
#define SetPortG0Low()	{GPIOG->BRR = BIT00;}
#define SetPortG0Reserve()	{GPIOG->ODR ^= BIT00;}
#define CheckPortG0()	(GPIOG->IDR & BIT00)

#define SetPortG1AsInputAnalog()	{GPIOG->CRL &= CLB0704;}
#define SetPortG1AsInputFloating()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT06;}
#define SetPortG1AsInputPullDown()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT07; GPIOG->BRR = BIT04;}
#define SetPortG1AsInputPullUp()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT07; GPIOG->BSRR = BIT04;}
#define SetPortG1AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT07 + BIT06 + BIT05;}
#define SetPortG1AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT07 + BIT05;}
#define SetPortG1AsOutputOpenDrain()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT06 + BIT05;}
#define SetPortG1AsOutputPushPull()	{GPIOG->CRL &= CLB0704; GPIOG->CRL |= BIT05;}
#define SetPortG1High()	{GPIOG->BSRR = BIT01;}
#define SetPortG1Low()	{GPIOG->BRR = BIT01;}
#define SetPortG1Reserve()	{GPIOG->ODR ^= BIT01;}
#define CheckPortG1()	(GPIOG->IDR & BIT01)

#define SetPortG2AsInputAnalog()	{GPIOG->CRL &= CLB1108;}
#define SetPortG2AsInputFloating()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT10;}
#define SetPortG2AsInputPullDown()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT11; GPIOG->BRR = BIT08;}
#define SetPortG2AsInputPullUp()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT11; GPIOG->BSRR = BIT08;}
#define SetPortG2AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT11 + BIT10 + BIT09;}
#define SetPortG2AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT11 + BIT09;}
#define SetPortG2AsOutputOpenDrain()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT10 + BIT09;}
#define SetPortG2AsOutputPushPull()	{GPIOG->CRL &= CLB1108; GPIOG->CRL |= BIT09;}
#define SetPortG2High()	{GPIOG->BSRR = BIT02;}
#define SetPortG2Low()	{GPIOG->BRR = BIT02;}
#define SetPortG2Reserve()	{GPIOG->ODR ^= BIT02;}
#define CheckPortG2()	(GPIOG->IDR & BIT02)

#define SetPortG3AsInputAnalog()	{GPIOG->CRL &= CLB1512;}
#define SetPortG3AsInputFloating()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT14;}
#define SetPortG3AsInputPullDown()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT15; GPIOG->BRR = BIT12;}
#define SetPortG3AsInputPullUp()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT15; GPIOG->BSRR = BIT12;}
#define SetPortG3AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT15 + BIT14 + BIT13;}
#define SetPortG3AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT15 + BIT13;}
#define SetPortG3AsOutputOpenDrain()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT14 + BIT13;}
#define SetPortG3AsOutputPushPull()	{GPIOG->CRL &= CLB1512; GPIOG->CRL |= BIT13;}
#define SetPortG3High()	{GPIOG->BSRR = BIT03;}
#define SetPortG3Low()	{GPIOG->BRR = BIT03;}
#define SetPortG3Reserve()	{GPIOG->ODR ^= BIT03;}
#define CheckPortG3()	(GPIOG->IDR & BIT03)

#define SetPortG4AsInputAnalog()	{GPIOG->CRL &= CLB1916;}
#define SetPortG4AsInputFloating()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT18;}
#define SetPortG4AsInputPullDown()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT19; GPIOG->BRR = BIT16;}
#define SetPortG4AsInputPullUp()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT19; GPIOG->BSRR = BIT16;}
#define SetPortG4AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT19 + BIT18 + BIT17;}
#define SetPortG4AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT19 + BIT17;}
#define SetPortG4AsOutputOpenDrain()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT18 + BIT17;}
#define SetPortG4AsOutputPushPull()	{GPIOG->CRL &= CLB1916; GPIOG->CRL |= BIT17;}
#define SetPortG4High()	{GPIOG->BSRR = BIT04;}
#define SetPortG4Low()	{GPIOG->BRR = BIT04;}
#define SetPortG4Reserve()	{GPIOG->ODR ^= BIT04;}
#define CheckPortG4()	(GPIOG->IDR & BIT04)

#define SetPortG5AsInputAnalog()	{GPIOG->CRL &= CLB2320;}
#define SetPortG5AsInputFloating()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT22;}
#define SetPortG5AsInputPullDown()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT23; GPIOG->BRR = BIT20;}
#define SetPortG5AsInputPullUp()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT23; GPIOG->BSRR = BIT20;}
#define SetPortG5AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT23 + BIT22 + BIT21;}
#define SetPortG5AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT23 + BIT21;}
#define SetPortG5AsOutputOpenDrain()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT22 + BIT21;}
#define SetPortG5AsOutputPushPull()	{GPIOG->CRL &= CLB2320; GPIOG->CRL |= BIT21;}
#define SetPortG5High()	{GPIOG->BSRR = BIT05;}
#define SetPortG5Low()	{GPIOG->BRR = BIT05;}
#define SetPortG5Reserve()	{GPIOG->ODR ^= BIT05;}
#define CheckPortG5()	(GPIOG->IDR & BIT05)

#define SetPortG6AsInputAnalog()	{GPIOG->CRL &= CLB2724;}
#define SetPortG6AsInputFloating()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT26;}
#define SetPortG6AsInputPullDown()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT27; GPIOG->BRR = BIT24;}
#define SetPortG6AsInputPullUp()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT27; GPIOG->BSRR = BIT24;}
#define SetPortG6AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT27 + BIT26 + BIT25;}
#define SetPortG6AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT27 + BIT25;}
#define SetPortG6AsOutputOpenDrain()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT26 + BIT25;}
#define SetPortG6AsOutputPushPull()	{GPIOG->CRL &= CLB2724; GPIOG->CRL |= BIT25;}
#define SetPortG6High()	{GPIOG->BSRR = BIT06;}
#define SetPortG6Low()	{GPIOG->BRR = BIT06;}
#define SetPortG6Reserve()	{GPIOG->ODR ^= BIT06;}
#define CheckPortG6()	(GPIOG->IDR & BIT06)

#define SetPortG7AsInputAnalog()	{GPIOG->CRL &= CLB3128;}
#define SetPortG7AsInputFloating()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT30;}
#define SetPortG7AsInputPullDown()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT31; GPIOG->BRR = BIT28;}
#define SetPortG7AsInputPullUp()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT31; GPIOG->BSRR = BIT28;}
#define SetPortG7AsOutputAlternateOpenDrain()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT31 + BIT30 + BIT29;}
#define SetPortG7AsOutputAlternatePushPull()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT31 + BIT29;}
#define SetPortG7AsOutputOpenDrain()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT30 + BIT29;}
#define SetPortG7AsOutputPushPull()	{GPIOG->CRL &= CLB3128; GPIOG->CRL |= BIT29;}
#define SetPortG7High()	{GPIOG->BSRR = BIT07;}
#define SetPortG7Low()	{GPIOG->BRR = BIT07;}
#define SetPortG7Reserve()	{GPIOG->ODR ^= BIT07;}
#define CheckPortG7()	(GPIOG->IDR & BIT07)

#define SetPortG8AsInputAnalog()	{GPIOG->CRH &= CLB0300;}
#define SetPortG8AsInputFloating()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT02;}
#define SetPortG8AsInputPullDown()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT03; GPIOG->BRR = BIT00;}
#define SetPortG8AsInputPullUp()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT03; GPIOG->BSRR = BIT00;}
#define SetPortG8AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT03 + BIT02 + BIT01;}
#define SetPortG8AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT03 + BIT01;}
#define SetPortG8AsOutputOpenDrain()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT02 + BIT01;}
#define SetPortG8AsOutputPushPull()	{GPIOG->CRH &= CLB0300; GPIOG->CRH |= BIT01;}
#define SetPortG8High()	{GPIOG->BSRR = BIT08;}
#define SetPortG8Low()	{GPIOG->BRR = BIT08;}
#define SetPortG8Reserve()	{GPIOG->ODR ^= BIT08;}
#define CheckPortG8()	(GPIOG->IDR & BIT08)

#define SetPortG9AsInputAnalog()	{GPIOG->CRH &= CLB0704;}
#define SetPortG9AsInputFloating()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT06;}
#define SetPortG9AsInputPullDown()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT07; GPIOG->BRR = BIT04;}
#define SetPortG9AsInputPullUp()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT07; GPIOG->BSRR = BIT04;}
#define SetPortG9AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT07 + BIT06 + BIT05;}
#define SetPortG9AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT07 + BIT05;}
#define SetPortG9AsOutputOpenDrain()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT06 + BIT05;}
#define SetPortG9AsOutputPushPull()	{GPIOG->CRH &= CLB0704; GPIOG->CRH |= BIT05;}
#define SetPortG9High()	{GPIOG->BSRR = BIT09;}
#define SetPortG9Low()	{GPIOG->BRR = BIT09;}
#define SetPortG9Reserve()	{GPIOG->ODR ^= BIT09;}
#define CheckPortG9()	(GPIOG->IDR & BIT09)

#define SetPortG10AsInputAnalog()	{GPIOG->CRH &= CLB1108;}
#define SetPortG10AsInputFloating()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT10;}
#define SetPortG10AsInputPullDown()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT11; GPIOG->BRR = BIT08;}
#define SetPortG10AsInputPullUp()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT11; GPIOG->BSRR = BIT08;}
#define SetPortG10AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT11 + BIT10 + BIT09;}
#define SetPortG10AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT11 + BIT09;}
#define SetPortG10AsOutputOpenDrain()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT10 + BIT09;}
#define SetPortG10AsOutputPushPull()	{GPIOG->CRH &= CLB1108; GPIOG->CRH |= BIT09;}
#define SetPortG10High()	{GPIOG->BSRR = BIT10;}
#define SetPortG10Low()	{GPIOG->BRR = BIT10;}
#define SetPortG10Reserve()	{GPIOG->ODR ^= BIT10;}
#define CheckPortG10()	(GPIOG->IDR & BIT10)

#define SetPortG11AsInputAnalog()	{GPIOG->CRH &= CLB1512;}
#define SetPortG11AsInputFloating()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT14;}
#define SetPortG11AsInputPullDown()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT15; GPIOG->BRR = BIT12;}
#define SetPortG11AsInputPullUp()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT15; GPIOG->BSRR = BIT12;}
#define SetPortG11AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT15 + BIT14 + BIT13;}
#define SetPortG11AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT15 + BIT13;}
#define SetPortG11AsOutputOpenDrain()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT14 + BIT13;}
#define SetPortG11AsOutputPushPull()	{GPIOG->CRH &= CLB1512; GPIOG->CRH |= BIT13;}
#define SetPortG11High()	{GPIOG->BSRR = BIT11;}
#define SetPortG11Low()	{GPIOG->BRR = BIT11;}
#define SetPortG11Reserve()	{GPIOG->ODR ^= BIT11;}
#define CheckPortG11()	(GPIOG->IDR & BIT11)

#define SetPortG12AsInputAnalog()	{GPIOG->CRH &= CLB1916;}
#define SetPortG12AsInputFloating()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT18;}
#define SetPortG12AsInputPullDown()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT19; GPIOG->BRR = BIT16;}
#define SetPortG12AsInputPullUp()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT19; GPIOG->BSRR = BIT16;}
#define SetPortG12AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT19 + BIT18 + BIT17;}
#define SetPortG12AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT19 + BIT17;}
#define SetPortG12AsOutputOpenDrain()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT18 + BIT17;}
#define SetPortG12AsOutputPushPull()	{GPIOG->CRH &= CLB1916; GPIOG->CRH |= BIT17;}
#define SetPortG12High()	{GPIOG->BSRR = BIT12;}
#define SetPortG12Low()	{GPIOG->BRR = BIT12;}
#define SetPortG12Reserve()	{GPIOG->ODR ^= BIT12;}
#define CheckPortG12()	(GPIOG->IDR & BIT12)

#define SetPortG13AsInputAnalog()	{GPIOG->CRH &= CLB2320;}
#define SetPortG13AsInputFloating()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT22;}
#define SetPortG13AsInputPullDown()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT23; GPIOG->BRR = BIT20;}
#define SetPortG13AsInputPullUp()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT23; GPIOG->BSRR = BIT20;}
#define SetPortG13AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT23 + BIT22 + BIT21;}
#define SetPortG13AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT23 + BIT21;}
#define SetPortG13AsOutputOpenDrain()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT22 + BIT21;}
#define SetPortG13AsOutputPushPull()	{GPIOG->CRH &= CLB2320; GPIOG->CRH |= BIT21;}
#define SetPortG13High()	{GPIOG->BSRR = BIT13;}
#define SetPortG13Low()	{GPIOG->BRR = BIT13;}
#define SetPortG13Reserve()	{GPIOG->ODR ^= BIT13;}
#define CheckPortG13()	(GPIOG->IDR & BIT13)

#define SetPortG14AsInputAnalog()	{GPIOG->CRH &= CLB2724;}
#define SetPortG14AsInputFloating()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT26;}
#define SetPortG14AsInputPullDown()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT27; GPIOG->BRR = BIT24;}
#define SetPortG14AsInputPullUp()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT27; GPIOG->BSRR = BIT24;}
#define SetPortG14AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT27 + BIT26 + BIT25;}
#define SetPortG14AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT27 + BIT25;}
#define SetPortG14AsOutputOpenDrain()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT26 + BIT25;}
#define SetPortG14AsOutputPushPull()	{GPIOG->CRH &= CLB2724; GPIOG->CRH |= BIT25;}
#define SetPortG14High()	{GPIOG->BSRR = BIT14;}
#define SetPortG14Low()	{GPIOG->BRR = BIT14;}
#define SetPortG14Reserve()	{GPIOG->ODR ^= BIT14;}
#define CheckPortG14()	(GPIOG->IDR & BIT14)

#define SetPortG15AsInputAnalog()	{GPIOG->CRH &= CLB3128;}
#define SetPortG15AsInputFloating()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT30;}
#define SetPortG15AsInputPullDown()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT31; GPIOG->BRR = BIT28;}
#define SetPortG15AsInputPullUp()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT31; GPIOG->BSRR = BIT28;}
#define SetPortG15AsOutputAlternateOpenDrain()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT31 + BIT30 + BIT29;}
#define SetPortG15AsOutputAlternatePushPull()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT31 + BIT29;}
#define SetPortG15AsOutputOpenDrain()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT30 + BIT29;}
#define SetPortG15AsOutputPushPull()	{GPIOG->CRH &= CLB3128; GPIOG->CRH |= BIT29;}
#define SetPortG15High()	{GPIOG->BSRR = BIT15;}
#define SetPortG15Low()	{GPIOG->BRR = BIT15;}
#define SetPortG15Reserve()	{GPIOG->ODR ^= BIT15;}
#define CheckPortG15()	(GPIOG->IDR & BIT15)

#endif




