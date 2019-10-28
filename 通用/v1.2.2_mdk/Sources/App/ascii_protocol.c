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
#include "global.h"

T_SysParam SysSeting;
E_PROTOCOL_TYPE ProtocolType;
u8  Flag_SetingDis=0;

u16 CurrentMark[CURRENT_DEMAR_NUM]=
{
    4000,8000,12000,16000,20000
};
/*����������Y = a*X+b */
T_Demarcate CurrentRatio[CURRENT_DEMAR_NUM -1];

//-----------------------------------------------------------------------------
extern E_MEAS_STATE MeasStatus;
extern u16 dist_num;
extern u8  FlagSleep;
extern u8 flag_disBool;
extern u32 dstMax,dstMin;
extern u8   Flag_NormalTest;
extern u8  Flag_Cal;
extern u16 CalNormDist;//10��
extern u8  Flag_QCTEST;
extern u16 QC_DIST;
extern u16 QC_NUB;
extern u8  FreeRun;
extern u8 Flag_ApdGn;
extern u16 AGC_NOW;
//-----------------------------------------------------------------------------
#define pro_printf  mPrintf

//------------�����ܣ���ȡӲ���汾
//���������dat
//�����������ӡ�汾��
void CMD_GetVersion(int dat)
{
    char ver[3];
    GetSoftDate(ver);

    if(SysSeting.Language == 1)
        pro_printf("�汾��Ϣ:H%d-S%d-%d/%d/%d\n", PCB_VERSION, SOFT_VERSION, ver[0]+2000, ver[1], ver[2]);
    else
        pro_printf("Version:H%d-S%d-%d/%d/%d\n", PCB_VERSION, SOFT_VERSION, ver[0]+2000, ver[1], ver[2]);
    pro_printf("GMP_V1.1.0(GeneralPulseMeasuring)\r\n");
    delay1us(10000);
}
//-----------------------------------------------------------------------------
//------------�����ܣ�Ĭ�ϵĳ�����������
void DefaultSetting(void)
{
    SysSeting.BaudRate = BAUDRATE_115200;
    SysSeting.OutputHZ = 100; //10 HZ
    SysSeting.RangeMax=300;//m
    SysSeting.RangeMin=1;//m
    SysSeting.PulseHZ=Pulse_freq_4KHZ;//20khz
    SysSeting.SWvalue=100;//1m

    SysSeting.APDV_LOW=95;
    SysSeting.APDV_MID=150;
    SysSeting.APDV_HIG=350;
    SysSeting.APDV_Cal=0;//��ѹ�궨��־λ���

    SysSeting.Cal1=0;//cm
    SysSeting.Cal1_MD=0;
    SysSeting.Cal1_HI=0;//cm
    SysSeting.Cal2=0;//cm
    SysSeting.Cal2_MD=0;
    SysSeting.Cal2_HI=0;//cm

    SysSeting.Gain1=0;//cm
    SysSeting.Gain1_MD=0;
    SysSeting.Gain1_HI=0;//cm
    SysSeting.Gain2=0;//cm
    SysSeting.Gain2_MD=0;
    SysSeting.Gain2_HI=0;//cm
    SysSeting.CurMol = 0;
    SysSeting.Ctemper=300;//30��
    SysSeting.PWM_rxHV=200;//pwm
    SysSeting.Msrefer=0;//��׼ =1ǰ��׼ =0���׼
    SysSeting.MsCurrMax=20;//mA
    SysSeting.MsCurrMin=4;//mA
    SysSeting.Flag_free=0;//���Զ�����
    //SysSeting.APD_HV = GAIN_APD_DEFAULT;
    //SysSeting.AGC_HV = GAIN_AGC_DEFAULT;
    SysSeting.Address = 0x01;
    SysSeting.Language = 0;//english

    SysSeting.CurrentRange.CurrentStart = 200; //�����������Ӧ�ľ���
    SysSeting.CurrentRange.CurrentEnd = 15000; //��������յ��Ӧ�ľ���

    SysSeting.CurrentDemar.CurrentDemarNbr = 0; //�궨����
    SysSeting.CurrentDemar.CurrentDemar[0] = 0; //�궨ֵ
    SysSeting.CurrentDemar.CurrentDemar[1] = 0; //�궨ֵ
    SysSeting.CurrentDemar.CurrentDemar[2] = 0; //�궨ֵ
    SysSeting.CurrentDemar.CurrentDemar[3] = 0; //�궨ֵ
    SysSeting.CurrentDemar.CurrentDemar[4] = 0; //�궨ֵ

}
//------------�����ܣ��ӻ�������ȡ���ò�����������ò���
void SettingRead(void)
{
    Flash_ReadData(EEP_SYSTEM_SETTING, (u8*)&SysSeting, sizeof(SysSeting));
    if(!Flag_SetingDis)
      FreeRun=SysSeting.Flag_free;//ֻ�������¿��������Ч
    else//��ȡ����������Ϣ
    {
      if(SysSeting.Language == 1)
      {
          Flag_SetingDis=0;
          pro_printf("===================������Ϣ=======================\n");
           delay1us(10000);
          pro_printf("������:%d\n",SysSeting.BaudRate);
          delay1us(10000);
          pro_printf("����Ƶ��:%dHZ\n",SysSeting.OutputHZ);//
          delay1us(10000);
          pro_printf("����:%dm~%dm\n",SysSeting.RangeMin,SysSeting.RangeMax);
          delay1us(10000);
          //pro_printf("��������:%dm\n",SysSeting.RangeMin);
          //delay1us(10000);
          if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
            pro_printf("����Ƶ��:4000HZ\n");
          else
            pro_printf("����Ƶ��:20000HZ\n");
          delay1us(10000);
          pro_printf("�����ظ�Ƶ��:%d\n",SysSeting.PulseHZ);
          delay1us(10000);
          pro_printf("����������:%dm\n",SysSeting.SWvalue);
          delay1us(10000);
          pro_printf("�궨�¶�:%f1��\n",SysSeting.Ctemper);
          //delay1us(10000);
          //pro_printf("�궨��ѹ:%dPWM\n",SysSeting.PWM_rxHV);
          delay1us(10000);
          pro_printf("����������:%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
          delay1us(10000);
          if(SysSeting.Cal1)
            pro_printf("�궨���:�궨ͨ��\n");
          else
            pro_printf("�궨���:�궨δͨ��\n");
          delay1us(10000);
          if(SysSeting.Msrefer)
            pro_printf("�궨��׼:ǰ��׼\n");
          else
            pro_printf("�궨��׼:���׼\n");
          delay1us(10000);
          if(SysSeting.Flag_free)
            pro_printf("�����Զ�������������\n");
          else
            pro_printf("�������Զ�����\n");
          delay1us(10000);
          CMD_GetVersion(0);
          pro_printf("=================================================\n");
          delay1us(10000);
        }
      else
       {
          Flag_SetingDis=0;
          pro_printf("================Factory Version====================\n");
           delay1us(10000);
          pro_printf("Baud rate:%d\n",SysSeting.BaudRate);
          delay1us(10000);
          pro_printf("Measure frequency:%dHZ\n",SysSeting.OutputHZ);//
          delay1us(10000);
          pro_printf("Range:%dm~%dm\n",SysSeting.RangeMin,SysSeting.RangeMax);
          delay1us(10000);
          //pro_printf("��������:%dm\n",SysSeting.RangeMin);
          //delay1us(10000);
          if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
            pro_printf("Pulse frequency:4000HZ\n");
          else
            pro_printf("Pulse frequency:20000HZ\n");
          delay1us(10000);
          pro_printf("Switch threshold:%dm\n",SysSeting.SWvalue);
          delay1us(10000);
          pro_printf("Calibration temperature:%f1��\n",SysSeting.Ctemper);
          //delay1us(10000);
          //pro_printf("�궨��ѹ:%dPWM\n",SysSeting.PWM_rxHV);
          delay1us(10000);
          pro_printf("Current loop range:%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
          delay1us(10000);
          if(SysSeting.Cal1)
            pro_printf("Calibration result:Pass\n");
          else
            pro_printf("Calibration result:Fail\n");
          delay1us(10000);
          if(SysSeting.Msrefer)
            pro_printf("Calibration base:Front base\n");
          else
            pro_printf("Calibration base:Back base\n");
          delay1us(10000);
          if(SysSeting.Flag_free)
            pro_printf("Boot automatically run continuous measurement\n");
          else
            pro_printf("Boot does not automatically\n");
          delay1us(10000);
          CMD_GetVersion(0);
          pro_printf("=================================================\n");
          delay1us(10000);
      }
    }
}
//------------�����ܣ��������ò���
void SettingSave(void)
{
    Flash_WriteData(EEP_SYSTEM_SETTING, (u8*)&SysSeting, sizeof(SysSeting));
    //д�뻺����
    EE_Flash_Write_All_Contents();
    //д��FLASH
}
//------------�����ܣ�AGCֵ����
void tlc5618_setting(void)
{
  //tlc5618_execute(SysSeting.APD_HV, SysSeting.AGC_HV);
  tlc5618_execute(LD_MD,500);//��LDV��AGC��//tx[1500]--68.4v,1400-89.3v,0.22v/DAC,1600--60v,1700--35v
  //
}
//------------�����ܣ���flash��ȡϵͳ���ò���
extern u16 dist_collect_tim_cnt ;
void SysParamInit(void)
{
    EE_Flash_Read_All_Contents();
    SettingRead();

    if((SysSeting.BaudRate != BAUDRATE_9600)
    &&(SysSeting.BaudRate != BAUDRATE_38400)
    &&(SysSeting.BaudRate != BAUDRATE_115200)
    &&(SysSeting.BaudRate != BAUDRATE_256000)
    &&(SysSeting.BaudRate != BAUDRATE_460800)
    &&(SysSeting.BaudRate != BAUDRATE_921600))
    {
        DefaultSetting();
        SettingSave();
    }
    //dist_num =10000/SysSeting.OutputHZ;//�ϵ�����ٶ�����
    if(SysSeting.PulseHZ==Pulse_freq_20KHZ){
        dist_collect_tim_cnt = 200;
    }else if(SysSeting.PulseHZ==Pulse_freq_4KHZ){
        dist_collect_tim_cnt = 50;
    }else
       dist_collect_tim_cnt = 50;

     BSP_USART_Config(SysSeting.BaudRate);//���ò�����
    //BSP_USART_Config(BAUDRATE_115200);
}
//------------�����ܣ���ȡ��׼
//���������dat
//�����������
void CMD_ReadStandard(int dat)
{
  if(SysSeting.Msrefer)
  {
   if(SysSeting.Language == 1)
    pro_printf("������ǰ��׼��\n");
   else
    pro_printf("Now is front base��\n");
    //pro_printf("Now is RearStandard\n");
  }
  else
  {
   if(SysSeting.Language == 1)
    pro_printf("�����Ǻ��׼��\n");
   else
    pro_printf("Now is back base��\n");

    //pro_printf("Now is FrontStandard\n");
  }
}
//------------�����ܣ����û�׼
//���������dat
//���������dst_standard
void CMD_SetStandard(int dat)
{
  SysSeting.Msrefer=dat;
  if(dat)
  {
    if(SysSeting.Language == 1)
     pro_printf("ǰ��׼���óɹ���\n");
    else
     pro_printf("Front base set ok��\n");
    //pro_printf("SetRearStandard OK\n");
  }
  else
  {
    if(SysSeting.Language == 1)
     pro_printf("���׼���óɹ���\n");
    else
     pro_printf("Back base set ok��\n");
    //pro_printf("SetFrontStandard OK\n");
  }
  SettingSave();
}
//------------�����ܣ���ȡ���������
//���������dat
//���������dst_standard
void CMD_ReadBool(int dat)
{
  flag_disBool=1;
  MeasStatus = SINGLE_MEAS;
}
//------------�����ܣ����ÿ���������
//���������dat
//���������dst_standard
void CMD_SetThd(int dat)
{
  SysSeting.SWvalue=dat;
  if(SysSeting.Language == 1)
    pro_printf("�������������óɹ���\n");
  else
    pro_printf("Switch threshold setting is ok��\n");
  SettingSave();
}
//------------�����ܣ���ȡ����������
//���������dat
//���������dst_standard
void CMD_ReadThd(int dat)
{
  //ThresholdBool=dat;
  if(SysSeting.Language == 1)
    pro_printf("��������Ϊ: %dm\n",SysSeting.SWvalue);
  else
    pro_printf("Switch threshold is: %dm\n",SysSeting.SWvalue);

}
//------------�����ܣ����β���
//���������dat
//���������MeasStatus
void CMD_SingleMeas(int dat)
{
  MeasStatus = SINGLE_MEAS;
  Flag_NormalTest=0;
  Contrl_635LD(0);//�򿪼�����׼
}
//------------�����ܣ���ʼ��������
//���������dat
//���������MeasStatus
void CMD_StartContisMeas(int dat)
{
	if(MeasStatus != CONTINUE_MEAS)
	{
		MeasStatus = CONTINUE_MEAS;
    	Flag_NormalTest=0;//������źŲ�����־
    	Contrl_635LD(0);
 	}


    //pro_printf("MS:ok\n");
}
//------------�����ܣ�ֹͣ��������
//���������dat
//���������MeasStatus
void CMD_StopContisMeas(int dat)
{
    MeasStatus = STOP_MEAS;
    FreeRun = 0;
    Contrl_635LD(1);//�رռ�����׼

}

//------------�����ܣ������Сֵ��������
//���������dat
//���������MeasStatus
void CMD_MaxMinMeas(int dat)
{
  MeasStatus = MAXMIN_MEAS;
  dstMax=0;
  dstMin=0;//��������Сֵ������
}
//------------�����ܣ�ֹͣ�������빦��ģʽ
//���������dat
//���������MeasStatus
void CMD_SleepDown(int dat)
{
  MeasStatus = STOP_MEAS;//���������־
  FlagSleep=1;//����˯�߱�־
  if(SysSeting.Language == 1)
    pro_printf("����˯��״̬...\n");
  else
    pro_printf("go sleep...\n");
}
//------------�����ܣ���������������
//���������dat
//���������SysSeting.BaudRate
void CMD_SetBaudrate(int dat)
{

    if((dat==BAUDRATE_4800)
        ||(dat==BAUDRATE_9600)
        ||(dat==BAUDRATE_38400)
        ||(dat==BAUDRATE_115200)
        ||(dat==BAUDRATE_256000)
        ||(dat==BAUDRATE_460800)
        ||(dat==BAUDRATE_921600))
    {
        if(dat!=SysSeting.BaudRate)
        {
            SysSeting.BaudRate = dat;
            if(SysSeting.Language == 1)
                pro_printf("���óɹ�!\n");
            else
               pro_printf("Set ok!\n");
            delay1us(10000);
            SettingSave();
            BSP_USART_Config(dat);// Initialize Uart0
        }
        //Printf("%d\n",dat);
       //pro_printf("MS:ok\n");
    }
    else
    {
        delay1us(10000);
        if(SysSeting.Language == 1)
            pro_printf("����ʧ��!\n");
        else
           pro_printf("Set error!\n");
    }
}
//------------�����ܣ����ò����ٶȣ�ͬ���޸�ƽ����������ʵ��
//���������dat
//���������dist_num
void CMD_SetOutputHZ(int dat)
{
  if(MeasStatus != 0)
    return;

  if(dat == 0){
    pro_printf("���ñ������1\r\n");
    return ;
  }
  int tmv_set = 1000000/dat - 1;
  if(dat <= 15){//����Ƶ�ʵ��ڷ�ֵʱ����Ҫ������ʱ��ֵ�Լ���ʱ������ֵ
    tmv_set = 999;
    OutputTimeStr.SuposOutputHzCnt = 1000/dat;//1000 = 1��
  }else{
    OutputTimeStr.SuposOutputHzCnt = 0;
  }
  hr_TimerBaseInit(TIM3,63,tmv_set);
  unsigned char tmpbuf[100]={0};
  sprintf(tmpbuf,"�������Ƶ��%dHZ %d\r\n",dat,OutputTimeStr.SuposOutputHzCnt);
  pro_printf(tmpbuf);
  SysSeting.OutputHZ = dat;
  SettingSave();
}
//------------�����ܣ����������ظ�Ƶ�ʣ�ͬ����������ʱ��ʵ��
//���������dat
//���������dist_num
extern u16 dist_collect_tim_cnt;
void CMD_SetPulseHZ(int dat)
{
  if(dat)//�ظ������õ�20Khz��ͬʱ���������
  {
    if(SysSeting.PulseHZ==Pulse_freq_20KHZ)
    {
      dist_collect_tim_cnt = 200;
    }
    else//�ظ��ʸı䣬ͬʱƥ�������4-->20
    {
      SysSeting.PulseHZ=Pulse_freq_20KHZ;
      dist_collect_tim_cnt = 200;
    }
  }
  else
  {
    if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
    {
      dist_collect_tim_cnt = 50;
    }
    else//�ظ��ʸı䣬ͬʱƥ�������20-->4
    {
      SysSeting.PulseHZ=Pulse_freq_4KHZ;
      dist_collect_tim_cnt = 50;
    }
  }
  if(SysSeting.Language == 1)
    pro_printf("���óɹ�!\n");
  else
    pro_printf("Set ok!\n");
  SettingSave();
}

//------------�����ܣ��������̣��޸���������ʵ��
//���������dat
//���������SysSeting.Range
void CMD_SetRange(int dat)
{
    if(dat>0 && dat<= 400) // 400m
    {
        SysSeting.RangeMax = dat;
        //DIST_MAX=dat*100;
        if(SysSeting.Language == 1)
           pro_printf("���óɹ�!\n");
        else
           pro_printf("Set ok!\n");
        SettingSave();
    }
    else
    {
        if(SysSeting.Language == 1)
           pro_printf("����ʧ��!\n");
        else
           pro_printf("Set error!\n");
    }
}

void CMD_GetRange(int dat)
{
  pro_printf("%d\n",SysSeting.RangeMax);
}

/*
//------------�����ܣ�����/�޸�APD��ѹ
//���������dat
//���������SysSeting.APD_HV
void CMD_APD_HV_Adj(int dat)
{
    if (dat>3) return;

    switch(dat)
    {
        case 0:
            if(SysSeting.APD_HV>=60)
                SysSeting.APD_HV -= 60;
            break;
        case 1:
            if(SysSeting.APD_HV <= (GAIN_APD_MAX-60))
                SysSeting.APD_HV += 60;
            break;
        case 2:
            if(SysSeting.APD_HV>=12)
                SysSeting.APD_HV -= 12;
            break;
        case 3:
            if(SysSeting.APD_HV <= (GAIN_APD_MAX-12))
                SysSeting.APD_HV += 12;
            break;
        default:
            break;
    }
    SettingSave();
    //tlc5618_setting();APD��ѹ�Ѿ��޸�ΪPWM��ʽ
    pro_printf("MS:ok\n");
}
//------------�����ܣ�����/�޸�AGC����
//���������dat
//���������SysSeting.AGC_HV
void CMD_AGC_HV_Adj(int dat)
{
    if (dat>3) return;

    switch(dat)
    {
        case 0:
            if(SysSeting.AGC_HV >= 60)
                SysSeting.AGC_HV -= 60;
            break;
        case 1:
            if(SysSeting.AGC_HV <= (GAIN_AGC_MAX-60))
                SysSeting.AGC_HV += 60;
            break;
        case 2:
            if(SysSeting.AGC_HV >= 12)
                SysSeting.AGC_HV -= 12;
            break;
        case 3:
            if(SysSeting.AGC_HV <= (GAIN_AGC_MAX-12))
                SysSeting.AGC_HV += 12;
            break;
        default:
            break;
    }
    SettingSave();
    tlc5618_setting();
    pro_printf("MS:ok\n");
}
*/

//------------�����ܣ���ʾASCIIָ�-�û�
//���������dat
//�����������ӡ�汾��
void CMD_ASCII(int dat)
{
  if(SysSeting.Language == 1)
  {
      pro_printf("//=================���� LK02 ָ�==================//\n");
      delay1us(10000);
      pro_printf(" MS:contis:��������!\n");
      delay1us(10000);
      pro_printf(" MS:single:���β���!\n");
      delay1us(10000);
      pro_printf(" MS:stopcontis:ֹͣ��������\n");
      delay1us(10000);
      pro_printf(" MS:setbase1:���û�׼Ϊǰ��׼!\n");
      delay1us(10000);
      pro_printf(" MS:setbase1:���û�׼Ϊ���׼!\n");
      delay1us(10000);
      pro_printf(" MS:pulsefreq0:���������ظ�Ƶ��Ϊ4KHZ!\n");
      delay1us(10000);
      pro_printf(" MS:pulsefreq1:���������ظ�Ƶ��Ϊ20KHZ!\n");
      delay1us(10000);
      pro_printf(" MS:switchthd:���ÿ���������[0~����]!\n");
      delay1us(10000);
      pro_printf(" MS:getswitch:��ȡ���������!\n");
      delay1us(10000);
      pro_printf(" MS:HZ:���ò���Ƶ��[10~1000HZ]!\n");
      delay1us(10000);
      pro_printf("======================����========================\n");
      delay1us(10000);
  }
  else
  {
      pro_printf("//=========Mileseey LK02 Support Command List===========//\n");
      delay1us(10000);
      pro_printf(" MS:contis:continuous measurement!\n");
      delay1us(10000);
      pro_printf(" MS:single:single measurement!\n");
      delay1us(10000);
      pro_printf(" MS:stopcontis:stop continuous measurement\n");
      delay1us(10000);
      pro_printf(" MS:setbase1:set measure base is front!\n");
      delay1us(10000);
      pro_printf(" MS:setbase1:set measure base is back!\n");
      delay1us(10000);
      pro_printf(" MS:pulsefreq0:set pulse repetition frequency is 4KHZ!\n");
      delay1us(10000);
      pro_printf(" MS:pulsefreq1:set pulse repetition frequency is 20KHZ!\n");
      delay1us(10000);
      pro_printf(" MS:switchthd:set switch threshold[0~max range]!\n");
      delay1us(10000);
      pro_printf(" MS:getswitch:get switch result!\n");
      delay1us(10000);
      pro_printf(" MS:HZ:set measure frequency[10~1000HZ]!\n");
      delay1us(10000);
      pro_printf("========================End===========================\n");
      delay1us(10000);
  }
  /*
     Printf("//====================Mileseey LI3 Support Command List=======================//\r\n");
    Printf(" contis:       Continuous measurement!\r\n");
    Printf(" stopcontis:   Stop Continuous measurement!\r\n");
    Printf(" single:       Single measure!\r\n");
    Printf(" getlaser:     Get laser status!\r\n");
    Printf(" setlaser:     Switch laser to on or off. e.g: setlaser x [x: 0=off,1=on].\r\n");
    Printf(" getmaxmindis: Get Max and Min Distanse.\r\n");
    Printf(" getldcurr:    Get LD current.\r\n");
    //Printf(" gethz:        Get measure rate.\r\n");
    //Printf(" sethz:        Set measure rate. e.g: sethz x [x: 1,2,5,10,20].\r\n");
    //Printf(" getrange:     Get measure range.\r\n");
    //Printf(" setrange:     Set measure range[200~60000].\r\n");
    Printf(" getoffset:    Get measure offset.\r\n");
    Printf(" setoffset:    Set measure offset.[-20000~20000].\r\n");
    Printf(" getbase:      Get measure base.\r\n");
    Printf(" setbase:      Set measre base[1=Front,0=Back].\r\n");
    Printf(" getaddr:      Get slave addr.\r\n");
    Printf(" setaddr:      Set slave addr[0~254].\r\n");
    Printf(" getbaud:      Get baud rate.\r\n");
    Printf(" setbaud:      Set baud rate[4800,9600,19200,38400,57600,115200].\r\n");
    Printf(" intosleep:    Set slave to sleep mode.\r\n");
    Printf(" rstcommparam: Reset comm param.\r\n");
    //Printf(" withdemar:    Set measure with demar[0/1].\r\n");
    Printf(" withsignal:   Set measure with signal[0/1]\r\n");
    Printf(" getmeasinfo:  Get measure info e.g:PWM,HV power.\r\n");
    Printf(" getsysinfo:   Get system info.\r\n");
    //Printf(" getpro:       Get protocol type.\r\n");
    //Printf(" setpro:       Set protocol type[0/1].0-RTU,1-ASCII\r\n");
    Printf(" getdemarinfo: Get demar information.\r\n");
    Printf(" mark1demar:   1.0m demar.\r\n");
    //Printf(" oncedemar:  Single demar. e.g setdemar x [x: 0~19].\r\n");
    //Printf(" contdemar:    Continuous demar.\r\n");
    Printf(" clrdemar:     Clear demar status.\r\n");
    Printf(" rsudemar:     Resume demar status.\r\n");
    Printf(" exitdemar:    Exit demar.\r\n");
    Printf(" qctest:       Start qc test.\r\n");
    Printf(" stopqctest:   Stop qc test.\r\n");
    //Printf(" clrallparam:  Clear EEPROMorFLASH to empty.\r\n");
    //Printf(" debug:        Switch to debug mode[0/1].\r\n");
    Printf(" help:         Print command list.\r\n");
    Printf("//======================================End===================================//\r\n");
 */
}
//------------�����ܣ����õ�����������ֵ
//���������dat
//���������current_MAX
void SetCurMax(int dat)
{
  if(dat<24&&dat>0)
  {
    SysSeting.MsCurrMax=dat;
    if(SysSeting.Language == 1)
       pro_printf("���óɹ�!\n");
    else
       pro_printf("Set ok!\n");
    SettingSave();
  }
  else
  {
    if(SysSeting.Language == 1)
       pro_printf("����ʧ��!\n");
    else
      pro_printf("Set error!\n");
  }
}
//------------�����ܣ����õ����������Сֵ
//���������dat
//���������current_MAX
void SetCurMin(int dat)
{
  if(dat<24&&dat>0)
  {
    SysSeting.MsCurrMin=dat;
    if(SysSeting.Language == 1)
       pro_printf("���óɹ�!\n");
    else
       pro_printf("Set ok!\n");
    SettingSave();
  }
  else
  {
    if(SysSeting.Language == 1)
       pro_printf("����ʧ��!\n");
    else
       pro_printf("Set error!\n");
  }
}
//------------�����ܣ���ȡ����������
//���������dat
//���������current_MAX
void GetCurSet(int dat)
{
  if(SysSeting.Language == 1)
    pro_printf("����������Ϊ:%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
  else
    pro_printf("current loop range :%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
  delay1us(10000);
}
//------------�����ܣ����ź���������
//���������dat
//���������current_MAX
void CMD_TestWithSig(int dat)
{
  Flag_NormalTest=1;//��׼���źŲ���
  MeasStatus = CONTINUE_MEAS;
}
//------------�����ܣ������źŲ���
//���������dat
//���������current_MAX
void CMD_TestWithoutSig(int dat)
{
    Flag_NormalTest=0;
    MeasStatus = CONTINUE_MEAS;
}
//------------�����ܣ���ȡ��������
//���������dat
//���������current_MAX
void CMD_ReadFactorySettings(int dat)
{
  Flag_SetingDis=1;
  EE_Flash_Read_All_Contents();
  SettingRead();
}
//------------������:�趨�궨����
//���������dat
//���������CalNormDist
void CMD_SetCal(int dat)
{
 CalNormDist=dat*100;
 if(SysSeting.Language == 1)
    Printf("�궨�����趨Ϊ%dm:\n",dat);
 else
    Printf("Set the calibration distance %dm:\n",dat);
 delay1us(100000);
}
//------------�����ܣ���ʼ�궨
//���������dat
//���������current_MAX
void CMD_StartCal(int dat)
{
  EE_Flash_Read_All_Contents();
  SettingRead();                            //��ȡFLASH�궨��
  if((SysSeting.Cal1==0)&&(SysSeting.Cal2==0))//ͬʱΪ0��Ϊδ�궨
  {
    delay1us(20000);
    if(SysSeting.Language == 1)
       Printf("=============��ʼ�궨=============\n");
    else
       Printf("==========start calibration=======\n");
    delay1us(20000);
    Flag_Cal=1;//���ñ궨��־λ
    Flag_NormalTest=1;//��׼���źŲ���
    MeasStatus = CONTINUE_MEAS;
    dist_collect_tim_cnt = 10;
  }
  else
  {
    if(SysSeting.Language == 1)
        Printf("���󣺸û����ѱ궨��ɣ�\n");
    else
        Printf("Error: the machine calibration has been finished��\n");
    delay1us(10000);
  }

}
//------------�����ܣ�����궨��Ϣ���ָ���������
//���������dat
//���������current_MAX
void CMD_StopCal(int dat)//������б궨��Ϣ�����ָ�Ĭ�ϳ�������
{
  DefaultSetting();
  if(SysSeting.Language == 1)
       pro_printf("���óɹ�!\n");
  else
       pro_printf("Set ok!\n");
  SettingSave();
  delay1us(20000);
}
//------------�����ܣ���ȡ�궨����
//���������dat
//���������current_MAX
//=================�궨��Ϣ====================
//SysSeting.APDV_LOW:220
//SysSeting.APDV_MID:306
//SysSeting.APDV_HIG:407
//4KhzCal_LOW:18CM
//4KhzCal_MDL:48CM
//4KhzCal_HIG:58CM
//20KhzCal_LOW:32CM
//20KhzCal_MDL:46CM
//20KhzCal_HIG:54CM
//4KhzGain_LOW:602  //�ݶ�ƫ��PerAPDGain 110���������ģ����LOW����HIG��С���ѧ������
//4KhzGain_MDL:486
//4KhzGain_HIG:366
//20KhzGain_LOW:572
//20KhzGain_MDL:494
//20KhzGain_HIG:384
//TempCal:32.9��
//�궨ͨ����
//============================================\n
void CMD_ReadCal(int dat)
{
  delay1us(10000);
  if(SysSeting.Language == 1)
    pro_printf("=================�궨��Ϣ====================\n");
  else
    pro_printf("============Calibration information===========\n");

  delay1us(10000);//

  pro_printf("SysSeting.APDV_LOW:%d\n",SysSeting.APDV_LOW);
  delay1us(10000);
  pro_printf("SysSeting.APDV_MID:%d\n",SysSeting.APDV_MID);
  delay1us(10000);
  pro_printf("SysSeting.APDV_HIG:%d\n",SysSeting.APDV_HIG);
  delay1us(10000);

  pro_printf("4KhzCal_LOW:%dCM\n",SysSeting.Cal1);
  delay1us(10000);
  pro_printf("4KhzCal_MDL:%dCM\n",SysSeting.Cal1_MD);
  delay1us(10000);
  pro_printf("4KhzCal_HIG:%dCM\n",SysSeting.Cal1_HI);

  delay1us(10000);
  pro_printf("20KhzCal_LOW:%dCM\n",SysSeting.Cal2);
  delay1us(10000);
  pro_printf("20KhzCal_MDL:%dCM\n",SysSeting.Cal2_MD);
  delay1us(10000);
  pro_printf("20KhzCal_HIG:%dCM\n",SysSeting.Cal2_HI);

  delay1us(10000);
  pro_printf("4KhzGain_LOW:%d\n",SysSeting.Gain1);
  delay1us(10000);
  pro_printf("4KhzGain_MDL:%d\n",SysSeting.Gain1_MD);
  delay1us(10000);
  pro_printf("4KhzGain_HIG:%d\n",SysSeting.Gain1_HI);

  delay1us(10000);
  pro_printf("20KhzGain_LOW:%d\n",SysSeting.Gain2);
  delay1us(10000);
  pro_printf("20KhzGain_MDL:%d\n",SysSeting.Gain2_MD);
  delay1us(10000);
  pro_printf("20KhzGain_HIG:%d\n",SysSeting.Gain2_HI);
 delay1us(10000);
 pro_printf("TempCal:%f1��\n",SysSeting.Ctemper);
 delay1us(10000);
 if(SysSeting.Cal2)
 {
   if(SysSeting.Language == 1)
    Printf("�궨�ɹ���\n");
   else
    Printf("Calibration success��\n");
 }
 else
 {
  if(SysSeting.Language == 1)
   Printf("�궨ʧ�ܣ�\n");
  else
   Printf("Calibration failure��\n");
 }
 delay1us(10000);
 pro_printf("============================================\\n\n");
}
//------------�����ܣ�QC���
//���Ŀ�ģ����4KHZ��20KHZ����Ƶ���µĲ�������
//���з�ʽ��QC����־λ��λ���Ⱥ��ӡ4��20KHZʱ�����ݣ����ԱȽ��
//���������dat
//���������current_MAX
void CMD_QCtest(int dat)
{
  delay1us(20000);
  if(SysSeting.Language == 1)
    Printf("=============��ʼƷ��=================\n");
  else
    Printf("=============START QC TEST============\n");
  delay1us(20000);
  Flag_QCTEST=1;
  QC_DIST=dat*100;
  MeasStatus= CONTINUE_MEAS;
  Flag_NormalTest=0;
  QC_NUB=0;
}
//------------�����ܣ�ֹͣQC���
//���������dat
//���������current_MAX
void CMD_StopQCtest(int dat)
{
  QC_NUB=0;
  Flag_QCTEST=0;
  MeasStatus = STOP_MEAS;
  Flag_NormalTest=0;
  if(SysSeting.Language == 1)
    Printf("ֹͣƷ�죡\n");
  else
    Printf("QC TEST STOP��\n");
}
//------------������:���ÿ����Զ���������
//���������dat
//���������Flag_free
//Flag_free=0 �������Զ����У�Flag_free=1 �����Զ���������
void CMD_FreeRun(int dat)
{
  SysSeting.Flag_free=0;
  SysSeting.CurMol = 2;
  //SysSeting.BaudRate = BAUDRATE_460800;
  //Printf("�������:\r\n460800������\r\n5K���Ƶ��\r\n�ϵ��Զ�ִ��\r\n");
  SettingSave();
  Printf("�����ΪͨѶЭ�鶨�ư汾v1.0\r\n");

}

void CMD_SetLanguage(int dat)
{
  delay1us(10000);
  if(dat)
  {
    SysSeting.Language=1;
    Printf("��ǰ����Ϊ���ģ�\n");
  }
  else
  {
    SysSeting.Language=0;
    Printf("The current language is English��\n");
  }
  delay1us(10000);
  SettingSave();
}

void CMD_SetCurrOut(int dat)
{
    u32 n_mA;

    n_mA = dat;

    if(n_mA>0&&n_mA<24)
    {
        ExDAC_WriteDat(n_mA*65536/24 - 1);
        if(SysSeting.Language == 1)
            Printf("�������óɹ�:%dmA\r\n",dat);
        else
            Printf("Set current OK,%dmA\r\n",dat);
    }
    else
    {
        if(SysSeting.Language == 1)
            Printf("����ֵ����!\r\n");
        else
            Printf("Error current!\r\n");
    }
}

void CMD_SetCurrDemar(int dat)
{
    u16 current_data;

    current_data = dat;
    if((current_data > (CurrentMark[0] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[0] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[0] = current_data;
        if(SysSeting.Language == 1)
            Printf("��ǰ�����궨�ɹ�:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[1] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[1] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[1] = current_data;
        if(SysSeting.Language == 1)
            Printf("��ǰ�����궨�ɹ�:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[2] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[2] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[2] = current_data;
        if(SysSeting.Language == 1)
            Printf("��ǰ�����궨�ɹ�:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[3] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[3] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[3] = current_data;
        if(SysSeting.Language == 1)
            Printf("��ǰ�����궨�ɹ�:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[4] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[4] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[4] = current_data;
        if(SysSeting.Language == 1)
            Printf("��ǰ�����궨�ɹ�:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else
    {
        if(SysSeting.Language == 1)
            Printf("Error current demar!\r\n");
        else
            Printf("����ĵ���ֵ!\r\n");
    }
}

void CMD_ClrCurrDemar(int dat)
{
    SysSeting.CurrentDemar.CurrentDemar[0] = 0;
    SysSeting.CurrentDemar.CurrentDemar[1] = 0;
    SysSeting.CurrentDemar.CurrentDemar[2] = 0;
    SysSeting.CurrentDemar.CurrentDemar[3] = 0;
    SysSeting.CurrentDemar.CurrentDemar[4] = 0;
    SysSeting.CurrentDemar.CurrentDemarNbr = 0;

    SettingSave();

    if(SysSeting.Language == 1)
        Printf("�����궨ֵ����ɹ�!\r\n");
    else
        Printf("clear current demar ok!\r\n");
}
void CMD_GetCurrDemar(int dat)
{
    if(SysSeting.Language == 1)
    {
        Printf("4mA   �궨ֵ: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[0]);
        Printf("8mA   �궨ֵ: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[1]);
        Printf("12mA  �궨ֵ: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[2]);
        Printf("16mA  �궨ֵ: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[3]);
        Printf("20mA  �궨ֵ: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[4]);
    }
    else
    {
        Printf("4mA   calibration value is %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[0]);
        Printf("8mA   calibration value is %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[1]);
        Printf("12mA  calibration value is %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[2]);
        Printf("16mA  calibration value is %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[3]);
        Printf("20mA  calibration value is %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[4]);
    }
}


void CMD_LsAddress(int dat)
{
  Printf("%d\n",SysSeting.Address);
}

void CMD_SetAddress(int dat)
{
  if(dat > 255 || dat < 1)
  {
    Printf("Set Faild !\n");
  }
  SysSeting.Address = dat;
  if(SysSeting.Language == 1)
    Printf("���óɹ�!\n");
  else
    Printf("Set ok!\n");
  SettingSave();
}

void CMD_LedOn(int dat)
{
  Contrl_635LD(0);//�򿪼�����׼
   Printf("MS:ok!\n");
}


void CMD_LedOff(int dat)
{
    Contrl_635LD(1);
  Printf("MS:ok!\n");
}


void CMD_LsOutputHz(int dat)
{
  char tPusBuf[50] = "";
  char tOutpBuf[50] = "";
  if(SysSeting.PulseHZ==Pulse_freq_20KHZ){
    sprintf(tPusBuf,"�����ظ�Ƶ��:20kHz\n");
  }else{
    sprintf(tPusBuf,"�����ظ�Ƶ��:4kHz\n");
  }
  sprintf(tOutpBuf,"%s���Ƶ��:%dHz\n",tPusBuf,SysSeting.OutputHZ);
  Printf(tOutpBuf);
}

const T_CmdHandle HandleTab[] = {
    {"MS:contis",   CMD_StartContisMeas}, //��ʼ��������
    {"MS:stopcontis",   CMD_StopContisMeas}, //ֹͣ��������
    {"MS:setbaudrate",   CMD_SetBaudrate},   //���ò�����
    {"MS:HZ",     CMD_SetOutputHZ},   //�������Ƶ��
    {"MS:setrange",  CMD_SetRange},      //��������
    //{"MS:APDHV",  CMD_APD_HV_Adj},    //����APD��ѹ
    //{"MS:AGCHV",  CMD_AGC_HV_Adj},    //����AGC��ѹ
    {"MS:version",CMD_GetVersion},    //��ȡ�汾��Ϣ
    {"MS:single", CMD_SingleMeas},     //���β���
    {"MS:pulsefreq", CMD_SetPulseHZ},  //�����ظ�Ƶ��
    {"MS:setbase", CMD_SetStandard},   //���û�׼
    {"MS:getbase", CMD_ReadStandard},  //��ȡ��׼
    //{"MS:getmaxmindis", CMD_MaxMinMeas},//�������������Сֵ
    //{"MS:switchthd", CMD_SetThd},//���ÿ���������
    //{"MS:readswitchthd", CMD_ReadThd},//��ȡ����������
    //{"MS:getswitch", CMD_ReadBool},//��ȡ���������
    //{"MS:help", CMD_ASCII},//��ȡ���������
    //{"MS:currentmax", SetCurMax},//���õ��������ֵ
    //{"MS:currentmin", SetCurMin},//���õ�������Сֵ
    //{"MS:getcurrent", GetCurSet},//��ȡ����������
    {"MS:withsignal", CMD_TestWithSig},//���źŲ���
    {"MS:withnosignal", CMD_TestWithoutSig},//�����źŲ���
    {"MS:setdemardis", CMD_SetCal},  //�趨�궨����
    {"MS:mark1demar", CMD_StartCal},  //��ʼ�궨
    {"MS:clrdemar", CMD_StopCal},  //ֹͣ�궨
    {"MS:getdemarinfo", CMD_ReadCal},  //��ȡ�궨��Ϣ
    //{"MS:setqcdis", CMD_QCtest},  //QC���
    //{"MS:stopqctest", CMD_StopQCtest},  //ֹͣQC���
    {"MS:getsysinfo", CMD_ReadFactorySettings},//��ȡ������Ϣ
    //{"MS:sleep", CMD_SleepDown},//˯�ߣ��������ģʽ
    //{"MS:setlanguage", CMD_SetLanguage},//��������
    //{"MS:setcurrout", CMD_SetCurrOut},//���õ������
    //{"MS:setcurrdemar", CMD_SetCurrDemar},//���õ����궨ֵ
    //{"MS:clrcurrdemar", CMD_ClrCurrDemar},//��������궨ֵ
    //{"MS:getcurrdemar", CMD_GetCurrDemar},//��ȡ�����궨ֵ
    {"MS:getaddress",CMD_LsAddress},//��ȡ��ַ
    {"MS:setaddress",CMD_SetAddress},//���õ�ַ
    {"MS:getrange",CMD_GetRange}, //��ѯ����
    {"MS:ledon",CMD_LedOn},//����׼��
    {"MS:ledoff",CMD_LedOff},//�ر���׼��
    {"MS:setfreerun", CMD_FreeRun},//�����Զ���������
    //{"MS:QCgetHz",CMD_LsOutputHz},//��QCʱ��ѯ���Ƶ�ʺ�����Ƶ��
};

const u8 MAX_CMD_NUM = 24;


