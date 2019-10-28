#include  <REG51.H>	 	
#include  <INTRINS.H>
#include  "ADXL345.h"
#include  "1602.h"

#define   uchar unsigned char
#define   uint unsigned int	
sbit	  SCL=P2^2;      //IIC时钟引脚定义
sbit 	  SDA=P2^3;      //IIC数据引脚定义

uchar m,n;
typedef unsigned char  BYTE;							   
typedef unsigned short WORD;

BYTE BUF1[8];                         //接收数据缓存区      	

int  dis_data;                       //变量

/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5u()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5m()
{
    WORD n = 560;

    while (n--);
}

/**************************************
起始信号
**************************************/
void ADXL345_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5u();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5u();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5u();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5u();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5u();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5u();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit ADXL345_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5u();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5u();                 //延时
    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5u();             //延时
        SCL = 0;                //拉低时钟线
        Delay5u();             //延时
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE ADXL345_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5u();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5u();             //延时
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uchar Single_Read(uchar SlaveAddress,uchar REG_Address)
{  
	uchar REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);                   //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read(uchar SlaveAddress,uchar ST_Address)
{   uchar i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(ST_Address);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<7; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF1[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 6)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    Delay5m();
}

//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
   Single_Write(ADXL345_SlaveAddress,0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write(ADXL345_SlaveAddress,0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write(ADXL345_SlaveAddress,0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write(ADXL345_SlaveAddress,0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write(ADXL345_SlaveAddress,0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write(ADXL345_SlaveAddress,0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write(ADXL345_SlaveAddress,0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}

void conversion1(uint temp_data)  
{  
    temp_data=temp_data%10000;   //取余运算
	m=temp_data/1000;
    temp_data=temp_data%1000;    //取余运算
    n=temp_data/100;	
}

//***********************************************************************
//显示x轴
void display_x()
{   
	float temp;
    dis_data=(BUF1[1]<<8)+BUF1[0];  //合成数据   
	if(dis_data<0)
	{
		dis_data=-dis_data;
		write_com(0x80+10);
	    write_data('-');   //显示正负符号位
	}
	else 
	write_com(0x80+10);
    write_data(' '); //显示空格
    temp=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
    conversion1(temp);          //转换出显示需要的数据

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
//显示y轴
void display_y()
{     
	float temp;
    dis_data=(BUF1[3]<<8)+BUF1[2];  //合成数据   
	if(dis_data<0)
	{
		dis_data=-dis_data;
	    write_com(0x80+0x40+2);
	    write_data('-');      //显示正负符号位
	}
	else 
	write_com(0x80+0x40+2);
    write_data(' '); //显示空格

    temp=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
    conversion1(temp);          //转换出显示需要的数据
	
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
//显示z轴
void display_z()
{      
	float temp;
    dis_data=(BUF1[5]<<8)+BUF1[4];    //合成数据   
	if(dis_data<0)
	{
		dis_data=-dis_data;
	    write_com(0x80+0x40+10);
	    write_data('-');       //显示负符号位
	}
	else 
	write_com(0x80+0x40+10);
    write_data(' ');  //显示空格

    temp=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
    conversion1(temp);          //转换出显示需要的数据
	
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