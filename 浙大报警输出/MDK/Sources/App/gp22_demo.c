/******************* (C) COPYRIGHT 2012 acam messelectronic GmbH ***************
******************** (C) COPYRIGHT 2008 STMicroelectronics *********************
 * File Name          : main.c
 * Author             : acam Support Team
 * Version            : 
 * Date               : 08-01-2014
 * Description        : Simple demonstration program to run TDC-GP22 in a 
 *                      laser rangefinder application and clock calibration.
 *                      The example is for communication with a 
 *                      STM32F105_VC microprocessor with max. SPI-frequency.
 *******************************************************************************
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH AN EXAMPLE CODING INFORMATION REGARDING OUR PRODUCTS. THE ACAM
 * RECOMMENDATIONS ARE BELIEVED USEFUL AND OPERABLE, NEVERTHELESS IT IS OF THE
 * CUSTOMER'S SOLE RESPONSIBILITY TO MODIFY, TEST AND VALIDATE THEM BEFORE
 * SETTING UP ANY PRODUCTION PROCESS. AS A RESULT, ACAM SHALL NOT BE HELD LIABLE
 * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS
 * ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF
 * THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "v_includes.h"
#include "stdio.h"

/* Private variables ---------------------------------------------------------*/
#define LOOP_DLY_100US    2000
#define LOOP_DLY_250ns    2
#define LOOP_DLY_1ms      3299

u32       CriticalSecCntr;
bool      configured_true=FALSE;

float     CLKHS_freq = 1.000;           // Clock frequency in MHz
float     CLKHS_freq_cal = 1.000;       // Calibrated Clock frequency in MHz
float     CLKHS_freq_corr_fact = 1.000; // Correction factor for Clock frequency

float     avg_diff_Cal2_Cal1 = 0;
float     diff_Cal2_Cal1_old = 0;
float     diff_Cal2_Cal1_new = 0;

float     average_RAW_Result = 0;
float     RAW_Result = 0;
float     Time_Result = 0;
float     Distance_Result = 0;

int       N_Measure_Cycles;

uint8_t   Error_Bit = 0;

/* PT1000 --------------------------------------------------------------------*/
//R0, A, B are parameters as specified in EN60 751
float     R0_at_0C = 1000;            // R0 is the RTD resistance at 0 °C
float     Coeff_A  = 3.9083/1000;     // A = 3,9083 x 10-3 °C-1
float     Coeff_B  = -5.775/10000000; // B = -5,775 x 10-7 °C-1
float     R1 = 0, R2 = 0;             // R1, R2 is resistance measured in Ohm
float     corr_fact = 1.0000;   // Corr.-factor for temperature resistance ratio

/* Opcodes -------------------------------------------------------------------*/
uint8_t   Init =                0x70;
uint8_t   Power_On_Reset =      0x50;
uint8_t   Start_TOF =           0x01;
uint8_t   Start_Temp =          0x02;
uint8_t   Start_Cal_Resonator = 0x03;
uint8_t   Start_Cal_TDC =       0x04;
uint8_t   Start_TOF_Restart =   0x05;
uint8_t   Start_Temp_Restart =  0x06;

uint32_t  *sram_memory     = ((uint32_t *)(SRAM_BASE + 0xB00));
uint32_t  sram_mem_offset  = 0x0;

uint32_t  Dummy_var = 0;

// For mathematical calculations
int       i;
int       j;

/* Device functions ----------------------------------------------------------*/
void      gp22_send_1byte(void *bus_type, uint8_t gp22_opcode_byte);
void      gp22_wr_config_reg(void *bus_type, uint8_t opcode_address,
                             uint32_t config_reg_data);
float     gp22_read_n_bytes(void *bus_type, uint8_t n, uint8_t read_opcode,
                            uint8_t read_addr, uint8_t fractional_bits);

uint16_t  gp22_read_status_bytes(void *bus_type);
uint8_t   gp22_status_count_error(void *bus_type);
void      gp22_analyse_error_bit(void *bus_type);

/* Bus functions -------------------------------------------------------------*/
void      SPIx_GPIOs_Init(void* bus_type);
void      SPIx_Interface_Init(void* bus_type);

/* Private functions ---------------------------------------------------------*/
void      Dly100us(void *arg);
void      Dly250ns(void *arg);
void      Dly1ms(void *arg);
void      Simple_delay_750ns(void *arg);
void      Ext_Interrupt_Init (void);


