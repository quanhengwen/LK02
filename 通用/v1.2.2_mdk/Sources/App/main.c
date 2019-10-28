/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  IO功能更新：
    1，加入电源控制功能，可切断/打开高压、发射、接收、比较电路PORWER_CTL-PB1
    2，增加485通信时的选择功能RS485_CTRL_PB8
    3，电流环接口引脚更改：SPI1_M0_PB9、SPI1_MI_PC14、SPI_CLK_PC15、SPI_CS_PD1
    4，发射高压使用DAC控制，接收高压扔使用定时器做，对应IO为PA3/TIM2_CH4
    5，CONTROL_SMALL/PD0，和小板相连，暂时无任何功能
  ******************************************************************************
  */
#include "global.h"
#include "stdio.h"

#define PerAPDGain      110//每级APD调节转换为AD603调节的DAC格数  同一反射物确定APD等级后测出的AGC差值
#define AxRefer         1200.0//目标信号幅值 1.2V-0.9V之间
#define DIST_AVR_NUM    2000
#define AGC_PEAK        1500 //AGC调整波形峰值 1.2V-0.9V之间
#define PtoVcoff        0.45 //PWM 转 高压值 系数
#define APD_TempCoff    1.4  //APD温漂系数
#define PWM_TempCoff    (float)(APD_TempCoff/PtoVcoff)
#define AGC_4K_LOW      570
#define AGC_4K_MID      460
#define AGC_4K_HIG      360
//------------------------------------------------------------------------------
u32 dist_tab[DIST_AVR_NUM];
u32 cal_tab[100];
u16 cal_cnt =0;
u16 dist_cnt = 0;
u16 PEAK_ADC=0;
u16 dist_collect_tim_cnt = 0;
//------------------------------------------------------------------------------
u16 dist_ok = 0;   // ok data
u16 dist_err = 0;  // error data
u16 dist_tout = 0; // timeout
u32 dist_final = 0;
u32 dist=0;
u32 status_gp2=0;
//------------------------------------------------------------------------------
u16 dist_num = 100;//200,30;//12-1KHZ,24-500HZ,48-250HZ
u16 AGC_NOW=0;//AGC now value
//------------------------------------------------------------------------------
E_MEAS_STATE MeasStatus ; // 1,continue meas 2,sing meas,0,stop meas
u8 flag_meas=0;//
u8 flag_AGC_ok=0;
//------------------------------------------------------------------------------
u16 APDV_OK=0,APDV_BR=0;
u16 Ax=0;//当前信号峰值
u32 temper=0;//当前温度值
u8 FLAG_APD_AGC_adj=0;//调节使能标志 FLAG=1：电压调节有效 ,FLAG=0:AGC调节有效
u8  FlagSleep=0;//睡眠标志
u32 dstMax=0,dstMin=0;
u8  flag_disBool=0;//显示开关量标志
u8   Flag_NormalTest=0;//标准测量标志
u16  NormalCnt=0;
u8  Flag_Cal=0;
u16 CalNormDist=1000;//默认标定距离 10m
u8  Flag_QCTEST=0;
u16 QC_DIST=0;
u16 QC_NUB=0;
u16   Qc1,Qc2;
u8  FreeRun=0;
s16 Cal;
u8 Flag_ApdGn=0;//APD、LD增益选择标志位
u8 APDGainState=0;//设置APD增益档位
u16	LD_NOW=0;
u8  Flag_FirstDist=0;


extern T_SysParam SysSeting;
extern E_PROTOCOL_TYPE ProtocolType;

/*
SysSeting.BaudRate
SysSeting.OutputHZ
SysSeting.Range
SysSeting.PulseHZ
SysSeting.SWvalue
SysSeting.Cal1
SysSeting.Cal2
SysSeting.Ctemper
SysSeting.PWM_rxHV
SysSeting.Msrefer
SysSeting.MsCurrMax
SysSeting.MsCurrMin
SysSeting.Address
*/

