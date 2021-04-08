/* 
 * File:   24C64_EEPROM_v1.0.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 13 Mart 2021 Cumartesi, 23:07
 * Version: v1.0
 */

/*@24C64_I2C_EEPROM
 * You must be include 24C64_EEPROM_v1.0.h file in source code file. 
 *  #include "24C64_EEPROM_v1.0.h"
 * 
 * You must be define EEPROM address in source code file.
 *  For example: #define EEPROM1 0xA0
 *
 * You must set the I2C_Master_Initialize in the 'main()' function.
 *  For example: I2C_Master_Initialize(I2C_SPEED_100KHz, I2C_SLEW_OFF, I2C_SMBus_OFF);
 *
 * You can use EEPROM write operation functions or EEPROM read operation functions.
 *  For examle: -   I2C_EEPROM_Byte_Write(EEPROM1, EE_Add, 'A');
 *              -   I2C_EEPROM_Page_Write(EEPROM1, EE_Add, writer_data_buffer, 32);
 *              -   I2C_EEPROM_Sequential_Read(EEPROM1, EE_Add, reader_data_buffer, 16);
 * 
 * NOTE: You must wait 5 milliseconds for consecutive writes to the same EEPROM device.
 */

#ifndef _24C64_EEPROM_H
#define	_24C64_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

/*@FUNCTION_PROTOTYPES*/
    
    //EEPROM_Write_Operation_Function_Prototypes
        void I2C_EEPROM_Byte_Write(unsigned char I2C_Address, unsigned int EEPROM_Address, unsigned char Data);
        void I2C_EEPROM_Page_Write(unsigned char I2C_Address, unsigned int EEPROM_Address, unsigned char *Data_Buffer, unsigned int Length_of_Data);
        
    //EEPROM_Read_Operation_Function_Prototypes
        unsigned char I2C_EEPROM_CurrentAdd_Read(unsigned char I2C_Address);
        unsigned char I2C_EEPROM_Random_Read(unsigned char I2C_Address, unsigned int EEPROM_Address);
        void I2C_EEPROM_Sequential_Read(unsigned char I2C_Address, unsigned int EEPROM_Address, char *Data_Buffer, unsigned int Length_of_Data);

#ifdef	__cplusplus
}
#endif

#endif	/* 24C64_EEPROM_H */