/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main(void)
{
  ENTR_CRT_SECTION();
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  SystemInit();

  EXT_CRT_SECTION();

  // Choose your Slot (SPI1, SPI2)
  void* Bus_Type = SPI1;
  
  /* controlled loop */
  while (Dummy_var!=11) // To control the loop, e.g. (Dummy_var!=7) 
  {
    if (Dummy_var==10) Dummy_var=0; // Infinite loop
    
    if(configured_true==FALSE)
    {  
      configured_true = TRUE;
      SPIx_GPIOs_Init(Bus_Type);
      SPIx_Interface_Init(Bus_Type);
      
      Ext_Interrupt_Init();
      
      gp22_send_1byte(Bus_Type, Power_On_Reset);
      Dly100us((void*)5);              // 500 us wait for GP22
 
      // Writing to the configuration registers (CR)
      // CR0: DIV_CLKHS = 2, START_CLKHS = 1, CALIBRATE = 0, NO_CAL_AUTO = 1, MESSB2 = 0, NEG_STOP = NEGSTART = 0, ...
      gp22_wr_config_reg(Bus_Type, 0x80, 0x00241000);  
      // CR1: EN_FAST_INIT = 1, HITIN2 = 1, HITIN1 = 1, ...
      gp22_wr_config_reg(Bus_Type, 0x81, 0x19C90000); 
      // CR2: EN_INT = b111, RFEDGE1 = RFEDGE2 = 0, ... 
      gp22_wr_config_reg(Bus_Type, 0x82, 0xE0000000); 
      // CR3: ... 
      gp22_wr_config_reg(Bus_Type, 0x83, 0x00000000);
      // CR4: ...
      gp22_wr_config_reg(Bus_Type, 0x84, 0x20000000); 
      // CR5: CON_FIRE = b000, EN_STARTNOISE = 1, ...
      gp22_wr_config_reg(Bus_Type, 0x85, 0x10000000); 
      // CR6: QUAD_RES = 0, ...
      gp22_wr_config_reg(Bus_Type, 0x86, 0x00000000); 
    }

    // .........................................................................
    // ........................Calibrate High Speed Clock.......................
    // ...................Laser Rangefinder Measurement CYCLE...................
    // .........................Caluculate Result Values........................
    
    N_Measure_Cycles = 50000;
    
    diff_Cal2_Cal1_old = diff_Cal2_Cal1_new;

if((Dummy_var==0) | (Dummy_var==10))
{
    //--------------------------------------------------------------------------
    // Start Calibrate High Speed Clock Cycle
    gp22_send_1byte(Bus_Type, Init);
    gp22_send_1byte(Bus_Type, Start_Cal_Resonator);

    // Wait for INT Slot_x
    if (Bus_Type==SPI1) while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)==1); 
    if (Bus_Type==SPI2) while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)==1);
       
    //Calculate Correction factor
    //The time interval to be measured is set by ANZ_PER_CALRES
    //which defines the number of periods of the 32.768 kHz clock:
    //2 periods = 61.03515625 µs
    CLKHS_freq_corr_fact = 61.03515625/
      gp22_read_n_bytes(Bus_Type, 4, 0xB0, 0x00, 16) * CLKHS_freq;
   
    printf("\n Correction factor for clock = %1.4f\n", CLKHS_freq_corr_fact); 
       
    CLKHS_freq_cal = CLKHS_freq * CLKHS_freq_corr_fact; // Calibrated Clock frequency
}

    //--------------------------------------------------------------------------
    // Start Seperate Calibration Measurement Cycle    
    gp22_send_1byte(Bus_Type, Init);
    
    gp22_send_1byte(Bus_Type, Start_Cal_TDC); // update calibration data

    // Note:
    // The calibration data are not addressed directly after the calibration
    // measurement but after the next regular measurement, before the next INIT.
    
    // Wait for INT Slot_x
    if (Bus_Type==SPI1) while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)==1); 
    if (Bus_Type==SPI2) while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)==1);

    gp22_wr_config_reg(Bus_Type, 0x81, 0x19490000);

    //--------------------------------------------------------------------------
    // 1st ToF Measurement plus calibratio data readout
    gp22_send_1byte(Bus_Type, Init);

    //Trigger pulse laser
    //    SetPortHigh;   
    GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_SET); // Output HIGH
    //    SetPortLow;
    GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET);   // Output LOW
    
    // Wait for INT Slot_x
    if (Bus_Type==SPI1) while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)==1); 
    if (Bus_Type==SPI2) while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)==1);

    // First regular measurement (to readout calibration data)
    RAW_Result = gp22_read_n_bytes(Bus_Type,4,0xB0,0x00,16);
