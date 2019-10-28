/*******************************************************************
*file name:    drv_modbus.c
*project:      C1
*Description:  Modbus
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2016.5.7
*note:         null
*******************************************************************/
#include "global.h"

//------------------------------------------------------------------
extern const u8 MAX_CMD2_NUM;
extern char UART0_RxBuf[];
extern T_SysParam SysSeting;

//------------------------------------------------------------------
#define Little2BigEndian16(DAT) (((DAT)>>8)|((DAT)<<8))

//===============================================================
//����: С�˷�ʽ����u16
//����:һ��u16  ���鸴�Ƶ�u8����
//���:u8 ����
//===============================================================
void LittleCopy_16(u8 *dest,u8 *src,u16 len)
{
    while(len)
    {
        *dest = *(src+1);
        *(dest+1) = *src;
        dest+=2;src+=2;
        len--;
    }
}

//================================================================
//����: С�˷�ʽһ��u32 ���ݸ��Ƶ�u8
//����:һ��u32  ���鸴�Ƶ�u8����
//���:u8 ����
//================================================================
void LittleCopy_32(u8 *dest,u8 *src,u16 len)
{
    while(len)
    {
        *dest = *(src+3);
        *(dest+1) = *(src+2);
        *(dest+2) = *(src+1);
        *(dest+3) = *src;
        dest+=4;src+=4;
        len--;
    }
}

#if 0
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================д����Ĵ���(��д)==============>
//Request:
//        FucCode:   1byte  0X10 
//        StartAddr: 2byte  0x0000~0xffff
//        Quantity:  2byte  1~125
//        ByteCount: 1byte  2*Quantity
//        REG_DAT:   2*Quantity
//Response:
//        FucCode:   1byte  0X10
//        StartAddr: 2byte  0x0000~0xffff
//        Quantity:  2byte  1~125
//ERROR: 
//        ErrorCode: FucCode|0x80
//        ExceptCode:0x01/0x02/0x03/0x04
//=================================================>
//buf: �������ָ��  ������������û���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int WriteMuitREG(u8 *buf)
{
    u16 i,temp;
    ModbusRequest *P_Request=(ModbusRequest *)buf;
    ModbusResponse *P_Response=(ModbusResponse *)buf;
    MODBUS_HANDLE pfnct;

    #define  LEN  MAX_CMD2_NUM//(sizeof(ModBusHandleTab))///sizeof(TypeModbusHandle))
    
    P_Request->Quantity = Little2BigEndian16(P_Request->Quantity);

    if( (P_Request->Quantity>0) && (P_Request->Quantity<125) )
    {
        temp = Little2BigEndian16(P_Request->StartAddr);
        for(i=0; i<LEN; i++)
        {
            if(ModBusHandleTab[i].addr==temp)
            {
                pfnct = ModBusHandleTab[i].ModbusHandle;
                (*pfnct)(P_Request, P_Response);
                break;
            }
        }
    }
    else
    {
        P_Response->FuncCode |=0x80;
        P_Response->Len_or_Err = ERR_CODE3;
    }
    
    //CRC16 verify
    if(P_Response->FuncCode&0x80)  //�쳣���  Addr(1)+FucCode(1)+ErrCode(1)+CRC(2)
    {
        temp = CRC16(buf,3);
        P_Response->Dat[0] = temp&0xff;
        P_Response->Dat[1] = temp>>8;
        temp = 5;  //�������ݵĳ���
    }
    else  //�����������  Addr(1)+FucCode(1)+StartAddr(2)+Quantity(2)+CRC(2)
    {
        P_Request->Quantity = Little2BigEndian16(P_Request->Quantity);
        temp = CRC16(buf,6);
        P_Request->ByteCount = temp&0xff;//����е��̬,������
        P_Request->Dat[0] = temp>>8;
        temp = 8;  //�������ݵĳ���
    }
    return temp;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     //=================������Ĵ���(ֻ��)==============>
//Request:
//        FucCode:   1byte  04 
//        StartAddr: 2byte  0x0000~0xffff
//        Quantity:  2byte  1~125
//Response:
//        FucCode:   1byte  04
//        length:    1byte  2*Quantity
//        Data:      2*Quantity    
//ERROR: 
//        ErrorCode: FucCode|0x80
//        ExceptCode:0x01/0x02/0x03/0x04
//=================================================>
//buf: �������ָ��  ������������û���
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int ReadInputREG(u8 *buf)
{
   int length;
   u16 i,temp;
   ModbusRequest *P_Request=(ModbusRequest *)buf;
   ModbusResponse *P_Response=(ModbusResponse *)buf;
   MODBUS_HANDLE pfnct;

   #define  LEN2  MAX_CMD2_NUM//(sizeof(ModBusHandleTab)/sizeof(TypeModbusHandle))

   P_Request->Quantity = Little2BigEndian16(P_Request->Quantity);
    
   if( (P_Request->Quantity>0) && (P_Request->Quantity<125) )
   {
        temp = Little2BigEndian16(P_Request->StartAddr);
        for(i=0; i<LEN2; i++)
        {
            if(ModBusHandleTab[i].addr==temp)
            {
                pfnct = ModBusHandleTab[i].ModbusHandle;
                (*pfnct)(P_Request, P_Response);
                break;
            }
        }
   }
   else
   {
       P_Response->FuncCode |=0x80;
       P_Response->Len_or_Err = ERR_CODE3;
   }
   if(P_Response->FuncCode&0x80)
   {
       length = 0;  
   }
   else
   {
       length = P_Response->Len_or_Err;
   }
    //CRC16 verify
    temp = CRC16(buf,length+3);
    P_Response->Dat[length] = temp&0xff;
    P_Response->Dat[length+1] = temp>>8;    
    return length+5;
}

//def N_MODBUS_CONTINU_MEASURE
/*
����:�����ݴ����modbusЭ��
����:   ��
����:   ��
*/
void ModbusSendPackt(u8 *pch,u16 len)
{
    ModbusResponse *p_response = (ModbusResponse *)UART0_RxBuf;
    u16 temp;

  #ifdef ENABLE_RS485
    RS485_Send();
  #endif

    p_response->Addr = SysSeting.Address;
    p_response->FuncCode = READ_HOLD_REG;
    p_response->Len_or_Err = len;
    memcpy(p_response->Dat,pch,len);

    temp = CRC16((u8*)UART0_RxBuf,len+3); //+3 bytes head 
    p_response->Dat[len] = temp&0xff;
    p_response->Dat[len+1] = temp>>8;   
    
    UART_SendPacket(UART0_RxBuf,len+5); //+3 bytes head +2 bytes CRC

  #ifdef ENABLE_RS485
    RS485_Receive();        
  #endif
}

void ModbusSendError(ERROR_CODE err)
{
    ModbusResponse *p_response = (ModbusResponse *)UART0_RxBuf;
    u16 temp;
    
  #ifdef ENABLE_RS485
    RS485_Send();
  #endif
  
    p_response->Addr = SysSeting.Address;
    p_response->FuncCode = READ_HOLD_REG | 0x80;
    p_response->Len_or_Err = ERR_CODE3;

    temp = CRC16((u8*)UART0_RxBuf,3); //+3 bytes head 
    p_response->Dat[0] = temp&0xff;
    p_response->Dat[1] = temp>>8;   
    
    UART_SendPacket(UART0_RxBuf,5); //+3 bytes head +2 bytes CRC

  #ifdef ENABLE_RS485
    RS485_Receive();        
  #endif
}
#endif