#define APDV_MAX    140
#define APDV_MIN    120
#define DIST_AX     700  //测量门槛

u16 PulsePeakDetector(void)
{
    u16 vol;
    vol = GetADCResult(ADC_Channel_1);
    //Printf("PUSE_MAX:%d\r\n",vol);
    delay1us(10);
    AGC_CTRL_HIGH();//discharge
    delay1us(50);
	AGC_CTRL_LOW();
	return vol;
}
//---------AGC_Rx---------------------

float zjk_adc_volt=0;
u16  AGC_RX(void)
{
	u16	PUSE_OK=AGC_PEAK ,PUSE_MAX=0,d_Vol=0;
    u16 Vot_apd=130;
    s16 adj_value=0;
    s16 total_value=0,adj_endvalue=0;

    PUSE_MAX=PulsePeakDetector();//检测峰值

    PEAK_ADC=PUSE_MAX;
    Ax=PUSE_MAX*3300/4096;//幅值-mv
	// zjk add 

    //return 0;//调试用
    //标定模式下的AGC调节方式--不在此选择APD增益，AGC增益使用逐点逼近方式
    if(Flag_Cal)
    {
      d_Vol=abs(PUSE_MAX-PUSE_OK);
      if(d_Vol<50){return 1;}//AGC精度为50-bit ADC，信号在50mv范围内
      else if(d_Vol>500)  {adj_value=20;}//信号差异较大，粗调
      else                {adj_value=2;}//信号差异较小，细调

      if(PUSE_MAX>PUSE_OK)
        {
          AGC_NOW=tlc5618_AGC_ADJ(0-adj_value);
         }
      else
        {
           AGC_NOW=tlc5618_AGC_ADJ(adj_value);
         }
      return 0;
    }
    if(!AGC_NOW){AGC_NOW=500;}
    if((abs(PUSE_MAX-PUSE_OK))<100){return 1;}//增益合适，100mv内不需要调节
//------------根据幅值计算的得到初步的增益调节值------------------------------
    adj_value=(s16)250*log10((double)(Ax)/AxRefer);//总共需要调节的AJC值
    total_value=AGC_NOW-adj_value;//增益调节后的当前AJC值

//------------根据AJC当前值得到下次APD电压等级以及理论计算后的AGC值-----------
    if(total_value<AGC_MIN+1)//增益下限，降低APD电压增益
    {
      if(!Flag_ApdGn)//已经到达电压等级下限
      {
        total_value=AGC_MIN;//AGC取最低值
        APDGainState=0;
      }
      else//此处调节的条件是 Flag_ApdGn！=0，在内部不会执行=0条件下的内容
      {
        if(APDGainState<1){APDGainState=1;}//防止溢出
        APDGainState-=1;
        total_value+=PerAPDGain;
      }
    }
    else if(total_value>AGC_MAX-1)//增益上限，提高APD增益
    {
      if(Flag_ApdGn==2)//已经到达电压等级上限
      {
        total_value=AGC_MAX;//AGC取最大值
        APDGainState=2;
      }
      else//此处调节的条件是 Flag_ApdGn！=2，在内部不会执行=2条件下的内容
      {
        if(APDGainState>1){APDGainState=1;}//防止溢出
        APDGainState+=1;
        total_value-=PerAPDGain;
      }
    }
    else//增益等级使用区域设置
    {
      //AGC调节在量程以内变化，不需要改变电压等级
    }
//------------根据理论的AGC增益值选择偏好的电压增益等级并计算出转化以后的电压等级以及AGC增益（理论值）并直接给出-----------
//****此处给出的增益的准确度和PerAPDGain精度有关，并且不同环境下可能不同****
//此处保证  AD603增益尽可能低，保证信噪比 保证总的放大倍数不变
    switch(APDGainState)
    {
      case 0:
        if(total_value>600)//AD603值 经验值
        {
          APDGainState=1;
          total_value-=PerAPDGain;
        }break;
      case 1:
        if(total_value<470)//中档增益下限设置 250+120=370<420
        {
          APDGainState=0;
          total_value+=PerAPDGain;
        }break;
      case 2:
        if(total_value<595)
        {
          APDGainState=1;
          total_value+=PerAPDGain;
        }break;
    }

    adj_endvalue=total_value;

    Slect_Gain(APDGainState);//设置APD增益档
    AGC_NOW=set_AGC_Gn(adj_endvalue);//tlc5618_execute(LD_VAL,adj_endvalue);

    return 1;
}
//---------APD_VOL--------------------
//905nmAPD Change of VBR with temperature 1.25~1.55V/K,use 1.4v/k
u8 APD_HV_AdjWithTemper(void)
{
    u32 vol;

    vol = GetADCResult(ADC_Channel_0);

    temper=(vol*100 - 74400)/119;/* T (°C) = (V OUT - 744mV) / 11.9mV/°C *///结果乘以10

    return temper;
}

