/* 
 * File:   24C64_EEPROM_v1.0.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 13 Mart 2021 Cumartesi, 23:07
 * Version: v1.0
 */

#include"24C64_EEPROM_v1.0.h"
#include"I2C_v1.1.h"

#define Reconnect_Cycle 3   //Reconnection Cycle to Address of I2C

/*@24C64_I2C_EEPROM_WRITE_FUNCTIONS*/
    void I2C_EEPROM_Byte_Write(unsigned char I2C_Address, unsigned int EEPROM_Address, unsigned char Data){
        I2C_Master_Start();
        for(int c=0;c<Reconnect_Cycle;c++){
            if(!I2C_Master_Write(I2C_Address)){
                I2C_Master_Write(EEPROM_Address>>8);
                I2C_Master_Write(EEPROM_Address);
                I2C_Master_Write(Data);
                break;
            }else if(c==2) break;
            I2C_Master_RepeatedStart();
        }
        I2C_Master_Stop();
    }

    void I2C_EEPROM_Page_Write(unsigned char I2C_Address, unsigned int EEPROM_Address, unsigned char *Data_Buffer, unsigned int Length_of_Data){
        I2C_Master_Start();
        for(int c=0;c<Reconnect_Cycle;c++){
            if(!I2C_Master_Write(I2C_Address)){
                I2C_Master_Write(EEPROM_Address>>8);
                I2C_Master_Write(EEPROM_Address);
                for(unsigned int i=0;i<Length_of_Data;i++){
                    I2C_Master_Write(Data_Buffer[i]);
                }
                break;
            }else if(c==2) break;
            I2C_Master_RepeatedStart();
        }
        I2C_Master_Stop();
    }

    
/*@24C64_I2C_EEPROM_READ_FUNCTIONS*/
    unsigned char I2C_EEPROM_CurrentAdd_Read(unsigned char I2C_Address){
        unsigned char Data_Read = 0xFF;
        I2C_Master_Start();
        for(int c=0;c<Reconnect_Cycle;c++){
            if(!I2C_Master_Write((I2C_Address|0x01))){
                Data_Read = I2C_Master_Read();
                I2C_Master_Send_NACK();
                break;
            }else if(c==2) break;
            I2C_Master_RepeatedStart();
        }
        I2C_Master_Stop();
        return Data_Read;
    }

    unsigned char I2C_EEPROM_Random_Read(unsigned char I2C_Address, unsigned int EEPROM_Address){
        unsigned char Data_Read = 0xFF;
        I2C_Master_Start();
        for(int c=0;c<Reconnect_Cycle;c++){
            if(!I2C_Master_Write(I2C_Address)){
                I2C_Master_Write(EEPROM_Address>>8);
                I2C_Master_Write(EEPROM_Address);
                I2C_Master_RepeatedStart();
                I2C_Master_Write((I2C_Address|0x01));
                Data_Read = I2C_Master_Read();
                I2C_Master_Send_NACK();
                break;
            }else if(c==2) break;
            I2C_Master_RepeatedStart();
        }
        I2C_Master_Stop();
        return Data_Read;
    }

    void I2C_EEPROM_Sequential_Read(unsigned char I2C_Address, unsigned int EEPROM_Address, char *Data_Buffer, unsigned int Length_of_Data){
        I2C_Master_Start();
        for(int c=0;c<Reconnect_Cycle;c++){
            if(!I2C_Master_Write(I2C_Address)){
                I2C_Master_Write(EEPROM_Address>>8);
                I2C_Master_Write(EEPROM_Address);
                I2C_Master_RepeatedStart();
                I2C_Master_Write((I2C_Address|0x01));
                for(unsigned int i=0;i<Length_of_Data;i++){
                    Data_Buffer[i] = I2C_Master_Read();
                    if(i == (Length_of_Data-1)){
                        I2C_Master_Send_NACK();
                    }else I2C_Master_Send_ACK();
                }
                break;
            }else if(c==2) break;
            I2C_Master_RepeatedStart();
        }
        I2C_Master_Stop();
    }
