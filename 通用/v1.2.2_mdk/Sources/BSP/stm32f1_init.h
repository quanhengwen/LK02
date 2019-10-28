/****************************************************************************
* �ļ�����bsp_init.h
* ���ܣ�  �弶��ʼ��:�����ʼ���� (ͷ�ļ�)
*         
*  
* ���ߣ� ��˫ϲ QQ89362582
* ���ڣ� 2014/2/27
****************************************************************************/
#ifndef __BSP_INITIALIZE_H_
#define __BSP_INITIALIZE_H_

//------------------------------------------------------------------------
//ѡ��ʱ��Դ �ڲ�RC/�ⲿ����
//------------------------------------------------------------------------
#ifdef INTERNAL_RC
	#define PLL_SOURCE	RCC_PLLSource_HSI_Div2 // 8/2=4M,�ڲ�8M RCʱ��
#else
	#define PLL_SOURCE	RCC_PLLSource_HSE_Div1 // 8M,�ⲿ8M����,һ�㾫ȷ�ȸ�
#endif

//------------------------------------------------------------------------
//FLASH�洢����ʱ����
//------------------------------------------------------------------------
#if (CLOCK_PLL < 24000001)			
	#define FLASH_SPEED	FLASH_Latency_0	       //����Ϊ��ʱ0��ʱ������
#elif (CLOCK_PLL < 48000001)
	#define FLASH_SPEED	FLASH_Latency_1	       //����Ϊ��ʱ1��ʱ������
#else 
	#define FLASH_SPEED	FLASH_Latency_2	       //����Ϊ��ʱ2��ʱ������
#endif

//------------------------------------------------------------------------
//���� AHBʱ��
//------------------------------------------------------------------------
	#define RCC_SYSCLK_DIV	RCC_SYSCLK_Div1 // ����AHBʱ��(CLK)(��ʱ����Ϊ=ϵͳʱ��)
	#define SYS_CLOCK		CLOCK_PLL		// ϵͳ��ʱ��

//------------------------------------------------------------------------
// 1.���õ���APB1ʱ��(HCLK1),(tim2~7 spi2)
// 2.���ø���APB2ʱ��(HCLK2)(IO ��tim1,8,ADC,spi1)
//------------------------------------------------------------------------
#if (CLOCK_PLL == 24000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_6	// 24M,8/2*6=24M
	//AHB,APB2,APB1ʱ�ӷ�Ƶ����
	#define RCC_PCLK1_DIV  	RCC_HCLK_Div1   // 24M,���õ���APB1ʱ��(HCLK1),(tim2~7 spi2)(tim2~7ʱ,��APB1��Div1ʱ2��Ƶ)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 24M,���ø���APB2ʱ��(HCLK2)(IO ��tim1,8,ADC,spi1)
	//AHB,APB2,APB1ʱ��
	#define PCLK1_CLOCK		(CLOCK_PLL)		// 24M,APB1ʱ��
	#define PCLK2_CLOCK		(CLOCK_PLL)		// 24M,APB2ʱ��
	//ADCʱ������ ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div2	// 12M,����ADCʱ��(��ʱ����Ϊ=PCLK2/2)
#endif

#if (CLOCK_PLL == 36000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_9	// 8/2*9=36M
	//APB2,APB1ʱ�ӷ�Ƶ����
	#define RCC_PCLK1_DIV	RCC_HCLK_Div1	// 36M,���õ���APB1ʱ��(HCLK1),(tim2~7 spi2)(tim2~7ʱ,��APB1��Div1ʱ2��Ƶ)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 36M,���ø���APB2ʱ��(HCLK2)(IO ��tim1,8,ADC,spi1)
	//APB2,APB1ʱ��
	#define PCLK1_CLOCK		(CLOCK_PLL)		// 36M,APB1ʱ��
	#define PCLK2_CLOCK		(CLOCK_PLL)		// 36M,APB2ʱ��
	//ADCʱ������ ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div4	// 9M,����ADCʱ��(��ʱ����Ϊ=PCLK2/4)
#endif

