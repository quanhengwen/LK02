/*******************************************************************
*file name:    drv_protocol.c
*project:      s2
*Description:  uart protocol
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2014.6.4
*note:         null
*******************************************************************/
#include "global.h"

//-----------------------------------------------------------------------------------------
//�����Ǻ궨��
//-----------------------------------------------------------------------------------------
#ifndef MCU_F0
#define UART_TIM TIM1

#define UART_TIMEOUT_EN()  do{}while(0)

//uart timeout handle
#define UART_TIMEOUT_DIS()  \
do{\
    UART_TIM->SR = (uint16_t)~TIM_FLAG_Update;\
    UART_TIM->DIER &= (uint16_t)~TIM_IT_Update;\
    UART_TIM->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));\
}while(0)

//uart timeout reset
#define UART_TIME_RESET() \
do{\
    UART_TIM->CNT = 0;\
    UART_TIM->DIER |= TIM_IT_Update;\
    UART_TIM->CR1 |= TIM_CR1_CEN;\
}while(0)

#else  // mcu F0, use uart timeout fuction
#define UART_TIMEOUT_EN()   do{USART1->CR2 |= USART_CR2_RTOEN;}while(0)
#define UART_TIMEOUT_DIS()  do{USART1->CR2 &= ~USART_CR2_RTOEN;}while(0)
#define UART_TIME_RESET()   do{}while(0)
#endif

//-----------------------------------------------------------------------------------------
//�����Ǳ���
//-----------------------------------------------------------------------------------------

//����
char UART0_RxBuf[BUF_LEN];      //receive buffer
volatile u8 UART0_RxPaktLen=0;  //Rx packet length
volatile u8 UART0_RxBufRdy=0;

extern const T_CmdHandle HandleTab[];
extern const u8 MAX_CMD_NUM;
extern T_SysParam SysSeting;
extern u8 ProtocolType;

//-----------------------------------------------------------------------------------------

/*
����:   ��ʱ��10ms��ʱ,�ж��е���
����:   ��
����:   ����
*/
void UART_TimeOutIRQ(void)
{
    UART_TIMEOUT_DIS();
    UART0_RxBufRdy = TRUE;
}


/*
����:   ��ȡ��������,�ж��е���
����:   ��
����:   ����
*/
void UART_RxIRQ(void)
{
    char ch;
   #ifdef MCU_F0
    ch = USART1->RDR;
   #else
    ch = USART1->DR;
   #endif
    if(UART0_RxBufRdy==FALSE) //buf no data and no ready 
    { 
        UART0_RxBuf[UART0_RxPaktLen++] = ch;
        if(ch=='\n')
        {
            UART_TIMEOUT_DIS();
            UART0_RxBufRdy = TRUE;
        }
        else
        {
            //���ö�ʱ��
            UART_TIME_RESET();
        }
    }
}

/*
����:   ����һ�����ݰ�
����:   ��
����:   ����
*/
void UART_SendPacket(char *pch,u16 len)
{
    while(len--)
    {
        put_char(*pch++);
    }
}

/*
����:   ��ȡ��������,�ж��е���
����:   ��
����:   ����
*/
void UART_StartReceive(void)
{
    UART_TIMEOUT_EN();
    UART0_RxBufRdy = FALSE;
    UART0_RxPaktLen = 0;
}


#ifdef ENABLE_UART_PROTOCOL

#if 1
/*
����:   �ַ����Ƚ�
����:   �ַ���
���:   hex
*/
bool StrCmp(const char *psrc,const char *pdest)
{   
    while((*psrc!='\0')&&(*pdest!='\0'))
    {
        if(*psrc!=*pdest)
        {
            return FALSE;
        }
        psrc++;
        pdest++;
    }
    return TRUE;
}

/*
����:   �ַ���תhex
����:   �ַ���
���:   hex
*/
s32 Str2Hex32(const char *str)
{
   s32 hex=0;
   u32 flg=0;
   
   if(*str=='-')
   {
      flg = 1;
      str++;
   }
   while((*str>='0')&&(*str<='9'))
   {
        hex *= 10;
        hex += (*str-'0');
        str++;
   }
   return flg?(-hex):hex;
}

/*
����:   �����ַ�������
����:   buf
����:   ����id
*/
s32 GetStrCmd(const char *buf)
{
    s32 i;
    for(i=0;i<MAX_CMD_NUM;i++)
    {
        if(StrCmp(HandleTab[i].str,buf)==TRUE)
        {
            return i;
        }
    }
    return -1;
}

bool GetStrDat(const char *buf,s32 *pdat,s32 len)
{
    while((*buf<'0')||(*buf>'9'))
    {
        if(*buf=='-')
            break;
        if(len==0)
            return FALSE;
        len--;
        buf++;
    }
    *pdat = Str2Hex32(buf);
    return TRUE;
}
#endif

/*
����:   ��������
����:   ��
����:   ����
*/
void USART_CmdParse(void)
{
    char *pbuf;
    s32 cmd_id,dat,len;
    CMD_HANDLE pfnct;
    u16 temp;

    if(UART0_RxBufRdy==FALSE)
    {
        return;
    }
    len = UART0_RxPaktLen;
    pbuf = UART0_RxBuf;

    if(pbuf[0]=='M' && pbuf[1] == 'S') // MS:xxxxx
    {
        cmd_id = GetStrCmd(pbuf);
        if(cmd_id >= 0)
        {
            GetStrDat(pbuf+5,&dat,len);
            pfnct = HandleTab[cmd_id].handle;
            pfnct(dat);
        }
    }
    else
    {
        if((pbuf[0] != SysSeting.Address) && (pbuf[3]!=0x1b))    //0x1b get Slave Add
        {
            UART_StartReceive();
            return;
        }

        //CRC16
        temp = pbuf[len-1];
        temp <<= 8;
        temp |= pbuf[len-2];
        ProtocolType = 1; // 1->rtu, 0->ascii

        //=======next is Modbus  protocol handle===========>
        switch(pbuf[1])  //Fuction Code
        { 
            case WRITE_MULT_REG:    //0x10=16
                temp = WriteMuitREG((u8*)pbuf);//�������ݳ���
            break;
            case READ_HOLD_REG:     //03=03
                temp = ReadInputREG((u8*)pbuf);//�������ݳ���
            break;
            default://Fuction Code �쳣1
                pbuf[1]|= 0x80;
                pbuf[2] = ERR_CODE1;  //���������
                temp = CRC16((u8*)pbuf,3);
                pbuf[3] = temp&0xff;//��4λ�ֽ�
                pbuf[4] = temp>>8;  //��4λ�ֽ�
                temp = 5;           //���ݳ���
            break;
        }
        
        UART_SendPacket(pbuf,temp); //�������  Addr(1)+FucCode(1)+length(1)+data........+CRC(2)
    }
    UART_StartReceive();  /*��ʼ��������*/
}

#endif




