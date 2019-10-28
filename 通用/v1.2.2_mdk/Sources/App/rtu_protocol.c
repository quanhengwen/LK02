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

extern T_SysParam SysSeting;
extern E_MEAS_STATE MeasStatus;
extern u16 dist_num;
extern u8 flag_disBool;
extern u32 dist_final;
//-----------------------------------------------------------------------------
#define pro_printf  mPrintf

//0 -- idle status 1 -- measuring
static unsigned char measure_flag = 0;
void CMD2_StartMeas(ModbusRequest *p_request, ModbusResponse *p_response)
{
    if(CONTINUE_MEAS != MeasStatus)
    {
        MeasStatus = CONTINUE_MEAS;
        if(measure_flag == 0)
        {
            measure_flag = 1;
            Contrl_635LD(0);//打开激光瞄准
        }
    }
    LittleCopy_32(p_response->Dat,(u8*)&dist_final,1);
    p_response->Len_or_Err = 4;
}
void CMD2_SingMeas(ModbusRequest *p_request, ModbusResponse *p_response)
{
    MeasStatus = SINGLE_MEAS;
}

void CMD2_StopMeas(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u16 tempval;
    measure_flag = 1;
    Contrl_635LD(1);//关闭激光瞄准
    LittleCopy_16((u8*)&tempval, p_request->Dat, 1);

    if(tempval == STOP_MEAS)
    {
        MeasStatus = STOP_MEAS;
    }
    else
    {
        p_response->FuncCode |=0x80;
        p_response->Len_or_Err = REG_DATA_ERR; //数据错误
    }
}
void CMD2_GetBase(ModbusRequest *p_request, ModbusResponse *p_response)
{
    p_response->Dat[0] = 0; //高位
    p_response->Dat[1] = SysSeting.Msrefer; //低位
    p_response->Len_or_Err = 2;
}
void CMD2_SetBase(ModbusRequest *p_request, ModbusResponse *p_response)
{
    if(p_request->Dat[1])
    {
        SysSeting.Msrefer = 1;
    }
    else
    {
        SysSeting.Msrefer = 0;
    }
    SettingSave();
}

void CMD2_GetBaudrate(ModbusRequest *p_request, ModbusResponse *p_response)
{
    LittleCopy_32(p_response->Dat,(u8*)&SysSeting.BaudRate,1);
    p_response->Len_or_Err = 4;
}

void CMD2_SetBaudrate(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u32 baudrate;

    LittleCopy_32((u8*)&baudrate, p_request->Dat, 1);

    if((baudrate==BAUDRATE_9600)
        ||(baudrate==BAUDRATE_38400)
        ||(baudrate==BAUDRATE_115200)
        ||(baudrate==BAUDRATE_256000)
        ||(baudrate==BAUDRATE_921600))
    {
        if(baudrate!=SysSeting.BaudRate)
        {
            SysSeting.BaudRate = baudrate;
            SettingSave();
            BSP_USART_Config(baudrate);// Initialize Uart0
        }
    }
    else
    {
        p_response->FuncCode |=0x80;
        p_response->Len_or_Err = REG_DATA_ERR; //数据错误
    }
}
void CMD2_GetPulseFreq(ModbusRequest *p_request, ModbusResponse *p_response)
{
    p_response->Dat[0] = 0;
    if(SysSeting.PulseHZ==Pulse_freq_20KHZ)
        p_response->Dat[1] = 1;
    else if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
        p_response->Dat[1] = 0;
    p_response->Len_or_Err = 2;
}

void CMD2_SetPulseFreq(ModbusRequest *p_request, ModbusResponse *p_response)
{
    if(p_request->Dat[1])//重复率设置到20Khz的同时调整输出率
    {
        if(SysSeting.PulseHZ==Pulse_freq_20KHZ)
        {
          ;
        }
        else//重复率改变，同时匹配输出率4-->20
        {
          SysSeting.PulseHZ=Pulse_freq_20KHZ;
          dist_num*=5;
        }
    }
    else
    {
        if(SysSeting.PulseHZ==Pulse_freq_4KHZ)
        {
          ;
        }
        else//重复率改变，同时匹配输出率20-->4
        {
          SysSeting.PulseHZ=Pulse_freq_4KHZ;
          dist_num/=5;
        }
    }
    SettingSave();
}

