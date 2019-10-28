//-----------------------------------------------------------------------------
// drv_global.h
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

#ifndef _DRV_GLOBAL_H__
#define _DRV_GLOBAL_H__

//-----------------------------------------------------------------------------
// UART
//-----------------------------------------------------------------------------
void printfx(const char *fmt, ...);

//-----------------------------------------------------------------------------
// SPI
//-----------------------------------------------------------------------------
void spi1_init(void);
u8   spi1_write_byte(u8 tx_dat);
void spi2_init(void);
u16 spi2_write_byte(u16 tx_dat);
u16  spi2_write_word(u16 tx_dat);

//-----------------------------------------------------------------------------
// IIC
//-----------------------------------------------------------------------------
#define MIMETIC_IIC_ENABLE
typedef enum
{		
	IIC_ACK,
	IIC_NACK
}type_iic_ack;
typedef enum
{		
	IIC_SPEED_HIGH,
	IIC_SPEED_LOW
}type_iic_speed; 
typedef enum
{		
	IIC_WRITE,
	IIC_READ
}type_iic_op;

void iic_setspeed(type_iic_speed status);
void iic_init(void);
bool iic_send_byte(u8 address,u8 cmd,u8 dat);
bool iic_send_same_bytes(u8 address,u8 cmd,u8 dat,u8 len);
bool iic_send_mul_bytes(u8 address,u8 cmd,u8 *pdat,u8 len);
bool iic_recv_mul_bytes(u8 address, u8 cmd, u8* pdat, u8 len);

#endif



