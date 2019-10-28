/****************************************************************************
* 文件名：bsp_init.c
* 功能：  板级初始化:外设初始化等
*         
*  
* 作者： 红双喜 QQ89362582
* 日期： 2014/2/27
****************************************************************************/
#include "global.h"


char TxBuf[64]="";//"high-speed pulse sensor.\n";

/*
*********************************************************************************************************
*                                             BSP_Clock_Init()
* Description : Initialize the system clock
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : BSP_Init().
* Note(s)     : none.
*********************************************************************************************************
*/
static void  BSP_Clock_Init (void)
{
    RCC_DeInit();
     
#ifdef INTERNAL_RC
    RCC_HSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);         //等待晶振稳定
#else
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_WaitForHSEStartUp() != SUCCESS);  //等待晶振稳定
#endif
    
    RCC_HCLKConfig(RCC_SYSCLK_DIV);  //设置AHB时钟(CLK)(这时设置为=系统时钟)
    RCC_PCLK2Config(RCC_PCLK2_DIV);   //设置高速APB2时钟(IO 和tim1,8~17,ADC)
    RCC_PCLK1Config(RCC_PCLK1_DIV);   //设置低速APB1时钟(tim2~7,I2C,SPI,UART,USB),当APB1≠Div1时TMI2~8 2倍频18MHZ
    RCC_ADCCLKConfig(ADC_CLOCK);      //设置ADC时钟(HCLK/4)=9MHz
    
    FLASH_SetLatency(FLASH_SPEED);//设置FLASH存储器延时时钟周期数
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//预取指缓存使能
    FLASH_UserOptionByteConfig(OB_IWDG_HW, OB_STOP_RST, OB_STDBY_NoRST); //cwd2013.5.11
     
    RCC_PLLConfig(PLL_SOURCE, PLL_MUL);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); 
     
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);
}

/*
*********************************************************************************************************
*                                             BSP_IO_Init()
* Description : Initialize the system IO
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : BSP_Init().
* Note(s)     : none.
*********************************************************************************************************
*/
static void BSP_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO), ENABLE);  //GPIOA,B,C,D,AFIO 时钟允许
    
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);    //关闭JTAG打开SWD
    
    GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);   //不使用外部晶振时候重映射成IO口
     
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//-----------------推挽输出--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //输出推挽
    
#ifdef GPIOA_PP
    GPIO_InitStructure.GPIO_Pin = GPIOA_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

#ifdef GPIOB_PP
    GPIO_InitStructure.GPIO_Pin = GPIOB_PP;     //输出推挽
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif

#ifdef GPIOC_PP
    GPIO_InitStructure.GPIO_Pin = GPIOC_PP;     //输出推挽
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_PP
    GPIO_InitStructure.GPIO_Pin = GPIOD_PP;     //输出推挽
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
    
//-----------------复用推挽输出--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

#ifdef GPIOA_AF_PP
    GPIO_InitStructure.GPIO_Pin = GPIOA_AF_PP;      //复用输出推挽
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_AF_PP
    GPIO_InitStructure.GPIO_Pin = GPIOB_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_AF_PP
    GPIO_InitStructure.GPIO_Pin = GPIOC_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_AF_PP
    GPIO_InitStructure.GPIO_Pin = GPIOD_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
    
//-----------------开漏输出--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;        //输出开漏

#ifdef GPIOA_OD     //目前没有 GPIOA_OD
    GPIO_InitStructure.GPIO_Pin = GPIOA_OD;     //输出开漏
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_OD
    GPIO_InitStructure.GPIO_Pin = GPIOB_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_OD
    GPIO_InitStructure.GPIO_Pin = GPIOC_OD;     //输出开漏
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_OD
    GPIO_InitStructure.GPIO_Pin = GPIOD_OD;     //输出开漏
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif

//-----------------复用开漏输出--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //复用输出开漏

#ifdef GPIOA_AF_OD
    GPIO_InitStructure.GPIO_Pin = GPIOA_AF_OD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_AF_OD
    GPIO_InitStructure.GPIO_Pin = GPIOB_AF_OD;      //复用输出开漏
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_AF_OD
    GPIO_InitStructure.GPIO_Pin = GPIOC_AF_OD;      //复用输出开漏
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_AF_OD
    GPIO_InitStructure.GPIO_Pin = GPIOD_AF_OD;      //复用输出开漏
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif

//-----------------悬空输入--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //输入浮空

