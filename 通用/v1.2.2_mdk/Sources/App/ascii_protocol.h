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
    s32 multiple;
    s16 constance;
} T_Demarcate;  //�궨�ṹ��

//-------------------------------------------------------------------------------

typedef struct  
{
    u32 CurrentStart;   //�����������Ӧ�ľ���
    u32 CurrentEnd; //��������յ��Ӧ�ľ���
}TypeCurrentRange;

typedef struct  
{
    u8  CurrentDemarNbr; //�궨����
    u16 CurrentDemar[CURRENT_DEMAR_NUM]; //�궨ֵ
}TypeCurrentDemar;


typedef struct
{
    u32 BaudRate;   // ������
    u16 OutputHZ;   // ���Ƶ��HZ
    u16 RangeMax;      // ����
    u16 RangeMin;      // ����
    u16 PulseHZ;    //�����ظ�Ƶ��
    u16 SWvalue;    //����������
    u16 APDV_LOW;   //APD��ѹ���� PWM
    u16 APDV_MID;   //APD��ѹ����
    u16 APDV_HIG;   //APD��ѹ����
    u8  APDV_Cal;   //��ѹ�궨��־
    s16 Cal1;       //�궨����1  4KHZ
    u8 CurMol;     //��ǰģʽ 0���궨ģʽ 1����ģʽ 2��ʽ����ģʽ
    s16 Cal1_MD;
    s16 Cal1_HI;    //������궨����1  4KHZ
    s16 Cal2;       //�궨����2  20KHZ
    s16 Cal2_MD;
    s16 Cal2_HI;    //������궨����2  20KHZ
    u16 Ctemper;    //�궨�¶�
    u16 PWM_rxHV;   //�궨ʱ�Ľ��ո�ѹ
    u8  Msrefer;    //��׼ 1,ǰ��׼ 0�����׼
    u8  MsCurrMax;  //��������������
    u8  MsCurrMin;  //��������������
    u16 Gain1;      // 4Khz������ֵ 
    u16 Gain1_MD;
    u16 Gain1_HI;    // 4Khz������ֵ 
    u16 Gain2;      // 20Khz������ֵ 
    u16 Gain2_MD;
    u16 Gain2_HI;    // 20Khz������ֵ 
    u8  Flag_free;  //�����Զ����б�־0\���Զ� ,1\�Զ�����
    u8  Address;    // modbus �ӻ���ַ
    u8  Language;   //0 english, 1 chinese
    TypeCurrentRange CurrentRange; //����������
    TypeCurrentDemar CurrentDemar; //�������궨
}T_SysParam;

void SysParamInit(void);
void tlc5618_setting(void);  
void SettingSave(void);

#endif

