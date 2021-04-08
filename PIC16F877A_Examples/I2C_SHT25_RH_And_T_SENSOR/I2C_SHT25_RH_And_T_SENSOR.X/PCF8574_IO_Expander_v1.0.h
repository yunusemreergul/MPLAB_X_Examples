/* 
 * File:   PCF8574_IO_Expander_v1.0.h
 * Author: ACER-PC
 *
 * Created on 09 Mart 2021 Sal?, 15:04
 * Version: v1.0
 */

#ifndef PCF8574_IO_EXPANDER_H
#define	PCF8574_IO_EXPANDER_H

#ifdef	__cplusplus
extern "C" {
#endif

/*@FUNCTION_PROTOTYPES*/
    void I2C_IO_Expander_Writer(unsigned char I2C_Address, unsigned char I2C_Data);
    typedef void (*p_I2C_IO_Expander_Writer_t)(unsigned char I2C_Address, unsigned char I2C_Data);
    p_I2C_IO_Expander_Writer_t p_I2C_IO_Expander_Writer = &I2C_IO_Expander_Writer;

#ifdef	__cplusplus
}
#endif

#endif	/* PCF8574_IO_EXPANDER_H */
