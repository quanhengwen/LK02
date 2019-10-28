/****************************************************************************
* 文件名：bsp_init.h
* 功能：  板级初始化:外设初始化等 (头文件)
*         
*  
* 作者： 红双喜 QQ89362582
* 日期： 2014/2/27
****************************************************************************/
#ifndef __BSP_INITIALIZE_H_
#define __BSP_INITIALIZE_H_

//------------------------------------------------------------------------
//选择时钟源 内部RC/外部晶体
//------------------------------------------------------------------------
#ifdef INTERNAL_RC
	#define PLL_SOURCE	RCC_PLLSource_HSI_Div2 // 8/2=4M,内部8M RC时钟
#else
	#define PLL_SOURCE	RCC_PLLSource_HSE_Div1 // 8M,外部8M晶体,一般精确度高
#endif

//------------------------------------------------------------------------
//FLASH存储器延时设置
//------------------------------------------------------------------------
#if (CLOCK_PLL < 24000001)			
	#define FLASH_SPEED	FLASH_Latency_0	       //设置为延时0个时钟周期
#elif (CLOCK_PLL < 48000001)
	#define FLASH_SPEED	FLASH_Latency_1	       //设置为延时1个时钟周期
#else 
	#define FLASH_SPEED	FLASH_Latency_2	       //设置为延时2个时钟周期
#endif

//------------------------------------------------------------------------
//设置 AHB时钟
//------------------------------------------------------------------------
	#define RCC_SYSCLK_DIV	RCC_SYSCLK_Div1 // 设置AHB时钟(CLK)(这时设置为=系统时钟)
	#define SYS_CLOCK		CLOCK_PLL		// 系统主时钟

//------------------------------------------------------------------------
// 1.设置低速APB1时钟(HCLK1),(tim2~7 spi2)
// 2.设置高速APB2时钟(HCLK2)(IO 和tim1,8,ADC,spi1)
//------------------------------------------------------------------------
#if (CLOCK_PLL == 24000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_6	// 24M,8/2*6=24M
	//AHB,APB2,APB1时钟分频配置
	#define RCC_PCLK1_DIV  	RCC_HCLK_Div1   // 24M,设置低速APB1时钟(HCLK1),(tim2~7 spi2)(tim2~7时,当APB1≠Div1时2倍频)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 24M,设置高速APB2时钟(HCLK2)(IO 和tim1,8,ADC,spi1)
	//AHB,APB2,APB1时钟
	#define PCLK1_CLOCK		(CLOCK_PLL)		// 24M,APB1时钟
	#define PCLK2_CLOCK		(CLOCK_PLL)		// 24M,APB2时钟
	//ADC时钟配置 ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div2	// 12M,设置ADC时钟(这时设置为=PCLK2/2)
#endif

#if (CLOCK_PLL == 36000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_9	// 8/2*9=36M
	//APB2,APB1时钟分频配置
	#define RCC_PCLK1_DIV	RCC_HCLK_Div1	// 36M,设置低速APB1时钟(HCLK1),(tim2~7 spi2)(tim2~7时,当APB1≠Div1时2倍频)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 36M,设置高速APB2时钟(HCLK2)(IO 和tim1,8,ADC,spi1)
	//APB2,APB1时钟
	#define PCLK1_CLOCK		(CLOCK_PLL)		// 36M,APB1时钟
	#define PCLK2_CLOCK		(CLOCK_PLL)		// 36M,APB2时钟
	//ADC时钟配置 ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div4	// 9M,设置ADC时钟(这时设置为=PCLK2/4)
#endif

#if (CLOCK_PLL == 48000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_12	// 8/2*12=48M
	//APB2,APB1时钟分频配置
	#define RCC_PCLK1_DIV	RCC_HCLK_Div2	// 24M,设置低速APB1时钟(HCLK1),(tim2~7 spi2)(tim2~7时,当APB1≠Div1时2倍频)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 24M,设置高速APB2时钟(HCLK2)(IO 和tim1,8,ADC,spi1)
	//APB2,APB1时钟
	#define PCLK1_CLOCK		(CLOCK_PLL/2)	// 24M,APB1时钟
	#define PCLK2_CLOCK		(CLOCK_PLL)		// 48M,APB2时钟
	//ADC时钟配置 ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div4	// 12M,设置ADC时钟(这时设置为=PCLK2/4)
#endif

#if (CLOCK_PLL == 64000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_16	// 8/2*16=64M
	//APB2,APB1时钟分频配置
	#define RCC_PCLK1_DIV	RCC_HCLK_Div2	// 64M,设置低速APB1时钟(HCLK1),(tim2~7 spi2)(tim2~7时,当APB1≠Div1时2倍频)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 64M,设置高速APB2时钟(HCLK2)(IO 和tim1,8,ADC,spi1)
	//APB2,APB1时钟
	#define PCLK1_CLOCK		(CLOCK_PLL/2)	// 32M,APB1时钟
	#define PCLK2_CLOCK		(CLOCK_PLL)	    // 64M,APB2时钟
	//ADC时钟配置 ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div6	// 11M,设置ADC时钟(这时设置为=PCLK2/6)
#endif

#if (CLOCK_PLL == 72000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_9	//8*9=72M
	//APB2,APB1时钟分频配置
	#define RCC_PCLK1_DIV	RCC_HCLK_Div2	//36M,设置低速APB1时钟(HCLK1),(tim2~7 spi2)(tim2~7时,当APB1≠Div1时2倍频)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	//72M,设置高速APB2时钟(HCLK2)(IO 和tim1,8,ADC,spi1)
	//APB2,APB1时钟
	#define PCLK1_CLOCK		(CLOCK_PLL/2)	//36M,APB1时钟
	#define PCLK2_CLOCK		(CLOCK_PLL)		//72M,APB2时钟
	//ADC时钟配置 ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div6	//12M,设置ADC时钟(这时设置为=PCLK2/6)
#endif

//------------------------------------------------------------------------
//TIMERS CONFIG
//APB1 ≠Div1时2倍频 ,APB2 ≠Div1时2倍频 
//------------------------------------------------------------------------
#define TIM_1_DIV	  1                            
#define TIM_1_CLOCK	 (PCLK2_CLOCK/(TIM_1_DIV+1))   // 32MHZ

#define TIM_2_DIV	  1                            
#define TIM_2_CLOCK	 (PCLK1_CLOCK*2/(TIM_2_DIV+1)) // 32MHZ

//-----------------------------------------------------------------------------------
//    以下是modbus 超时时钟配置
//-----------------------------------------------------------------------------------
#define MODBUS_TIM         500  // 5000us 定时
#define MODBUS_ONE_COUNT   10   // 100us一个计数
#define MODBUS_FREQ        (1000000/MODBUS_ONE_COUNT) // 1S/100us = 10KHZ

#define MODBUS_TIM_PERIOD       MODBUS_TIM/MODBUS_ONE_COUNT  //记数次数
#define MODBUS_TIM_PRESCALER    (TIM_1_CLOCK/MODBUS_FREQ-1)+ TIM_1_DIV //10KHZ = 100us

//------------------------------------------------------------------------
//接口函数
//------------------------------------------------------------------------
void SystemInit(void);
void System_Init(void);

void SysTickStart(void);
void SysTickStop(void);

void BSP_USART_Config(unsigned long baud_rate);

void put_char(char ch);
void put_string(char *pch, int len);

#ifdef ENABLE_WATCH_DOG
void FreeWatchDog(void);
#else
#define FreeWatchDog()  do{}while(0)
#endif

#endif

