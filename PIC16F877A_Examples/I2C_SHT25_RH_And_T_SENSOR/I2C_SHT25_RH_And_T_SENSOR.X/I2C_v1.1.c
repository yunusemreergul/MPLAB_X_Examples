/* 
 * File:   I2C_v1.1.h
 * Author: Yunus Emre ERGUL
 *
 * Created on 26 Ocak 2021 Sal?, 14:54
 * Version: v1.1
 * Version Information: - 'I2C_Master_Check_Idle();' function has been added to the end of other Master functions to check the processing of Master functions.
 */

#include "I2C_v1.1.h"

/*@I2C_MASTER_COMMUNICATION_FUNCTIONS*/

    void I2C_Master_Initialize(I2C_BaudRate_t I2C_BaudRate, Slew_Rate_t I2C_SMP_OnOff, SMBus_t I2C_CKE_OnOff){
        SSPSTAT = (I2C_SMP_OnOff<<7)|(I2C_CKE_OnOff<<6);    //Initial MSSP STATUS REGISTER.
        SSPCON = 0b00101000;                                //Initial MSSP CONTROL REGISTER 1.
        SSPCON2 = 0x00;                                     //Initial MSSP CONTROL REGISTER 2.
        SSPADD = (_XTAL_FREQ/(4*I2C_BaudRate)) - 1;         //Initial BAUD RATE GENERATOR.
        TRISCbits.TRISC3 = SET;                             //Initial TRISC<3> Bit (SCL set to input).
        TRISCbits.TRISC4 = SET;                             //Initial TRISC<4> Bit (SDA set to input).
    }

    static inline void I2C_Master_Check_Idle(void){
        while((SSPSTATbits.R_nW)||(SSPCON2bits.SEN)||(SSPCON2bits.RSEN)||(SSPCON2bits.PEN)||(SSPCON2bits.RCEN)||(SSPCON2bits.ACKEN));   //Wait till I2C module completes previous operation and becomes idle.
    }

    void I2C_Master_Start(void){
        I2C_Master_Check_Idle();
        SSPCON2bits.SEN = SET;  //I2C Stop Start Condition has been set.
        I2C_Master_Check_Idle();
    }

    void I2C_Master_RepeatedStart(void){
        I2C_Master_Check_Idle();
        SSPCON2bits.RSEN = SET; //I2C Stop Repeated Start Condition has been set.
        I2C_Master_Check_Idle();
    }

    void I2C_Master_Stop(void){
        I2C_Master_Check_Idle();
        SSPCON2bits.PEN = SET;  //I2C Stop Condition has been set.
        I2C_Master_Check_Idle();
    }

    void I2C_Master_Send_ACK(void){
        I2C_Master_Check_Idle();
        SSPCON2bits.ACKDT = 0;      //ACK information.
        SSPCON2bits.ACKEN = SET;    //The ACK sender has been set.
        I2C_Master_Check_Idle();
    }
    
    void I2C_Master_Send_NACK(void){
        I2C_Master_Check_Idle();
        SSPCON2bits.ACKDT = 1;      //NACK information.
        SSPCON2bits.ACKEN = SET;    //The NACK sender has been set.
        I2C_Master_Check_Idle();
    }

    unsigned char I2C_Master_Write(unsigned char Master_Tx_Data){
        I2C_Master_Check_Idle();
        SSPBUF = Master_Tx_Data;   //Upload data to be transferred to the slave device.
        I2C_Master_Check_Idle();
        return SSPCON2bits.ACKSTAT;         //Retunrs Acknowledge Status bit.
    }

    unsigned char I2C_Master_Read(void){
        unsigned char Recieved_Data;
        //Check For Receive Overflow
            if(SSPCONbits.SSPOV){
                uint8_t dummy = SSPBUF;     //Read the SSPBUF register to clear.
                SSPCONbits.SSPOV = CLEAR;   //Clear the Receive Overflow Indicator bit.
            }
        I2C_Master_Check_Idle();
        SSPCON2bits.RCEN = SET; //Initiate I2C Receive Enable Sequence.
        I2C_Master_Check_Idle();
        Recieved_Data = SSPBUF; //Read the data received from the slave device.
        return Recieved_Data;   //Returns received data from the slave device.
    }


