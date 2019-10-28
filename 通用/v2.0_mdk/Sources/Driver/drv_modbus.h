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
	READ_COILS_STATUS	= 1, // ����Ȧ
	READ_INPUT_STATUS	= 2, // ����ɢ������
	READ_HOLD_REG		= 3, // �����ּĴ���  ��д
	READ_INPUT_REG		= 4, // ������Ĵ���  ֻ��
	WRITE_SING_COIL		= 5, // д������Ȧ
	WRITE_SING_REG 		= 6, // д�����Ĵ���
	WRITE_MULT_COIL		= 15,// д�����Ȧ	
	WRITE_MULT_REG 		= 16,// д����Ĵ���
	MASK_WRITE_REG 		= 22,// �������μĴ���ָ��
	READ_WRITE_REG  	= 23 // ��д����Ĵ���
}; 

typedef enum  
{                      
    FUNCE_ERR = 1,      // Fuction Code error        //���������
    ADDR_ERR = 2,       // start address error     //��ַ�����
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
  	u8 Len_or_Err; 	      // ��������������  ���߳�����
	u8 Dat[RX_BUF_LEN-3]; // ��Ϊ������쳣���룬����������Ϊ0
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


