//-----------------------------------------------------------------------------
// f34x_main.c
//-----------------------------------------------------------------------------
// Copyright 2015 MC Ltd, Inc.
// http://www.mc.com
//
// Program Description:
//
// driver definitions for the pluse measuring.
//
// PRJ:            X HIGH SPEED MEASURING
// Target:         STM32F10X
// Tool chain:     IAR
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (CM)
//    -27 Oct 2015
//    -Latest release before new firmware coding standard
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.h"

#ifdef USE_KEIL
#define asm __asm
#endif
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define OP_CODE_WR(ADDR)    (0x80 | (ADDR))
#define OP_CODE_RD(ADDR)    (0xB0 | (ADDR))

#define OPC_INIT                 0x70
#define OPC_RESET                0x50
#define OPC_ID                   0xB7  // 56bit ID
#define OPC_PW1ST                0xB8
#define OPC_CONFIG2EEPROM        0xC0  // write config to eeprom
#define OPC_EEPROM2CONFIG        0xF0  // read config from eeprom
#define OPC_CONFIG_CMP           0xC5  // compare config & eeprom
//-----------------------------------------------------------------------------
#define OPC_START_CYCLE          0x01
#define OPC_START_TEMP           0x02
#define OPC_START_CAL_RESONATOR  0x03
#define OPC_START_CAL_TDC        0x04
#define OPC_RESTART_CYCLE        0x05
#define OPC_RESTART_TEMP         0x06

extern T_SysParam SysSeting;
extern u32  status_gp2;
extern u8   flag_meas;
extern u16 Ax;
extern u8 FLAG_APD_AGC_adj;
extern u8  Flag_Cal;
extern u8  Flag_ApdGn;
//extern u32  rd_reg_x;
extern u16	    LD_NOW;
//static u16     LD_OLD=0;
static u16	LD_VAL=1420;
static u16	AGC_VAL=500;
static u16  GP22_NS=0;
extern u8  APDGainState;//APD����״̬
//-----------------------------------------------------------------------------

void dly100ns(u32 ns)
{
    while(ns--) // 5��ָ������ 104ns
    {
        asm("NOP");asm("NOP");asm("NOP");
    }
}

void delay1us(u32 us)
{
    while(us--) // 1us
    {
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        asm("NOP");
        //USART_CmdParse();
    }
}

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void gp22_send_byte (u8 byte)
{
    GP22_SPI_CS_ENABLE();
    asm("NOP");
    asm("NOP");
    spi1_write_byte(byte);
    asm("NOP");
    GP22_SPI_CS_DISABLE();
}

void gp22_write_config_reg (u8 op_code,u32 config_reg)
{
    GP22_SPI_CS_ENABLE();
    asm("NOP");
    asm("NOP");
    spi1_write_byte(op_code);
    spi1_write_byte(config_reg>>24); // high
    spi1_write_byte(config_reg>>16); // mid2
    spi1_write_byte(config_reg>>8);  // mid1
    spi1_write_byte(config_reg);     // low
    asm("NOP");
    GP22_SPI_CS_DISABLE();
}

u32 gp22_read_dword(u8 op_code)
{
    u32 i, result_read;
	
    GP22_SPI_CS_ENABLE();
    asm("NOP");
    asm("NOP");
    spi1_write_byte(op_code);

    result_read = spi1_write_byte(0xFF);
    for (i = 1; i < 4; i++)
    {       
        result_read <<= 8;
        result_read |= spi1_write_byte(0xFF);
    }
    asm("NOP");
    GP22_SPI_CS_DISABLE();
    
    return result_read;
}

u8 ReadGP22Status(void)
{
  u8    Flag_tdc=0;
  
  status_gp2=gp22_read_dword(OP_CODE_RD(0x04));
  status_gp2>>=16;
  //Printf("S:%d\r\n",state);//Printf("%f2m\n",dist);
  if((status_gp2&0x0600)==0)//if((status_gp2&0x0300)==0)
      Flag_tdc=0;//TDCδ���
  else
      Flag_tdc=1;//TDC���
  return Flag_tdc;
}

void gp22_read_spi_test_reg(void)
{ 
#if 1
    int i;
    u8 buf[7];
    
    GP22_SPI_CS_ENABLE();
    asm("NOP");
    spi1_write_byte(OPC_ID);

    for(i=0;i<7;i++)
        buf[i] = spi1_write_byte(0xFF);
    
    GP22_SPI_CS_DISABLE();
    
    Printf("gp22 ID:%x,%x,%x,%x,%x,%x,%x\n",
        buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6]);
#else
    u8 id;

    GP22_SPI_CS_ENABLE();

    spi1_write_byte(OP_CODE_RD(5));

    id = spi1_write_byte(0xFF);

    GP22_SPI_CS_DISABLE();

    Printf("gp22 spi test ID = %x\r\n",id);