void CMD2_GetSwitchthd(ModbusRequest *p_request, ModbusResponse *p_response)
{
    p_response->Dat[0] = SysSeting.SWvalue>>8; //高位
    p_response->Dat[1] = SysSeting.SWvalue&0x00ff; //低位
    p_response->Len_or_Err = 2;
}

void CMD2_GetSwitchResult(ModbusRequest *p_request, ModbusResponse *p_response)
{
    flag_disBool=1;
    MeasStatus = SINGLE_MEAS;
}

void CMD2_SetSwitchthd(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u16 switchthd;

    LittleCopy_16((u8*)&switchthd, p_request->Dat, 1);
    SysSeting.SWvalue=switchthd;
    SettingSave();
}
void CMD2_GetAutorun(ModbusRequest *p_request, ModbusResponse *p_response)
{
    p_response->Dat[0] = 0;
    p_response->Dat[1] = SysSeting.Flag_free;
    p_response->Len_or_Err = 2;
}

void CMD2_SetAutorun(ModbusRequest *p_request, ModbusResponse *p_response)
{
    if(p_request->Dat[1])
    {
        SysSeting.Flag_free = 1;
    }
    else
    {
        SysSeting.Flag_free = 0;
    }
    SettingSave();
}

void CMD2_GetCurrentRange(ModbusRequest *p_request, ModbusResponse *p_response)
{
    LittleCopy_32(&p_response->Dat[0],(u8*)&SysSeting.CurrentRange,2);
    p_response->Len_or_Err = 8;
}

void CMD2_SetCurrentRange(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u32 current_start,current_end;

    LittleCopy_32((u8*)&current_start,&p_request->Dat[0],1);
    LittleCopy_32((u8*)&current_end,&p_request->Dat[4],1);
    if((current_start<current_end)&&(current_end <= SysSeting.RangeMax))
    {
        SysSeting.CurrentRange.CurrentStart = current_start;
        SysSeting.CurrentRange.CurrentEnd = current_end;
        SettingSave();
    }
    else
    {
        p_response->FuncCode |=0x80;
        p_response->Len_or_Err = REG_DATA_ERR; //数据错误
    }
}

void CMD2_GetOutputHZ(ModbusRequest *p_request, ModbusResponse *p_response)
{
    p_response->Dat[0] = SysSeting.OutputHZ>>8; //高位
    p_response->Dat[1] = SysSeting.OutputHZ&0x00ff; //低位
    p_response->Len_or_Err = 2;
}

void CMD2_SetOutputHZ(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u16 hz;

    LittleCopy_16((u8*)&hz, p_request->Dat, 1);

    if(hz>0 && hz <= 1000) //
    {
        SysSeting.OutputHZ = hz;
        //根据脉冲重复率计算输出hz
        if(SysSeting.PulseHZ==Pulse_freq_20KHZ)
          dist_num =20000/hz;
        else
          dist_num =4000/hz;

        SettingSave();
    }
    else
    {
        p_response->FuncCode |=0x80;
        p_response->Len_or_Err = REG_DATA_ERR; //数据错误
    }
}

void CMD2_SetRange(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u16 range;

    LittleCopy_16((u8*)&range, p_request->Dat, 1);

    if(range>0 && range<1000) // 1KM
    {
        SysSeting.RangeMax = range;
        SettingSave();
    }
    else
    {
        p_response->FuncCode |=0x80;
        p_response->Len_or_Err = REG_DATA_ERR; //数据错误
    }
}
/*
void CMD2_APD_HV_Adj(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u16 index;

    LittleCopy_16((u8*)&index, p_request->Dat, 1);

    if (index>3) return;

    switch(index)
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
    tlc5618_setting();
}

void CMD2_AGC_HV_Adj(ModbusRequest *p_request, ModbusResponse *p_response)
{
    u16 index;

    LittleCopy_16((u8*)&index, p_request->Dat, 1);

    if (index>3) return;

    switch(index)
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
}
*/
void GetSoftDate(char *date)
{
    const char *p_date = __DATE__; //sep 18 2013
    const char MonthTb[12][3]={{"Jan"},{"Feb"},{"Mar"},{"Apr"},{"May"},{"Jun"},{"Jul"},{"Aug"},{"Sep"},{"Oct"},{"Nov"},{"Dec"}};
    const char *p_month;
    u32 i;

    //月份转换成数字的
    i = 12;
    while(i)
    {
        i--;
        p_month = &MonthTb[i][0];
        if((p_month[0]==p_date[0])&&(p_month[1]==p_date[1])&&(p_month[2]==p_date[2]))
        {
            i++;
            break;
        }
    }
    date[0] = (p_date[9]-'0')*10 + (p_date[10]-'0');  //年
    date[1] = i; //月
    date[2] = ((p_date[4]==' ') ? 0 : (p_date[4]-'0'))*10 + (p_date[5]-'0'); //防止显示空格
}

