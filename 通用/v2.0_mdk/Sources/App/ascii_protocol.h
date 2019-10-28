/*******************************************************************
*file name:    ascii_protocol.c
*project:      C1
*Description:  uart protocol
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2016.5.7
*note:         null
*******************************************************************/
#ifndef _ASCII_PROTOCOL_H_
#define _ASCII_PROTOCOL_H_

#include "stdint.h"
//-------------------------------------------------------------------------------
#define EEP_ADDR_START        (0)
#define EEP_SYSTEM_SETTING    (0+EEP_ADDR_START)          // 1byte  0,1,2  

//-------------------------------------------------------------------------------
#define BAUDRATE_4800       ((u32)4800)
#define BAUDRATE_9600       ((u32)9600)
#define BAUDRATE_19200       ((u32)19200)
#define BAUDRATE_38400       ((u32)38400)
#define BAUDRATE_115200      ((u32)115200)
#define BAUDRATE_256000      ((u32)256000)
#define BAUDRATE_460800      ((u32)460800)
#define BAUDRATE_921600      ((u32)921600)

//-------------------------------------------------------------------------------
#define GAIN_APD_MAX         2048        // default value
#define GAIN_APD_DEFAULT     1200//864   // default value 
#define GAIN_AGC_MAX         1048        // default value
#define GAIN_AGC_MIN         24          // default value
#define GAIN_AGC_INC_VALUE   5           // default value
#define GAIN_AGC_MAX_LEVEL  (GAIN_AGC_MAX-GAIN_AGC_INC_VALUE)// default value
#define GAIN_AGC_MIN_LEVEL  (GAIN_AGC_MIN+GAIN_AGC_INC_VALUE)// default value
#define GAIN_AGC_DEFAULT     630//650         // default value

#define Pulse_freq_20KHZ     40000//15k      50000-20k
#define Pulse_freq_4KHZ      270 //4k-270


#define Pulse_freq_1KHZ      50
#define Pulse_freq_500HZ     25
#define Pulse_freq_100HZ     5

#define DEMAR_OFFSET        500
#define CURRENT_DEMAR_NUM 5

typedef struct {
    int32_t multiple;
    int16_t constance;
} T_Demarcate;  //�궨�ṹ��

//-------------------------------------------------------------------------------

typedef struct  
{
    uint32_t CurrentStart;   //�����������Ӧ�ľ���
    uint32_t CurrentEnd; //��������յ��Ӧ�ľ���
}TypeCurrentRange;

typedef struct  
{
    uint8_t  CurrentDemarNbr; //�궨����
    uint16_t CurrentDemar[CURRENT_DEMAR_NUM]; //�궨ֵ
}TypeCurrentDemar;


typedef struct
{
    uint32_t BaudRate;   // ������
    uint16_t OutputHZ;   // ���Ƶ��HZ
    uint16_t RangeMax;      // ����
    uint16_t RangeMin;      // ����
    uint16_t PulseHZ;    //�����ظ�Ƶ��
    uint16_t SWvalue;    //����������
    uint16_t APDV_LOW;   //APD��ѹ���� PWM
    uint16_t APDV_MID;   //APD��ѹ����
    uint16_t APDV_HIG;   //APD��ѹ����
    uint8_t  APDV_Cal;   //��ѹ�궨��־
    int16_t Cal1;       //�궨����1  4KHZ
    uint8_t CurMol;     //��ǰģʽ 0���궨ģʽ 1����ģʽ 2��ʽ����ģʽ
    int16_t Cal1_MD;
    int16_t Cal1_HI;    //������궨����1  4KHZ
    int16_t Cal2;       //�궨����2  20KHZ
    int16_t Cal2_MD;
    int16_t Cal2_HI;    //������궨����2  20KHZ
    uint16_t Ctemper;    //�궨�¶�
    uint16_t PWM_rxHV;   //�궨ʱ�Ľ��ո�ѹ
    uint8_t  Msrefer;    //��׼ 1,ǰ��׼ 0�����׼
    uint8_t  MsCurrMax;  //��������������
    uint8_t  MsCurrMin;  //��������������
    uint16_t Gain1;      // 4Khz������ֵ 
    uint16_t Gain1_MD;
    uint16_t Gain1_HI;    // 4Khz������ֵ 
    uint16_t Gain2;      // 20Khz������ֵ 
    uint16_t Gain2_MD;
    uint16_t Gain2_HI;    // 20Khz������ֵ 
    uint8_t  Flag_free;  //�����Զ����б�־0\���Զ� ,1\�Զ�����
    uint8_t  Address;    // modbus �ӻ���ַ
    uint8_t  Language;   //0 english, 1 chinese
		uint8_t frameType;    //����0 ascii �� 1: modbus
    TypeCurrentRange CurrentRange; //����������
    TypeCurrentDemar CurrentDemar; //�������궨
}T_SysParam;

void SysParamInit(void);
void tlc5618_setting(void);  
void SettingSave(void);

#endif

