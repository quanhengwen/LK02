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
} T_Demarcate;  //标定结构体

//-------------------------------------------------------------------------------

typedef struct  
{
    uint32_t CurrentStart;   //电流输出起点对应的距离
    uint32_t CurrentEnd; //电流输出终点对应的距离
}TypeCurrentRange;

typedef struct  
{
    uint8_t  CurrentDemarNbr; //标定点数
    uint16_t CurrentDemar[CURRENT_DEMAR_NUM]; //标定值
}TypeCurrentDemar;


typedef struct
{
    uint32_t BaudRate;   // 波特率
    uint16_t OutputHZ;   // 输出频率HZ
    uint16_t RangeMax;      // 量程
    uint16_t RangeMin;      // 量程
    uint16_t PulseHZ;    //脉冲重复频率
    uint16_t SWvalue;    //开关量门限
    uint16_t APDV_LOW;   //APD电压增益 PWM
    uint16_t APDV_MID;   //APD电压增益
    uint16_t APDV_HIG;   //APD电压增益
    uint8_t  APDV_Cal;   //高压标定标志
    int16_t Cal1;       //标定数据1  4KHZ
    uint8_t CurMol;     //当前模式 0待标定模式 1测试模式 2正式出厂模式
    int16_t Cal1_MD;
    int16_t Cal1_HI;    //高增益标定数据1  4KHZ
    int16_t Cal2;       //标定数据2  20KHZ
    int16_t Cal2_MD;
    int16_t Cal2_HI;    //高增益标定数据2  20KHZ
    uint16_t Ctemper;    //标定温度
    uint16_t PWM_rxHV;   //标定时的接收高压
    uint8_t  Msrefer;    //基准 1,前基准 0，后基准
    uint8_t  MsCurrMax;  //电流环量程上限
    uint8_t  MsCurrMin;  //电流环量程下限
    uint16_t Gain1;      // 4Khz低增益值 
    uint16_t Gain1_MD;
    uint16_t Gain1_HI;    // 4Khz高增益值 
    uint16_t Gain2;      // 20Khz低增益值 
    uint16_t Gain2_MD;
    uint16_t Gain2_HI;    // 20Khz高增益值 
    uint8_t  Flag_free;  //开机自动运行标志0\不自动 ,1\自动运行
    uint8_t  Address;    // modbus 从机地址
    uint8_t  Language;   //0 english, 1 chinese
		uint8_t frameType;    //设置0 ascii 或 1: modbus
    TypeCurrentRange CurrentRange; //电流环量程
    TypeCurrentDemar CurrentDemar; //电流环标定
}T_SysParam;

void SysParamInit(void);
void tlc5618_setting(void);  
void SettingSave(void);

#endif

