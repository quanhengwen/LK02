#ifndef __1602_H__
#define __1602_H__

#define uchar unsigned char
#define uint unsigned int

void write_com(uchar com);
void write_data(uchar date);//数据写入
void init();//液晶初始化

#endif