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
/*电流环计算Y = a*X+b */
T_Demarcate CurrentRatio[CURRENT_DEMAR_NUM -1];

//-----------------------------------------------------------------------------
extern E_MEAS_STATE MeasStatus;
extern u16 dist_num;
extern u8  FlagSleep;
extern u8 flag_disBool;
extern u32 dstMax,dstMin;
extern u8   Flag_NormalTest;
extern u8  Flag_Cal;
extern u16 CalNormDist;//10米
extern u8  Flag_QCTEST;
extern u16 QC_DIST;
extern u16 QC_NUB;
extern u8  FreeRun;
extern u8 Flag_ApdGn;
extern u16 AGC_NOW;
//-----------------------------------------------------------------------------
#define pro_printf  mPrintf

//------------程序功能：获取硬件版本
//输入参数：dat
//输出参数：打印版本号
void CMD_GetVersion(int dat)
{
    char ver[3];
    GetSoftDate(ver);

    if(SysSeting.Language == 1)
        pro_printf("版本信息:H%d-S%d-%d/%d/%d\n", PCB_VERSION, SOFT_VERSION, ver[0]+2000, ver[1], ver[2]);
    else
        pro_printf("Version:H%d-S%d-%d/%d/%d\n", PCB_VERSION, SOFT_VERSION, ver[0]+2000, ver[1], ver[2]);
    pro_printf("GMP_V1.1.0(GeneralPulseMeasuring)\r\n");
    delay1us(10000);
}
//-----------------------------------------------------------------------------
//------------程序功能：默认的出厂参数设置
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
    SysSeting.APDV_Cal=0;//高压标定标志位清空

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
    SysSeting.Ctemper=300;//30℃
    SysSeting.PWM_rxHV=200;//pwm
    SysSeting.Msrefer=0;//基准 =1前基准 =0后基准
    SysSeting.MsCurrMax=20;//mA
    SysSeting.MsCurrMin=4;//mA
    SysSeting.Flag_free=0;//不自动运行
    //SysSeting.APD_HV = GAIN_APD_DEFAULT;
    //SysSeting.AGC_HV = GAIN_AGC_DEFAULT;
    SysSeting.Address = 0x01;
    SysSeting.Language = 0;//english

    SysSeting.CurrentRange.CurrentStart = 200; //电流输出起点对应的距离
    SysSeting.CurrentRange.CurrentEnd = 15000; //电流输出终点对应的距离

    SysSeting.CurrentDemar.CurrentDemarNbr = 0; //标定点数
    SysSeting.CurrentDemar.CurrentDemar[0] = 0; //标定值
    SysSeting.CurrentDemar.CurrentDemar[1] = 0; //标定值
    SysSeting.CurrentDemar.CurrentDemar[2] = 0; //标定值
    SysSeting.CurrentDemar.CurrentDemar[3] = 0; //标定值
    SysSeting.CurrentDemar.CurrentDemar[4] = 0; //标定值

}
//------------程序功能：从缓冲区读取设置并保存过的设置参数
void SettingRead(void)
{
    Flash_ReadData(EEP_SYSTEM_SETTING, (u8*)&SysSeting, sizeof(SysSeting));
    if(!Flag_SetingDis)
      FreeRun=SysSeting.Flag_free;//只有在重新开机后才生效
    else//读取出厂设置信息
    {
      if(SysSeting.Language == 1)
      {
          Flag_SetingDis=0;
          pro_printf("===================出厂信息=======================\n");
           delay1us(10000);
          pro_printf("波特率:%d\n",SysSeting.BaudRate);
          delay1us(10000);
          pro_printf("测量频率:%dHZ\n",SysSeting.OutputHZ);//
          delay1us(10000);
          pro_printf("量程:%dm~%dm\n",SysSeting.RangeMin,SysSeting.RangeMax);
          delay1us(10000);
          //pro_printf("量程下限:%dm\n",SysSeting.RangeMin);
          //delay1us(10000);
          if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
            pro_printf("脉冲频率:4000HZ\n");
          else
            pro_printf("脉冲频率:20000HZ\n");
          delay1us(10000);
          pro_printf("脉冲重复频率:%d\n",SysSeting.PulseHZ);
          delay1us(10000);
          pro_printf("开关量门限:%dm\n",SysSeting.SWvalue);
          delay1us(10000);
          pro_printf("标定温度:%f1℃\n",SysSeting.Ctemper);
          //delay1us(10000);
          //pro_printf("标定高压:%dPWM\n",SysSeting.PWM_rxHV);
          delay1us(10000);
          pro_printf("电流环量程:%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
          delay1us(10000);
          if(SysSeting.Cal1)
            pro_printf("标定结果:标定通过\n");
          else
            pro_printf("标定结果:标定未通过\n");
          delay1us(10000);
          if(SysSeting.Msrefer)
            pro_printf("标定基准:前基准\n");
          else
            pro_printf("标定基准:后基准\n");
          delay1us(10000);
          if(SysSeting.Flag_free)
            pro_printf("开机自动运行连续测量\n");
          else
            pro_printf("开机不自动运行\n");
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
          //pro_printf("量程下限:%dm\n",SysSeting.RangeMin);
          //delay1us(10000);
          if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
            pro_printf("Pulse frequency:4000HZ\n");
          else
            pro_printf("Pulse frequency:20000HZ\n");
          delay1us(10000);
          pro_printf("Switch threshold:%dm\n",SysSeting.SWvalue);
          delay1us(10000);
          pro_printf("Calibration temperature:%f1℃\n",SysSeting.Ctemper);
          //delay1us(10000);
          //pro_printf("标定高压:%dPWM\n",SysSeting.PWM_rxHV);
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
//------------程序功能：保存设置参数
void SettingSave(void)
{
    Flash_WriteData(EEP_SYSTEM_SETTING, (u8*)&SysSeting, sizeof(SysSeting));
    //写入缓冲区
    EE_Flash_Write_All_Contents();
    //写入FLASH
}
//------------程序功能：AGC值设置
void tlc5618_setting(void)
{
  //tlc5618_execute(SysSeting.APD_HV, SysSeting.AGC_HV);
  tlc5618_execute(LD_MD,500);//（LDV，AGC）//tx[1500]--68.4v,1400-89.3v,0.22v/DAC,1600--60v,1700--35v
  //
}
//------------程序功能：从flash读取系统配置参数
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
    //dist_num =10000/SysSeting.OutputHZ;//上电测量速度设置
    if(SysSeting.PulseHZ==Pulse_freq_20KHZ){
        dist_collect_tim_cnt = 200;
    }else if(SysSeting.PulseHZ==Pulse_freq_4KHZ){
        dist_collect_tim_cnt = 50;
    }else
       dist_collect_tim_cnt = 50;

     BSP_USART_Config(SysSeting.BaudRate);//设置波特率
    //BSP_USART_Config(BAUDRATE_115200);
}
//------------程序功能：读取基准
//输入参数：dat
//输出参数：无
void CMD_ReadStandard(int dat)
{
  if(SysSeting.Msrefer)
  {
   if(SysSeting.Language == 1)
    pro_printf("现在是前基准！\n");
   else
    pro_printf("Now is front base！\n");
    //pro_printf("Now is RearStandard\n");
  }
  else
  {
   if(SysSeting.Language == 1)
    pro_printf("现在是后基准！\n");
   else
    pro_printf("Now is back base！\n");

    //pro_printf("Now is FrontStandard\n");
  }
}
//------------程序功能：设置基准
//输入参数：dat
//输出参数：dst_standard
void CMD_SetStandard(int dat)
{
  SysSeting.Msrefer=dat;
  if(dat)
  {
    if(SysSeting.Language == 1)
     pro_printf("前基准设置成功！\n");
    else
     pro_printf("Front base set ok！\n");
    //pro_printf("SetRearStandard OK\n");
  }
  else
  {
    if(SysSeting.Language == 1)
     pro_printf("后基准设置成功！\n");
    else
     pro_printf("Back base set ok！\n");
    //pro_printf("SetFrontStandard OK\n");
  }
  SettingSave();
}
//------------程序功能：读取开关量结果
//输入参数：dat
//输出参数：dst_standard
void CMD_ReadBool(int dat)
{
  flag_disBool=1;
  MeasStatus = SINGLE_MEAS;
}
//------------程序功能：设置开关量门限
//输入参数：dat
//输出参数：dst_standard
void CMD_SetThd(int dat)
{
  SysSeting.SWvalue=dat;
  if(SysSeting.Language == 1)
    pro_printf("开关量门限设置成功！\n");
  else
    pro_printf("Switch threshold setting is ok！\n");
  SettingSave();
}
//------------程序功能：读取开关量门限
//输入参数：dat
//输出参数：dst_standard
void CMD_ReadThd(int dat)
{
  //ThresholdBool=dat;
  if(SysSeting.Language == 1)
    pro_printf("开关门限为: %dm\n",SysSeting.SWvalue);
  else
    pro_printf("Switch threshold is: %dm\n",SysSeting.SWvalue);

}
//------------程序功能：单次测量
//输入参数：dat
//输出参数：MeasStatus
void CMD_SingleMeas(int dat)
{
  MeasStatus = SINGLE_MEAS;
  Flag_NormalTest=0;
  Contrl_635LD(0);//打开激光瞄准
}
//------------程序功能：开始测量命令
//输入参数：dat
//输出参数：MeasStatus
void CMD_StartContisMeas(int dat)
{
	if(MeasStatus != CONTINUE_MEAS)
	{
		MeasStatus = CONTINUE_MEAS;
    	Flag_NormalTest=0;//清除带信号测量标志
    	Contrl_635LD(0);
 	}


    //pro_printf("MS:ok\n");
}
//------------程序功能：停止测量命令
//输入参数：dat
//输出参数：MeasStatus
void CMD_StopContisMeas(int dat)
{
    MeasStatus = STOP_MEAS;
    FreeRun = 0;
    Contrl_635LD(1);//关闭激光瞄准

}

//------------程序功能：最大最小值连续测量
//输入参数：dat
//输出参数：MeasStatus
void CMD_MaxMinMeas(int dat)
{
  MeasStatus = MAXMIN_MEAS;
  dstMax=0;
  dstMin=0;//清除最大最小值缓冲区
}
//------------程序功能：停止测量进入功耗模式
//输入参数：dat
//输出参数：MeasStatus
void CMD_SleepDown(int dat)
{
  MeasStatus = STOP_MEAS;//清除测量标志
  FlagSleep=1;//设置睡眠标志
  if(SysSeting.Language == 1)
    pro_printf("进入睡眠状态...\n");
  else
    pro_printf("go sleep...\n");
}
//------------程序功能：波特率设置命令
//输入参数：dat
//输出参数：SysSeting.BaudRate
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
                pro_printf("设置成功!\n");
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
            pro_printf("设置失败!\n");
        else
           pro_printf("Set error!\n");
    }
}
//------------程序功能：设置测量速度，同过修改平均测量次数实现
//输入参数：dat
//输出参数：dist_num
void CMD_SetOutputHZ(int dat)
{
  if(MeasStatus != 0)
    return;

  if(dat == 0){
    pro_printf("设置必须大于1\r\n");
    return ;
  }
  int tmv_set = 1000000/dat - 1;
  if(dat <= 15){//设置频率低于阀值时，需要调整定时器值以及定时器计数值
    tmv_set = 999;
    OutputTimeStr.SuposOutputHzCnt = 1000/dat;//1000 = 1秒
  }else{
    OutputTimeStr.SuposOutputHzCnt = 0;
  }
  hr_TimerBaseInit(TIM3,63,tmv_set);
  unsigned char tmpbuf[100]={0};
  sprintf(tmpbuf,"设置输出频率%dHZ %d\r\n",dat,OutputTimeStr.SuposOutputHzCnt);
  pro_printf(tmpbuf);
  SysSeting.OutputHZ = dat;
  SettingSave();
}
//------------程序功能：设置脉冲重复频率，同过修脉冲间隔时间实现
//输入参数：dat
//输出参数：dist_num
extern u16 dist_collect_tim_cnt;
void CMD_SetPulseHZ(int dat)
{
  if(dat)//重复率设置到20Khz的同时调整输出率
  {
    if(SysSeting.PulseHZ==Pulse_freq_20KHZ)
    {
      dist_collect_tim_cnt = 200;
    }
    else//重复率改变，同时匹配输出率4-->20
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
    else//重复率改变，同时匹配输出率20-->4
    {
      SysSeting.PulseHZ=Pulse_freq_4KHZ;
      dist_collect_tim_cnt = 50;
    }
  }
  if(SysSeting.Language == 1)
    pro_printf("设置成功!\n");
  else
    pro_printf("Set ok!\n");
  SettingSave();
}

//------------程序功能：设置量程，修改量程上限实现
//输入参数：dat
//输出参数：SysSeting.Range
void CMD_SetRange(int dat)
{
    if(dat>0 && dat<= 400) // 400m
    {
        SysSeting.RangeMax = dat;
        //DIST_MAX=dat*100;
        if(SysSeting.Language == 1)
           pro_printf("设置成功!\n");
        else
           pro_printf("Set ok!\n");
        SettingSave();
    }
    else
    {
        if(SysSeting.Language == 1)
           pro_printf("设置失败!\n");
        else
           pro_printf("Set error!\n");
    }
}

void CMD_GetRange(int dat)
{
  pro_printf("%d\n",SysSeting.RangeMax);
}

/*
//------------程序功能：设置/修改APD高压
//输入参数：dat
//输出参数：SysSeting.APD_HV
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
    //tlc5618_setting();APD高压已经修改为PWM方式
    pro_printf("MS:ok\n");
}
//------------程序功能：设置/修改AGC增益
//输入参数：dat
//输出参数：SysSeting.AGC_HV
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

//------------程序功能：显示ASCII指令集-用户
//输入参数：dat
//输出参数：打印版本号
void CMD_ASCII(int dat)
{
  if(SysSeting.Language == 1)
  {
      pro_printf("//=================迈测 LK02 指令集==================//\n");
      delay1us(10000);
      pro_printf(" MS:contis:连续测量!\n");
      delay1us(10000);
      pro_printf(" MS:single:单次测量!\n");
      delay1us(10000);
      pro_printf(" MS:stopcontis:停止连续测量\n");
      delay1us(10000);
      pro_printf(" MS:setbase1:设置基准为前基准!\n");
      delay1us(10000);
      pro_printf(" MS:setbase1:设置基准为后基准!\n");
      delay1us(10000);
      pro_printf(" MS:pulsefreq0:设置脉冲重复频率为4KHZ!\n");
      delay1us(10000);
      pro_printf(" MS:pulsefreq1:设置脉冲重复频率为20KHZ!\n");
      delay1us(10000);
      pro_printf(" MS:switchthd:设置开关量门限[0~量程]!\n");
      delay1us(10000);
      pro_printf(" MS:getswitch:获取开关量结果!\n");
      delay1us(10000);
      pro_printf(" MS:HZ:设置测量频率[10~1000HZ]!\n");
      delay1us(10000);
      pro_printf("======================结束========================\n");
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
//------------程序功能：设置电流环输出最大值
//输入参数：dat
//输出参数：current_MAX
void SetCurMax(int dat)
{
  if(dat<24&&dat>0)
  {
    SysSeting.MsCurrMax=dat;
    if(SysSeting.Language == 1)
       pro_printf("设置成功!\n");
    else
       pro_printf("Set ok!\n");
    SettingSave();
  }
  else
  {
    if(SysSeting.Language == 1)
       pro_printf("设置失败!\n");
    else
      pro_printf("Set error!\n");
  }
}
//------------程序功能：设置电流环输出最小值
//输入参数：dat
//输出参数：current_MAX
void SetCurMin(int dat)
{
  if(dat<24&&dat>0)
  {
    SysSeting.MsCurrMin=dat;
    if(SysSeting.Language == 1)
       pro_printf("设置成功!\n");
    else
       pro_printf("Set ok!\n");
    SettingSave();
  }
  else
  {
    if(SysSeting.Language == 1)
       pro_printf("设置失败!\n");
    else
       pro_printf("Set error!\n");
  }
}
//------------程序功能：读取电流环量程
//输入参数：dat
//输出参数：current_MAX
void GetCurSet(int dat)
{
  if(SysSeting.Language == 1)
    pro_printf("电流环量程为:%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
  else
    pro_printf("current loop range :%dmA~%dmA\n",SysSeting.MsCurrMin,SysSeting.MsCurrMax);
  delay1us(10000);
}
//------------程序功能：带信号连续测量
//输入参数：dat
//输出参数：current_MAX
void CMD_TestWithSig(int dat)
{
  Flag_NormalTest=1;//标准带信号测量
  MeasStatus = CONTINUE_MEAS;
}
//------------程序功能：不带信号测量
//输入参数：dat
//输出参数：current_MAX
void CMD_TestWithoutSig(int dat)
{
    Flag_NormalTest=0;
    MeasStatus = CONTINUE_MEAS;
}
//------------程序功能：读取出厂设置
//输入参数：dat
//输出参数：current_MAX
void CMD_ReadFactorySettings(int dat)
{
  Flag_SetingDis=1;
  EE_Flash_Read_All_Contents();
  SettingRead();
}
//------------程序功能:设定标定距离
//输入参数：dat
//输出参数：CalNormDist
void CMD_SetCal(int dat)
{
 CalNormDist=dat*100;
 if(SysSeting.Language == 1)
    Printf("标定距离设定为%dm:\n",dat);
 else
    Printf("Set the calibration distance %dm:\n",dat);
 delay1us(100000);
}
//------------程序功能：开始标定
//输入参数：dat
//输出参数：current_MAX
void CMD_StartCal(int dat)
{
  EE_Flash_Read_All_Contents();
  SettingRead();                            //读取FLASH标定区
  if((SysSeting.Cal1==0)&&(SysSeting.Cal2==0))//同时为0，为未标定
  {
    delay1us(20000);
    if(SysSeting.Language == 1)
       Printf("=============开始标定=============\n");
    else
       Printf("==========start calibration=======\n");
    delay1us(20000);
    Flag_Cal=1;//设置标定标志位
    Flag_NormalTest=1;//标准带信号测量
    MeasStatus = CONTINUE_MEAS;
    dist_collect_tim_cnt = 10;
  }
  else
  {
    if(SysSeting.Language == 1)
        Printf("错误：该机器已标定完成！\n");
    else
        Printf("Error: the machine calibration has been finished！\n");
    delay1us(10000);
  }

}
//------------程序功能：清除标定信息并恢复出厂设置
//输入参数：dat
//输出参数：current_MAX
void CMD_StopCal(int dat)//清除所有标定信息，并恢复默认出厂设置
{
  DefaultSetting();
  if(SysSeting.Language == 1)
       pro_printf("设置成功!\n");
  else
       pro_printf("Set ok!\n");
  SettingSave();
  delay1us(20000);
}
//------------程序功能：读取标定数据
//输入参数：dat
//输出参数：current_MAX
//=================标定信息====================
//SysSeting.APDV_LOW:220
//SysSeting.APDV_MID:306
//SysSeting.APDV_HIG:407
//4KhzCal_LOW:18CM
//4KhzCal_MDL:48CM
//4KhzCal_HIG:58CM
//20KhzCal_LOW:32CM
//20KhzCal_MDL:46CM
//20KhzCal_HIG:54CM
//4KhzGain_LOW:602  //梯度偏差PerAPDGain 110就是正常的，如果LOW过大，HIG过小则光学有问题
//4KhzGain_MDL:486
//4KhzGain_HIG:366
//20KhzGain_LOW:572
//20KhzGain_MDL:494
//20KhzGain_HIG:384
//TempCal:32.9℃
//标定通过！
//============================================\n
void CMD_ReadCal(int dat)
{
  delay1us(10000);
  if(SysSeting.Language == 1)
    pro_printf("=================标定信息====================\n");
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
 pro_printf("TempCal:%f1℃\n",SysSeting.Ctemper);
 delay1us(10000);
 if(SysSeting.Cal2)
 {
   if(SysSeting.Language == 1)
    Printf("标定成功！\n");
   else
    Printf("Calibration success！\n");
 }
 else
 {
  if(SysSeting.Language == 1)
   Printf("标定失败！\n");
  else
   Printf("Calibration failure！\n");
 }
 delay1us(10000);
 pro_printf("============================================\\n\n");
}
//------------程序功能：QC检测
//检测目的：检测4KHZ和20KHZ脉冲频率下的测量精度
//运行方式：QC检测标志位置位，先后打印4、20KHZ时的数据，并对比结果
//输入参数：dat
//输出参数：current_MAX
void CMD_QCtest(int dat)
{
  delay1us(20000);
  if(SysSeting.Language == 1)
    Printf("=============开始品检=================\n");
  else
    Printf("=============START QC TEST============\n");
  delay1us(20000);
  Flag_QCTEST=1;
  QC_DIST=dat*100;
  MeasStatus= CONTINUE_MEAS;
  Flag_NormalTest=0;
  QC_NUB=0;
}
//------------程序功能：停止QC检测
//输入参数：dat
//输出参数：current_MAX
void CMD_StopQCtest(int dat)
{
  QC_NUB=0;
  Flag_QCTEST=0;
  MeasStatus = STOP_MEAS;
  Flag_NormalTest=0;
  if(SysSeting.Language == 1)
    Printf("停止品检！\n");
  else
    Printf("QC TEST STOP！\n");
}
//------------程序功能:设置开机自动运行命令
//输入参数：dat
//输出参数：Flag_free
//Flag_free=0 开机不自动运行；Flag_free=1 开机自动连续测量
void CMD_FreeRun(int dat)
{
  SysSeting.Flag_free=0;
  SysSeting.CurMol = 2;
  //SysSeting.BaudRate = BAUDRATE_460800;
  //Printf("输出配置:\r\n460800波特率\r\n5K输出频率\r\n上电自动执行\r\n");
  SettingSave();
  Printf("本软件为通讯协议定制版本v1.0\r\n");

}

void CMD_SetLanguage(int dat)
{
  delay1us(10000);
  if(dat)
  {
    SysSeting.Language=1;
    Printf("当前语言为中文！\n");
  }
  else
  {
    SysSeting.Language=0;
    Printf("The current language is English！\n");
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
            Printf("电流设置成功:%dmA\r\n",dat);
        else
            Printf("Set current OK,%dmA\r\n",dat);
    }
    else
    {
        if(SysSeting.Language == 1)
            Printf("电流值错误!\r\n");
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
            Printf("当前电流标定成功:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[1] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[1] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[1] = current_data;
        if(SysSeting.Language == 1)
            Printf("当前电流标定成功:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[2] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[2] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[2] = current_data;
        if(SysSeting.Language == 1)
            Printf("当前电流标定成功:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[3] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[3] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[3] = current_data;
        if(SysSeting.Language == 1)
            Printf("当前电流标定成功:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else if((current_data > (CurrentMark[4] - DEMAR_OFFSET))
    &&(current_data < (CurrentMark[4] + DEMAR_OFFSET)))
    {
        SysSeting.CurrentDemar.CurrentDemar[4] = current_data;
        if(SysSeting.Language == 1)
            Printf("当前电流标定成功:%dmA\r\n",current_data/1000);
        else
            Printf("Set current demar OK,%dmA\r\n",current_data/1000);
    }
    else
    {
        if(SysSeting.Language == 1)
            Printf("Error current demar!\r\n");
        else
            Printf("错误的电流值!\r\n");
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
        Printf("电流标定值清除成功!\r\n");
    else
        Printf("clear current demar ok!\r\n");
}
void CMD_GetCurrDemar(int dat)
{
    if(SysSeting.Language == 1)
    {
        Printf("4mA   标定值: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[0]);
        Printf("8mA   标定值: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[1]);
        Printf("12mA  标定值: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[2]);
        Printf("16mA  标定值: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[3]);
        Printf("20mA  标定值: %f3mA\r\n",SysSeting.CurrentDemar.CurrentDemar[4]);
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
    Printf("设置成功!\n");
  else
    Printf("Set ok!\n");
  SettingSave();
}

void CMD_LedOn(int dat)
{
  Contrl_635LD(0);//打开激光瞄准
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
    sprintf(tPusBuf,"脉冲重复频率:20kHz\n");
  }else{
    sprintf(tPusBuf,"脉冲重复频率:4kHz\n");
  }
  sprintf(tOutpBuf,"%s输出频率:%dHz\n",tPusBuf,SysSeting.OutputHZ);
  Printf(tOutpBuf);
}

const T_CmdHandle HandleTab[] = {
    {"MS:contis",   CMD_StartContisMeas}, //开始连续测量
    {"MS:stopcontis",   CMD_StopContisMeas}, //停止连续测量
    {"MS:setbaudrate",   CMD_SetBaudrate},   //设置波特率
    {"MS:HZ",     CMD_SetOutputHZ},   //设置输出频率
    {"MS:setrange",  CMD_SetRange},      //设置量程
    //{"MS:APDHV",  CMD_APD_HV_Adj},    //调整APD高压
    //{"MS:AGCHV",  CMD_AGC_HV_Adj},    //调整AGC高压
    {"MS:version",CMD_GetVersion},    //获取版本信息
    {"MS:single", CMD_SingleMeas},     //单次测量
    {"MS:pulsefreq", CMD_SetPulseHZ},  //脉冲重复频率
    {"MS:setbase", CMD_SetStandard},   //设置基准
    {"MS:getbase", CMD_ReadStandard},  //读取基准
    //{"MS:getmaxmindis", CMD_MaxMinMeas},//连续测量最大最小值
    //{"MS:switchthd", CMD_SetThd},//设置开关量门限
    //{"MS:readswitchthd", CMD_ReadThd},//读取开关量门限
    //{"MS:getswitch", CMD_ReadBool},//读取开关量结果
    //{"MS:help", CMD_ASCII},//读取开关量结果
    //{"MS:currentmax", SetCurMax},//设置电流环最大值
    //{"MS:currentmin", SetCurMin},//设置电流环最小值
    //{"MS:getcurrent", GetCurSet},//读取电流环量程
    {"MS:withsignal", CMD_TestWithSig},//带信号测量
    {"MS:withnosignal", CMD_TestWithoutSig},//不带信号测量
    {"MS:setdemardis", CMD_SetCal},  //设定标定距离
    {"MS:mark1demar", CMD_StartCal},  //开始标定
    {"MS:clrdemar", CMD_StopCal},  //停止标定
    {"MS:getdemarinfo", CMD_ReadCal},  //读取标定信息
    //{"MS:setqcdis", CMD_QCtest},  //QC检测
    //{"MS:stopqctest", CMD_StopQCtest},  //停止QC检测
    {"MS:getsysinfo", CMD_ReadFactorySettings},//读取出厂信息
    //{"MS:sleep", CMD_SleepDown},//睡眠，进入待机模式
    //{"MS:setlanguage", CMD_SetLanguage},//设置语言
    //{"MS:setcurrout", CMD_SetCurrOut},//设置电流输出
    //{"MS:setcurrdemar", CMD_SetCurrDemar},//设置电流标定值
    //{"MS:clrcurrdemar", CMD_ClrCurrDemar},//清除电流标定值
    //{"MS:getcurrdemar", CMD_GetCurrDemar},//获取电流标定值
    {"MS:getaddress",CMD_LsAddress},//获取地址
    {"MS:setaddress",CMD_SetAddress},//设置地址
    {"MS:getrange",CMD_GetRange}, //查询量程
    {"MS:ledon",CMD_LedOn},//打开瞄准灯
    {"MS:ledoff",CMD_LedOff},//关闭瞄准灯
    {"MS:setfreerun", CMD_FreeRun},//设置自动运行命令
    //{"MS:QCgetHz",CMD_LsOutputHz},//过QC时查询输出频率和脉冲频率
};

const u8 MAX_CMD_NUM = 24;


