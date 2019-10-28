/*******************************************************************
*file name:    meas_eeprom.c
*project:      s5
*Description:  eeprom read write
*Platform:     stm32f10x
*firmware:     v1.0
*Author:       cwd
*data:         2013.1.25
*note:         
*******************************************************************/
#include "global.h"


#ifdef ENABLE_EEPROM

#if defined(AT24C16)
    #define E_PAGE_SIZE     16 /*AT24C16:128 pages of 16 bytes each*/
    #define E_ADDR_SW(addr) (ADDRESS_EEPROM+(u8)(((u16)(addr)>>7)&0x000e))
#elif defined(AT24C08)
    #define E_PAGE_SIZE     16 /*AT24C08:64 pages of 16 bytes each*/
    #define E_ADDR_SW(addr) (ADDRESS_EEPROM+(u8)(((u16)(addr)>>7)&0x0006))
#elif defined(AT24C04)
    #define E_PAGE_SIZE     16 /*AT24C04:32 pages of 16 bytes each*/
    #define E_ADDR_SW(addr) (ADDRESS_EEPROM+(u8)(((u16)(addr)>>7)&0x0002))
#else
    #define E_PAGE_SIZE     8  /*AT24C02:32 pages of 8 bytes each*/
    #define E_ADDR_SW(addr) (ADDRESS_EEPROM)
#endif

#if 0
/*
描述:   写一个字节到eeprom的指定地址
输入:   写入的地址,数据
输出:   无
*/
bool Eeprom_WriteByte(u16 address, u8 data)
{
    bool flag;
    
    if (address > SIZE_EEPROM)
        return FALSE;
    
    SetPortEepromWriteEnable();
    
    flag = I2cSendByte(E_ADDR_SW(address), address&0xff, data);   //从机地址+写操作
  
    DelayMS(10);
  
    SetPortEepromWriteDisable();
    
    return flag;
}


/*
描述:   从eeprom的指定地址读取一个字节
输入:   读取的地址
输出:   读到的数据
*/

