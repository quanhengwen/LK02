#include <reg52.h>
#include <math.h>
#include <stdio.h>  
#include "1602.h"
#include "delay.h"
#include "HMC5883.h"
#include "ADXL345.h"

#define uchar unsigned char
extern BYTE BUF[8];

void main()
{
	uchar devid;
    int x,y,z;
    double angle;  	
    init();
    Init_ADXL345();
    Init_HMC5883();
	devid=Single_Read(ADXL345_SlaveAddress,0X00); //读出的数据为0XE5,表示正确
    while(1)            //循环
    { 
		Init_ADXL345();                //初始化ADXL345 
		Multiple_read(ADXL345_SlaveAddress,0x32);       //连续读出数据，存储在BUF中
		display_x();                   //---------显示X轴
    	display_y();                   //---------显示Y轴
    	display_z();                   //---------显示Z轴

		Multiple_read_HMC5883();      //连续读出数据，存储在BUF中
	    x=BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register
	    z=BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register
	    y=BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register
	
	    angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
	    angle*=10;
	    conversion(angle);       //计算数据和显示                
   }
}