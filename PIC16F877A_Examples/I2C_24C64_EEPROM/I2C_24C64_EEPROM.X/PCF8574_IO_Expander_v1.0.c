/* 
 * File:   PCF8574_IO_Expander_v1.0.c
 * Author: ACER-PC
 *
 * Created on 09 Mart 2021 Sal?, 15:04
 * Version: v1.0
 */

#include "PCF8574_IO_Expander_v1.0.h"
#include "I2C_v1.1.h"

/*@IO_EXTANDER_WRITER_FUNCTION*/

    void I2C_IO_Expander_Writer(unsigned char I2C_Address, unsigned char I2C_Data){
        I2C_Master_Start();
        I2C_Master_Write(I2C_Address);
        I2C_Master_Write(I2C_Data);
        I2C_Master_Stop();
    }
