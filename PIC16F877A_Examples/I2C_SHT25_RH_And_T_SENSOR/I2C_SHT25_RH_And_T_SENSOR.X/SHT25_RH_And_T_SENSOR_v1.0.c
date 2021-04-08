/* 
 * File:   SHT25_RH_And_T_SENSOR_v1.0.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 21 Mart 2021 Pazar, 04:03
 * Version: v1.0
 */

#include "SHT25_RH_And_T_SENSOR_v1.0.h"
#include "I2C_v1.1.h"

/*@DEFINITIONS*/
    #define Measurement_delay_ms(x)   __delay_ms(x)
    #define SHT25_I2C_Address 0x40  //b'1000 000'

    //SHT25 Sensor Commands
    #define Trigger_T_Measurement_HM        0xE3 //Hold Master      //Not Used!
    #define Trigger_RH_Measurement_HM       0xE5 //Hold Master      //Not Used!
    #define Trigger_T_Measurement_NoHM      0xF3 //No Hold Master
    #define Trigger_RH_Measurement_NoHM     0xF5 //No Hold Master
    #define Write_User_Register             0xE6                    //Not Used!
    #define Read_User_Register              0xE7                    //Not Used!
    #define Soft_Reset_Command              0xFE

/*@SHT25_RH_And_T_SENSOR_FUNCTIONS*/
    unsigned int I2C_SHT25_Temperature_Read(void){
        unsigned int Measurement_Buffer[2];
        I2C_Master_Start();
        while(I2C_Master_Write(SHT25_I2C_Address<<1));
        while(I2C_Master_Write(Trigger_T_Measurement_NoHM));
        I2C_Master_Stop();
        Measurement_delay_ms(100);
        I2C_Master_Start();
        while(I2C_Master_Write((SHT25_I2C_Address<<1)|0x01));
        Measurement_Buffer[0] = I2C_Master_Read();
        I2C_Master_Send_ACK();
        Measurement_Buffer[1] = I2C_Master_Read();
        I2C_Master_Send_NACK();
        I2C_Master_Stop();
        return ((((Measurement_Buffer[0] * 256.0) + Measurement_Buffer[1]) * 175.72) / 65536.0) - 45.85;
    }

    unsigned int I2C_SHT25_Relative_Humidity_Read(void){
        unsigned int Measurement_Buffer[2];
        I2C_Master_Start();
        while(I2C_Master_Write(SHT25_I2C_Address<<1));
        while(I2C_Master_Write(Trigger_RH_Measurement_NoHM));
        I2C_Master_Stop();
        Measurement_delay_ms(30);
        I2C_Master_Start();
        while(I2C_Master_Write((SHT25_I2C_Address<<1)|0x01));
        Measurement_Buffer[0] = I2C_Master_Read();
        I2C_Master_Send_ACK();
        Measurement_Buffer[1] = I2C_Master_Read();
        I2C_Master_Send_NACK();
        I2C_Master_Stop();
        return ((((Measurement_Buffer[0] * 256.0) + Measurement_Buffer[1]) * 125.0) / 65536.0) - 6.0;
    }

    void I2C_SHT25_Soft_Reset(void){
        I2C_Master_Start();
        I2C_Master_Write(SHT25_I2C_Address<<1);
        I2C_Master_Write(Soft_Reset_Command);
        I2C_Master_Stop();
    }
