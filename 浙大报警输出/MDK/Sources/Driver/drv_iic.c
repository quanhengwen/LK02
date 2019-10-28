//-----------------------------------------------------------------------------
// drv_iic.c
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

#include "global.h"

#ifdef MIMETIC_IIC_ENABLE
type_iic_speed iic_highspeed;
static void iicdelay(void)
{
    volatile u16 icnt;
    if (iic_highspeed==IIC_SPEED_HIGH){
        icnt = 3;
    }else{
        icnt = 30;
    }
    while(icnt){
        icnt--;
    }
}
void iic_setspeed(type_iic_speed status)
{
	iic_highspeed = status;
}
static void iic_start(void)
{
	IIC_SET_SDA_HIGH();//IIC_SDA = 1;
	iicdelay();
	IIC_SET_SCL_HIGH();//IIC_SCL = 1;
	iicdelay();
	IIC_SET_SDA_LOW();//IIC_SDA = 0;
	iicdelay();
	IIC_SET_SCL_LOW();//IIC_SCL = 0;
	iicdelay();
}
static void iic_stop(void)
{
	IIC_SET_SDA_LOW();//IIC_SDA = 0;
	iicdelay();
	IIC_SET_SCL_HIGH();//IIC_SCL = 1;
	iicdelay();
	IIC_SET_SDA_HIGH();//IIC_SDA = 1;
	iicdelay();
}
static bool iic_check_ack(void)
{
	bool bret;
	u16  timeout;

	IIC_SET_SDA_HIGH();//IIC_SDA = 1;
	iicdelay();
	IIC_SET_SCL_HIGH();//IIC_SCL = 1;
	iicdelay();
	bret = FALSE;
	timeout = 20000;
	do
	{
		if(!IIC_CHK_SDA())//if(IIC_SDA==0)
		{
			bret = TRUE;
			break;
		}
	}while (--timeout);
	IIC_SET_SCL_LOW();//IIC_SCL = 0;
	iicdelay();
	return bret;
}
void iic_tx_ack(type_iic_ack ack)
{
	if(ack==IIC_NACK){
  		IIC_SET_SDA_HIGH();//IIC_SDA = 1;//NACK
    }else{
		IIC_SET_SDA_LOW();//IIC_SDA = 0;//ACK
    }
	iicdelay();
	IIC_SET_SCL_HIGH();//IIC_SCL = 1;
	iicdelay();
	IIC_SET_SCL_LOW();//IIC_SCL = 0;
	iicdelay();
}
static bool iic_tx_byte(u8 byte)
{
	u8   i;
	bool bret;
	i = 8;
	do
	{	
		if (byte&0x80){
        	IIC_SET_SDA_HIGH();//IIC_SDA = 1;
        }else{
        	IIC_SET_SDA_LOW();//IIC_SDA = 0;
        }
		byte<<=1;
		iicdelay();
		IIC_SET_SCL_HIGH();//IIC_SCL = 1;
		iicdelay();
		IIC_SET_SCL_LOW();//IIC_SCL = 0;
		iicdelay();
	}while(--i);
	//check ack
	//I2C_DATA_INPUT; 
	bret = iic_check_ack();
	//I2C_DATA_OUTPUT;
	return bret;
}

static u8 iic_rx_byte(type_iic_ack ack)
{
	u8 i;
    u8 byte;
	
	//I2C_DATA_INPUT;
	IIC_SET_SDA_HIGH();//IIC_SDA = 1;
	i = 8;
    byte = 0;
	do
	{
		IIC_SET_SCL_HIGH();//IIC_SCL = 1;
		iicdelay();
		byte <<= 1;
		if(IIC_CHK_SDA())//if(IIC_SDA==1)
		{
			byte |= 0x01;
		}
		iicdelay();
		IIC_SET_SCL_LOW();//IIC_SCL = 0;
		iicdelay();
	}while(--i);
	//ack & nack
	//I2C_DATA_OUTPUT;
	iic_tx_ack(ack);
	
	return byte;
}

static bool iic_send_bytes(u8 address,u8 command,u8 *pdat,u8 length,bool nextflag)
{
    bool bret;

    bret = FALSE;
	iic_start();
	if(iic_tx_byte(address))//address
	{
		if(iic_tx_byte(command))//command
		{
			bret = TRUE;
			while(length)
			{
				length--;
				if(!iic_tx_byte(*pdat))//tx data
				{
					bret = FALSE;
					break;
				}
				if(nextflag)
				{
					pdat++;
				}
			}
		}
	}
	iic_stop();
	
	return bret;
}
#endif

void iic_init(void) 
{    
    iic_highspeed = IIC_SPEED_HIGH;
}

bool iic_send_byte(u8 address,u8 cmd,u8 dat)
{
	return iic_send_bytes(address,cmd,&dat,1,FALSE);
}

bool iic_send_same_bytes(u8 address,u8 cmd,u8 dat,u8 len)
{
	return iic_send_bytes(address,cmd,&dat,len,FALSE);
}	

bool iic_send_mul_bytes(u8 address,u8 cmd,u8 *pdat,u8 len)
{
	return iic_send_bytes(address,cmd,pdat,len,TRUE);
}	

bool iic_recv_mul_bytes(u8 address, u8 cmd, u8* pdat, u8 len)
{
	bool flag;

    flag = FALSE;
	iic_start();
	if (iic_tx_byte(address))//address
	{
		if (iic_tx_byte(cmd))//command
		{
			iic_start();
			if(iic_tx_byte(address|0x01))//read cmd
			{
				while(--len)
				{
					*pdat++ = iic_rx_byte(IIC_ACK);//rx data
				}
				*pdat = iic_rx_byte(IIC_NACK);
				flag = TRUE;
			}
		}
	}
	iic_stop();
 	return flag;
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