/*@I2C_SLAVE_COMMUNICATION_FUNCTIONS*/
    
    void I2C_Slave_Initialize(I2C_Slave_Mode_t I2C_Slave_Mode, I2C_Slave_Address_t I2C_Slave_Address, Slew_Rate_t I2C_SLEW_OnOff, SMBus_t I2C_SMBus_OnOff){
        SSPSTAT = (I2C_SLEW_OnOff<<7)|(I2C_SMBus_OnOff<<6); //Initial MSSP STATUS REGISTER.
        SSPCON = (0b00100000)|(I2C_Slave_Mode);                     //Initial MSSP CONTROL REGISTER 1.
        SSPCON2 = 0x01;                                             //Initial MSSP CONTROL REGISTER 2 (Stretch enabled).
        SSPADD = I2C_Slave_Address;                                 //Initial BAUD RATE GENERATOR.
        TRISCbits.TRISC3 = SET;                                     //Initial TRISC<3> Bit (SCL set to input).
        TRISCbits.TRISC4 = SET;                                     //Initial TRISC<4> Bit (SDA set to input).
        PIR1bits.SSPIF = CLEAR;                                     //Synchronous Serial Port Interrupt Flag Clear.
        PIE1bits.SSPIE = SET;                                       //Synchronous Serial Port Interrupt Enable.
    }
    
    static void I2C_Slave_Check_Overflow_And_Collision(void){
        if((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            uint8_t dummy = SSPBUF; //Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;   //Clear the overflow flag
            SSPCONbits.WCOL = 0;    //Clear the collision bit
            SSPCONbits.CKP = 1;     //Release Clock Stretch.
        }
    }
    
    void I2C_Slave_Transmit(unsigned char Slave_Tx_Data){
        I2C_Slave_Check_Overflow_And_Collision();
        //Master Read And Slave Transmit Conditions
            if(SSPSTATbits.D_nA == 0 && SSPSTATbits.R_nW == 1){
                SSPBUF = Slave_Tx_Data;   //Upload data to be transferred to the master device.
                SSPCONbits.CKP = SET;           //Release Clock Stretch.
                while(SSPSTATbits.BF);          //Check for SSPBUF register is empty.
            }else if(SSPSTATbits.D_nA == 1 && SSPSTATbits.R_nW == 1){
                SSPBUF = Slave_Tx_Data;   //Upload data to be transferred to the master device.
                SSPCONbits.CKP = SET;           //Release Clock Stretch.
                while(SSPSTATbits.BF);          //Check for SSPBUF register is empty.
            }
    }
    
    unsigned char I2C_Slave_Receive(void){
        I2C_Slave_Check_Overflow_And_Collision();
        //Master Read And Slave Receive Conditions
            unsigned char RX_Data = 0x00;
            if(SSPSTATbits.D_nA == 0 && SSPSTATbits.R_nW == 0){             //Last Byte Was An Address
                uint8_t dummy = SSPBUF;         //Read the SSPBUF register to clear.
                SSPCONbits.CKP = SET;           //Release Clock Stretch.
            }else if(SSPSTATbits.D_nA == 1 && SSPSTATbits.R_nW == 0){       //Last Byte Was An Data
                //while(!SSPSTATbits.BF);       //Check for SSPBUF register is full.(There is a double buffer in receive operations.)(NOT USE)
                RX_Data = SSPBUF;               //Read the data received from the master device.
                SSPCONbits.CKP = SET;           //Release Clock Stretch.
            }
        return RX_Data;
    }
    