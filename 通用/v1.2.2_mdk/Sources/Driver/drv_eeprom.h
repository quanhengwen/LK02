/*******************************************************************
*file name:     meas_eeprom.h
*project:        s5
*Description:  eeprom read write
*Platform: 	 stm32f10x
*firmware:      v1.0
*Author:         cwd
*data:		  2013.1.25
*note:            null
*******************************************************************/
#ifndef _DRV_EEPROM_H_
#define _DRV_EEPROM_H_



#ifdef ENABLE_EEPROM

#define ADDRESS_EEPROM 0xa0

#define AT24C02

//EEPROM³ß´ç
#if defined(AT24C08)
	#define SIZE_EEPROM	1024	
#elif defined(AT24C04)
	#define SIZE_EEPROM	512		
#else  //AT24C02
	#define SIZE_EEPROM	256		
#endif

typedef enum {		
	EEP_WRITE,
	EEP_READ,
}E_EepromCmd;

bool Eeprom_ReadData(u16 address, u8 *pdata, u16 length);
bool Eeprom_WriteData(u16 address, u8 *pdata, u16 length);
void Eeprom_Init(void);

#else	//use Flash

#define SIZE_EEPROM		128     // Flash emulated EEPROM size (in byte)

#define VARIABLE_START_ADDRESS  ((uint32_t)0x0800FC00) /* EEPROM emulation start address: the last page (the 63nd k)*/
//#define VARIABLE_START_ADDRESS  ((uint32_t)0x08007C00) /* EEPROM emulation start address: the last page (the 31nd k)*/

bool EE_Flash_Init(void);

bool Flash_WriteData(u16 address, u8 *pdata, u16 length);
bool Flash_ReadData(u16 address, u8 *pdata, u16 length);

bool EE_Flash_Write_All_Contents (void);
bool EE_Flash_Read_All_Contents (void);

bool McuFlash_EreasePage(u32 pageAddr);
bool McuFlash_WriteData(u32 address, u16 *pdata, u16 length);
bool McuFlash_ReadData(u32 address, u16 *pdata, u16 length);

#endif  //end if using Flash


#endif


