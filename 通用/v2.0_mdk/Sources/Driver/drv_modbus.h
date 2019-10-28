/*******************************************************************
*file name:     meas_uart.h
*project:        L2
*Description:  uart read write
*Platform: 	  uCOSII2.86
*firmware:      v1.0
*Author:         cwd
*data:		  2013.1.25
*note:            null
*******************************************************************/
#ifndef _DRV_MODBUS_H_
#define _DRV_MODBUS_H_

//-------------------------------------------------------------------------------
#define RX_BUF_LEN  128
#define TX_BUF_LEN  256

#define MODBUS_HANDLE_NUM 50
#define ERRFLAG                     0x80

#define _NULL_                  ((void *)0)

//-------------------------------------------------------------------------------
//modbus data
enum FNC_CODE {					   
	READ_COILS_STATUS	= 1, // 读线圈
	READ_INPUT_STATUS	= 2, // 读离散量输入
	READ_HOLD_REG		= 3, // 读保持寄存器  读写
	READ_INPUT_REG		= 4, // 读输入寄存器  只读
	WRITE_SING_COIL		= 5, // 写单个线圈
	WRITE_SING_REG 		= 6, // 写单个寄存器
	WRITE_MULT_COIL		= 15,// 写多个线圈	
	WRITE_MULT_REG 		= 16,// 写多个寄存器
	MASK_WRITE_REG 		= 22,// 处理屏蔽寄存器指令
	READ_WRITE_REG  	= 23 // 读写多个寄存器
}; 

typedef enum  
{                      
    FUNCE_ERR = 1,      // Fuction Code error        //功能码错误
    ADDR_ERR = 2,       // start address error     //地址码错误
    REG_CNT_ERR = 3,    // Quantity error            
    REG_DATA_ERR = 4,   // data error
    CRC_ERR = 5         // CRC error
}ERROR_CODE; 

typedef struct
{
    u8 Data[RX_BUF_LEN];
    u8 Cnt;
    u8 IsRdy;
}Buffer_T;


//-------------------------------------------------------------------------------
typedef struct {
	u8   Addr;
	u8   FuncCode;
	u16  StartAddr;
	u16  Quantity;
	u8   ByteCount;
	u8   Dat[RX_BUF_LEN-7];
}ModbusRequest;

typedef struct {
	u8 Addr;
	u8 FuncCode;
  	u8 Len_or_Err; 	      // 请求数据数长度  或者出错码
	u8 Dat[RX_BUF_LEN-3]; // 仅为输出错异常代码，正常操作设为0
}ModbusResponse;

//-------------------------------------------------------------------------------
typedef void (*MODBUS_HANDLE)(ModbusRequest *p_request, ModbusResponse *p_response);

typedef struct T_MODBUSHANDLE{
	u8 addr;
	MODBUS_HANDLE ModbusHandle;
}TypeModbusHandle;

//-------------------------------------------------------------------------------
void LittleCopy_16(u8 *dest,u8 *src,u16 len);
void LittleCopy_32(u8 *dest,u8 *src,u16 len);

int WriteMuitREG(u8 *buf);
int ReadInputREG(u8 *buf);

void ModbusSendPackt(u8 *pch,u16 len);
void ModbusSendError(ERROR_CODE err);

void UART_SendPacket(char *pch,u16 len);

#endif


