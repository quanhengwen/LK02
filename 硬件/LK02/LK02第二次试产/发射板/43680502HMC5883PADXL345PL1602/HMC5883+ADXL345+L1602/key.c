#include"reg52.h"
#include"key.h"
#include"delay.h"
#include"1602.h"

uchar code tab_1[]={"zhuang yuan is a"};//初始化年月日
uchar code tab_2[]={"good student "};//初始化时分?
uchar code tab_3[]={"bad student"};

sbit key0=P1^0;
sbit key1=P1^1;

void key()
{
	uint i;
	if(key1==0)
		{
			delay(5);	   //只有延时5秒时液晶屏才有显示
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
			delay(5);//如果改成十秒，则1602不显示
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