//    printf("\n 1. Measured RAW Value = %.0f \n",RAW_Result); // RAW value

    // Check Status Register, next free result register
//    printf("Stat_Reg = 0x%04X \n",gp22_read_status_bytes(Bus_Type)); 

    // readout the new calibration data from result register adr 0x01
    gp22_wr_config_reg(Bus_Type, 0x81, 0x67490000);
    diff_Cal2_Cal1_new = gp22_read_n_bytes(Bus_Type,4,0xB0,0x01,16);
    
    //--------------------------------------------------------------------------
    // Caluculate the real time after the hole first cycle loop
    while (diff_Cal2_Cal1_old != 0) 
    {
        avg_diff_Cal2_Cal1 = (diff_Cal2_Cal1_new+diff_Cal2_Cal1_old) / 2;

//        printf("\n OLD Cal2-Cal1 RAW Value = %.0f \n",diff_Cal2_Cal1_old);
//        printf("\n NEW Cal2-Cal1 RAW Value = %.0f \n",diff_Cal2_Cal1_new);

        average_RAW_Result /= N_Measure_Cycles;
    
        // Used Formulas:
        // ---------------------------------------------------
        //                 T_ref
        // Time_Value = ----------- * measured_RAW_Value
        //               Cal2-Cal1
        // ---------------------------------------------------
        //                   velocity_of_light
        // Distance_Value = ------------------- * Time_Value
        //                           2
        // ---------------------------------------------------
        
        // For this Source Code would be a Reference Clock used with 1 MHz
        
        Time_Result = (average_RAW_Result/avg_diff_Cal2_Cal1) * 1000;//time [ns]

        Distance_Result = Time_Result / 6.671281904; //distance [m]
        
        printf("\n Time Measure Result (ToF) = %.3f ns\n",Time_Result);
        printf(" corresponds to %.3f m of Distance\n",Distance_Result);
        printf(" to reflected point after %u Measurements\n",N_Measure_Cycles);

        diff_Cal2_Cal1_old = 0;
    }

    //--------------------------------------------------------------------------
    // if more than one measure cycle
    average_RAW_Result = RAW_Result; // set first value of average_RAW_Result
    
    gp22_wr_config_reg(Bus_Type, 0x81, 0x19C90000); // EN_FAST_INIT = 1
    gp22_send_1byte(Bus_Type, Init);
    
    //Trigger pulse laser
    //    SetPortHigh;   
    GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_SET);   // Output HIGH
    //    SetPortLow;
    GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET); // Output LOW
    
    //--------------------------------------------------------------------------
    // n'th ToF Measurement
    for (int i=2; i<=N_Measure_Cycles;i++)
    {
        // Wait for INT Slot_x
        if (Bus_Type==SPI1) while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)==1); 
        if (Bus_Type==SPI2) while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_11)==1);

        RAW_Result = gp22_read_n_bytes(Bus_Type,4,0xB0,0x00,16);
//        printf(" %u. Measure RAW Value = %.0f \n",i,RAW_Result); // RAW value
        average_RAW_Result += RAW_Result;
        
        //Trigger pulse laser
        //    SetPortHigh;   
        GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_SET);   // Output HIGH
        //    SetPortLow;
        GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET); // Output LOW 
    }
    
    //--------------------------------------------------------------------------

    printf("\nNEW CYCLE...\n"); 

    Dummy_var++; // To Control the loop
    
  } // End while Dummy_var

} //End main


/*******************************************************************************
 * Device Functions
 ******************************************************************************/

/*******************************************************************************
 * Function Name: gp22_send_1byte
 * Parameters: Opcode byte
 *
 * Return: none
 *
 * Description: Writes the Opcode to GP21
 *
 ******************************************************************************/
