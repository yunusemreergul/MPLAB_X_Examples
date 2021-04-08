/*
 * File:   I2C_SHT25_RH_And_T_SENSOR_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 21 Mart 2021 Pazar, 03:59
 */


#include "configurations.h"
#include "I2C_v1.1.h"
#include "I2C_LCD_v2.0.h"
#include "SHT25_RH_And_T_SENSOR_v1.0.h"
#include <stdio.h>

I2C_LCD_t LCD1;

int8_t T;
char T_str[20];
uint8_t RH;
char RH_str[20];

void main(void) {
    Initial_Configurations();
    I2C_Master_Initialize(I2C_SPEED_100KHz, I2C_SLEW_OFF, I2C_SMBus_OFF);
    I2C_LCD_init(&LCD1, 0x40, LCD_2LINE, LCD_5x8DOTS);
    
    I2C_LCD_clear(LCD1);
    I2C_LCD_set_cursor(LCD1, 1, 3);
    I2C_LCD_write_string(LCD1, "LCD1 INITIALIZED");
    __delay_ms(500);
    I2C_LCD_set_cursor(LCD1, 1, 1);
    I2C_LCD_write_string(LCD1, "I2C SHT25 READING..");
    
    while(1){
        T = I2C_SHT25_Temperature_Read();
        RH = I2C_SHT25_Relative_Humidity_Read();
        sprintf(T_str, "T:%3d%cC", T, 0xDF);
        sprintf(RH_str, "RH:%3d%%", RH);
        I2C_LCD_set_cursor(LCD1, 3, 10);
        I2C_LCD_write_string(LCD1, T_str);
        I2C_LCD_set_cursor(LCD1, 3, 1);
        I2C_LCD_write_string(LCD1, RH_str);
        __delay_ms(100);
    }
    return;
}
