#include"delay.h"
/*******************ÑÓÊ±z(ms)***********************/
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=112;y>0;y--);  //1ms
}
