#ifndef _BIT_TYPE_H_
#define _BIT_TYPE_H_

#ifdef MCU_F0

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */

#endif

typedef unsigned long long	u64;
typedef long long	s64;
#ifndef bool
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#endif

typedef union {
	unsigned char Byte;
	struct {
		unsigned int N0:4;
		unsigned int N1:4;
	} Nibbles;
	struct {
		unsigned int b0:1;
		unsigned int b1:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b6:1;
		unsigned int b7:1;
	} Bits;
} Type8Bits;

typedef union {
	unsigned short Short;
	struct {
		unsigned char B0;
		unsigned char B1;
	} Bytes;
	struct {
		unsigned int N0:4;
		unsigned int N1:4;
		unsigned int N2:4;
		unsigned int N3:4;
	} Nibbles;
	struct {
		unsigned int b0:1;
		unsigned int b1:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b6:1;
		unsigned int b7:1;
		unsigned int b8:1;
		unsigned int b9:1;
		unsigned int b10:1;
		unsigned int b11:1;
		unsigned int b12:1;
		unsigned int b13:1;
		unsigned int b14:1;
		unsigned int b15:1;
	} Bits;
} Type16Bits;

typedef union {
	struct {
		unsigned char B0;
		unsigned char B1;
		unsigned char B2;
	} Bytes;
	struct {
		unsigned int N0:4;
		unsigned int N1:4;
		unsigned int N2:4;
		unsigned int N3:4;
		unsigned int N4:4;
		unsigned int N5:4;
	} Nibbles;
	struct {
		unsigned int b0:1;
		unsigned int b1:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b6:1;
		unsigned int b7:1;
		unsigned int b8:1;
		unsigned int b9:1;
		unsigned int b10:1;
		unsigned int b11:1;
		unsigned int b12:1;
		unsigned int b13:1;
		unsigned int b14:1;
		unsigned int b15:1;
		unsigned int b16:1;
		unsigned int b17:1;
		unsigned int b18:1;
		unsigned int b19:1;
		unsigned int b20:1;
		unsigned int b21:1;
		unsigned int b22:1;
		unsigned int b23:1;
	} Bits;
} Type24Bits;

typedef union {
	unsigned long Long;
	struct {
		unsigned short S0;
		unsigned short S1;
	} Shorts;
	struct {
		unsigned char B0;
		unsigned char B1;
		unsigned char B2;
		unsigned char B3;
	} Bytes;
	struct {
		unsigned int N0:4;
		unsigned int N1:4;
		unsigned int N2:4;
		unsigned int N3:4;
		unsigned int N4:4;
		unsigned int N5:4;
		unsigned int N6:4;
		unsigned int N7:4;
	} Nibbles;
	struct {
		unsigned int b0:1;
		unsigned int b1:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b6:1;
		unsigned int b7:1;
		unsigned int b8:1;
		unsigned int b9:1;
		unsigned int b10:1;
		unsigned int b11:1;
		unsigned int b12:1;
		unsigned int b13:1;
		unsigned int b14:1;
		unsigned int b15:1;
		unsigned int b16:1;
		unsigned int b17:1;
		unsigned int b18:1;
		unsigned int b19:1;
		unsigned int b20:1;
		unsigned int b21:1;
		unsigned int b22:1;
		unsigned int b23:1;
		unsigned int b24:1;
		unsigned int b25:1;
		unsigned int b26:1;
		unsigned int b27:1;
		unsigned int b28:1;
		unsigned int b29:1;
		unsigned int b30:1;
		unsigned int b31:1;
	} Bits;
} Type32Bits;


#define LOGIC_FALSE 0		//逻辑假
#define LOGIC_TRUE 1			//逻辑真
#define MAX_1_BYTE 255		//单字节最大值
#define MAX_2_BYTE 65535		//双字节最大值
#define TIME_1014MS 38		//秒计时器=1011.712
#define ZERO 0			//秒计时器置零

#define CLB0	0xfe		//bit0 clear mask
#define CLB1	0xfd		//bit1 clear mask
#define CLB2	0xfb		//bit2 clear mask
#define CLB3	0xf7		//bit3 clear mask
#define CLB4	0xef		//bit4 clear mask
#define CLB5	0xdf		//bit5 clear mask
#define CLB6	0xbf		//bit6 clear mask
#define CLB7	0x7f		//bit7 clear mask
#define BIT0	1		//bit0 set mask
#define BIT1	2		//bit1 set mask
#define BIT2	4		//bit2 set mask
#define BIT3	8		//bit3 set mask
#define BIT4	0x10		//bit4 set mask
#define BIT5	0x20		//bit5 set mask
#define BIT6	0x40		//bit6 set mask
#define BIT7	0x80		//bit7 set mask

