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
//以下是宏定义
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
//以下是变量
//-----------------------------------------------------------------------------------------

//接收
//char UART0_RxBuf[BUF_LEN];      //receive buffer
//volatile u8 UART0_RxPaktLen=0;  //Rx packet length
//volatile u8 UART0_RxBufRdy=0;
Buffer_T UART0_TxBuf;
Buffer_T UART0_RxBuf;

extern const T_CmdHandle HandleTab[];
extern const u8 MAX_CMD_NUM;
extern T_SysParam SysSeting;
extern E_PROTOCOL_TYPE ProtocolType;
extern const TypeModbusHandle ModBusHandleTab[];

//-----------------------------------------------------------------------------------------

/*
描述:   定时器10ms超时,中断中调用
输入:   无
返回:   数据
*/
static u8 ac = 0;
void UART_TimeOutIRQ(void)
{
    UART_TIMEOUT_DIS();
    UART0_RxBuf.IsRdy = TRUE;
    UART0_RxBuf.Data[UART0_RxBuf.Cnt] = 0;
    //USART_CmdParse();

}


/*
描述:   读取接收数据,中断中调用
输入:   无
返回:   数据
*/
void UART_RxIRQ(void)
{
    char ch;
   #ifdef MCU_F0
    ch = USART1->RDR;
   #else
    ch = USART1->DR;
   #endif
    if(UART0_RxBuf.IsRdy==FALSE) //buf no data and no ready
    {
        UART0_RxBuf.Data[UART0_RxBuf.Cnt++] = ch;
        //if(ch=='\n')
        if((UART0_RxBuf.Cnt >= sizeof(UART0_RxBuf.Data))||
        (UART0_RxBuf.Data[1]==READ_HOLD_REG)&&(UART0_RxBuf.Cnt ==8)||
        (UART0_RxBuf.Data[1]==WRITE_MULT_REG)&&(UART0_RxBuf.Data[6]==(UART0_RxBuf.Cnt - 9)))
        {
            UART_TIMEOUT_DIS();
            UART0_RxBuf.IsRdy = 1;
            UART0_RxBuf.Data[UART0_RxBuf.Cnt] = 0;
        }
        else
        {
            //重置定时器
            UART_TIME_RESET();
        }
    }
}

/*
描述:   发送一个数据包
输入:   无
返回:   数据
*/
void UART_SendPacket(char *pch,u16 len)
{
    while(len--)
    {
        put_char(*pch++);
    }
}

/*
描述:   读取接收数据,中断中调用
输入:   无
返回:   数据
*/
void UART_StartReceive(void)
{
    UART_TIMEOUT_EN();
    UART0_RxBuf.IsRdy = 0;
    UART0_RxBuf.Cnt = 0;
}


#ifdef ENABLE_UART_PROTOCOL