//数据滤波，
//**确保滤波在不同的输出频率下计算耗时相等
u32 FilterBublesort(u32 *p,u32 n)
 {
      u32 i,j,k;
      u64 Sum_Arry=0;
      if(!n)
        {return 0;}
      if(n<51)//50个数据以内冒泡排序，以外直接平均
      {
        for(j=0;j<n;j++)   /* 气泡法要排序n次*/
        {
             for(i=0;i<n-j;i++)  /* 值比较大的元素沉下去后，只把剩下的元素中的最大值再沉下去就可以啦 */
             {
                  if(*(p+i)>*(p+i+1))  /* 把值比较大的元素沉到底 */
                  {
                       k=*(p+i);
                       *(p+i)=*(p+i+1);
                       *(p+i+1)=k;
                  }
             }
        }
      }
     if(n<=6)//数量较小时，取中值
     {
        return *(p+i/2+1);
     }
     else//数量较大时，取限幅平均值
     {
       for(i=3;i<n-3;i++)//去掉最大最小值
       {
         //Printf("%d\r\n",*(p+i));
         Sum_Arry+=*(p+i);//求和
       }
       return Sum_Arry/(n-6);//平均
     }
 }

//-------------------------------------------
void TurnDACOutput(u32 Distance)
{
  u16  ItoDac=0;
  u16  DsttoI=0;
  if(Distance<100)//盲区处理
  {
    DsttoI=SysSeting.MsCurrMin*1000;
    ItoDac=(u16)DsttoI*(65536)/(24000) - 1;
  }
  else
  {
  DsttoI=(Distance - SysSeting.RangeMin*100)*1000*(SysSeting.MsCurrMax-SysSeting.MsCurrMin)/(SysSeting.RangeMax*100 - SysSeting.RangeMin*100)+SysSeting.MsCurrMin*1000;//电流单位为uA
  ItoDac=(u16)DsttoI*(65536)/(24000) - 1;
  }
  ExDAC_WriteDat(ItoDac);
}

//设置635激光指示灯 1-close 0-open
void Contrl_635LD(u8 state)
{
	if(state)
		{
		CTL_LD635_H();
		}
	else
		{
		CTL_LD635_L();
		}
}


//-------------------------------------------
//-------------------------------------------
/*
功能：高压电路、接收电路、发射电路上电动作
顺序：高压电源工作->高压正反馈输入
      接收电源工作->接收AGC增益输入
      发射电源工作->发射控制端初始置低
*/
void POWER_On_Init(void)
{
#define ENABLE_OUT_CURRENT
  gp22_init(); //GP22初始化
  ExDAC_Init();//电流环初始化
  //ExDAC_WriteDat(0x800);
  tlc5618_init();//DAC芯片初始化
  TX_PULSE_LOW();//脉冲发射触发关闭
  SetPortB1Low();//功率模块电源打开,发射接收高压电源
  AGC_CTRL_LOW();//峰值检波拉低，处于检波状态
  Contrl_635LD(1);//1-close 0-open 635激光瞄准关闭
  //--
  PWMSet_APD(SysSeting.APDV_LOW);//上电默认APD增益选择LOW//APD_LO
  set_AGC_Gn(500);//AGC增益上电设置，中档
  set_LD_HV(LD_LO);//默认选择低档增益
  delay1us(100000);//

  //RS485_CTRL_Recieve();
//  RS485_CTRL_DRIVER();
//  delay1us(200000);
//  RS485_CTRL_Recieve();

}
//-------------------------------------------
/*
功能：高压电路、接收电路、发射电路断电动作
顺序：高压电源断开->高压正反馈输入
      接收电源断开->接收AGC增益输入
      发射电源断开->发射控制端初始置低
*/

