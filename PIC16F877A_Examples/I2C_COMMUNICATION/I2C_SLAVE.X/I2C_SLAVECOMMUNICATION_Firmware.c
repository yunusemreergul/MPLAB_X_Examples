/*
 * File:   I2C_SLAVECOMMUNICATION_Firmware.c
 * Author: Yunus Emre ERGUL
 *
 * Created on 19 Ocak 2021 Sal?, 07:21
 */

#include "configurations.h"
#include "I2C.h"

/*@I2C COMMUNICATION SLAVE EXAMPLE CODE*/

    unsigned char Slave_TX_Data = 0x00;
    unsigned char Slave_RX_Data = 0x00;

    //I2C Slave Communication ISR Handler Functions Prototype
    void I2C_Slave_ISR_Handler_Function(void);

    //Interrupt Function Definition
    void __interrupt() ISR(void){
        I2C_Slave_ISR_Handler_Function();
    }

    //Main Function Definition
    void main(void){
        Initial_Configurations();
        I2C_Slave_Initialize(I2C_SLAVE_7BIT, I2C_SLAVE_ADDRESS(0x40), I2C_SLEW_OFF, I2C_SMBus_OFF);  //Init I2C Slave Mode.

        while(1){
            Slave_TX_Data = 0xF0; //Transmission is not using.
            PORTB = Slave_RX_Data;
        }
        return;
    }

    //I2C Slave Communication ISR Handler Functions Definition (Note: Written by the user.)
    void I2C_Slave_ISR_Handler_Function(void){
        //Check for SSPIF
        if(PIR1bits.SSPIF){
            I2C_Slave_Transmit(Slave_TX_Data);    //Transmission is not using.
            Slave_RX_Data = I2C_Slave_Receive();
            PIR1bits.SSPIF = CLEAR; //Clear SSPIF
        }
    }
