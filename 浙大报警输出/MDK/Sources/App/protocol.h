//-----------------------------------------------------------------------------
// sys_init.h
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
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


//-------------------------------------------------------------------------------
#define EEP_ADDR_START        (0)
#define EEP_SYSTEM_STATUS     (0+EEP_ADDR_START)          // 1byte  0,1,2  
#define EEP_DEMARCATE_DIST    (1+EEP_SYSTEM_STATUS)       // 2byte  uint:cm
#define EEP_GAIN_APD          (2+EEP_DEMARCATE_DIST)      // 2byte  0-4095
#define EEP_GAIN_AGC          (2+EEP_GAIN_APD)            // 2byte  0-4095
#define EEP_COM_BAUDRATE      (2+EEP_GAIN_AGC)            // 4byte  default:921600
#define EEP_PROTOCOL_TYPE     (4+EEP_COM_BAUDRATE)        // 1byte

//-------------------------------------------------------------------------------
#define BAUDRATE_19200       ((u32)19200)
#define BAUDRATE_115200      ((u32)115200)
#define BAUDRATE_460800      ((u32)460800)
#define BAUDRATE_921600      ((u32)921600)

//-------------------------------------------------------------------------------
#define GAIN_APD_MAX         2048        // default value
#define GAIN_APD_DEFAULT     864         // default value 
#define GAIN_AGC_MAX         1048        // default value
#define GAIN_AGC_MIN         24          // default value
#define GAIN_AGC_INC_VALUE   5           // default value
#define GAIN_AGC_MAX_LEVEL  (GAIN_AGC_MAX-GAIN_AGC_INC_VALUE)// default value
#define GAIN_AGC_MIN_LEVEL  (GAIN_AGC_MIN+GAIN_AGC_INC_VALUE)// default value
#define GAIN_AGC_DEFAULT     650         // default value

//-------------------------------------------------------------------------------
enum
{	
    PT_RTU,
    PT_ASC
};

enum
{	
    SS_NONE,
    SS_CHECKED,
    SS_DEMARCATED
};

enum 
{	
    FCODE_SET_BAUDRATE,
    FCODE_APD_ADJUST, 
    FCODE_AGC_ADJUST,
    FCODE_CHMODE,
    FCODE_GET_VERSION,
    FCODE_NUMS
};

typedef  void (*cmd_res_handle)(u32 arg);
typedef struct
{
	u8 func_code;
	cmd_res_handle handle;
}t_cmd_res_handle;


void parameter_init(void);
void tlc5618_setting(void);  

#endif

