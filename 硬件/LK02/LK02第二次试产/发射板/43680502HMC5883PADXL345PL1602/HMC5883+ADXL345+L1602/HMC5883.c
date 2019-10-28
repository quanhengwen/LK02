#include  <INTRINS.H>
#include  <REG51.H>
#include  <stdio.h>
#include "HMC5883.h"	
#include "1602.h"


sbit	  SCL=P2^0;      //IIC时钟引脚定义
sbit 	  SDA=P2^1;      //IIC数据引脚定义

#define SlaveAddress   0x3C   //定义器件在IIC总线中的从地址

typedef unsigned short WORD;

BYTE BUF[8];                         //接收数据缓存区      	
uchar ge,shi,bai,qian,wan;           //显示变量

/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
    _nop_();
	_nop_();
	_nop_();
	_nop_();
    _nop_();
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
起始信号
**************************************/
void HMC5883_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void HMC5883_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void HMC5883_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit HMC5883_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void HMC5883_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    HMC5883_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE HMC5883_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}

//***************************************************

void Single_Write_HMC5883(uchar REG_Address,uchar REG_data)
{
    HMC5883_Start();                  //起始信号
    HMC5883_SendByte(SlaveAddress);   //发送设备地址+写信号
    HMC5883_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf 
    HMC5883_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf
    HMC5883_Stop();                   //发送停止信号
}

////********单字节读取内部寄存器*************************
//uchar Single_Read_HMC5883(uchar REG_Address)
//{  uchar REG_data;
//    HMC5883_Start();                          //起始信号
//    HMC5883_SendByte(SlaveAddress);           //发送设备地址+写信号
//    HMC5883_SendByte(REG_Address);                   //发送存储单元地址，从0开始    
//    HMC5883_Start();                          //起始信号
//    HMC5883_SendByte(SlaveAddress+1);         //发送设备地址+读信号
//    REG_data=HMC5883_RecvByte();              //读出寄存器数据
//    HMC5883_SendACK(1);   
//    HMC5883_Stop();                           //停止信号
//    return REG_data; 
//}
//******************************************************
//
//连续读出HMC5883内部角度数据，地址范围0x3~0x5
//
//******************************************************
void Multiple_read_HMC5883(void)
{   uchar i;
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress);           //发送设备地址+写信号
    HMC5883_SendByte(0x03);                   //发送存储单元地址，从0x32开始    
    HMC5883_Start();                          //起始信号
    HMC5883_SendByte(SlaveAddress+1);         //发送设备地址+读信号
     for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = HMC5883_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           HMC5883_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //回应ACK
       }
   }
    HMC5883_Stop();                          //停止信号
    Delay5ms();
}

//初始化HMC5883，根据需要请参考pdf进行修改****
void Init_HMC5883()
{
     Single_Write_HMC5883(0x02,0x00);  //
}

//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000;
    temp_data=temp_data%10000;   //取余运算
    qian=temp_data/1000;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data; 
	
	write_com(0x80);
    write_data('A');
    write_com(0x81);
    write_data(':');
    write_com(0x82);
    write_data(0X30+qian);
    write_com(0x83);
    write_data(0X30+bai);
    write_com(0x84);
    write_data(0X30+shi);
    write_com(0x85);
    write_data('.');
    write_com(0x86);
    write_data(0X30+ge); 
}