void gp22_send_1byte (void *bus_type, uint8_t gp22_opcode_byte)
{
     // Deactivating Reset SPIx
     if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
     if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
     
     while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {} 
     SPI_I2S_SendData(bus_type, gp22_opcode_byte);     // OPCODE TO Device 
     while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {} 
  Simple_delay_750ns((void*)10); // important delay (16) at SPI freq.=750kHz

     // Reset to device SPIx
     if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
     if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
}

/*******************************************************************************
 * Function Name: gp22_wr_config_reg
 * Parameters: Address byte, 4 bytes of Configuration
 *
 * Return: none
 *
 * Description: Writes the config.reg. specified in GP21 with the data 
 *
 ******************************************************************************/
void gp22_wr_config_reg (void *bus_type, uint8_t opcode_address,
                         uint32_t config_reg_data)
{
    uint8_t Data_Byte_Lo    = config_reg_data;
    uint8_t Data_Byte_Mid1  = config_reg_data>>8;
    uint8_t Data_Byte_Mid2  = config_reg_data>>16;
    uint8_t Data_Byte_Hi    = config_reg_data>>24;

    uint8_t common_delay    = 10; // important delay (16) at SPI freq.=750kHz

    // Deactivating Reset SPIx
    if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
    if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);

    while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {} 

    SPI_I2S_SendData(bus_type, opcode_address);  // RAM WR OPCODE+ADDRESS
    Simple_delay_750ns((void*)common_delay);

    while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {}
    SPI_I2S_SendData(bus_type, Data_Byte_Hi);  // DATA BYTE HIGH 
    Simple_delay_750ns((void*)common_delay);

    while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {}
    SPI_I2S_SendData(bus_type, Data_Byte_Mid2);  // DATA MID - 2 
    Simple_delay_750ns((void*)common_delay);

    while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {}
    SPI_I2S_SendData(bus_type, Data_Byte_Mid1);  // DATA MID - 1
    Simple_delay_750ns((void*)common_delay);

    while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {}
    SPI_I2S_SendData(bus_type, Data_Byte_Lo);  // DATA LOW
    Simple_delay_750ns((void*)common_delay);

    while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==0) {}
    Simple_delay_750ns((void*)common_delay);

    // Reset to device SPIx
    if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
    if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
}

/*******************************************************************************
 * Function Name: gp22_read_n_bytes
 * Parameters: bus_type = (SPI1, SPI2)
 *             n_bytes = how many bytes should be read
 *             read_opcode = read opcode of the device
 *             read_addr = read address of the device
 *             fractional_bits = number of fractional bits of read data
 *
 * Return: n bytes from the specified read address
 *
 * Description: Reads n bytes from an address in GP21
 *
 ******************************************************************************/              
float gp22_read_n_bytes(void *bus_type, uint8_t n_bytes, uint8_t read_opcode,
                   uint8_t read_addr, uint8_t fractional_bits)
{
    uint32_t    Result_read = 0;
    float       Result = 0;
    uint8_t     read_opcode_addr = read_opcode | read_addr;

    //.............. Result = n Byte = n x 8 bits......................
    if (bus_type==SPI1 | bus_type==SPI2) 
    {
        // Deactivating Reset SPIx
        if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
        if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);

        SPI_I2S_SendData(bus_type, read_opcode_addr);  // READ OPCODE + Address

        while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==RESET) {};
        Simple_delay_750ns((void*)10); // important delay (16) at SPI freq.=750kHz

        //Compulsory reads to DR and SR to clear OVR,
        //so that next incoming data is saved
        SPI_I2S_ReceiveData(bus_type);                     // To clear OVR
        SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE); // To clear OVR

        //Reading byte1
        SPI_I2S_SendData(bus_type, 0x00FF);  // DUMMY WRITE
        // Wait until RX buffer is not empty, then read the received data
        while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_RXNE)==0) {}
        Result_read = SPI_I2S_ReceiveData(bus_type); //  Read

        for (int n = 1; n < n_bytes; n++)
        {       
        //Reading byte2 .. byte.n
        SPI_I2S_SendData(bus_type, 0x00FF);  // DUMMY WRITE
        // Wait until RX buffer is not empty, then read the received data
        while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_RXNE)==0) {}

        Result_read = Result_read<<8;
        Result_read |= SPI_I2S_ReceiveData(bus_type); //  Read
        }

        // Reset to device SPIx
        if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
        if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
    }
  
    Result = Result_read / pow(2, fractional_bits);

    return Result;
}                 

