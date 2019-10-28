//-----------------------------------------------------------------------------
// f34x_main.c
//-----------------------------------------------------------------------------
// Copyright 2015 MC Ltd, Inc.
// http://www.mc.com
//
// Program Description:
//
// driver definitions for the pluse measuring.
//
// PRJ:            X HIGH SPEED MEASURING
// Target:         STM32F10X
// Tool chain:     IAR
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (CM)
//    -27 Oct 2015
//    -Latest release before new firmware coding standard
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.h"

u16 gv_gain_for_apd;             // 0~4095  outA for APD 
u16 gv_gain_for_agc;             // 0~4095  outB for AGC
u32 gv_com_baudrate = 0;


u8 gv_protocol_mode;

//-----------------------------------------------------------------------------
#define pro_printf  mPrintf

//-----------------------------------------------------------------------------
void parameter_init(void)
{     
    u8 gv_sys_status = SS_NONE;
    
    gv_com_baudrate = BAUDRATE_921600;
    gv_gain_for_apd = GAIN_APD_DEFAULT;
    gv_gain_for_agc = GAIN_AGC_DEFAULT;
    gv_protocol_mode = PT_RTU;

    EE_Flash_Read_All_Contents();
    
    Flash_ReadData(EEP_SYSTEM_STATUS, &gv_sys_status, 1);
    
    if (gv_sys_status!=SS_CHECKED && gv_sys_status!=SS_DEMARCATED)
    {
        gv_sys_status = SS_CHECKED; 
        Flash_WriteData(EEP_SYSTEM_STATUS, &gv_sys_status, 1);
        Flash_WriteData(EEP_GAIN_APD, (u8*)&gv_gain_for_apd, 2);
        Flash_WriteData(EEP_GAIN_AGC, (u8*)&gv_gain_for_agc, 2);
        Flash_WriteData(EEP_COM_BAUDRATE, (u8*)&gv_com_baudrate, 4);
        Flash_WriteData(EEP_PROTOCOL_TYPE, &gv_protocol_mode, 1);
    }
    else
    {
        Flash_ReadData(EEP_GAIN_APD, (u8*)&gv_gain_for_apd, 2);
        Flash_ReadData(EEP_GAIN_AGC, (u8*)&gv_gain_for_agc, 2);
        Flash_ReadData(EEP_COM_BAUDRATE, (u8*)&gv_com_baudrate, 4);
        Flash_ReadData(EEP_PROTOCOL_TYPE, &gv_protocol_mode, 1);
    }
}


void tlc5618_setting(void)  
{
    tlc5618_execute(gv_gain_for_apd, gv_gain_for_agc);
}

void cmd_set_baudrate(int arg)
{
    if((arg==BAUDRATE_115200)||(arg==BAUDRATE_460800)||(arg==BAUDRATE_921600))
    {
        if(arg!=gv_com_baudrate)
        {
            gv_com_baudrate = arg;
            Flash_WriteData(EEP_COM_BAUDRATE,(u8*)&arg, 4);
            EE_Flash_Write_All_Contents();
            BSP_USART_Config(arg);// Initialize Uart0
        }
    }
}

void cmd_apd_hv_adj(int arg)
{
    if (arg>3) return;

    switch(arg)
    {
        case 0:
        {
            if(gv_gain_for_apd>60) 
                gv_gain_for_apd -= 60;
            else
                gv_gain_for_apd = 0;
            break;
        }
        case 1:
        {
            gv_gain_for_apd += 60;
            if(gv_gain_for_apd>GAIN_APD_MAX) 
                gv_gain_for_apd = GAIN_APD_MAX;
            //pro_printf("hv add\r\n");
            break;
        }
        case 2:
        {
            if(gv_gain_for_apd>12) 
                gv_gain_for_apd -= 12;
            else
                gv_gain_for_apd = 0;
            break;
        }
        case 3:
        {
            gv_gain_for_apd += 12;
            if(gv_gain_for_apd>GAIN_APD_MAX) 
                gv_gain_for_apd = GAIN_APD_MAX;
            break;
        }
        default: break;
    }
    Flash_WriteData(EEP_GAIN_APD,(u8*)&gv_gain_for_apd, 2);
    EE_Flash_Write_All_Contents();
    tlc5618_setting();
}

void cmd_agc_hv_adj(int arg)
{
    if (arg>3) return;

    switch(arg)
    {
        case 0:
        {
            if(gv_gain_for_agc>60) 
                gv_gain_for_agc -= 60;
            else
                gv_gain_for_agc = 0;
            break;
        }
        case 1:
        {
            gv_gain_for_agc += 60;
            if(gv_gain_for_agc>GAIN_AGC_MAX) 
                gv_gain_for_agc = GAIN_AGC_MAX;
            //pro_printf("hv add\r\n");
            break;
        }
        case 2:
        {
            if(gv_gain_for_agc>12) 
                gv_gain_for_agc -= 12;
            else
                gv_gain_for_agc = 0;
            break;
        }
        case 3:
        {
            gv_gain_for_agc += 12;
            if(gv_gain_for_agc>GAIN_AGC_MAX) 
                gv_gain_for_agc = GAIN_AGC_MAX;
            break;
        }
        default: break;
    }
    Flash_WriteData(EEP_GAIN_AGC,(u8*)&gv_gain_for_agc, 2);
    EE_Flash_Write_All_Contents();
    tlc5618_setting();
}

void cmd_change_mode(int arg)
{
    if (arg>1) return;
    if(arg==1){
        gv_protocol_mode = PT_ASC;
    }else{
        gv_protocol_mode = PT_RTU;
    }
    Flash_WriteData(EEP_PROTOCOL_TYPE, &gv_protocol_mode, 1);
    EE_Flash_Write_All_Contents();
}

void cmd_get_versions(int arg)
{
    arg = arg;
    pro_printf("\r\n#HW:v01,SW:v01\r\n");   
    //dly1ms((void*)1000);
}

const T_CmdHandle HandleTab[] = 
{
    {FCODE_SET_BAUDRATE,  cmd_set_baudrate},
    {FCODE_APD_ADJUST,    cmd_apd_hv_adj},
    {FCODE_AGC_ADJUST,    cmd_agc_hv_adj},
    {FCODE_CHMODE,        cmd_change_mode},
    {FCODE_GET_VERSION,   cmd_get_versions}
};


