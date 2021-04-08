/* 
 * File:   I2C.h
 * Author: Yunus Emre ERGUL
 *
 * Created on 26 Ocak 2021 Sal?, 14:54
 */

/*@I2C_MSSP_MODULE_COMMUNICATION -> For The PIC16F877A Device
 * 
 * Firstly, you should add the "configuration.h" file for register definitions and configuration defines.
 * 
 * I2C MASTER MODE: - For the master mode use of the I2C module, it must be configured once with the "I2C_Master_Initialize" function.
 *                  - Depending on the data structure of the communication to be established,
 *                    data receiving or data sending status should be implement with the Master functions.
 *                  - In multi-master usage, Bus Collision Interrupt can be used for bus collision.
 * 
 * I2C SLAVE MODE: - For the slave mode use of the I2C module, it must be configured once with the "I2C_Slave_Initialize" function.
 *                 - For the receive and send functions, the Global, Peripheral, MSSP module SSP interrupts must be set and the ISR handler function written.
 *                 - The "I2C_Slave_Transmit" must be called once within the ISR handler function for the transmitted data.
 *                 - The "I2C_Slave_Receive" must be called once within the ISR handler function for the received data.
 *                 - Note: The "I2C_Slave_Initialize" function is written for 7-bit addressing only.
 */

#ifndef I2C_H
#define	I2C_H

#include "configurations.h"     //Added by user.
#include<stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*@DEFINITIONS*/
    //I2C Master Mode Baud Rate Type And Definitions
    typedef const unsigned long I2C_BaudRate_t;
    #define I2C_SPEED_100KHz    ((I2C_BaudRate_t)100000)
    #define I2C_SPEED_400KHz    ((I2C_BaudRate_t)400000)
    #define I2C_SPEED_1MHz      ((I2C_BaudRate_t)1000000)
    
    //I2C Slave Mode Type And Definitions
    typedef unsigned char I2C_Slave_Mode_t;
    #define I2C_SLAVE_7BIT          ((I2C_Slave_Mode_t)0b0110)
    #define I2C_SLAVE_10BIT         ((I2C_Slave_Mode_t)0b0111)
    #define I2C_SLAVE_7BIT_S_P_INT  ((I2C_Slave_Mode_t)0b1110)
    #define I2C_SLAVE_10BIT_S_P_INT ((I2C_Slave_Mode_t)0b1111)

    //I2C Slave Address Type And Macro Definition
    typedef const unsigned char I2C_Slave_Address_t;
    #define I2C_SLAVE_ADDRESS(Slave_Address) ((I2C_Slave_Address_t)Slave_Address)
    
    //I2C Slew Rate Type And Definitions
    typedef bool Slew_Rate_t;
    #define I2C_SLEW_ON     ((Slew_Rate_t)0)
    #define I2C_SLEW_OFF    ((Slew_Rate_t)1)
    
    //I2C SMBus Type And Definitions
    typedef bool SMBus_t;
    #define I2C_SMBus_OFF   ((SMBus_t)0)
    #define I2C_SMBus_ON    ((SMBus_t)1)
    
/*@FUNCTION_PROTOTYPES*/
                                     
    //Master_Mode_Function_Prototypes
        void I2C_Master_Initialize(I2C_BaudRate_t I2C_BaudRate, Slew_Rate_t I2C_SLEW_OnOff, SMBus_t I2C_SMBus_OnOff);
        void I2C_Master_Start(void);
        void I2C_Master_RepeatedStart(void);
        void I2C_Master_Stop(void);
        void I2C_Master_Send_ACK(void);
        void I2C_Master_Send_NACK(void);
        unsigned char I2C_Master_Write(unsigned char Master_Tx_Data);   //Retunrs Acknowledge Status bit.
        unsigned char I2C_Master_Read(void);
    

    //Slave_Mode_Function_Prototypes
        void I2C_Slave_Initialize(I2C_Slave_Mode_t I2C_Slave_Mode, I2C_Slave_Address_t I2C_Slave_Address, Slew_Rate_t I2C_SLEW_OnOff, SMBus_t I2C_SMBus_OnOff);
        void I2C_Slave_Transmit(unsigned char Slave_Tx_Data);
        unsigned char I2C_Slave_Receive(void);
        
#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */
