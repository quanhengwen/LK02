/*******************************************************************
*file name:     meas_measure.c
*project:        s5
*Description:  i2c read write
*Platform:    MT6250A
*firmware:      v1.0
*Author:         cwd
*data:        2013.1.25
*note:            null
*******************************************************************/
#include "global.h"

#if defined(CWD_DEBUG) || defined(ENABLE_UART_PROTOCOL)

#include<stdarg.h>

//-----------------------------------------------------------------------------
//#define  putchar  put_char
#define  FLOAT_EN

char *printf_dec(char *buf, s32 dec, u32 div)//整数转换成字符串
{
    char temp[12];
    u32 val,len=0;

    if(dec<0)
    {
        dec = -dec;
        *buf++ = '-';
    }
    
    while(1)
    {
        val = dec/10;
        temp[len++] = (dec-val*10)+'0';
        dec = val;
       #ifdef FLOAT_EN
        if(div)
        {
            if(len==div)
                temp[len++] = '.';
            else if((len>div)&&(dec==0)) 
                break;
        }
        else
        {
            if(dec==0) 
                break;
        }
       #else
        if(dec==0) break;
       #endif
    }

    while(len)
    {
        len--;
        *buf++ = temp[len];
    }
    
    return buf;
}

char *printf_hex(char *buf, u32 hex)
{
    u8 cnt=0,temp[12];
    u32 val;

    do
    {
        val = hex&0xf;
        temp[cnt] = val + ((val>9)?('A'-10):'0');
        cnt++;
        hex >>= 4;
    }while(hex);

    while(cnt)
    {
        cnt--;
        *buf++ = temp[cnt];
    }
    
    return buf;
}

/*
    example: Printf("%dmV",520)--> 520mV
             Printf("%f3V",520)--> 0.520V
*/
char *cwdPrintf(char *buf, const char *fmt, va_list ap)
{
    const char *s;
    s32 d;
    u32 div = 0;
    
    while (*fmt) 
    {
        if (*fmt !='%') 
        {
            *buf++ = *fmt;
        }
        else
        {
            fmt++;
            switch (*fmt) 
            {
              #ifdef FLOAT_EN
                case 'f':
                    fmt++;
                    div = *fmt-'0';
              #endif
                case 'd':
                    d = va_arg(ap, s32);
                    buf = printf_dec(buf, d, div);
                    //printf_hex(d,div);
                    div = 0;
                    break;
                case 'x':
                    d = va_arg(ap, s32);
                    buf = printf_hex(buf, d);
                    break;
                case 's':
                    s = va_arg(ap, const char *);
                    while(*s) 
                    {
                        *buf++ = *s++;
                    }
                    break;
                case 'c':
                    *buf++ = va_arg(ap, const char);
                    break;
                /* Add other specifiers here... */              
                default:
                    break;
            }
        }
        fmt++;
    }
    return buf;   /* Dummy return value */
} 

int sPrintf(char *buf, const char *fmt, ...)
{
    int len;
    
    va_list va;

    va_start(va, fmt);
    len = cwdPrintf(buf, fmt, va) - buf;
    va_end(va);

    return len;
}

int mPrintf(const char *fmt, ...)
{
    char ch_buf[128];
    int len;
    va_list va;//变长参数 va_list

    va_start(va, fmt);//#define  va_start(ap,v)     ( ap = (va_list)&v + _INTSIZEOF(v) ) ap指向第一个可变参数在的内存地址
    len = cwdPrintf(ch_buf, fmt, va)- ch_buf;
    va_end(va);       //#define  va_end(ap)         ( ap = (va_list)0 ) 使ap不再指向堆栈,而是跟NULL一样

    if(len>128)   //防止溢出
        len = 128;
    
    put_string(ch_buf, len);

    
    
    return len;
}

#endif


