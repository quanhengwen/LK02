/*********************************************
文件名称：1602.c
文件功能：1602液晶驱动
**********************************************/
#include"1602.h"
#include<reg52.h>
#include"delay.h"

sbit lcden=P2^7;
sbit rs=P2^5;
sbit rw=P2^6;

/*******************************************
函数名称：write_com
函数功能：1602液晶写指令
入口参数：c:1602液晶指令
出口参数：无
********************************************/
void write_com(uchar com)
{
	rs=0;
	delay(5);
	P0=com;
	lcden=1;
	delay(5);
	lcden=0;	
}
/*****************************************
函数名称：write—date
函数功能：1602液晶写数据
入口参数：c:1602液晶数据
出口参数：无
*****************************************/
void write_data(uchar date)//数据写入
{
	rs=1;
	delay(5);
	P0=date;
	lcden=1;
	delay(5);
	lcden=0;	
}
/*******************************************
函数名称：init
函数功能：1602液晶初始化
人口参数：无
出口参数：无
*******************************************/
void init()//液晶初始化
{

	rw=0;
	write_com(0x38); //显示模式(初始化液晶)设置
	write_com(0x0c);  //光标不闪
	write_com(0x06); //显示开关及光标
	write_com(0x01);//数据指针设置(设置数据地址指针)清屏指令，每次显示下一次内容时，必需清屏
	write_com(0x80);	
}