/*******************************************************************************
 * Function Name: gp22_read_status_bytes
 * Parameters: bus_type = (SPI1, SPI2)
 *
 * Return: 2 bytes from the status register, address 0x04
 *
 * Description: Reads 2 bytes from an address in GP22
 *
 ******************************************************************************/              
uint16_t gp22_read_status_bytes(void *bus_type)
{
  uint16_t    Result_read = 0;
  uint8_t     n_bytes = 2;
  
  uint8_t     read_opcode_addr = 0xB0 | 0x04;

  //.............. Result = 2 Byte = 16 bits......................
  if (bus_type==SPI1 | bus_type==SPI2) 
  {
       // Deactivating Reset SPIx
       if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
       if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
      
       SPI_I2S_SendData(bus_type, read_opcode_addr);  // READ OPCODE + Address
       
       while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE)==RESET) {};
       Simple_delay_750ns((void*)10); // important delay (16) at SPI freq.=750kHz
       
       //Compulsory reads to DR and SR to clear OVR,
       //so that next incoming data is saved
       SPI_I2S_ReceiveData(bus_type);                     // To clear OVR
       SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_TXE); // To clear OVR

         //Reading byte1
         SPI_I2S_SendData(bus_type, 0x00FF);  // DUMMY WRITE
         // Wait until RX buffer is not empty, then read the received data
         while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_RXNE)==0) {}
         Result_read = SPI_I2S_ReceiveData(bus_type); //  Read

       for (int n = 1; n < n_bytes; n++)
       {       
         //Reading byte2 .. byte.n
         SPI_I2S_SendData(bus_type, 0x00FF);  // DUMMY WRITE
         // Wait until RX buffer is not empty, then read the received data
         while (SPI_I2S_GetFlagStatus(bus_type, SPI_I2S_FLAG_RXNE)==0) {}

         Result_read = Result_read<<8;
         Result_read |= SPI_I2S_ReceiveData(bus_type); //  Read
       }

       // Reset to device SPIx
       if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
       if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
  }
  
  return Result_read;
}                 

/*******************************************************************************
 * Function Name: gp22_status_count_error
 * Parameters: bus_type = (SPI1, SPI2)
 *
 * Return: only one Error Bit (9..15) from the status register, address 0x04
 *
 * Description: Reads 2 bytes from an address in GP22
 ******************************************************************************/              
uint8_t gp22_status_count_error(void *bus_type)
{
  uint16_t STAT_REG = 0x0000;
  uint8_t  count_error     = 0;

  STAT_REG = gp22_read_status_bytes(bus_type);
  
  if ((STAT_REG&0x0200)==0x0200) count_error++; //Bit9: Timeout_TDC
  if ((STAT_REG&0x0400)==0x0400) count_error++; //Bit10: Timeout_Precounter
  if ((STAT_REG&0x0800)==0x0800) count_error++; //Bit11: Error_open
  if ((STAT_REG&0x1000)==0x1000) count_error++; //Bit12: Error_short
  if ((STAT_REG&0x2000)==0x2000) count_error++; //Bit15: EEPROM_Error
  if ((STAT_REG&0x4000)==0x4000) count_error++; //Bit14: EEPROM_DED
  if ((STAT_REG&0x8000)==0x8000) count_error++; //Bit13: EEPROM_eq_CREG
         
  return count_error;
}

/*******************************************************************************
 * Function Name: gp22_analyse_error_bit
 * Parameters: none
 *
 * Return: none
 *
 * Description: Analyse the bit from the status register
 ******************************************************************************/              
void gp22_analyse_error_bit(void *bus_type)
{
  uint16_t STAT_REG = 0x0000;

  STAT_REG = gp22_read_status_bytes(bus_type);
  
  //Bit9: Timeout_TDC
  if ((STAT_REG&0x0200)==0x0200) 
    printf("-Indicates an overflow of the TDC unit\n");
  //Bit10: Timeout_Precounter
  if ((STAT_REG&0x0400)==0x0400) 
    printf("-Indicates an overflow of the 14 bit precounter in MR 2\n");
  //Bit11: Error_open
  if ((STAT_REG&0x0800)==0x0800) 
    printf("-Indicates an open sensor at temperature measurement\n");
  //Bit12: Error_short
  if ((STAT_REG&0x1000)==0x1000) 
    printf("-Indicates a shorted sensor at temperature measurement\n");
  //Bit13: EEPROM_Error
  if ((STAT_REG&0x2000)==0x2000) 
    printf("-Single error in EEPROM which has been corrected\n");
  //Bit14: EEPROM_DED
  if ((STAT_REG&0x4000)==0x4000) 
    printf("-Double error detection. A multiple error has been detected whcich can not be corrected.\n");
  //Bit15: EEPROM_eq_CREG
  if ((STAT_REG&0x8000)==0x8000) 
    printf("-Indicates whether the content of the configuration registers equals the EEPROM\n");
}