#endif
}
/*
void gp22_init_2(void)
{
    GP22_SPI_CS_DISABLE();
    GP22_RSTN_DISABLE();
    delay1us(1);;
    GP22_RSTN_ENABLE();
    delay1us(1);;
    GP22_RSTN_DISABLE();
    delay1us(1);;
    gp22_send_byte(OPC_RESET);
    delay1us(500);
    
    gp22_write_config_reg(OP_CODE_WR(0x00), 0x00242f12);//0x00242712 //0x00242112//me 0x00242212// 75m up 00042f12
    dly100ns(2);
    // CR1: EN_FAST_INIT = 0, HIT1 = 1, HITIN2 = 1, HITIN1 = 1, ...
    gp22_write_config_reg(OP_CODE_WR(0x01), 0x21420023); //0x21420023 me
    dly100ns(2);
    // CR2: EN_INT = b101, RFEDGE1 = RFEDGE2 = 0, DELVAL1 = 0
    gp22_write_config_reg(OP_CODE_WR(0x02), 0xE0000057);//0xA0000057//me 0x20000057//ֻʱ��ALU�ж�
    
    dly100ns(2);    
    // CR3: EN_ERR_VAL = 1,timeout.
    gp22_write_config_reg(OP_CODE_WR(0x03), 0x00000041);//0x00000041 timeout=ffffffff,64us=9600m
    dly100ns(2);
    gp22_write_config_reg(OP_CODE_WR(0x04), 0x20000042);
    dly100ns(2);
    gp22_write_config_reg(OP_CODE_WR(0x05), 0x00000029);
    dly100ns(2);
    // CR6: DOUBLE_RES = 1, 90ps->45ps
    gp22_write_config_reg(OP_CODE_WR(0x06), 0x00001038);//0x00001038//0x00101038//ģʽ������������22ps
    
    delay1us(100);
    gp22_send_byte(OPC_INIT);
    asm("NOP");
 //   gp22_read_spi_test_reg();
    GP22_START_ENABLE();
    GP22_STOP1_ENABLE();
}
*/
void gp22_init(void)
{
    GP22_SPI_CS_DISABLE();
    delay1us(100);
    GP22_RSTN_DISABLE();
    delay1us(100);;
    GP22_RSTN_ENABLE();
    delay1us(100);;
    GP22_RSTN_DISABLE();
    delay1us(100);;
    GP22_START_ENABLE();
    GP22_STOP1_ENABLE();

    gp22_send_byte(OPC_RESET);
    delay1us(700);
    
    //gp22_write_config_reg(OP_CODE_WR(0x01), 0x01C18000);
    //ANZ_FIRE = 1(1����������) DIV_FIRE=2 (3��Ƶ)
    // CR0: DIV_CLKHS = 2, START_CLKHS = 1, CALIBRATE = 0(У׼�رս�������Χ1����), 
    // NO_CAL_AUTO = 0(�������Զ�У׼), MESSB2 = 0(������Χ1), NEG_STOP = 0(������), NEG_START = 1(�½���), ...
    gp22_write_config_reg(OP_CODE_WR(0x00), 0x00242712);//0x00242712 //0x00240712
    // CR1: EN_FAST_INIT = 0, HIT1 = 1, HITIN2 = 1, HITIN1 = 1, ...
    gp22_write_config_reg(OP_CODE_WR(0x01), 0x02420023); //0x01410000//0x02420023
    // CR2: EN_INT = b101, RFEDGE1 = RFEDGE2 = 0, DELVAL1 = 0
    gp22_write_config_reg(OP_CODE_WR(0x02), 0xA0000057);//0xE0000057//me 0x20000057//ֻʱ��ALU�ж�//F80000000�����½������� 
    // CR3: EN_ERR_VAL = 1,timeout.
    gp22_write_config_reg(OP_CODE_WR(0x03), 0x00000041);//0x20000041//me 0x39000041//EN_ERR_VAL close
    gp22_write_config_reg(OP_CODE_WR(0x04), 0x20000042);
    gp22_write_config_reg(OP_CODE_WR(0x05), 0x00000029);
    // CR6: DOUBLE_RES = 1, 90ps->45ps
    gp22_write_config_reg(OP_CODE_WR(0x06), 0x00000038);//0x00001038//0x00101038//ģʽ1����������45ps
    delay1us(100);
}

