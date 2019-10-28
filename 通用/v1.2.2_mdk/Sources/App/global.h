/****************************************************************************
* 文件名：global.h
* 功能：  全局
*         
*  
* 作者： 红双喜 QQ89362582
* 日期： 2014/2/27
****************************************************************************/
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//----------------------------------------------------------
#define PCB_VERSION     3
#define SOFT_VERSION    2

#define INTERNAL_RC            //内部RC振荡
#define CLOCK_PLL    64000000  //系统时钟频率64MHz
#define SYS_TICK_MS  5         //系统滴答定时器5mS  

//----------------------------------------------------------
#define ENABLE_UART_PROTOCOL
//#define ENABLE_WATCH_DOG
#define CWD_DEBUG

//----------------------------------------------------------
#include <string.h>
#include <math.h>

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#include "st_type.h"
#include "stm32_io_defs.h"
#include "stm32f1_init.h"

//driver
#include "debug.h"
#include "drv_eeprom.h"
#include "drv_uart.h"
#include "drv_crc16.h"
#include "drv_modbus.h"
#include "drv_adc.h"
#include "drv_spi.h"

//timer
#include "my_timer.h"
#include "drv_PwmHV.h"
//app
#include "public.h"
#include "ascii_protocol.h"
#include "rtu_protocol.h"
#include "measure.h"
#include "meas_current.h"

#endif