u32 cal_dst(u32 dist1)
{
  float k=0.935,b=-0.0526;
  u32   real_val=0;
  return real_val=k*dist1+b;
}
void LOW_Pwoer(void)
{
  tlc5618_execute(1900,200);
}
void POWER_Off_Init(void)
{
  SetPortB1Low();//功率模块电源关闭
  delay1us(100000);//100ms delay
}

//显示最大最小值
void dis_maxmin(u32 d)
{
  if((dstMin==0)&&(dstMax==0)){dstMin=d;dstMax=d;}
  else
  {
    if(d<dstMin)
    {
      dstMin=d;
    }
    else if(d>dstMax)
    {
      dstMax=d;
    }
  }
  Printf("Max:%f2m, Min:%f2m\r\n",dstMax,dstMin);

}
//----sleep
void GoSleep(void)
{
  if(FlagSleep)
  {;}
  while(0);
}

//标定功能子函数
//输入：标定的重复频率
//输出：该重复频率下:增益HI下的CAl_HI和增益LOW下的CAL_LO，两个标定结果
void Cal_hdl(u16 Freq_Ps,u8 gain)
{
    SysSeting.PulseHZ=Freq_Ps;//设置脉冲重复频率
    Slect_Gain(gain);//选择增益

    //--------------标定时序----------------//
    cal_cnt++;

    if((cal_cnt>500)&&(abs(PEAK_ADC-AGC_PEAK)<50))//测量50次以上，且AGC调节达到稳定
      {
        //判定此时标定的距离是否正确
        //部分数据打印
        Cal=dist-CalNormDist;//有可能为负数
        delay1us(20000);

        if(SysSeting.Language == 1)
            Printf("\n标定差值：%dCM\n",Cal);
        else
            Printf("\nCalibration difference：%dCM\n",Cal);

        delay1us(20000);
        if(abs(Cal)>300)//误差距离是否大于3米,标定失败！
        {
          Cal=0;
          delay1us(20000);


              Printf("%dHZ标定失败: 距离误差过大！\n",Freq_Ps);
              delay1us(20000);
              Printf("==============标定失败======================\n\n");



          delay1us(20000);
          //退出标定模式
          Flag_Cal=0;//停止标定
          Flag_NormalTest=0;//标准带信号测量
          MeasStatus = STOP_MEAS;
          cal_cnt=0;
        }
        else//===============标定成功=================
        {
          if(Freq_Ps==Pulse_freq_4KHZ)
          {
            switch(gain)
            {
            case 0:
                SysSeting.Cal1=Cal;
                SysSeting.Gain1=AGC_NOW;
                break;
            case 1:
                SysSeting.Cal1_MD=Cal;
                SysSeting.Gain1_MD=AGC_NOW;
                break;
            case 2:
                SysSeting.Cal1_HI=Cal;
                SysSeting.Gain1_HI=AGC_NOW;
                break;
            default:break;
            }
          }
          else
          {
            switch(gain)
            {
            case 0:
                SysSeting.Cal2=Cal;
                SysSeting.Gain2=AGC_NOW;
                break;
            case 1:
                SysSeting.Cal2_MD=Cal;
                SysSeting.Gain2_MD=AGC_NOW;
                break;
            case 2:
                SysSeting.Cal2_HI=Cal;
                SysSeting.Gain2_HI=AGC_NOW;
                break;
            default:break;
            }
          }
          delay1us(10000);


            Printf("%dHZ标定完成!\n",Freq_Ps);

          SysSeting.Ctemper=temper;//记录标定时的高压值、温度值
          SettingSave();
          cal_cnt=0;

        }
      }
    else if(cal_cnt>800)//AGC无法调节到给定值，标定失败!
      {
        Cal=0;
        delay1us(10000);


        Printf("%dHZ标定失败: 信号不正常！\n",Freq_Ps);
        delay1us(10000);
        Printf("==============标定失败======================\n\n");
        NVIC_SystemReset();
        //退出标定模式
        Flag_Cal=0;//停止标定
        Flag_NormalTest=0;//标准带信号测量
        MeasStatus = STOP_MEAS;
        cal_cnt=0;
      }

}