/*******************************************************************************
 * Bus Functions
 ******************************************************************************/

/*******************************************************************************
 * Function Name: SPIx_GPIOs_Init
 * Parameters: Int32U Clk, Int32U Width
 * Return: none
 *
 * Description: Init GPIOs used in SPIx interface
 *
 ******************************************************************************/
void SPIx_GPIOs_Init(void* bus_type)
{
GPIO_InitTypeDef GPIO_InitStructure; // GPIO_InitTypeDef defined in library

  // Enable GPIO clock and release reset
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | 
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,  DISABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,  ENABLE);

  // Configure   SPI1_CLK  - PA5
  //             SPI1_MOSI - PA7
  //             SPI1_MISO - PA6
  // Chip select SPI1_NSS  - PA4
  // External Interrupt Input line PD4

  // Configure   SPI2_CLK  - PB13
  //             SPI2_MOSI - PB15
  //             SPI2_MISO - PB14
  // Chip select SPI2_NSS  - PB12
  // External Interrupt Input line PE11  
  
// SPI1_NSS
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  if (bus_type==SPI1) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
                        GPIO_Init(GPIOA, &GPIO_InitStructure);
                      } // SPI1 - PA4
  if (bus_type==SPI2) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
                        GPIO_Init(GPIOB, &GPIO_InitStructure);
                      } // SPI2 - PB12

//  SPI1_CLK
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  if (bus_type==SPI1) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
                        GPIO_Init(GPIOA, &GPIO_InitStructure);
                      } // SPI1 - PA5
  if (bus_type==SPI2) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
                        GPIO_Init(GPIOB, &GPIO_InitStructure);
                      } // SPI2 - PB13

//   SPI1_MISO
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  if (bus_type==SPI1) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
                        GPIO_Init(GPIOA, &GPIO_InitStructure);
                      } // SPI1 - PA6
  if (bus_type==SPI2) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
                        GPIO_Init(GPIOB, &GPIO_InitStructure);
                      } // SPI2 - PB14
  
//   SPI1_MOSI
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  if (bus_type==SPI1) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
                        GPIO_Init(GPIOA, &GPIO_InitStructure);
                      } // SPI1 - PA7
  if (bus_type==SPI2) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
                        GPIO_Init(GPIOB, &GPIO_InitStructure);
                      } // SPI1 - PB15
 
  SPI_I2S_DeInit(bus_type);

// External Interrupt Input
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  if (bus_type==SPI1) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
                        GPIO_Init(GPIOD, &GPIO_InitStructure);
                      } // SPI1 - PD4
  if (bus_type==SPI2) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
                        GPIO_Init(GPIOE, &GPIO_InitStructure);
                      } // SPI2 - PE11
  
// SPI ENABLE Output for the evaluation kit
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  if (bus_type==SPI1) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
                        GPIO_Init(GPIOD, &GPIO_InitStructure);
                      } // SPI1 - PD3
  if (bus_type==SPI2) { GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
                        GPIO_Init(GPIOE, &GPIO_InitStructure);
                      } // SPI2 - PE10

  // SPIx Enable = RSN for GP22
  if (bus_type==SPI1) GPIO_WriteBit(GPIOD, GPIO_Pin_3, Bit_SET); // SPI1 - PD3
  if (bus_type==SPI2) GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_SET); // SPI2 - PE10
}

/*******************************************************************************
 * Function Name: SPIx_Interface_Init
 * Parameters: Int32U Clk, Int32U Width
 * Return: none
 *
 * Description: Init SPI1 or SPI2 Interface
 *
 ******************************************************************************/
