#include  <INTRINS.H>
#include  <REG51.H>
#include  <stdio.h>
#include "HMC5883.h"	
#include "1602.h"


sbit	  SCL=P2^0;      //IICʱ�����Ŷ���
sbit 	  SDA=P2^1;      //IIC�������Ŷ���

#define SlaveAddress   0x3C   //����������IIC�����еĴӵ�ַ

typedef unsigned short WORD;

BYTE BUF[8];                         //�������ݻ�����      	
uchar ge,shi,bai,qian,wan;           //��ʾ����

/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
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
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
��ʼ�ź�
**************************************/
void HMC5883_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void HMC5883_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void HMC5883_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit HMC5883_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void HMC5883_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    HMC5883_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE HMC5883_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}

//***************************************************

void Single_Write_HMC5883(uchar REG_Address,uchar REG_data)
{
    HMC5883_Start();                  //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    HMC5883_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    HMC5883_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
    HMC5883_Stop();                   //����ֹͣ�ź�
}

////********���ֽڶ�ȡ�ڲ��Ĵ���*************************
//uchar Single_Read_HMC5883(uchar REG_Address)
//{  uchar REG_data;
//    HMC5883_Start();                          //��ʼ�ź�
//    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
//    HMC5883_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ    
//    HMC5883_Start();                          //��ʼ�ź�
//    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
//    REG_data=HMC5883_RecvByte();              //�����Ĵ�������
//    HMC5883_SendACK(1);   
//    HMC5883_Stop();                           //ֹͣ�ź�
//    return REG_data; 
//}
//******************************************************
//
//��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
//
//******************************************************
void Multiple_read_HMC5883(void)
{   uchar i;
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    HMC5883_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x32��ʼ    
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
     for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = HMC5883_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           HMC5883_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //��ӦACK
       }
   }
    HMC5883_Stop();                          //ֹͣ�ź�
    Delay5ms();
}

//��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�****
void Init_HMC5883()
{
     Single_Write_HMC5883(0x02,0x00);  //
}

//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000;
    temp_data=temp_data%10000;   //ȡ������
    qian=temp_data/1000;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10;
    temp_data=temp_data%10;      //ȡ������
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