#if 1
/*
描述:   字符串比较
输入:   字符串
输出:   hex
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
描述:   字符串转hex
输入:   字符串
输出:   hex
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
   return flg?(-hex):hex;//问号条件表达式 c= a<b?a:b;条件表达式优先于幅值表达式:当a<b时 c=a;否则c=b;
}

/*
描述:   解析字符串命令
输入:   buf
返回:   命令id
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
描述:   解析数据
输入:   无
返回:   数据
*/ 
s32 cmd_id=0,dat=0;
void USART_CmdParse(void)
{
    char i,*pbuf = (char *)UART0_RxBuf.Data;
   
    CMD_HANDLE pfnct;
    ModbusResponse *ModResponse = (ModbusResponse *)&UART0_TxBuf.Data;
    ModbusRequest *ModReq = (ModbusRequest *)&UART0_RxBuf.Data;
    u16 temp,crc;
    if(UART0_RxBuf.IsRdy != TRUE)
      return;
    if(pbuf[0]=='M' && pbuf[1] == 'S') // MS:xxxxx
    {
        ProtocolType = PROTOCOL_ASCII;
        cmd_id = GetStrCmd(pbuf);
        if(cmd_id >= 0)
        {
            GetStrDat(pbuf+5,&dat,UART0_RxBuf.Cnt);
            pfnct = HandleTab[cmd_id].handle;
            pfnct(dat);
        }
        memset(pbuf,0,UART0_RxBuf.Cnt);
    }
    else//modbus
    {
        if((pbuf[0]!= SysSeting.Address) && (pbuf[3]!=0x0B))    //0x0b get Slave Add
        {
            UART_StartReceive();
            return;
        }

        //判断是否写多寄存器或者读多寄存器，否则非法
        if((pbuf[1] != READ_HOLD_REG)&&(pbuf[1] != WRITE_MULT_REG))
        {
            memcpy(UART0_TxBuf.Data,UART0_RxBuf.Data,2);
            UART0_TxBuf.Data[1] |= ERRFLAG;
            UART0_TxBuf.Data[2] = FUNCE_ERR;
            UART0_TxBuf.Cnt = 5;
            goto Response;
        }

        //命令长度不正确
        //写多寄存器
        //寄存器数量高字节不可能大于0
        //寄存器数量低字节为寄存器字节数的一半
        //传输的字节数等于字节数+9
        if((pbuf[1] == WRITE_MULT_REG)&&
        ((pbuf[4] > 0)
        ||(pbuf[5] != (pbuf[6]/2))
        ||(UART0_RxBuf.Cnt != (pbuf[6] + 9))))
        {
            memcpy(UART0_TxBuf.Data,UART0_RxBuf.Data,2);
            UART0_TxBuf.Data[1] |= ERRFLAG;
            UART0_TxBuf.Data[2] = REG_CNT_ERR;
            UART0_TxBuf.Cnt = 5;
            goto Response;
        }

        //CRC16
        temp = pbuf[UART0_RxBuf.Cnt - 1];
        temp <<= 8;
        temp |= pbuf[UART0_RxBuf.Cnt - 2];
        crc = CRC16(pbuf,UART0_RxBuf.Cnt - 2);

        memcpy(UART0_TxBuf.Data,pbuf,2);

        if(temp != crc)
        {
            UART0_TxBuf.Data[1] |= ERRFLAG;
            UART0_TxBuf.Data[2] = CRC_ERR;
            UART0_TxBuf.Cnt = 5;
        }
        else
        {
            i = 0;
            ProtocolType = PROTOCOL_RTU;
            while(ModBusHandleTab[i].ModbusHandle != _NULL_)
            {
                if(ModBusHandleTab[i].addr == pbuf[3])//起始地址
                {
                    if(pbuf[1] == WRITE_MULT_REG)
                        memcpy(UART0_TxBuf.Data,pbuf,6);

                    ModBusHandleTab[i].ModbusHandle(ModReq,ModResponse);
                    break;
                }
                i++;
            }
        }

        if(UART0_TxBuf.Data[1]&0x80)//返回错误码
            UART0_TxBuf.Cnt = 5;
        else
        {
            if(pbuf[1] == WRITE_MULT_REG)
                UART0_TxBuf.Cnt = 8;
            else
            {
                if(UART0_TxBuf.Data[2] == 0)
                {
                    UART_StartReceive();
                    return;
                }
                UART0_TxBuf.Cnt = UART0_TxBuf.Data[2] + 5;
            }
        }

        Response:
        crc = CRC16(UART0_TxBuf.Data,UART0_TxBuf.Cnt - 2);
        UART0_TxBuf.Data[UART0_TxBuf.Cnt -2] = (u8)(crc&0xFF);
        UART0_TxBuf.Data[UART0_TxBuf.Cnt -1] = (u8)((crc&0xFF00)>>8);
        if(pbuf[3]!=0x07)
            put_string((char *)UART0_TxBuf.Data,UART0_TxBuf.Cnt);
        memset(UART0_TxBuf.Data,0,UART0_TxBuf.Cnt);
        UART0_TxBuf.Cnt = 0;

    }
    UART_StartReceive();  /*开始接收数据*/
}

#endif



UsartDatStr_t UsartDatStr;


void DMA_Init_Mem2Periph(unsigned int PeriphAddr, unsigned int MemAddr, unsigned short bufsize,DMA_Channel_TypeDef* DMA_Ch)
{
	DMA_InitTypeDef    DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                  					 //开DMA时钟
	DMA_DeInit(DMA_Ch);                                                 				   //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (unsigned int)PeriphAddr;         				   //源头BUF 既是 (&(USART1->DR))
	DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned int)MemAddr;                					 //目标BUF 既是要写在哪
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                  					 //外设作源头//外设是作为数据传输的目的地还是来源
	DMA_InitStructure.DMA_BufferSize = bufsize;                                        //DMA缓存的大小 单位在下边设定
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               //外设地址寄存器不递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                        //内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;        //外设字节为单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;            //内存字节为单位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                               	 //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                            //4优先级之一的(高优先) VeryHigh/High/Medium/Low
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                   //非内存到内存
	DMA_Init(DMA_Ch, &DMA_InitStructure);                                   			 //根据DMA_InitStruct中指定的参数初始化DMA的通道1寄存器
	DMA_Cmd(DMA_Ch, ENABLE);                                                			 //正式允许DMA
	DMA_ITConfig(DMA_Ch,DMA_IT_TC,ENABLE);
}



//dma发送
void Uart1_DMASendOutOnce(char* buf, unsigned int bufsize)
{
	if(bufsize > 0)
	{
		DMA_Init_Mem2Periph((unsigned int)&USART1->DR,(unsigned int)buf,bufsize,DMA1_Channel4);
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
		DMA_Cmd(DMA1_Channel4, ENABLE);  //使能USART  TX 所指示的通道
		USART_Cmd(USART1 , ENABLE);
	}
}

void DMA1_Channel4_IRQHandler()
{
	if(DMA_GetITStatus(DMA1_IT_TC4) != RESET)
  {
    UsartDatStr.FinishedTxFlag  = 1;
    GPIO_ResetBits(GPIOB,GPIO_Pin_8);
    DMA_ClearITPendingBit(DMA1_IT_TC4);
  }
}

