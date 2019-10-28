/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  IO���ܸ��£�
    1�������Դ���ƹ��ܣ����ж�/�򿪸�ѹ�����䡢���ա��Ƚϵ�·PORWER_CTL-PB1
    2������485ͨ��ʱ��ѡ����RS485_CTRL_PB8
    3���������ӿ����Ÿ��ģ�SPI1_M0_PB9��SPI1_MI_PC14��SPI_CLK_PC15��SPI_CS_PD1
    4�������ѹʹ��DAC���ƣ����ո�ѹ��ʹ�ö�ʱ��������ӦIOΪPA3/TIM2_CH4
    5��CONTROL_SMALL/PD0����С����������ʱ���κι���
  ******************************************************************************
  */
#include "global.h"
#include "stdio.h"

#define PerAPDGain      110//ÿ��APD����ת��ΪAD603���ڵ�DAC����  ͬһ������ȷ��APD�ȼ�������AGC��ֵ
#define AxRefer         1200.0//Ŀ���źŷ�ֵ 1.2V-0.9V֮��
#define DIST_AVR_NUM    2000
#define AGC_PEAK        1500 //AGC�������η�ֵ 1.2V-0.9V֮��
#define PtoVcoff        0.45 //PWM ת ��ѹֵ ϵ��
#define APD_TempCoff    1.4  //APD��Ưϵ��
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
u16 Ax=0;//��ǰ�źŷ�ֵ
u32 temper=0;//��ǰ�¶�ֵ
u8 FLAG_APD_AGC_adj=0;//����ʹ�ܱ�־ FLAG=1����ѹ������Ч ,FLAG=0:AGC������Ч
u8  FlagSleep=0;//˯�߱�־
u32 dstMax=0,dstMin=0;
u8  flag_disBool=0;//��ʾ��������־
u8   Flag_NormalTest=0;//��׼������־
u16  NormalCnt=0;
u8  Flag_Cal=0;
u16 CalNormDist=1000;//Ĭ�ϱ궨���� 10m
u8  Flag_QCTEST=0;
u16 QC_DIST=0;
u16 QC_NUB=0;
u16   Qc1,Qc2;
u8  FreeRun=0;
s16 Cal;
u8 Flag_ApdGn=0;//APD��LD����ѡ���־λ
u8 APDGainState=0;//����APD���浵λ
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
#define DIST_AX     700  //�����ż�

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

    PUSE_MAX=PulsePeakDetector();//����ֵ

    PEAK_ADC=PUSE_MAX;
    Ax=PUSE_MAX*3300/4096;//��ֵ-mv
	// zjk add 

    //return 0;//������
    //�궨ģʽ�µ�AGC���ڷ�ʽ--���ڴ�ѡ��APD���棬AGC����ʹ�����ƽ���ʽ
    if(Flag_Cal)
    {
      d_Vol=abs(PUSE_MAX-PUSE_OK);
      if(d_Vol<50){return 1;}//AGC����Ϊ50-bit ADC���ź���50mv��Χ��
      else if(d_Vol>500)  {adj_value=20;}//�źŲ���ϴ󣬴ֵ�
      else                {adj_value=2;}//�źŲ����С��ϸ��

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
    if((abs(PUSE_MAX-PUSE_OK))<100){return 1;}//������ʣ�100mv�ڲ���Ҫ����
//------------���ݷ�ֵ����ĵõ��������������ֵ------------------------------
    adj_value=(s16)250*log10((double)(Ax)/AxRefer);//�ܹ���Ҫ���ڵ�AJCֵ
    total_value=AGC_NOW-adj_value;//������ں�ĵ�ǰAJCֵ

//------------����AJC��ǰֵ�õ��´�APD��ѹ�ȼ��Լ����ۼ�����AGCֵ-----------
    if(total_value<AGC_MIN+1)//�������ޣ�����APD��ѹ����
    {
      if(!Flag_ApdGn)//�Ѿ������ѹ�ȼ�����
      {
        total_value=AGC_MIN;//AGCȡ���ֵ
        APDGainState=0;
      }
      else//�˴����ڵ������� Flag_ApdGn��=0�����ڲ�����ִ��=0�����µ�����
      {
        if(APDGainState<1){APDGainState=1;}//��ֹ���
        APDGainState-=1;
        total_value+=PerAPDGain;
      }
    }
    else if(total_value>AGC_MAX-1)//�������ޣ����APD����
    {
      if(Flag_ApdGn==2)//�Ѿ������ѹ�ȼ�����
      {
        total_value=AGC_MAX;//AGCȡ���ֵ
        APDGainState=2;
      }
      else//�˴����ڵ������� Flag_ApdGn��=2�����ڲ�����ִ��=2�����µ�����
      {
        if(APDGainState>1){APDGainState=1;}//��ֹ���
        APDGainState+=1;
        total_value-=PerAPDGain;
      }
    }
    else//����ȼ�ʹ����������
    {
      //AGC�������������ڱ仯������Ҫ�ı��ѹ�ȼ�
    }
//------------�������۵�AGC����ֵѡ��ƫ�õĵ�ѹ����ȼ��������ת���Ժ�ĵ�ѹ�ȼ��Լ�AGC���棨����ֵ����ֱ�Ӹ���-----------
//****�˴������������׼ȷ�Ⱥ�PerAPDGain�����йأ����Ҳ�ͬ�����¿��ܲ�ͬ****
//�˴���֤  AD603���澡���ܵͣ���֤����� ��֤�ܵķŴ�������
    switch(APDGainState)
    {
      case 0:
        if(total_value>600)//AD603ֵ ����ֵ
        {
          APDGainState=1;
          total_value-=PerAPDGain;
        }break;
      case 1:
        if(total_value<470)//�е������������� 250+120=370<420
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

    Slect_Gain(APDGainState);//����APD���浵
    AGC_NOW=set_AGC_Gn(adj_endvalue);//tlc5618_execute(LD_VAL,adj_endvalue);

    return 1;
}
//---------APD_VOL--------------------
//905nmAPD Change of VBR with temperature 1.25~1.55V/K,use 1.4v/k
u8 APD_HV_AdjWithTemper(void)
{
    u32 vol;

    vol = GetADCResult(ADC_Channel_0);

    temper=(vol*100 - 74400)/119;/* T (��C) = (V OUT - 744mV) / 11.9mV/��C *///�������10

    return temper;
}

//�����˲���
//**ȷ���˲��ڲ�ͬ�����Ƶ���¼����ʱ���
u32 FilterBublesort(u32 *p,u32 n)
 {
      u32 i,j,k;
      u64 Sum_Arry=0;
      if(!n)
        {return 0;}
      if(n<51)//50����������ð����������ֱ��ƽ��
      {
        for(j=0;j<n;j++)   /* ���ݷ�Ҫ����n��*/
        {
             for(i=0;i<n-j;i++)  /* ֵ�Ƚϴ��Ԫ�س���ȥ��ֻ��ʣ�µ�Ԫ���е����ֵ�ٳ���ȥ�Ϳ����� */
             {
                  if(*(p+i)>*(p+i+1))  /* ��ֵ�Ƚϴ��Ԫ�س����� */
                  {
                       k=*(p+i);
                       *(p+i)=*(p+i+1);
                       *(p+i+1)=k;
                  }
             }
        }
      }
     if(n<=6)//������Сʱ��ȡ��ֵ
     {
        return *(p+i/2+1);
     }
     else//�����ϴ�ʱ��ȡ�޷�ƽ��ֵ
     {
       for(i=3;i<n-3;i++)//ȥ�������Сֵ
       {
         //Printf("%d\r\n",*(p+i));
         Sum_Arry+=*(p+i);//���
       }
       return Sum_Arry/(n-6);//ƽ��
     }
 }

//-------------------------------------------
void TurnDACOutput(u32 Distance)
{
  u16  ItoDac=0;
  u16  DsttoI=0;
  if(Distance<100)//ä������
  {
    DsttoI=SysSeting.MsCurrMin*1000;
    ItoDac=(u16)DsttoI*(65536)/(24000) - 1;
  }
  else
  {
  DsttoI=(Distance - SysSeting.RangeMin*100)*1000*(SysSeting.MsCurrMax-SysSeting.MsCurrMin)/(SysSeting.RangeMax*100 - SysSeting.RangeMin*100)+SysSeting.MsCurrMin*1000;//������λΪuA
  ItoDac=(u16)DsttoI*(65536)/(24000) - 1;
  }
  ExDAC_WriteDat(ItoDac);
}

//����635����ָʾ�� 1-close 0-open
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
���ܣ���ѹ��·�����յ�·�������·�ϵ綯��
˳�򣺸�ѹ��Դ����->��ѹ����������
      ���յ�Դ����->����AGC��������
      �����Դ����->������ƶ˳�ʼ�õ�
*/
void POWER_On_Init(void)
{
#define ENABLE_OUT_CURRENT
  gp22_init(); //GP22��ʼ��
  ExDAC_Init();//��������ʼ��
  //ExDAC_WriteDat(0x800);
  tlc5618_init();//DACоƬ��ʼ��
  TX_PULSE_LOW();//���巢�䴥���ر�
  SetPortB1Low();//����ģ���Դ��,������ո�ѹ��Դ
  AGC_CTRL_LOW();//��ֵ�첨���ͣ����ڼ첨״̬
  Contrl_635LD(1);//1-close 0-open 635������׼�ر�
  //--
  PWMSet_APD(SysSeting.APDV_LOW);//�ϵ�Ĭ��APD����ѡ��LOW//APD_LO
  set_AGC_Gn(500);//AGC�����ϵ����ã��е�
  set_LD_HV(LD_LO);//Ĭ��ѡ��͵�����
  delay1us(100000);//

  //RS485_CTRL_Recieve();
//  RS485_CTRL_DRIVER();
//  delay1us(200000);
//  RS485_CTRL_Recieve();

}
//-------------------------------------------
/*
���ܣ���ѹ��·�����յ�·�������·�ϵ綯��
˳�򣺸�ѹ��Դ�Ͽ�->��ѹ����������
      ���յ�Դ�Ͽ�->����AGC��������
      �����Դ�Ͽ�->������ƶ˳�ʼ�õ�
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
  SetPortB1Low();//����ģ���Դ�ر�
  delay1us(100000);//100ms delay
}

//��ʾ�����Сֵ
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

//�궨�����Ӻ���
//���룺�궨���ظ�Ƶ��
//��������ظ�Ƶ����:����HI�µ�CAl_HI������LOW�µ�CAL_LO�������궨���
void Cal_hdl(u16 Freq_Ps,u8 gain)
{
    SysSeting.PulseHZ=Freq_Ps;//���������ظ�Ƶ��
    Slect_Gain(gain);//ѡ������

    //--------------�궨ʱ��----------------//
    cal_cnt++;

    if((cal_cnt>500)&&(abs(PEAK_ADC-AGC_PEAK)<50))//����50�����ϣ���AGC���ڴﵽ�ȶ�
      {
        //�ж���ʱ�궨�ľ����Ƿ���ȷ
        //�������ݴ�ӡ
        Cal=dist-CalNormDist;//�п���Ϊ����
        delay1us(20000);

        if(SysSeting.Language == 1)
            Printf("\n�궨��ֵ��%dCM\n",Cal);
        else
            Printf("\nCalibration difference��%dCM\n",Cal);

        delay1us(20000);
        if(abs(Cal)>300)//�������Ƿ����3��,�궨ʧ�ܣ�
        {
          Cal=0;
          delay1us(20000);


              Printf("%dHZ�궨ʧ��: ����������\n",Freq_Ps);
              delay1us(20000);
              Printf("==============�궨ʧ��======================\n\n");



          delay1us(20000);
          //�˳��궨ģʽ
          Flag_Cal=0;//ֹͣ�궨
          Flag_NormalTest=0;//��׼���źŲ���
          MeasStatus = STOP_MEAS;
          cal_cnt=0;
        }
        else//===============�궨�ɹ�=================
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


            Printf("%dHZ�궨���!\n",Freq_Ps);

          SysSeting.Ctemper=temper;//��¼�궨ʱ�ĸ�ѹֵ���¶�ֵ
          SettingSave();
          cal_cnt=0;

        }
      }
    else if(cal_cnt>800)//AGC�޷����ڵ�����ֵ���궨ʧ��!
      {
        Cal=0;
        delay1us(10000);


        Printf("%dHZ�궨ʧ��: �źŲ�������\n",Freq_Ps);
        delay1us(10000);
        Printf("==============�궨ʧ��======================\n\n");
        NVIC_SystemReset();
        //�˳��궨ģʽ
        Flag_Cal=0;//ֹͣ�궨
        Flag_NormalTest=0;//��׼���źŲ���
        MeasStatus = STOP_MEAS;
        cal_cnt=0;
      }

}

//��ȡAPD��ѹ������
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
        Ax=PulsePeakDetector()*3300/4096;//��ֵ-mv
        //Printf("Ax=%d\n",Ax);
        if(Ax>AxRefer)
          pw_Apd=PWM_Adj_APD(-1);//��ֵ�ߣ���ѹ�µ�
        else
          pw_Apd=PWM_Adj_APD(1);
        delay1us(50000);//2ms wait for apd_vot steady
      }
    }while(fabs(Ax-AxRefer)>20);//��ֵ��20mv������� ���ڳɹ�
  return pw_Apd;
}

//����ʵ��ó�10�״�������Ϊ���ʵ�AGC�����Ϊ��
/*
4Klow=600��4Kmid=475��4Khig=350�������125bit�������5db
*/
void Cal_APDV(void)
{
  if(!SysSeting.APDV_Cal)//��˳��궨������λ�ĸ�ѹֵ,ֻ��һ��
  {
    /*
    Ax=0;
    tlc5618_execute(LD_LO,AGC_4K_LOW);//�̶�AGC����
    PWMSet_APD(APD_LO);//��ʼ����ֵ
    delay1us(100000);//10ms�ȴ���ѹ�ȶ�
    SysSeting.APDV_LOW=get_APD_vot();
    Printf("APDV_LOW:%d\n",SysSeting.APDV_LOW);

    Ax=0;
    tlc5618_execute(LD_MD,AGC_4K_MID);//�̶�AGC����
    PWMSet_APD(APD_MD);//��ʼ����ֵ
    delay1us(100000);//10ms�ȴ���ѹ�ȶ�
    SysSeting.APDV_MID=get_APD_vot();
    Printf("APDV_MID:%d\n",SysSeting.APDV_MID);

    Ax=0;
    tlc5618_execute(LD_HI,AGC_4K_HIG);//�̶�AGC����
    PWMSet_APD(APD_HI);//��ʼ����ֵ
    delay1us(100000);//10ms�ȴ���ѹ�ȶ�
    SysSeting.APDV_HIG=get_APD_vot();
    Printf("APDV_HIG:%d\n",SysSeting.APDV_HIG);
    SysSeting.APDV_Cal=1;
    //�����궨��ʼ��
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
//�궨
//���ȹ̶�����AGC����궨��������APD��ѹ
//�궨ʱ�̶�����Ƶ��Ϊ10HZ
u8 CAlMEASURE(void)
{
  if(Flag_Cal)
  {
    Cal_APDV();//�궨��ѹֵ
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

    if(SysSeting.Cal2_HI)//���һ�����ݱ궨��ɺ��˳��궨ģʽ
    {
      SysSeting.CurMol = 1;
      SettingSave();
      Flag_Cal=0;//ֹͣ�궨
      Flag_NormalTest=0;//��׼���źŲ���
      MeasStatus = STOP_MEAS;
      cal_cnt=0;
      Slect_Gain(LOW);//�ָ�������ģʽ
      delay1us(10000);

        Printf("=================�궨�ɹ�=================\n\n");

      delay1us(10000);
      NVIC_SystemReset();
    }
  }
  return 1;
}
//������� ��ȥ�̶���ֵ
u32 range_Get(u32 d)
{
  u32 d_cal=0;
  if(!Flag_Cal)//�Ǳ궨ģʽ��
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
    return d;//�궨ģʽ��
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

//�����������
void meas_range(void)
{
  u8  bool_out=0;
  int ret;
  u32 dist_tim;
  u8 txbuf[12]={0};
  u16 temp=0;
  u8 tmpbuf[20] = {0};
  u8 tmpsize = 0;
  ret = trigger_pulse(&dist);//����ʱ��
  dist_tab[dist_ok++] =dist;//�����˲�������
  dist_cnt++;
  if(dist_cnt>=dist_collect_tim_cnt)//ƽ������Ϊdist_num
  {
      APD_HV_AdjWithTemper();//�¶Ȳɼ�
      dist_tim=FilterBublesort(dist_tab,dist_ok);//��ȡʱ�䣬�������˲�
      //dist_tim = dist;//dist_tab[0];
      dist =CalcDistance(dist_tim);//����ʱ�������룬�Լ������궨
      //�궨���ݴ���**��������Ƶ��ѡ��궨����
      dist=range_Get(dist);
      //------------------��׼
      if(SysSeting.Msrefer){dist-=12;}//ѡ��ǰ��׼
      //------------------�궨
      //CAlMEASURE();
      if((dist<SysSeting.RangeMax*100)&&(dist>0))//�������õ�400������SysSeting.RangeMin*100
      {
        dist_final = dist;
        //TurnDACOutput(dist);//��ӵ��������
        if(dist<SysSeting.SWvalue*100)
        {bool_out=0;}
        else
        {bool_out=1;}        //���������
        if(MeasStatus == MAXMIN_MEAS)//ʹ�������Сֵ��ʽ��ӡ
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
                LittleCopy_32(&txbuf[3],(u8*)&dist,1);// 4 bytes����
                txbuf[7] = 0;
                txbuf[8] = bool_out;
                temp = CRC16(txbuf,7);
                txbuf[9] = temp&0xff;//��λ��ǰ
                txbuf[10] = temp>>8; //��λ�ں�
                put_string((char *)txbuf, 11);
            }
            flag_disBool=0;//��������ӡֻ���ڵ��β���
          }
          else if(Flag_NormalTest)//���źŲ���
          {
            if(++NormalCnt>10)//50
            {
              //ȫ����Ax��1.2V���Ҿ��������ģ�Զ������ܻ�ƫС����С0.6v �ż�
              if(ProtocolType == PROTOCOL_ASCII)
                Printf("%f2m,%dmv,%f1��,%d,%dlv\r\n",dist,Ax,temper,AGC_NOW,Flag_ApdGn);
              //Printf("%f2m,%dmv,%f1��,%d,%d\r\n",dist,Ax,temper,AGC_NOW,dstMax);
              NormalCnt=0;
            }
          }
          else
          {
            if(!Flag_QCTEST)//�Ƿ����QC���
          //====================================//ֱ�Ӵ����������
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
                    LittleCopy_32(&txbuf[3],(u8*)&dist,1);// 4 bytes����
                    temp = CRC16(txbuf,7);
                    txbuf[7] = temp&0xff;//��λ��ǰ
                    txbuf[8] = temp>>8; //��λ�ں�
                    put_string((char *)txbuf, 9);
                    */
                }
            }
          //====================================//
            else//QC���
            {
              QC_NUB++;
              if(QC_NUB<100)//4KHZ���
              {
                SysSeting.PulseHZ=Pulse_freq_4KHZ;

                if(QC_NUB==99)
                {
                  Qc1=abs(dist-QC_DIST);
                  if((!SysSeting.Cal1)&&(!SysSeting.Cal2))//�ж��궨�Ƿ�ͨ��
                  {
                    if(SysSeting.Language == 1)
                        Printf("�궨δͨ����\n");
                    else
                        Printf("Calibration failure��\n");
                  }
                  else
                  {
                   if(SysSeting.Language == 1)
                    Printf("�궨ͨ����\n");
                   else
                    Printf("Calibration success��\n");

                  }
                  delay1us(20000);
                  if(SysSeting.Language == 1)
                   Printf("4KHZ��%f2m ƫ�%dcm\n",dist,Qc1);
                  else
                   Printf("4KHZ��%f2m deviation��%dcm\n",dist,Qc1);
                }
               }
              else if((QC_NUB>99)&&(QC_NUB<200))//20KHZ���
              {
                SysSeting.PulseHZ=Pulse_freq_20KHZ;
                if(QC_NUB==199)
                {
                  Qc2=abs(dist-QC_DIST);
                  if(SysSeting.Language == 1)
                   Printf("20KHZ��%f2m ƫ�%dcm\r\n",dist,Qc2);
                  else
                   Printf("20KHZ��%f2m error��%dcm\n",dist,Qc2);

                }
              }
              else
              {
                delay1us(20000);
                if((Qc1<10)&&(Qc2<10))
                {
                    if(SysSeting.Language == 1)
                       Printf("==============Ʒ��ͨ����============\n\n");
                    else
                       Printf("==============QC PASS��============\n\n");
                }
                else
                { if(SysSeting.Language == 1)
                    Printf("==============Ʒ��δͨ����============\n\n");
                  else
                   Printf("==============QC FAIL��============\n\n");
                }
                delay1us(20000);
                Flag_QCTEST=0;
                QC_NUB=0;
                MeasStatus = STOP_MEAS;
              }
            }//qc
          }//�����źŲ���
        }
				
				/*���β�������*/
        if(MeasStatus == SINGLE_MEAS){
          MeasStatus = STOP_MEAS;//=2Ϊ���β���
          Contrl_635LD(1);//�رռ�����׼
        }

        //TurnDACOutput(dist);
        //Printf("%f2m,%d,%d\r\n",dist,dist_tim,status_gp2);
        //put_string((char *)&dist, 4);//**modbusʹ�ø÷�ʽ
      }
      else//�����̻����źŵ���
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
            LittleCopy_32(&txbuf[3],(u8*)&dist,1);// 4 bytes����
            temp = CRC16(txbuf,7);
            txbuf[7] = temp&0xff;//��λ��ǰ
            txbuf[8] = temp>>8; //��λ�ں�
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
    SysParamInit();// ��ȡFlash����
    POWER_On_Init();//�ϵ��ʼ��
    StartAdcSample();//ADC��ʼ��
    Contrl_635LD(1);//�رռ�����׼
    TimerBoard_Init();

    while (1)
    {
      if(MeasStatus||FreeRun){
				zjk_test_count ++;   //zjk:������
          //if(SysSeting.CurMol != 2)
          //  Contrl_635LD(0);//�򿪼�����׼
          if(!Flag_FirstDist){//�״β�������
            dist_cnt=0;
            dist_ok=0;
            if(++i>1000){
              i=0;
              Flag_FirstDist=1;
            }
          }
          meas_range();//---------���--------//
          if(++j>6)  //--------AGC----------//
          {
            j=0;
            //APDLD_GAIN_ADJ();//APD/LD�������
            AGC_RX();//AD603�������
          }
          delay1us(50000/SysSeting.PulseHZ);//-----�����ظ�Ƶ�ʿ���------//
        }
        else
        {
          //Contrl_635LD(1);//�رռ�����׼
          Flag_FirstDist=0;
        }
        USART_CmdParse();
        GoSleep();
    }
}