#ifdef GPIOA_IFLOAT
    GPIO_InitStructure.GPIO_Pin = GPIOA_IFLOAT;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_IFLOAT
    GPIO_InitStructure.GPIO_Pin = GPIOB_IFLOAT; //输入浮空
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_IFLOAT
    GPIO_InitStructure.GPIO_Pin = GPIOC_IFLOAT; //输入浮空
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_IFLOAT
    GPIO_InitStructure.GPIO_Pin = GPIOD_IFLOAT; //输入浮空
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif

//-----------------下拉输入--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   //输入带下拉

#ifdef GPIOA_IPD
    GPIO_InitStructure.GPIO_Pin = GPIOA_IPD;            //开机按键
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_IPD
    GPIO_InitStructure.GPIO_Pin = GPIOB_IPD;            //输入带下拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_IPD
    GPIO_InitStructure.GPIO_Pin = GPIOC_IPD;            //输入带下拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_IPD
    GPIO_InitStructure.GPIO_Pin = GPIOD_IPD;            //输入带下拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif

//-----------------上拉输入--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //输入带上拉

#ifdef GPIOA_IPU
    GPIO_InitStructure.GPIO_Pin = GPIOA_IPU;        //输入带上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_IPU
    GPIO_InitStructure.GPIO_Pin = GPIOB_IPU;        //输入带上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_IPU
    GPIO_InitStructure.GPIO_Pin = GPIOC_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);          //PortC只能作为输入,输出时只能同时1个脚
#endif
#ifdef GPIOD_IPU
    GPIO_InitStructure.GPIO_Pin = GPIOD_IPU;        //输入带上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif

//-----------------模拟输入--------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;       //模拟输入

#ifdef GPIOA_AIN
    GPIO_InitStructure.GPIO_Pin = GPIOA_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#ifdef GPIOB_AIN
    GPIO_InitStructure.GPIO_Pin = GPIOB_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef GPIOC_AIN
    GPIO_InitStructure.GPIO_Pin = GPIOC_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef GPIOD_AIN
    GPIO_InitStructure.GPIO_Pin = GPIOD_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif

}
 
 /*
 *******************************************************************************
 * Function Name  : PUTCHAR_PROTOTYPE
 * Description    : Retargets the C library printf function to the USART.
 * Input          : None
 * Output         : None
 * Return         : None
 * note:
 LSI = 40K = 40000
 Reload Value = 250ms/IWDG counter clock period                          
                                = 0.25s / (LsiFreq/Prescaler)                         
 *******************************************************************************
 */
#ifdef ENABLE_WATCH_DOG
 
#define WDG_TIMEOUT         1000000 //1000000us
#define LSI_PERIOD          25      //一个周期25us
#define WDG_RELOAD_VALUE    (u32)(WDG_TIMEOUT/(LSI_PERIOD*256))
 
static void BSP_WatchDog_Init(void)
{
    IWDG->KR = 0X5555;//IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);使能对IWDG->PR和IWDG->RLR的写                                                
    IWDG->PR = IWDG_Prescaler_256; //IWDG_SetPrescaler(IWDG_Prescaler_256);设置分频系数   
    IWDG->RLR = WDG_RELOAD_VALUE; //IWDG_SetReload(0xfff);从加载寄存器 IWDG->RLR  
    IWDG->KR = 0XAAAA;//IWDG_ReloadCounter();  //喂狗          
    IWDG->KR = 0XCCCC;//IWDG_Enable();  使能看门狗 
}
void FreeWatchDog(void)
{
    IWDG->KR = 0XAAAA;//IWDG_ReloadCounter();  //喂狗          
}
#endif
 
/*
*******************************************************************************
* Function Name  : PUTCHAR_PROTOTYPE
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************
*/
#if defined(CWD_DEBUG) || defined(ENABLE_UART_PROTOCOL) || defined(ENABLE_BLE)

#define REMAP_USART1

static void BSP_USART_IO(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
#ifdef REMAP_USART1
    #define UART_TX_PIN  GPIO_Pin_6
    #define UART_RX_PIN  GPIO_Pin_7
    #define UART_GPIO    GPIOB
#else
    #define UART_TX_PIN  GPIO_Pin_9
    #define UART_RX_PIN  GPIO_Pin_10
    #define UART_GPIO    GPIOA
#endif
    
  #ifdef REMAP_USART1
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);     //usart1 重映射到
  #endif
  
    //USART1 Rx (PB7) as input floating
    GPIO_InitStructure.GPIO_Pin = UART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//注意：Rx为浮空;
    GPIO_Init(UART_GPIO, &GPIO_InitStructure);

    //USART1 Tx (PB6) pin as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = UART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void BSP_UartDMA_Config(uint32_t TxBuffer)
{
    DMA_InitTypeDef DMA_InitStructure;

    #define USART1_DR_BASE 0x40013804

    /* USARTy TX DMA1 Channel (triggered by USARTy Tx event) Config */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;
    DMA_InitStructure.DMA_MemoryBaseAddr = TxBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize =25; //25;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    
    /* Enable USARTy DMA Rx and TX request */
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
   
    /* Enable USARTy TX DMA1 Channel */
    DMA_Cmd(DMA1_Channel4, ENABLE);

    /* Enable USARTz RX DMA1 Channel */
    USART_Cmd(USART1, ENABLE);
}

