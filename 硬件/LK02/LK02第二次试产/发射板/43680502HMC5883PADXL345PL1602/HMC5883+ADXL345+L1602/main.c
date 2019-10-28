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
	devid=Single_Read(ADXL345_SlaveAddress,0X00); //����������Ϊ0XE5,��ʾ��ȷ
    while(1)            //ѭ��
    { 
		Init_ADXL345();                //��ʼ��ADXL345 
		Multiple_read(ADXL345_SlaveAddress,0x32);       //�����������ݣ��洢��BUF��
		display_x();                   //---------��ʾX��
    	display_y();                   //---------��ʾY��
    	display_z();                   //---------��ʾZ��

		Multiple_read_HMC5883();      //�����������ݣ��洢��BUF��
	    x=BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register
	    z=BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register
	    y=BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register
	
	    angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
	    angle*=10;
	    conversion(angle);       //�������ݺ���ʾ                
   }
}