void SPIx_Interface_Init(void* bus_type)
{
  // Initialising the SPIx interface
  SPI_InitTypeDef SPI_InitStructure;
  
    /* Configures the system clock (SYSCLK) */
//  RCC_SYSCLKConfig (RCC_SYSCLKSource_HSI); // Source-freq. 8.000MHz
//  RCC_SYSCLKConfig (RCC_SYSCLKSource_HSE); // Source-freq. 20.000MHz
  RCC_SYSCLKConfig (RCC_SYSCLKSource_PLLCLK); // Source-freq. 57.6MHz ( (72MHz/25MHz) * HSE) )
  
    /* Adjusts the Internal High Speed oscillator (HSI) calibration value.
    * @param  HSICalibrationValue: specifies the calibration trimming value.
    *   This parameter must be a number between 0 and 0x1F. */
  //RCC_AdjustHSICalibrationValue(0x10); //0x00..0x0F // 3.8..4.2MHZ

    /* Configures the AHB clock (HCLK) */
  RCC_HCLKConfig (RCC_SYSCLK_Div1);


  // Clock Enable and Reset release
  if (bus_type==SPI1)
  {
    RCC_APB2PeriphResetCmd (RCC_APB2Periph_SPI1, DISABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_SPI1, ENABLE);
  }

  if (bus_type==SPI2)
  {
    RCC_APB1PeriphResetCmd (RCC_APB1Periph_SPI2, DISABLE);
    RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);
    RCC_PCLK1Config (RCC_HCLK_Div1); // in order to adapt the clock frequenz
  }
  
  // All are defined in stm32f10x_spi.h
  SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;    
  SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
  // SPI frequence devider
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;

  SPI_Init(bus_type, &SPI_InitStructure);
  SPI_Cmd(bus_type, ENABLE); // Enabling the SPIx Interface

  // Enabling the NSS Output during transmission
  SPI_SSOutputCmd (bus_type, ENABLE); 
  // SPIx - SSN to Device - Set to High for reset
  if (bus_type==SPI1) GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
  if (bus_type==SPI2) GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
}


/*******************************************************************************
 * Private Functions
 ******************************************************************************/

/*******************************************************************************
 * Function Name: Dly100us, Dly250ns, Dly1ms, Simple_delay_750ns
 * Parameters: delay multiplier
 *
 * Return: none
 *
 * Description: Delay Dly * (100us, 250ns, 1ms, 750ns)
 *
 ******************************************************************************/
void Dly100us(void *arg)                        // Gives 100us delay with arg 1
{
    u32 Dely = (u32)arg;
 while(Dely--)
 {
   for(int i = LOOP_DLY_100US; i; i--);
 }
}

void Dly250ns(void *arg)                        // Gives 250ns delay with arg 1
{
u32 Dely = (u32)arg;
 while(Dely--)
 {
   for(int i = LOOP_DLY_250ns; i; i--);
 }
}

void Dly1ms(void *arg)                            // Gives 1ms delay with arg 1
{
  u32 Dely = (u32)arg;
 while(Dely--)
 {
   for(int i = LOOP_DLY_1ms; i; i--);
 }
}

void Simple_delay_750ns(void *arg)             // Gives 750ns delay, with arg 1 
{
u32 Dely = (u32)arg;
   for(int i = Dely; (i!=0); i--);

}

/*******************************************************************************
 * Function Name  : Ext_Interrupt_Init
 * Return: none
 *
 * Description    : External interrupt/event controller (EXTI)
 * The external interrupt/event controller consists of 20 edge detector lines
 * used to generate interrupt/event requests. Each line can be independently
 * configured to select the trigger event (rising edge, falling edge, both) and
 * can be masked independently. A pending register maintains the status of the
 * interrupt requests. The EXTI can detect an external line with a pulse width
 * shorter than the Internal APB2 clock period. Up to 80 GPIOs can be connected
 * to the 16 external interrupt lines.
 *
 * In this case: GPIOD - Port 8
 * Jumper J65
 *
 ******************************************************************************/
void Ext_Interrupt_Init (void)
{
  GPIO_InitTypeDef GPIO_InitStructure; // GPIO_InitTypeDef defined in library

  // Enable GPIO clock and release reset
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD ,  DISABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD ,  ENABLE);

  // GPIO - PE7 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
GPIO_EventOutputConfig(GPIO_PortSourceGPIOD, GPIO_PinSource8);
  GPIO_WriteBit(GPIOD, GPIO_Pin_8, Bit_RESET);
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
/******************* (C) COPYRIGHT 2012 acam messelectronic GmbH **************/