void BSP_USART_Config(unsigned long baud_rate)
{
    USART_InitTypeDef USART_InitStructure;

    /* enable clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* reset */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);    //时钟复位
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);   //停止时钟复位

    BSP_USART_IO();
    
    //以下是uart设置
    USART_InitStructure.USART_BaudRate =baud_rate; //baud_rate;//115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);
    
#if defined(ENABLE_UART_PROTOCOL) || defined(ENABLE_BLE)
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_ClearFlag(USART1, (USART_FLAG_TXE | USART_FLAG_TC | USART_FLAG_RXNE));
    NVIC_ClearPendingIRQ(USART1_IRQn);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //抢占优先级5,数字越小,优先级越高
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//允许接收中断
    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);//允许发送中断
#endif
    
    USART_Cmd(USART1, ENABLE);
    BSP_UartDMA_Config((uint32_t)TxBuf);
}
#endif


/*
*******************************************************************************
* Function Name  : PUTCHAR_PROTOTYPE
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************
*/
void put_char(char ch)
{
    USART1->DR = ch;
    while(!(USART1->SR & USART_FLAG_TC));
    USART_ClearFlag(USART1,USART_FLAG_TC);
}

int get_char(char *pch)
{
    int timeout = 2000*(CLOCK_PLL/1000000)/6; // 6 Instruction cycle, 2000us timeout
   
    while(!(USART1->SR & USART_FLAG_RXNE))
    {
        if(timeout--==0)
            return 0;
    }
    *pch = USART1->DR;
    
    return 1;
}

void put_string(char *pch, int len)//采用DMA标志查询的办法实现
{
    char *pbuf = TxBuf;
    int size = len;
    unsigned char ch = *pch;
    //GPIO_SetBits(GPIOB,GPIO_Pin_8);
    while(size){
      
      while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
      USART1->DR = (u8) ch;  
      
      pch++;
      ch = *pch;
      size--;
    } //GPIO_ResetBits(GPIOB,GPIO_Pin_8);
    return ;
    
//RS485_CTRL_DRIVER();//开始发送
    //RS485_CTRL_Recieve();//开始接收
    while(len)
    {
        len--;
        *pbuf++ = *pch++;
    }
    //while(!(DMA1->ISR & DMA1_FLAG_TC4));
    //while(!(USART1->SR & USART_FLAG_TC));   
    DMA_ClearFlag(DMA1_FLAG_TC4);
    USART_ClearFlag(USART1,USART_FLAG_TC);
    
    DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);//close DMA
    DMA1_Channel4->CNDTR = size;//保存DMA数据传送量
    DMA1_Channel4->CCR |= DMA_CCR1_EN;  //open DMA,开始数据传输

   
    RS485_CTRL_DRIVER();//开始发送
    while(!(DMA1->ISR & DMA1_FLAG_TC4));
    while(!(USART1->SR & USART_FLAG_TC));//等待发送完成
	RS485_CTRL_Recieve();
/**/
    
}

/*
*********************************************************************************************************
*                                             BSP_NVIC_PriorityGroup()
* Description : Initialize the board's time
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : BSP_Init().
* Note(s)     : modbus Timeout 5ms
*********************************************************************************************************
*/
static void BSP_NVIC_PriorityGroup(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);     //选择使用优先级分组第3组
}

/*
*********************************************************************************************************
*                                             BSP_TIM14_Init()
* Description : Initialize the board's time
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : BSP_Init().
* Note(s)     : modbus Timeout 5ms
*********************************************************************************************************
*/
static void BSP_TIM1_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

  #ifdef STM32F10X_LD_VL
    #define TIM1_UP_IRQN    TIM1_UP_TIM16_IRQn
  #else
    #define TIM1_UP_IRQN    TIM1_UP_IRQn
  #endif
    
    /* TIM1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);   // reset
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
    
    /* Enable the TIM1 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
        
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 59; //5000us = 5ms
    TIM_TimeBaseStructure.TIM_Prescaler = 63; //36M/1200 = 10KHZ //100us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* TIM clear flag */
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    
    /* TIM IT enable */
    //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    /* TIM enable counter */
    //TIM_Cmd(TIM1, ENABLE);
}

