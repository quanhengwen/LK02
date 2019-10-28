#ifndef __HMC5883_H__
#define __HMC5883_H__

#define uchar unsigned char
#define uint unsigned int

typedef unsigned char  BYTE;

void Multiple_read_HMC5883(void);
void Init_HMC5883();
void conversion(uint temp_data) ;

#endif