//������㺯��
u32 CalcDistance(u32 val)
{
    //u64 dist;
    float dist_f;

    #define GP22_CLK     1.25//5M/2//1.25 /* 5MHZ/4 = 1.25MHZ */
    //#define GP22_NS      800//800  /* (1000/GP22_CLK) = 1000ns/1.25 = 800ns */
    #define DIST_PER_NS  (u32)(119916983) /* ((u64)C_VELOCITY*(GP22_NS/2)) �Ŵ� 10000 �� ,��λ cm */
    #define GP22_CM_GAIN (u32)(655360000) /*  �Ŵ� 10000 �� ,����65536, ����float���� */

    dist_f = (((float)val)/65536.0) * (GP22_NS/2) * C_VELOCITY-430;
    //dist = (((s64)val*DIST_PER_NS + (GP22_CM_GAIN/2))/GP22_CM_GAIN - 400);

    return (u32)dist_f;
    //return dist;
}
//����ģʽ����
void Mode_Config(u8 mode)
{
      if(mode==1)
      {
		gp22_send_byte(OPC_RESET);

        gp22_write_config_reg(OP_CODE_WR(0x00), 0x00242712);   //����ģʽ1��������TDC�Զ�У׼,�ڲ�ʱ��4��Ƶ
        gp22_write_config_reg(OP_CODE_WR(0x01), 0x01410023);//0x01420023 //stop //zjk:ͨ��1Ԥ��������2
        //gp22_write_config_reg(OP_CODE_WR(0x02), 0xA0000057);
        //gp22_write_config_reg(OP_CODE_WR(0x03), 0x00000041);
        gp22_write_config_reg(OP_CODE_WR(0x03), 0x20000041);
        //gp22_write_config_reg(OP_CODE_WR(0x06), 0x00000038);

		gp22_write_config_reg(OP_CODE_WR(0x02), 0xA0000057);
		gp22_write_config_reg(OP_CODE_WR(0x04), 0x20000042);
    	gp22_write_config_reg(OP_CODE_WR(0x05), 0x00000029);
		gp22_write_config_reg(OP_CODE_WR(0x06), 0x00000038);
		
       }
      else
      {
	  	gp22_send_byte(OPC_RESET);
		
				gp22_write_config_reg(OP_CODE_WR(0x00), 0x00142f12);//0x00242f12--4fps��0x00142f12--2fps//zjk:����ģʽ2,������TDC�Զ�У׼���ڲ�ʱ��2��Ƶ
      gp22_write_config_reg(OP_CODE_WR(0x01), 0x21420023);//0x21420023--mode2//0x01410000--mode1 //zjk:ͨ��1Ԥ��������2,alu��ǰ���ݼ���ķ�ʽ hit2-hit1  stop-start
      //gp22_write_config_reg(OP_CODE_WR(0x02), 0xA0000000);
      //gp22_write_config_reg(OP_CODE_WR(0x03), 0x18000041);//0x00000041
      gp22_write_config_reg(OP_CODE_WR(0x03), 0x20000041);
      //gp22_write_config_reg(OP_CODE_WR(0x06), 0x00000038);

	    gp22_write_config_reg(OP_CODE_WR(0x02), 0xA0000057);
		gp22_write_config_reg(OP_CODE_WR(0x04), 0x20000042);
    	gp22_write_config_reg(OP_CODE_WR(0x05), 0x00000029);
		gp22_write_config_reg(OP_CODE_WR(0x06), 0x00000038);
		
      }
}

//���巢������
void PulseGenerate(void)
{
      gp22_send_byte(OPC_INIT);
      dly100ns(5);//24
      //-----------------------
      TX_PULSE_HIGH();   //TX HIGH
      asm("NOP");
      asm("NOP");
      asm("NOP");
     // asm("NOP"); // 50ns
      TX_PULSE_LOW();   //TX LOW
}
//##################################################
//  MOMENT_AGC_CTRL ˲������: Լ14ns 
//  TX_PULSE_CTRL ��������: Լ100ns
// У׼��������ҪУ׼��ʱ��У׼***
//##################################################
int trigger_pulse(u32 *pDist)
{
    Mode_Config(1);
    //gp22_write_config_reg(OP_CODE_WR(0x01), 0x02420023);//���ڶ���stop�ź�
    PulseGenerate();
    //gp22_write_config_reg(OP_CODE_WR(0x01), 0x02420023);
    //------------����ʱ��
    while(GP22_CHK_INTN()==1);
    if(!ReadGP22Status())//��ȡGP22״̬
    {
        *pDist=gp22_read_dword(OP_CODE_RD(0x00));
        GP22_NS=800;
        //if(*pDist<54613)//С��100m
        if(*pDist<74072) //С��130m
        {
          return 0;
        }
        
      } 
	  else
	  	*pDist = 0;

	  
//---------ģʽ���������--------
    {
        //delay1us(50000/SysSeting.PulseHZ);//delay1us(60);
        Mode_Config(2);//��ʱ��һ��STOP����,ģʽ2Ϊ�ڶ��������ȼ�
        PulseGenerate();
        while(GP22_CHK_INTN()==1);
        //---------ģʽ���������--------
        if(!ReadGP22Status())
        {
          *pDist=gp22_read_dword(OP_CODE_RD(0x00));
          GP22_NS=400;//���¼�ʱϵ��
          return 0;
        }
		else
		  	*pDist = 0;
    }
    return 1;
}


