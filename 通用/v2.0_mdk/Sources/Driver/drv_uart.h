/*******************************************************************
*file name:    drv_uart.c
*project:      s2
*Description:  uart driver
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2014.6.4
*note:         null
*******************************************************************/
#ifndef _DRV_UART_H_
#define _DRV_UART_H_

//---------------------------------------------------------------
//以下是宏定义
#define BUF_LEN 64

//---------------------------------------------------------------
//以下是结构体
typedef  void (*CMD_HANDLE)(int);

typedef struct{
    const char *str;
    CMD_HANDLE handle;
}T_CmdHandle;

//---------------------------------------------------------------
//以下是外部函数接口
extern void UART_TimeOutIRQ(void);
extern void UART_TxIRQ(void);
extern void UART_RxIRQ(void);
extern void USART_CmdParse(void);
extern void UART_StartReceive(void);

 
typedef struct UsartDatStr_s
{
  unsigned char TxBuffer[200];
  unsigned short TxSize;
  unsigned char FinishedTxFlag;
}UsartDatStr_t;

extern UsartDatStr_t UsartDatStr;
//dma发送
void Uart1_DMASendOutOnce(char* buf, unsigned int bufsize);


#endif