bool Eeprom_ReadByte(u16 address,u8 *pdata)
{
    bool flag=FALSE;
    
    if (address > SIZE_EEPROM)
        return FALSE;
    
    I2cStart();
    if (I2cSend8Bits(E_ADDR_SW(address))) //从机地址
    {
        if (I2cSend8Bits(address&0xff))
        {
            I2cStart();
            if (I2cSend8Bits(E_ADDR_SW(address)+1)//从机地址+写
            {
                *pdata = I2cRecv8Bits(IIC_NACK);
                flag = TRUE;
            }
        }
    }
    I2cStop();
    return flag;
}
#endif

/*
描述:   从eeprom指定的开始地址读取n个字节
输入:   读取的开始地址,数据指针,长度
输出:   ucEepromBuffer,是否成功
*/
bool Eeprom_ReadData(u16 address, u8 *pdata, u16 length)
{   
    if ((address+length) > SIZE_EEPROM)
        return FALSE;

    SetI2cHigh(FALSE);
    //SetI2cHigh(TRUE);

    if(I2c2RecvMulBytes(E_ADDR_SW(address), address&0xff, pdata, length)==FALSE)
        return FALSE;

    return TRUE;
}

/*
描述:   从eeprom指定的开始地址,写n个字节(最多16个字节)
输入:   读取的开始地址,数据指针,长度
输出:   写是否成功
*/
bool Eeprom_WriteData(u16 address, u8 *pdata, u16 length)
{
    u16 len;
    u8 state=0;
    
    if ((address+length) > SIZE_EEPROM)
        return FALSE;

    SetPortEepromWriteEnable();

    SetI2cHigh(FALSE);
    //SetI2cHigh(TRUE);

    while(1)
    {
        if(state==0)
        {
            state = 1;
            len = E_PAGE_SIZE - address&(E_PAGE_SIZE-1);
            if(len>length) /*不够满一页*/
                len = length;
        }
        else
        {
            if(length>=E_PAGE_SIZE)
                len = E_PAGE_SIZE;
            else  /*不够满一页*/
                len = length;
        }
        if(I2c2SendMulBytes(E_ADDR_SW(address), address&0xff, pdata, len)==FALSE)
            return FALSE;
        address += len;
        pdata += len;
        length -= len;
        DelayMS(6); /*>5ms*/
        if(length==0)
            break;
    }
    SetPortEepromWriteDisable();

    return TRUE;
}

/*
描述:   初始化EEPROM,连续发9个CLK,DATA高
输入:   无
输出:   无
*/
void Eeprom_Init(void)
{
    u8 nX=9;
        
    SetPortEepromWriteDisable();
    
    SetI2cHigh(FALSE);
    //SetI2cHigh(TRUE);
    
    I2C2_DATA_HIGH();
    do //发出9个时钟
    {
        I2C2_CLK_LOW();
        I2cDelay();
        I2C2_CLK_HIGH();        
        I2cDelay();
    }while (--nX);
}

#else   //use Flash

#define FLASH_SIZE_MAX  64  // 64*2 = 128 Bytes

/*
 this is to restore,update the system parameters. and will be written to the flash before power off.
 all the contents will be read out from the flash after power on.
*/
u16 FlashContents[FLASH_SIZE_MAX];


//=======================================================================
//擦除mcu的flash指定的一页，pageAddr为页起始地址      
//erease one page.
//if succeed, return FLASH_COMPLETE.
//if failed, return error code.
//this function will be called when Powering ON/OFF, or during calibration.
//=======================================================================
bool McuFlash_EreasePage(u32 pageAddr)
{
    FLASH_Status status;
    u32 test;

    FLASH_Unlock();
    status = FLASH_ErasePage(pageAddr);  /* Erase Page */
    FLASH_Lock();

    /* If erase operation was failed, a Flash error code is returned */
    if (status != FLASH_COMPLETE)
        return FALSE;
    
    test = (*(__IO uint32_t*)pageAddr);
       
    if(test == 0xFFFFFFFF)    //Ereased
        return TRUE;
    else    //something wrong.
        return FALSE;
}

//=======================================================================
//Write U16 to flash
//功能子函数：从address地址连续写入length个半字(16位)的数据到flash
//=======================================================================
bool McuFlash_WriteData(u32 address, u16 *pdata, u16 length)
{
    u32 i;

    FLASH_Unlock();

    for (i=0; i<length; i++)    //write to Flash.
    {
        if (FLASH_ProgramHalfWord(address+(i<<1), *pdata++) != FLASH_COMPLETE)    //write contents to flash.
        {
            FLASH_Lock();
            return FALSE;
        }
    }

    FLASH_Lock();
    
    return TRUE;
}

//=======================================================================
//Read U16 to flash 
//功能子函数：从address地址连续读取length个半字(16位)的数据到pdata[]数组
//=======================================================================
bool McuFlash_ReadData(u32 address, u16 *pdata, u16 length)
{
    u32 i;

    for(i=0; i<length; i++)
    {
        *pdata++ = *(__IO uint16_t*)(address+(i<<1)); //count by byte.
    }

    return TRUE;
}

//=======================================================================
//Initiate the Flash pages. (erease them all) 擦出FLASH最后一页空间（63nd）
//this function will be called only once during PCBA testing.
//=======================================================================
bool EE_Flash_Init(void)
{
    u16 i = 3;
    bool FlashStatus;

    do
    {
        FlashStatus = McuFlash_EreasePage(VARIABLE_START_ADDRESS);
        i--;
    }while ((FlashStatus != TRUE) && (i>0));

    
    return FlashStatus;
}

//=========================================================
//EE_Flash_Write_All_Contents 擦除并将缓冲区所有数据写入FLASH
//write into Flash all the contents when powering off the device.
//=========================================================
bool EE_Flash_Write_All_Contents(void)
{
    EE_Flash_Init();       //erease the Flash.
    return McuFlash_WriteData(VARIABLE_START_ADDRESS, (u16*)&FlashContents[0], FLASH_SIZE_MAX);
}

//=========================================================
//EE_Flash_Read_All_Contents 从FLASH读出所有数据到缓冲区
//read all the contents from Flash when powering on the device.
//=========================================================
bool EE_Flash_Read_All_Contents (void)
{
    return McuFlash_ReadData(VARIABLE_START_ADDRESS, (u16*)&FlashContents[0], FLASH_SIZE_MAX);
}

//=======================================================================
//EE_Flash_Update_Buffer_Contents.
//upate the contents in uv FlashContents[64] buffer.写入缓冲区
//=======================================================================
bool Flash_WriteData(u16 address, u8 *pdata, u16 length)
{
    u8 *pbuf = (u8*)&FlashContents[0];
    u32 i;

    pbuf += address;
    
    for(i=0;i<length;i++)
        *pbuf++ = *pdata++;
    
    return TRUE;
}

//=======================================================================
//EE_Flash_Update_Buffer_Contents.
//upate the contents in uv FlashContents[64] buffer.从缓冲区读出
//=======================================================================
bool Flash_ReadData(u16 address, u8 *pdata, u16 length)
{
    u8 *pbuf = (u8*)&FlashContents[0];
    u32 i;

    pbuf += address;
    
    for(i=0;i<length;i++)
        *pdata++ = *pbuf++;
    
    return TRUE;
}

#endif

