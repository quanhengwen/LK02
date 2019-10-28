#include  <REG51.H>	 	
#include  <INTRINS.H>
#include  "ADXL345.h"
#include  "1602.h"

#define   uchar unsigned char
#define   uint unsigned int	
sbit	  SCL=P2^2;      //IICʱ�����Ŷ���
sbit 	  SDA=P2^3;      //IIC�������Ŷ���

uchar m,n;
typedef unsigned char  BYTE;							   
typedef unsigned short WORD;

BYTE BUF1[8];                         //�������ݻ�����      	

int  dis_data;                       //����

/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5u()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5m()
{
    WORD n = 560;

    while (n--);
}

/**************************************
��ʼ�ź�
**************************************/
void ADXL345_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5u();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5u();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void ADXL345_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5u();                 //��ʱ
    SDA = 1;                    //����������
    Delay5u();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5u();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5u();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit ADXL345_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5u();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5u();                 //��ʱ
    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void ADXL345_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5u();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5u();             //��ʱ
    }
    ADXL345_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE ADXL345_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5u();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5u();             //��ʱ
    }
    return dat;
}

//******���ֽ�д��*******************************************

void Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)
{
    ADXL345_Start();                  //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    ADXL345_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
    ADXL345_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
    ADXL345_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
uchar Single_Read(uchar SlaveAddress,uchar REG_Address)
{  
	uchar REG_data;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=ADXL345_RecvByte();              //�����Ĵ�������
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
//*********************************************************
//
//��������ADXL345�ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
//
//*********************************************************
void Multiple_read(uchar SlaveAddress,uchar ST_Address)
{   uchar i;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_SendByte(ST_Address);                   //���ʹ洢��Ԫ��ַ����0x32��ʼ	
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<7; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF1[i] = ADXL345_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 6)
        {
           ADXL345_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //��ӦACK
       }
   }
    ADXL345_Stop();                          //ֹͣ�ź�
    Delay5m();
}

//*****************************************************************

//��ʼ��ADXL345��������Ҫ��ο�pdf�����޸�************************
void Init_ADXL345()
{
   Single_Write(ADXL345_SlaveAddress,0x31,0x0B);   //������Χ,����16g��13λģʽ
   Single_Write(ADXL345_SlaveAddress,0x2C,0x08);   //�����趨Ϊ12.5 �ο�pdf13ҳ
   Single_Write(ADXL345_SlaveAddress,0x2D,0x08);   //ѡ���Դģʽ   �ο�pdf24ҳ
   Single_Write(ADXL345_SlaveAddress,0x2E,0x80);   //ʹ�� DATA_READY �ж�
   Single_Write(ADXL345_SlaveAddress,0x1E,0x00);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
   Single_Write(ADXL345_SlaveAddress,0x1F,0x00);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
   Single_Write(ADXL345_SlaveAddress,0x20,0x05);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
}

void conversion1(uint temp_data)  
{  
    temp_data=temp_data%10000;   //ȡ������
	m=temp_data/1000;
    temp_data=temp_data%1000;    //ȡ������
    n=temp_data/100;	
}

//***********************************************************************
//��ʾx��
void display_x()
{   
	float temp;
    dis_data=(BUF1[1]<<8)+BUF1[0];  //�ϳ�����   
	if(dis_data<0)
	{
		dis_data=-dis_data;
		write_com(0x80+10);
	    write_data('-');   //��ʾ��������λ
	}
	else 
	write_com(0x80+10);
    write_data(' '); //��ʾ�ո�
    temp=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
    conversion1(temp);          //ת������ʾ��Ҫ������

	write_com(0x80+8);
    write_data('X'); 
	write_com(0x80+9);
    write_data(':');
	write_com(0x80+11);
    write_data(m+0x30);
	write_com(0x80+12);
    write_data('.');
	write_com(0x80+13);
    write_data(n+0x30);
	write_com(0x80+14);
    write_data('g');
}

//***********************************************************************
//��ʾy��
void display_y()
{     
	float temp;
    dis_data=(BUF1[3]<<8)+BUF1[2];  //�ϳ�����   
	if(dis_data<0)
	{
		dis_data=-dis_data;
	    write_com(0x80+0x40+2);
	    write_data('-');      //��ʾ��������λ
	}
	else 
	write_com(0x80+0x40+2);
    write_data(' '); //��ʾ�ո�

    temp=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
    conversion1(temp);          //ת������ʾ��Ҫ������
	
	write_com(0x80+0x40);
    write_data('Y'); 
	write_com(0x80+0x40+1);
    write_data(':');
	write_com(0x80+0x40+3);
    write_data(m+0x30);
	write_com(0x80+0x40+4);
    write_data('.');
	write_com(0x80+0x40+5);
    write_data(n+0x30);
	write_com(0x80+0x40+6);
    write_data('g');  
}

//***********************************************************************
//��ʾz��
void display_z()
{      
	float temp;
    dis_data=(BUF1[5]<<8)+BUF1[4];    //�ϳ�����   
	if(dis_data<0)
	{
		dis_data=-dis_data;
	    write_com(0x80+0x40+10);
	    write_data('-');       //��ʾ������λ
	}
	else 
	write_com(0x80+0x40+10);
    write_data(' ');  //��ʾ�ո�

    temp=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
    conversion1(temp);          //ת������ʾ��Ҫ������
	
	write_com(0x80+0x40+8);
    write_data('Y'); 
	write_com(0x80+0x40+9);
    write_data(':');
	write_com(0x80+0x40+11);
    write_data(m+0x30);
	write_com(0x80+0x40+12);
    write_data('.');
	write_com(0x80+0x40+13);
    write_data(n+0x30);
	write_com(0x80+0x40+14);
    write_data('g'); 
}