void tlc5618_init(void)
{
    TLC5618_SPI_CS_DISABLE();
}

u16 tlc5618_execute(u16 code_a,u16 code_b)
{
    LD_VAL=code_a;
    AGC_VAL=code_b;
    spi2_write_word((code_b|0x1000)); // d12 = 1, write to double buffer
    spi2_write_word((code_a|0x8000)); // d15 = 1, copy code to A & B from double buffer
    return AGC_VAL;
}
//���÷����ѹ
u16 set_LD_HV(u16 LDv)
{
  tlc5618_execute(LDv,AGC_VAL);
  return LD_VAL;
}
//���ý��ո�ѹ
u16 set_AGC_Gn(u16 AGCg)
{
  tlc5618_execute(LD_VAL,AGCg);
  return AGC_VAL;
}

//����ѡ��-APD/LD
//***APD��ѹ��λ�ı�ʱ��Ҫ����ʱ����Ȼ���ܵ��º������ڳ���
u8 Slect_Gain(u8 lev)
{
  if(Flag_ApdGn==lev)//�����־δ�ı�,������APD��ѹֵ
  {
    return 0;
  }
  Flag_ApdGn=lev;//���µ�ǰAPD״̬��־
  switch(lev)
  {
    case 0:
        PWMSet_APD(SysSeting.APDV_LOW);
        set_LD_HV(LD_LO);//LD_NOW=LD_LO;
        break;
    case 1:
        PWMSet_APD(SysSeting.APDV_MID);
        set_LD_HV(LD_MD);//LD_NOW=LD_MD;
        break;
    case 2:
        PWMSet_APD(SysSeting.APDV_HIG);
        set_LD_HV(LD_HI);//LD_NOW=LD_HI;
        break;
    default:break;
  }
  //delay1us(50000);//��ʱ50ms,�ȴ���ѹ�ȶ�
  return 1;
}
void APDLD_GAIN_ADJ(void)
{
  //APDGainState
  //�ڷǱ궨ģʽ�£�603����ﵽ���޻����ڱ궨ģʽ��ʱ��APD/LD�����ѡ//
  if(!Flag_Cal)//�Ǳ궨ģʽ��
  {
    /*
    switch(Flag_ApdGn)
    {
      case 0:
        if(AGC_VAL==AGC_MIN){APDGainState=0;}
        else if((AGC_VAL>AGC_MIN)&&(AGC_VAL<600)){APDGainState=0;}
        else {APDGainState=1;}
        break;
      case 1:
        if(AGC_VAL<251){APDGainState=0;}
        else if((AGC_VAL>250)&&(AGC_VAL<AGC_MAX)){APDGainState=1;}
        else {APDGainState=2;}
        break;
      case 2:
        if(AGC_VAL<501){APDGainState=1;}
        else if((AGC_VAL>500)&&(AGC_VAL<AGC_MAX)){APDGainState=2;}
        else {APDGainState=2;}
        break;
      default:break;
    }
    */
    /*
    if(AGC_VAL==AGC_MIN){
      Slect_Gain(LOW);
      }
    else if((AGC_VAL==AGC_MAX)&&(Ax<750)){//���źŷ�ֵ����750mvʱ�����������
      Slect_Gain(HIGH);
      }
    else  //�Ӹ�����(�߹���)�л���������(�͹���)
      {
        if((Flag_ApdGn==2)&&(AGC_VAL<400))//�е�����ȼ������ã�
        {
          Slect_Gain(MDLL);
        }
      }
    */
   // Slect_Gain(APDGainState);
  }
}
//AD603�������
u16 tlc5618_AGC_ADJ(int value)
{
	AGC_VAL+=value;
	if(AGC_VAL<AGC_MIN) 
        AGC_VAL=AGC_MIN;
    else if(AGC_VAL>AGC_MAX)   
        AGC_VAL=AGC_MAX;
    else
        ;           
	tlc5618_execute(LD_VAL,AGC_VAL);
	return AGC_VAL;
}
//LD��ѹ����
u16 tlc5618_LDV_ADJ(int value)
{
  LD_VAL+=value;
  if(LD_VAL<50)       {LD_VAL=50;}  //DAC���ޣ���ѹ����
  else if(LD_VAL>2000){LD_VAL=2000;}//DAC���ޣ���ѹ����
  else{;}
  tlc5618_execute(LD_VAL,AGC_VAL);
  return LD_VAL;
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