void CMD2_GetVersion(ModbusRequest *p_request, ModbusResponse *p_response)
{
    char dt[3];

    GetSoftDate(dt);

	p_response->Dat[0] = PCB_VERSION;  //高位
	p_response->Dat[1] = SOFT_VERSION; //低位
	p_response->Dat[2] = dt[0]; //低位
	p_response->Dat[3] = dt[1]; //低位
	p_response->Dat[4] = dt[2]; //低位
	p_response->Dat[5] = 0;     //保留
	p_response->Len_or_Err = 6;
}


void CMD2_LEDCtrl(ModbusRequest *p_request, ModbusResponse *p_response)
{

}

void CMD2_GetAddress(ModbusRequest *p_request, ModbusResponse *p_response)
{
	p_response->Dat[0] = 0;  //高位
	p_response->Dat[1] = SysSeting.Address; //低位
	p_response->Len_or_Err = 2;
}

void CMD2_SetAddress(ModbusRequest *p_request, ModbusResponse *p_response)
{
    SysSeting.Address = p_request->Dat[1]; //更新地址
    p_response->Addr = SysSeting.Address;
    SettingSave();
}


void CMD20_LedCtl(ModbusRequest *p_request, ModbusResponse *p_response)
{

  if(p_request->Dat[1] == 0){
    
     Contrl_635LD(0);//打开激光瞄准
      p_response->Dat[0] = 1;
    
  }else{
    Contrl_635LD(1);//打开激光瞄准
    p_response->Dat[0] = 0;
  }
  p_response->Len_or_Err = 1;
}


const TypeModbusHandle ModBusHandleTab[] = {
    {0x01, CMD2_StartMeas},  //开始测量
    {0x02, CMD2_SingMeas},
    {0x03, CMD2_GetBase},
    {0x04, CMD2_GetBaudrate},
    {0x05, CMD2_GetPulseFreq},  //脉冲重复频率
    {0x06, CMD2_GetSwitchthd},  //读取开关门限
    {0x07, CMD2_GetSwitchResult},
    {0x08, CMD2_GetAutorun},
    {0x09, CMD2_GetOutputHZ},	//读取测量频率
    {0x0A, CMD2_GetCurrentRange},
	{0x0B, CMD2_GetAddress},     //获取从机地址
	{0x0C, CMD2_GetVersion},     //获取系统软硬件版本号
    {0x0E, CMD20_LedCtl},     //获取系统软硬件版本号

    {0x10, CMD2_StopMeas},
    {0x11, CMD2_SetBase},
    {0x12, CMD2_SetBaudrate},
	{0x13, CMD2_SetOutputHZ},	//设置测量频率
	{0x14, CMD2_SetRange},	    //设置测量量程
    {0x15, CMD2_SetPulseFreq},  //脉冲重复频率
    {0x16, CMD2_SetSwitchthd},  //设置开关门限
	{0x17, CMD2_SetAutorun},
	{0x18, CMD2_SetCurrentRange}, //设置电流环量程
	{0x19, CMD2_SetAddress},

    //{0x05, CMD2_APD_HV_Adj},     //调整APD高压
    //{0x06, CMD2_AGC_HV_Adj},     //调整AGC高压
	{0x1A,CMD20_LedCtl},
};

const u8 MAX_CMD2_NUM = 22;

