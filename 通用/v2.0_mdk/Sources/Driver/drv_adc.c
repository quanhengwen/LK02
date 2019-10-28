/*******************************************************************
*file name:    drv_adc.c
*project:      s2
*Description:  ADC DMA sample
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2014.6.4
*note:         null
*******************************************************************/
#include "global.h"


#define ADC_BUFFER_MAX  100

u16 AdcData[ADC_BUFFER_MAX];


void SetAdChannel(u32 channel1, u32 channel2, u32 buf_addr, u32 buf_size)
{
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    
    #define ADC_DR_ADDRESS      ((u32)0x4001244C)

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  //ADC1时钟开启
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //DMA1 时钟允许

    /* ADC_DeInit(ADC1); */
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);  //Enable ADC1 reset state 
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE); //Release ADC1 from reset state 

    //--------ADC1 configuration------------------------------------------------------
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC 工作模式 ADC1 ADC2 单独工作
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;//DISABLE;       //多通道扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //是否启用连续转换模式,一次启动,采样N个数据
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //触发方式,软件
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;      //数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 2;     //ADC规则转换通道数量
    ADC_Init(ADC1, &ADC_InitStructure);
    
    //---ADC1 channel select-------------------------------------
    ADC_RegularChannelConfig(ADC1, channel1, 1, ADC_SampleTime_28Cycles5);
    ADC_RegularChannelConfig(ADC1, channel2, 1, ADC_SampleTime_28Cycles5);

    //----DMA channel1 configuration-------------------------------------------------
    DMA_DeInit(DMA1_Channel1);      //复位DMA1_Channel1
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_DR_ADDRESS;  //外围设备基地址
    DMA_InitStructure.DMA_MemoryBaseAddr = buf_addr;            //内存基地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;          //外设是作为数据传输的目的地还是来源
    DMA_InitStructure.DMA_BufferSize = buf_size;        //设置DMA在传输时缓冲区的长度 word
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;    //外围地址是否自动增长
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;     //设置DMA内存递增模式
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     //外围设备寄存器尺寸16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     //内存尺寸16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;     //DMA 循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;     //DMA 通道优先级,最高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        //设置DMA通道的内存到内存传输功能，当然要禁止
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);            //初始化DMA通道1

  #if 0
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC | DMA_IT_HT, ENABLE);       //使能DMA传输完成和传输一半中断
    DMA_ClearITPendingBit (DMA1_IT_GL1 | DMA_IT_HT);
  #endif
  
    DMA_Cmd(DMA1_Channel1, ENABLE); //配置完成后,启动DMA通道

    ADC_DMACmd(ADC1, ENABLE);   //Enable ADC1 DMA

    //----同步并开始转换-------------------------------------
    ADC_Cmd(ADC1, ENABLE);   //Enable ADC1

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //手工启动第一次AD转换
}

// Stop ADC DMA. 
void StopAdcDMA (void)
{
    ADC_Cmd(ADC1, DISABLE);
    DMA_Cmd(DMA1_Channel1, DISABLE);
}

//set ADC channel to signal channel.
void StartAdcSample(void)
{
    SetAdChannel(ADC_Channel_0, ADC_Channel_1, (u32)AdcData, ADC_BUFFER_MAX);
}

/*
描述:   设置AD的通道,5K,Apd,电池,温度,LD1,LD2,并且在后台开始
输入:   对第几个通道采样, 0 / 1
输出:   1mV
*/
u16 GetADCResult(u32 channel)
{
    u32 i,sum = 0,voltage;

    if(channel == ADC_Channel_0)
    {
        for(i=10; i<40; i++)
            sum += AdcData[(i<<1)+1];
    }
    else
    {
        for(i=10; i<40; i++)
            sum += AdcData[(i<<1)];
    }

    //for(i=0;i<ADC_BUFFER_MAX;i++)
    //Printf("vol%d:%dmV\r\n", i,AdcData[i]*3300/4096);

    //Printf("\n\n\n");

    voltage = sum/30;
	//printf("sum_AVG=%dmV\r\n",voltage*3300/4096);	
    
    return (u16)((voltage*3300)>>12);  // *3300/4096 
}


