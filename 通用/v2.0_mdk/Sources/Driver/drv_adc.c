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

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  //ADC1ʱ�ӿ���
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //DMA1 ʱ������

    /* ADC_DeInit(ADC1); */
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);  //Enable ADC1 reset state 
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE); //Release ADC1 from reset state 

    //--------ADC1 configuration------------------------------------------------------
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC ����ģʽ ADC1 ADC2 ��������
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;//DISABLE;       //��ͨ��ɨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  //�Ƿ���������ת��ģʽ,һ������,����N������
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //������ʽ,���
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;      //�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 2;     //ADC����ת��ͨ������
    ADC_Init(ADC1, &ADC_InitStructure);
    
    //---ADC1 channel select-------------------------------------
    ADC_RegularChannelConfig(ADC1, channel1, 1, ADC_SampleTime_28Cycles5);
    ADC_RegularChannelConfig(ADC1, channel2, 1, ADC_SampleTime_28Cycles5);

    //----DMA channel1 configuration-------------------------------------------------
    DMA_DeInit(DMA1_Channel1);      //��λDMA1_Channel1
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_DR_ADDRESS;  //��Χ�豸����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = buf_addr;            //�ڴ����ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;          //��������Ϊ���ݴ����Ŀ�ĵػ�����Դ
    DMA_InitStructure.DMA_BufferSize = buf_size;        //����DMA�ڴ���ʱ�������ĳ��� word
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;    //��Χ��ַ�Ƿ��Զ�����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;     //����DMA�ڴ����ģʽ
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     //��Χ�豸�Ĵ����ߴ�16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     //�ڴ�ߴ�16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;     //DMA ѭ��ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;     //DMA ͨ�����ȼ�,���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        //����DMAͨ�����ڴ浽�ڴ洫�书�ܣ���ȻҪ��ֹ
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);            //��ʼ��DMAͨ��1

  #if 0
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC | DMA_IT_HT, ENABLE);       //ʹ��DMA������ɺʹ���һ���ж�
    DMA_ClearITPendingBit (DMA1_IT_GL1 | DMA_IT_HT);
  #endif
  
    DMA_Cmd(DMA1_Channel1, ENABLE); //������ɺ�,����DMAͨ��

    ADC_DMACmd(ADC1, ENABLE);   //Enable ADC1 DMA

    //----ͬ������ʼת��-------------------------------------
    ADC_Cmd(ADC1, ENABLE);   //Enable ADC1

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //�ֹ�������һ��ADת��
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
����:   ����AD��ͨ��,5K,Apd,���,�¶�,LD1,LD2,�����ں�̨��ʼ
����:   �Եڼ���ͨ������, 0 / 1
���:   1mV
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