#if (CLOCK_PLL == 48000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_12	// 8/2*12=48M
	//APB2,APB1ʱ�ӷ�Ƶ����
	#define RCC_PCLK1_DIV	RCC_HCLK_Div2	// 24M,���õ���APB1ʱ��(HCLK1),(tim2~7 spi2)(tim2~7ʱ,��APB1��Div1ʱ2��Ƶ)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 24M,���ø���APB2ʱ��(HCLK2)(IO ��tim1,8,ADC,spi1)
	//APB2,APB1ʱ��
	#define PCLK1_CLOCK		(CLOCK_PLL/2)	// 24M,APB1ʱ��
	#define PCLK2_CLOCK		(CLOCK_PLL)		// 48M,APB2ʱ��
	//ADCʱ������ ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div4	// 12M,����ADCʱ��(��ʱ����Ϊ=PCLK2/4)
#endif

#if (CLOCK_PLL == 64000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_16	// 8/2*16=64M
	//APB2,APB1ʱ�ӷ�Ƶ����
	#define RCC_PCLK1_DIV	RCC_HCLK_Div2	// 64M,���õ���APB1ʱ��(HCLK1),(tim2~7 spi2)(tim2~7ʱ,��APB1��Div1ʱ2��Ƶ)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	// 64M,���ø���APB2ʱ��(HCLK2)(IO ��tim1,8,ADC,spi1)
	//APB2,APB1ʱ��
	#define PCLK1_CLOCK		(CLOCK_PLL/2)	// 32M,APB1ʱ��
	#define PCLK2_CLOCK		(CLOCK_PLL)	    // 64M,APB2ʱ��
	//ADCʱ������ ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div6	// 11M,����ADCʱ��(��ʱ����Ϊ=PCLK2/6)
#endif

#if (CLOCK_PLL == 72000000)
	//PLL
	#define PLL_MUL			RCC_PLLMul_9	//8*9=72M
	//APB2,APB1ʱ�ӷ�Ƶ����
	#define RCC_PCLK1_DIV	RCC_HCLK_Div2	//36M,���õ���APB1ʱ��(HCLK1),(tim2~7 spi2)(tim2~7ʱ,��APB1��Div1ʱ2��Ƶ)
	#define RCC_PCLK2_DIV	RCC_HCLK_Div1	//72M,���ø���APB2ʱ��(HCLK2)(IO ��tim1,8,ADC,spi1)
	//APB2,APB1ʱ��
	#define PCLK1_CLOCK		(CLOCK_PLL/2)	//36M,APB1ʱ��
	#define PCLK2_CLOCK		(CLOCK_PLL)		//72M,APB2ʱ��
	//ADCʱ������ ADC<=14MHZ
	#define ADC_CLOCK		RCC_PCLK2_Div6	//12M,����ADCʱ��(��ʱ����Ϊ=PCLK2/6)
#endif

//------------------------------------------------------------------------
//TIMERS CONFIG
//APB1 ��Div1ʱ2��Ƶ ,APB2 ��Div1ʱ2��Ƶ 
//------------------------------------------------------------------------
#define TIM_1_DIV	  1                            
#define TIM_1_CLOCK	 (PCLK2_CLOCK/(TIM_1_DIV+1))   // 32MHZ

#define TIM_2_DIV	  1                            
#define TIM_2_CLOCK	 (PCLK1_CLOCK*2/(TIM_2_DIV+1)) // 32MHZ

//-----------------------------------------------------------------------------------
//    ������modbus ��ʱʱ������
//-----------------------------------------------------------------------------------
#define MODBUS_TIM         500  // 5000us ��ʱ
#define MODBUS_ONE_COUNT   10   // 100usһ������
#define MODBUS_FREQ        (1000000/MODBUS_ONE_COUNT) // 1S/100us = 10KHZ

#define MODBUS_TIM_PERIOD       MODBUS_TIM/MODBUS_ONE_COUNT  //��������
#define MODBUS_TIM_PRESCALER    (TIM_1_CLOCK/MODBUS_FREQ-1)+ TIM_1_DIV //10KHZ = 100us

//------------------------------------------------------------------------
//�ӿں���
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

