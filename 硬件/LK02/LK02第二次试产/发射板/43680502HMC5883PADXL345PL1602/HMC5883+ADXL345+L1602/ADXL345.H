#ifndef __ADXL345_H__
#define __ADXL345_H__

#define uchar unsigned char
#define uint unsigned int

#define	ADXL345_SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                                      //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A

uchar Single_Read(uchar SlaveAddress,uchar REG_Address);
void Multiple_read(uchar SlaveAddress,uchar ST_Address);
void Init_ADXL345();
void display_x();
void display_y();
void display_z();

#endif