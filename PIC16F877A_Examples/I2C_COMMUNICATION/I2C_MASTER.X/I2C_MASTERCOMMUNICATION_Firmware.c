/*
 * File:   I2C_MASTERCOMMUNICATION_Firmware.c
 * Author: Yunus Emre ERGUL
 *
 * Created on 19 Ocak 2021 Sal?, 07:21
 */

#include "configurations.h"
#include "I2C.h"

/*@I2C COMMUNICATION MASTER EXAMPLE CODE*/

    //Example_Code_Function_Prototypes
    void Two_Byte_Write_Operation(void);
    void Two_Byte_Read_And_Write_Operation(void);

    unsigned char Receive_Buffer[2];

    void main(void) {
        Initial_Configurations();
        I2C_Master_Initialize(I2C_SPEED_400KHz, I2C_SLEW_OFF, I2C_SMBus_OFF);

        while(1){
            //ExampleCode1: Master_Two Byte Reading Operation With RepeatedStart.
            if(!PORTBbits.RB0){
                Two_Byte_Write_Operation();
                __delay_ms(500); //Monitoring time delay for I2C debugger.
            }

            //ExampleCode2: Master_Two Byte Reading Operation And Master_Two Byte Writing Operation With RepeatedStart.
            if(PORTBbits.RB0){
                Two_Byte_Read_And_Write_Operation();
                __delay_ms(2000); //Monitoring time delay for I2C debugger.
            }
        }
        return;
    }

    void Two_Byte_Write_Operation(void){
        I2C_Master_Start();
        I2C_Master_Write(0x40);
        I2C_Master_Write(PORTD);
        I2C_Master_Write(PORTD);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0x40);
        I2C_Master_Write(PORTD);
        I2C_Master_Write(PORTD);
        I2C_Master_Stop();
    }

    void Two_Byte_Read_And_Write_Operation(void){
        I2C_Master_Start();
        PORTAbits.RA0 = I2C_Master_Write(0x41);
        Receive_Buffer[0] = I2C_Master_Read();
        I2C_Master_Send_ACK();
        Receive_Buffer[1] = I2C_Master_Read();
        I2C_Master_Send_NACK();
        I2C_Master_RepeatedStart();
        PORTAbits.RA0 = I2C_Master_Write(0x40);
        I2C_Master_Write(Receive_Buffer[0]+1);
        I2C_Master_Write(Receive_Buffer[0]+1);
        I2C_Master_Stop();
    }