#define CLB00	0xfffffffe		//bit00 clear mask
#define CLB01	0xfffffffd		//bit01 clear mask
#define CLB02	0xfffffffb		//bit02 clear mask
#define CLB03	0xfffffff7		//bit03 clear mask
#define CLB04	0xffffffef		//bit04 clear mask
#define CLB05	0xffffffdf		//bit05 clear mask
#define CLB06	0xffffffbf		//bit06 clear mask
#define CLB07	0xffffff7f		//bit07 clear mask
#define CLB08	0xfffffeff		//bit08 clear mask
#define CLB09	0xfffffdff		//bit09 clear mask
#define CLB10	0xfffffbff		//bit10 clear mask
#define CLB11	0xfffff7ff		//bit11 clear mask
#define CLB12	0xffffefff		//bit12 clear mask
#define CLB13	0xffffdfff		//bit13 clear mask
#define CLB14	0xffffbfff		//bit14 clear mask
#define CLB15	0xffff7fff		//bit15 clear mask
#define CLB16	0xfffeffff		//bit16 clear mask
#define CLB17	0xfffdffff		//bit17 clear mask
#define CLB18	0xfffbffff		//bit18 clear mask
#define CLB19	0xfff7ffff		//bit19 clear mask
#define CLB20	0xffefffff		//bit20 clear mask
#define CLB21	0xffdfffff		//bit21 clear mask
#define CLB22	0xffbfffff		//bit22 clear mask
#define CLB23	0xff7fffff		//bit23 clear mask
#define CLB24	0xfeffffff		//bit24 clear mask
#define CLB25	0xfdffffff		//bit25 clear mask
#define CLB26	0xfbffffff		//bit26 clear mask
#define CLB27	0xf7ffffff		//bit27 clear mask
#define CLB28	0xefffffff		//bit28 clear mask
#define CLB29	0xdfffffff		//bit29 clear mask
#define CLB30	0xbfffffff		//bit30 clear mask
/*
#define CLB31	0x7fffffff		//bit31 clear mask
#define CLB32	0xfffffffe		//bit00 clear mask
#define CLB33	0xfffffffd		//bit01 clear mask
#define CLB34	0xfffffffb		//bit02 clear mask
#define CLB35	0xfffffff7		//bit03 clear mask
#define CLB36	0xffffffef		//bit04 clear mask
#define CLB37	0xffffffdf		//bit05 clear mask
#define CLB38	0xffffffbf		//bit06 clear mask
#define CLB39	0xffffff7f		//bit07 clear mask
#define CLB40	0xfffffeff		//bit08 clear mask
#define CLB41	0xfffffdff		//bit09 clear mask
#define CLB42	0xfffffbff		//bit10 clear mask
#define CLB43	0xfffff7ff		//bit11 clear mask
#define CLB44	0xffffefff		//bit12 clear mask
#define CLB45	0xffffdfff		//bit13 clear mask
#define CLB46	0xffffbfff		//bit14 clear mask
#define CLB47	0xffff7fff		//bit15 clear mask
#define CLB48	0xfffeffff		//bit16 clear mask
#define CLB49	0xfffdffff		//bit17 clear mask
#define CLB50	0xfffbffff		//bit18 clear mask
#define CLB51	0xfff7ffff		//bit19 clear mask
#define CLB52	0xffefffff		//bit20 clear mask
#define CLB53	0xffdfffff		//bit21 clear mask
#define CLB54	0xffbfffff		//bit22 clear mask
#define CLB55	0xff7fffff		//bit23 clear mask
#define CLB56	0xfeffffff		//bit24 clear mask
#define CLB57	0xfdffffff		//bit25 clear mask
#define CLB58	0xfbffffff		//bit26 clear mask
#define CLB59	0xf7ffffff		//bit27 clear mask
#define CLB60	0xefffffff		//bit28 clear mask
#define CLB61	0xdfffffff		//bit29 clear mask
#define CLB62	0xbfffffff		//bit30 clear mask
#define CLB63	0x7fffffff		//bit31 clear mask
*/
#define BIT00	0x1		//bit00 set mask
#define BIT01	0x2		//bit01 set mask
#define BIT02	0x4		//bit02 set mask
#define BIT03	0x8		//bit03 set mask
#define BIT04	0x10		//bit04 set mask
#define BIT05	0x20		//bit05 set mask
#define BIT06	0x40		//bit06 set mask
#define BIT07	0x80		//bit07 set mask
#define BIT08	0x100		//bit08 set mask
#define BIT09	0x200		//bit09 set mask
#define BIT10	0x400		//bit10 set mask
#define BIT11	0x800		//bit11 set mask
#define BIT12	0x1000		//bit12 set mask
#define BIT13	0x2000		//bit13 set mask
#define BIT14	0x4000		//bit14 set mask
#define BIT15	0x8000		//bit15 set mask
#define BIT16	0x10000		//bit16 set mask
#define BIT17	0x20000		//bit17 set mask
#define BIT18	0x40000		//bit18 set mask
#define BIT19	0x80000		//bit19 set mask
#define BIT20	0x100000		//bit20 set mask
#define BIT21	0x200000		//bit21 set mask
#define BIT22	0x400000		//bit22 set mask
#define BIT23	0x800000		//bit23 set mask
#define BIT24	0x1000000		//bit24 set mask
#define BIT25	0x2000000		//bit25 set mask
#define BIT26	0x4000000		//bit26 set mask
#define BIT27	0x8000000		//bit27 set mask
#define BIT28	0x10000000		//bit28 set mask
#define BIT29	0x20000000		//bit29 set mask
#define BIT30	0x40000000		//bit30 set mask
#define BIT31	0x80000000		//bit31 set mask
#define CLB0300	0xfffffff0		//bit03~00 clear mask
#define CLB0704	0xffffff0f		//bit07~04 clear mask
#define CLB1108	0xfffff0ff		//bit11~08 clear mask
#define CLB1512	0xffff0fff		//bit15~12 clear mask
#define CLB1916	0xfff0ffff		//bit19~16 clear mask
#define CLB2320	0xff0fffff		//bit23~20 clear mask
#define CLB2724	0xf0ffffff		//bit27~24 clear mask
#define CLB3128	0x0fffffff		//bit31~28 clear mask

#endif