//获取APD电压工作点
u16 get_APD_vot(void)
{
  u8    i=0;
  u16   pw_Apd=0;

    do
    {
      trigger_pulse(&dist);
      delay1us(210);//set freq to 4khz
      if(++i>20)// per 20 pulse AGC once
      {
        i=0;
        Ax=PulsePeakDetector()*3300/4096;//幅值-mv
        //Printf("Ax=%d\n",Ax);
        if(Ax>AxRefer)
          pw_Apd=PWM_Adj_APD(-1);//幅值高，电压下调
        else
          pw_Apd=PWM_Adj_APD(1);
        delay1us(50000);//2ms wait for apd_vot steady
      }
    }while(fabs(Ax-AxRefer)>20);//幅值在20mv误差以内 调节成功
  return pw_Apd;
}

//根据实验得出10米处三个较为合适的AGC增益点为：
/*
4Klow=600，4Kmid=475，4Khig=350，各相差125bit，即相差5db
*/
void Cal_APDV(void)
{
  if(!SysSeting.APDV_Cal)//按顺序标定三个档位的高压值,只跑一次
  {
    /*
    Ax=0;
    tlc5618_execute(LD_LO,AGC_4K_LOW);//固定AGC增益
    PWMSet_APD(APD_LO);//初始给定值
    delay1us(100000);//10ms等待高压稳定
    SysSeting.APDV_LOW=get_APD_vot();
    Printf("APDV_LOW:%d\n",SysSeting.APDV_LOW);

    Ax=0;
    tlc5618_execute(LD_MD,AGC_4K_MID);//固定AGC增益
    PWMSet_APD(APD_MD);//初始给定值
    delay1us(100000);//10ms等待高压稳定
    SysSeting.APDV_MID=get_APD_vot();
    Printf("APDV_MID:%d\n",SysSeting.APDV_MID);

    Ax=0;
    tlc5618_execute(LD_HI,AGC_4K_HIG);//固定AGC增益
    PWMSet_APD(APD_HI);//初始给定值
    delay1us(100000);//10ms等待高压稳定
    SysSeting.APDV_HIG=get_APD_vot();
    Printf("APDV_HIG:%d\n",SysSeting.APDV_HIG);
    SysSeting.APDV_Cal=1;
    //后续标定初始化
    */
    SysSeting.APDV_LOW=140;
    SysSeting.APDV_MID=260;
    SysSeting.APDV_HIG=380;
    SysSeting.APDV_Cal=1;
    Ax=0;
    Slect_Gain(1);
  }
  else
  {}
}
//标定
//首先固定三个AGC增益标定三个档的APD高压
//标定时固定测量频率为10HZ
u8 CAlMEASURE(void)
{
  if(Flag_Cal)
  {
    Cal_APDV();//标定高压值
    if(!SysSeting.Cal1)
      Cal_hdl(Pulse_freq_4KHZ,LOW);
    else if(!SysSeting.Cal1_MD)
      Cal_hdl(Pulse_freq_4KHZ,MDLL);
    else if(!SysSeting.Cal1_HI)
      Cal_hdl(Pulse_freq_4KHZ,HIGH);
    else if(!SysSeting.Cal2)
      Cal_hdl(Pulse_freq_20KHZ,LOW);
    else if(!SysSeting.Cal2_MD)
      Cal_hdl(Pulse_freq_20KHZ,MDLL);
    else if(!SysSeting.Cal2_HI)
      Cal_hdl(Pulse_freq_20KHZ,HIGH);

    if(SysSeting.Cal2_HI)//最后一个数据标定完成后，退出标定模式
    {
      SysSeting.CurMol = 1;
      SettingSave();
      Flag_Cal=0;//停止标定
      Flag_NormalTest=0;//标准带信号测量
      MeasStatus = STOP_MEAS;
      cal_cnt=0;
      Slect_Gain(LOW);//恢复低增益模式
      delay1us(10000);

        Printf("=================标定成功=================\n\n");

      delay1us(10000);
      NVIC_SystemReset();
    }
  }
  return 1;
}
//距离解算 减去固定差值
u32 range_Get(u32 d)
{
  u32 d_cal=0;
  if(!Flag_Cal)//非标定模式下
  {
    if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
    {
      switch(Flag_ApdGn)
      {
      case 0:
          d_cal=d-SysSeting.Cal1;
          break;
      case 1:
          d_cal=d-SysSeting.Cal1_MD;
          break;
      case 2:
          d_cal=d-SysSeting.Cal1_HI;
          break;
      default:break;
      }
    }
    else
    {
      switch(Flag_ApdGn)
      {
      case 0:
          d_cal=d-SysSeting.Cal2;
          break;
      case 1:
          d_cal=d-SysSeting.Cal2_MD;
          break;
      case 2:
          d_cal=d-SysSeting.Cal2_HI;
          break;
      default:break;
      }
    }
    return d_cal;
  }
  else
    return d;//标定模式下
}