/*
*********************************************************************************************************
*                                               BSP_ADC_Init()
* Description : Initialize the board's ADC
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : BSP_Init().
* Note(s)     : ADC
*********************************************************************************************************
*/
static void BSP_ADC_Init(void)
{
    //ADC配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);  //Enable ADC1 reset state 
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE); //Release ADC1 from reset state 

    /* calibration after power on only one times */
    ADC_Cmd(ADC1, ENABLE);        //启动校准前， ADC 必须处于关电状态 (ADON=’0’) 超过至少两个 ADC 时钟周期。
    ADC_ResetCalibration(ADC1);      //复位ADC1 校准
    while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位完成
    ADC_StartCalibration(ADC1);            //开始ADC1 校准转换
    while(ADC_GetCalibrationStatus(ADC1));     //等待转换完成
    
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
}

/*
*********************************************************************************************************
*                                               BSP_DMA_Init()
* Description : Initialize the board's DMA
* Argument(s) : none.
* Return(s)   : none.
* Caller(s)   : BSP_Init().
* Note(s)     : DMA
*********************************************************************************************************
*/
static void BSP_DMA_Init(void)
{
    //NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //DMA 时钟允许
  #if 0
    DMA_ClearFlag(DMA1_IT_GL4);
    NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);   
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;      //更新事件  DMA1_Channel1_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    //(0~16) 抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //允许中断
    NVIC_Init(&NVIC_InitStructure);   //写入设置
  #endif
}

/** bsp_spi1_init()
  * @brief  SPI1初始化
  * @param  无
  * @retval 无
  */
void BSP_SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    
    /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/

    /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Confugure MISO pin as Input Floating  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    /* SPI1 configuration ------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;//SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);
    
    /* Enable SPI1 CRC calculation */
    //SPI_CalculateCRC(SPI1, ENABLE);

    /* Enable SPI1 */
    SPI_Cmd(SPI1, ENABLE);
}

/** bsp_spi2_init()
  * @brief  SPI2初始化
  * @param  无
  * @retval 无
  */
void BSP_SPI2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    
    /* Configure SPI2 pins: SCK, MISO and MOSI ---------------------------------*/

    /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Confugure MISO pin as Input Floating  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    /* SPI2 configuration ------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;//SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    /* Enable SPI2 CRC calculation */
    //SPI_CalculateCRC(SPI1, ENABLE);
    /* Enable SPI2 */

	//SPI_SSOutputCmd(SPI2, ENABLE);
	//SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);
	
    SPI_Cmd(SPI2, ENABLE);
}

void SysTickStart(void)
{
  SysTick_Config(CLOCK_PLL / (1000/SYS_TICK_MS));
}
void SysTickStop(void)
{
  SysTick->VAL=0; 
  SysTick->CTRL=0;
}

/** bsp_systemInit()
  * @brief  系统初始化
  * @param  无
  * @retval 无
  */
void System_Init(void)
{
    BSP_Clock_Init();	        //时钟初始化
    BSP_IO_Init();              //IO口配置
    BSP_NVIC_PriorityGroup();   //中断优先级分组 
    BSP_TIM1_Init();
    BSP_ADC_Init();
    BSP_DMA_Init();
    BSP_SPI1_Init();            //SPI1初始化
    BSP_SPI2_Init();            //SPI2初始化
    PwmCongfig();               //PWM
    /* Setup SysTick Timer for 1 msec interrupts  */
    SysTickStop();//SysTick_Config(CLOCK_PLL / (1000/SYS_TICK_MS));//SysTick->VAL=0; SysTick->CTRL=0;//close

  #ifdef ENABLE_WATCH_DOG
    BSP_WatchDog_Init();        //内部WatchDog初始化
  #endif

  #if defined(CWD_DEBUG) || defined(ENABLE_UART_PROTOCOL) || defined(ENABLE_BLE)
    BSP_USART_Config(115200);//921600
    //BSP_UartDMA_Config((uint32_t)TxBuf);
  #endif
}

/** SystemInit()
  * @brief  启动文件调用,所以要声明
  * @param  无
  * @retval 无
  */
void SystemInit(void)
{
	;//nothing
} 

/** SystemInit()
  * @brief  PWM启动初始化
  * @param  无
  * @retval 无
  */
void Tim_2_3_Init(void)
{
	;//nothing
} 
 


