/*******************************************************************
*file name:    drv_adc.c
*project:      s2
*Description:  ADC DMA sample
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2014.6.4
*note:         null
*******************************************************************/
#include "global.h"


void spi1_stop(void)
{
//  GP22_SPI_CS_DISABLE();
}

u8 spi1_write_byte(u8 tx_dat)
{
    u8 rx_dat;

    while((SPI1->SR & SPI_I2S_FLAG_TXE) == 0);
    SPI1->DR = tx_dat;

    while((SPI1->SR & SPI_I2S_FLAG_RXNE) == 0);
    rx_dat = SPI1->DR;

    //while((SPI1->SR & SPI_I2S_FLAG_BSY) != (u16)RESET);

    return rx_dat;
}


//写一个半字
//tx_dat:要写入的半字
//返回值:NULL
u16 spi2_write_word(u16 tx_dat)
{
	TLC5618_SPI_CS_ENABLE();

    while((SPI2->SR & SPI_I2S_FLAG_TXE) == 0);
	SPI2->DR = (tx_dat>>8);

    while((SPI2->SR & SPI_I2S_FLAG_TXE) == 0);
    SPI2->DR = tx_dat&0xff;

    while((SPI2->SR & SPI_I2S_FLAG_BSY) != 0);

    TLC5618_SPI_CS_DISABLE();
    
    return 0;
}