u8 Packet(u8* pGetBuf,u32 distres)
{
  if(!pGetBuf)
    return 0;
  /*
  u8 numbuf[10];
  u8 index = 0;
  pGetBuf[0]=0x02;
  sprintf(numbuf,"%.6d",distres*10);
  index = strlen(numbuf);
  memcpy(pGetBuf+1,numbuf,index);
  pGetBuf[index+1] = 0x03;
  return index+2;
  */
  memset(pGetBuf,0x00,sizeof(pGetBuf));
  if(distres != 0){
    sprintf(pGetBuf,"---\r\n");
  }else{
    sprintf(pGetBuf,"%.1f\r\n",distres/100.0);
  }
  return 6;//(strlen(pGetBuf));
}

//脉冲测量函数
void meas_range(void)
{
  u8  bool_out=0;
  int ret;
  u32 dist_tim;
  u8 txbuf[12]={0};
  u16 temp=0;
  u8 tmpbuf[20] = {0};
  u8 tmpsize = 0;
  ret = trigger_pulse(&dist);//测量时间
  dist_tab[dist_ok++] =dist;//加入滤波缓冲区
  dist_cnt++;
  if(dist_cnt>=dist_collect_tim_cnt)//平均次数为dist_num
  {
      APD_HV_AdjWithTemper();//温度采集
      dist_tim=FilterBublesort(dist_tab,dist_ok);//读取时间，并加入滤波
      //dist_tim = dist;//dist_tab[0];
      dist =CalcDistance(dist_tim);//根据时间解算距离，以及初步标定
      //标定数据处理**根据脉冲频率选择标定数据
      dist=range_Get(dist);
      //------------------基准
      if(SysSeting.Msrefer){dist-=12;}//选择前基准
      //------------------标定
      //CAlMEASURE();
      if((dist<SysSeting.RangeMax*100)&&(dist>0))//量程设置到400米以内SysSeting.RangeMin*100
      {
        dist_final = dist;
        //TurnDACOutput(dist);//添加电流环输出
        if(dist<SysSeting.SWvalue*100)
        {bool_out=0;}
        else
        {bool_out=1;}        //开关量输出
        if(MeasStatus == MAXMIN_MEAS)//使用最大最小值方式打印
        {
          dis_maxmin(dist);
        }
        else
        {
          if(flag_disBool)
          {
            if(ProtocolType == PROTOCOL_ASCII)
                Printf("%f2m | %d\r\n",dist,bool_out);
            else if(ProtocolType == PROTOCOL_RTU)
            {
                txbuf[0]=SysSeting.Address;
                txbuf[1]=READ_HOLD_REG;
                txbuf[2] = 6;
                LittleCopy_32(&txbuf[3],(u8*)&dist,1);// 4 bytes距离
                txbuf[7] = 0;
                txbuf[8] = bool_out;
                temp = CRC16(txbuf,7);
                txbuf[9] = temp&0xff;//低位在前
                txbuf[10] = temp>>8; //高位在后
                put_string((char *)txbuf, 11);
            }
            flag_disBool=0;//开关量打印只限于单次测量
          }
          else if(Flag_NormalTest)//带信号测量
          {
            if(++NormalCnt>10)//50
            {
              //全量程Ax在1.2V左右就是正常的，远距离可能会偏小，最小0.6v 门槛
              if(ProtocolType == PROTOCOL_ASCII)
                Printf("%f2m,%dmv,%f1℃,%d,%dlv\r\n",dist,Ax,temper,AGC_NOW,Flag_ApdGn);
              //Printf("%f2m,%dmv,%f1℃,%d,%d\r\n",dist,Ax,temper,AGC_NOW,dstMax);
              NormalCnt=0;
            }
          }
          else
          {
            if(!Flag_QCTEST)//是否进行QC检测
          //====================================//直接串口数据输出
            {
              if(ProtocolType == PROTOCOL_ASCII){
                //tmpsize = Packet(tmpbuf,dist);
                //put_string((char *)tmpbuf, tmpsize);
                //delay1us(10000);
                if(SysSeting.CurMol != 2){
                  Printf("%f2m\r\n",dist);
                }
              }

                else if(ProtocolType == PROTOCOL_RTU)
                {
                    if(SysSeting.CurMol != 2){
                        Printf("%f2m\r\n",dist);
                    }
                    /*
                    txbuf[0]=SysSeting.Address;
                    txbuf[1]=READ_HOLD_REG;
                    txbuf[2] = 4;
                    LittleCopy_32(&txbuf[3],(u8*)&dist,1);// 4 bytes距离
                    temp = CRC16(txbuf,7);
                    txbuf[7] = temp&0xff;//低位在前
                    txbuf[8] = temp>>8; //高位在后
                    put_string((char *)txbuf, 9);
                    */
                }
            }
          //====================================//
            else//QC检测
            {
              QC_NUB++;
              if(QC_NUB<100)//4KHZ检测
              {
                SysSeting.PulseHZ=Pulse_freq_4KHZ;

                if(QC_NUB==99)
                {
                  Qc1=abs(dist-QC_DIST);
                  if((!SysSeting.Cal1)&&(!SysSeting.Cal2))//判定标定是否通过
                  {
                    if(SysSeting.Language == 1)
                        Printf("标定未通过！\n");
                    else
                        Printf("Calibration failure！\n");
                  }
                  else
                  {
                   if(SysSeting.Language == 1)
                    Printf("标定通过！\n");
                   else
                    Printf("Calibration success！\n");

                  }
                  delay1us(20000);
                  if(SysSeting.Language == 1)
                   Printf("4KHZ：%f2m 偏差：%dcm\n",dist,Qc1);
                  else
                   Printf("4KHZ：%f2m deviation：%dcm\n",dist,Qc1);
                }
               }
              else if((QC_NUB>99)&&(QC_NUB<200))//20KHZ检测
              {
                SysSeting.PulseHZ=Pulse_freq_20KHZ;
                if(QC_NUB==199)
                {
                  Qc2=abs(dist-QC_DIST);
                  if(SysSeting.Language == 1)
                   Printf("20KHZ：%f2m 偏差：%dcm\r\n",dist,Qc2);
                  else
                   Printf("20KHZ：%f2m error：%dcm\n",dist,Qc2);

                }
              }
              else
              {
                delay1us(20000);
                if((Qc1<10)&&(Qc2<10))
                {
                    if(SysSeting.Language == 1)
                       Printf("==============品检通过！============\n\n");
                    else
                       Printf("==============QC PASS！============\n\n");
                }
                else
                { if(SysSeting.Language == 1)
                    Printf("==============品检未通过！============\n\n");
                  else
                   Printf("==============QC FAIL！============\n\n");
                }
                delay1us(20000);
                Flag_QCTEST=0;
                QC_NUB=0;
                MeasStatus = STOP_MEAS;
              }
            }//qc
          }//不带信号测量
        }
				
				/*单次测量结束*/
        if(MeasStatus == SINGLE_MEAS){
          MeasStatus = STOP_MEAS;//=2为单次测量
          Contrl_635LD(1);//关闭激光瞄准
        }

        //TurnDACOutput(dist);
        //Printf("%f2m,%d,%d\r\n",dist,dist_tim,status_gp2);
        //put_string((char *)&dist, 4);//**modbus使用该方式
      }
      else//超量程或者信号低弱
      {
        dist_final = 0;
        if(MeasStatus == SINGLE_MEAS)
            MeasStatus = STOP_MEAS;

        if(ProtocolType == PROTOCOL_ASCII)
        {
          if(SysSeting.CurMol != 2){
            Printf("---\r\n");
          }
        }
        else if(ProtocolType == PROTOCOL_RTU)
        {
            if(SysSeting.CurMol != 2){
                Printf("---\r\n");
            }
            /*
            txbuf[0]=SysSeting.Address;
            txbuf[1]=READ_HOLD_REG;
            txbuf[2] = 4;
            dist = 0xFF000000;
            LittleCopy_32(&txbuf[3],(u8*)&dist,1);// 4 bytes距离
            temp = CRC16(txbuf,7);
            txbuf[7] = temp&0xff;//低位在前
            txbuf[8] = temp>>8; //高位在后
            put_string((char *)txbuf, 9);
            */
        }
      }

      CAlMEASURE();
      dist_ok = 0;
      dist_cnt = 0;
  }
}

