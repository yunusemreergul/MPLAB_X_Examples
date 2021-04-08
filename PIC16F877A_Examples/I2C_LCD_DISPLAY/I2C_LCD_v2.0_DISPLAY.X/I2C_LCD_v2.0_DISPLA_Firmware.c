/*
 * File:   I2C_LCD_v2.0_DISPLA_Firmware.c
 * Author: ACER-PC
 *
 * Created on 09 Mart 2021 Sal?, 12:58
 */


#include "configurations.h"
#include "I2C.h"
#include "I2C_LCD_v2.0.h"

I2C_LCD_t LCD1;
I2C_LCD_t LCD2;

void main(void){
    Initial_Configurations();
    I2C_Master_Initialize(I2C_SPEED_100KHz, I2C_SLEW_OFF, I2C_SMBus_OFF);
    
    I2C_LCD_init(&LCD1, 0x40, LCD_2LINE, LCD_5x8DOTS);
    I2C_LCD_init(&LCD2, 0x4E, LCD_2LINE, LCD_5x8DOTS);
    
    I2C_LCD_set_cursor(LCD1,1,1);
    I2C_LCD_write_string(LCD1,"LCD1");
    I2C_LCD_set_cursor(LCD2,1,1);
    I2C_LCD_write_string(LCD2,"LCD2");
    __delay_ms(1000);
    
    I2C_LCD_BackLight_OFF(&LCD1);
    
    I2C_LCD_set_cursor(LCD2,2,4);
    I2C_LCD_write_string(LCD2,"HELLO WORD");
    I2C_LCD_clear(LCD1);
    //LCD_clear(LCD2_ADD);
    
    I2C_LCD_set_cursor(LCD1,2,3);
    I2C_LCD_write_char(LCD1,'Y');
    __delay_ms(200);
    I2C_LCD_write_char(LCD1,'U');
    __delay_ms(200);
    I2C_LCD_write_char(LCD1,'N');
    __delay_ms(200);
    I2C_LCD_write_char(LCD1,'U');
    __delay_ms(200);
    I2C_LCD_write_char(LCD1,'S');
    __delay_ms(200);
    I2C_LCD_write_string(LCD1," EMRE");
    __delay_ms(200);
    I2C_LCD_set_cursor(LCD1,3,6);
    I2C_LCD_write_string(LCD1,"ERGUL");
    __delay_ms(500);
    
    while(1){
        for(int i=0;i<6;i++){
            I2C_LCD_cursor_or_display_shift(LCD1, LCD_DISPLAY_MOVE, LCD_MOVE_RIGHT);
            __delay_ms(250);
        }
        for(int i=6;i>0;i--){
            I2C_LCD_cursor_or_display_shift(LCD1, LCD_DISPLAY_MOVE, LCD_MOVE_LEFT);
            __delay_ms(250);
        }
    }
    return;
}
