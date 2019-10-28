/*******************************************************************
*file name:    ascii_protocol.c
*project:      C1
*Description:  uart protocol
*Platform:     stm32
*firmware:     v1.0
*Author:       cwd
*data:         2016.5.7
*note:         null
*******************************************************************/
#ifndef _RTU_PROTOCOL_H_
#define _RTU_PROTOCOL_H_


//-------------------------------------------------------------------------------
//#define EEP_ADDR_START        (0)
//#define EEP_SYSTEM_SETTING    (0+EEP_ADDR_START)          // 1byte  0,1,2  

//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//#define GAIN_APD_MAX         2048        // default value
//#define GAIN_APD_DEFAULT     864         // default value 
//#define GAIN_AGC_MAX         1048        // default value
//#define GAIN_AGC_MIN         24          // default value
//#define GAIN_AGC_INC_VALUE   5           // default value
//#define GAIN_AGC_MAX_LEVEL  (GAIN_AGC_MAX-GAIN_AGC_INC_VALUE)// default value
//#define GAIN_AGC_MIN_LEVEL  (GAIN_AGC_MIN+GAIN_AGC_INC_VALUE)// default value
//#define GAIN_AGC_DEFAULT     650         // default value

//-------------------------------------------------------------------------------
typedef enum  
{                      
    STOP_MEAS = 0,       
    CONTINUE_MEAS = 1,       
    SINGLE_MEAS = 2,  
    MAXMIN_MEAS = 3,
}E_MEAS_STATE; 

typedef enum  
{    
    PROTOCOL_ASCII = 0,//ascii 
    PROTOCOL_RTU = 1,  //modbus RTU        
}E_PROTOCOL_TYPE; 



//void SysParamInit(void);
//void tlc5618_setting(void);  
//void GetSoftDate(char *date);

#endif