//-------------------------------------------
#define pro_printf Printf

extern void TimerBoard_Init( void );

//232&485
uint32_t zjk_test_count=0;
int main(void)
{
    #define ENABLE_OUT_CURRENT
    u32 i=0,j=0;

    System_Init();
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0003000);
    SysParamInit();// 读取Flash数据
    POWER_On_Init();//上电初始化
    StartAdcSample();//ADC初始化
    Contrl_635LD(1);//关闭激光瞄准
    TimerBoard_Init();

    while (1)
    {
      if(MeasStatus||FreeRun){
				zjk_test_count ++;   //zjk:测试用
          //if(SysSeting.CurMol != 2)
          //  Contrl_635LD(0);//打开激光瞄准
          if(!Flag_FirstDist){//首次测量消抖
            dist_cnt=0;
            dist_ok=0;
            if(++i>1000){
              i=0;
              Flag_FirstDist=1;
            }
          }
          meas_range();//---------测距--------//
          if(++j>6)  //--------AGC----------//
          {
            j=0;
            //APDLD_GAIN_ADJ();//APD/LD增益调节
            AGC_RX();//AD603增益调节
          }
          delay1us(50000/SysSeting.PulseHZ);//-----脉冲重复频率控制------//
        }
        else
        {
          //Contrl_635LD(1);//关闭激光瞄准
          Flag_FirstDist=0;
        }
        USART_CmdParse();
        GoSleep();
    }
}

