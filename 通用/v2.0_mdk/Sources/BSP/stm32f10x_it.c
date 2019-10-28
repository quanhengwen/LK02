/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  __vector_table
          DCD     sfe(CSTACK)
          DCD     Reset_Handler             ; Reset Handler
          DCD     NMI_Handler               ; NMI Handler
          DCD     HardFault_Handler         ; Hard Fault Handler
          DCD     MemManage_Handler         ; MPU Fault Handler
          DCD     BusFault_Handler          ; Bus Fault Handler
          DCD     UsageFault_Handler        ; Usage Fault Handler
          DCD     0                         ; Reserved
          DCD     0                         ; Reserved
          DCD     0                         ; Reserved
          DCD     0                         ; Reserved
          DCD     SVC_Handler               ; SVCall Handler
          DCD     DebugMon_Handler          ; Debug Monitor Handler
          DCD     0                         ; Reserved
          DCD     PendSV_Handler            ; PendSV Handler
          DCD     SysTick_Handler           ; SysTick Handler
  
           ; External Interrupts
          DCD     WWDG_IRQHandler           ; Window Watchdog
          DCD     PVD_IRQHandler            ; PVD through EXTI Line detect
          DCD     TAMPER_IRQHandler         ; Tamper
          DCD     RTC_IRQHandler            ; RTC
          DCD     FLASH_IRQHandler          ; Flash
          DCD     RCC_IRQHandler            ; RCC
          DCD     EXTI0_IRQHandler          ; EXTI Line 0
          DCD     EXTI1_IRQHandler          ; EXTI Line 1
          DCD     EXTI2_IRQHandler          ; EXTI Line 2
          DCD     EXTI3_IRQHandler          ; EXTI Line 3
          DCD     EXTI4_IRQHandler          ; EXTI Line 4
          DCD     DMA1_Channel1_IRQHandler  ; DMA1 Channel 1
          DCD     DMA1_Channel2_IRQHandler  ; DMA1 Channel 2
          DCD     DMA1_Channel3_IRQHandler  ; DMA1 Channel 3
          DCD     DMA1_Channel4_IRQHandler  ; DMA1 Channel 4
          DCD     DMA1_Channel5_IRQHandler  ; DMA1 Channel 5
          DCD     DMA1_Channel6_IRQHandler  ; DMA1 Channel 6
          DCD     DMA1_Channel7_IRQHandler  ; DMA1 Channel 7
          DCD     ADC1_2_IRQHandler         ; ADC1 & ADC2
          DCD     USB_HP_CAN1_TX_IRQHandler  ; USB High Priority or CAN1 TX
          DCD     USB_LP_CAN1_RX0_IRQHandler ; USB Low  Priority or CAN1 RX0
          DCD     CAN1_RX1_IRQHandler       ; CAN1 RX1
          DCD     CAN1_SCE_IRQHandler       ; CAN1 SCE
          DCD     EXTI9_5_IRQHandler        ; EXTI Line 9..5
          DCD     TIM1_BRK_IRQHandler       ; TIM1 Break
          DCD     TIM1_UP_IRQHandler        ; TIM1 Update
          DCD     TIM1_TRG_COM_IRQHandler   ; TIM1 Trigger and Commutation
          DCD     TIM1_CC_IRQHandler        ; TIM1 Capture Compare
          DCD     TIM2_IRQHandler           ; TIM2
          DCD     TIM3_IRQHandler           ; TIM3
          DCD     TIM4_IRQHandler           ; TIM4
          DCD     I2C1_EV_IRQHandler        ; I2C1 Event
          DCD     I2C1_ER_IRQHandler        ; I2C1 Error
          DCD     I2C2_EV_IRQHandler        ; I2C2 Event
          DCD     I2C2_ER_IRQHandler        ; I2C2 Error
          DCD     SPI1_IRQHandler           ; SPI1
          DCD     SPI2_IRQHandler           ; SPI2
          DCD     USART1_IRQHandler         ; USART1
          DCD     USART2_IRQHandler         ; USART2
          DCD     USART3_IRQHandler         ; USART3
          DCD     EXTI15_10_IRQHandler      ; EXTI Line 15..10
          DCD     RTCAlarm_IRQHandler       ; RTC Alarm through EXTI Line
          DCD     USBWakeUp_IRQHandler      ; USB Wakeup from suspend
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "global.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern volatile rt_tick_t rt_tick;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    rt_tick++;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

#ifdef STM32F10X_LD_VL
void TIM1_UP_TIM16_IRQHandler(void)
#else
void TIM1_UP_IRQHandler(void)       //TIM1 Update
#endif
{
#ifdef ENABLE_UART_PROTOCOL 
    UART_TimeOutIRQ(); //modbus超时
#endif
}

void USART1_IRQHandler(void)
{
#ifdef ENABLE_UART_PROTOCOL
    //if((USART1->CR1&USART_FLAG_RXNE)&&(USART1->SR&USART_FLAG_RXNE))//接收中断?
    if(USART1->SR&USART_FLAG_RXNE)//接收中断?
    {
        //USART1->SR &= ~USART_FLAG_RXNE;
        UART_RxIRQ(); //读接收到的数据,同时清除中断标记
    }
#endif
}
 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
