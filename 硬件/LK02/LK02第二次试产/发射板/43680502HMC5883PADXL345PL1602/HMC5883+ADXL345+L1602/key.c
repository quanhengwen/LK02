#include"reg52.h"
#include"key.h"
#include"delay.h"
#include"1602.h"

uchar code tab_1[]={"zhuang yuan is a"};//��ʼ��������
uchar code tab_2[]={"good student "};//��ʼ��ʱ���
uchar code tab_3[]={"bad student"};

sbit key0=P1^0;
sbit key1=P1^1;

void key()
{
	uint i;
	if(key1==0)
		{
			delay(5);	   //ֻ����ʱ5��ʱҺ����������ʾ
			if(key1==0)
			{		  		
				 write_com(0x01);
				 write_com(0x81);
				 for(i=0;i<12;i++)
				 	{
						write_data(tab_2[i]);
						delay(200);
					}
						while(!key0);
							{
								void main();
							}
			}
		} 
		if(key0==0)
		{
			delay(5);//����ĳ�ʮ�룬��1602����ʾ
			if(key0==0)
			{		  		
				 write_com(0x01);
				 write_com(0x81);
					 for(i=0;i<11;i++)
					 	{
							write_data(tab_3[i]);
							delay(200);
						}
			}
		}  
}			   

