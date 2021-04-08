/*
 * File:   I2C_24C64_EEPROM_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 13 Mart 2021 Cumartesi, 23:01
 */


#include "configurations.h"
#include "I2C_v1.1.h"
#include "I2C_LCD_v2.0.h"
#include "24C64_EEPROM_v1.0.h"
#include <stdio.h>

I2C_LCD_t LCD1;

#define EEPROM1 0xA0
#define EE_PAGE_INC PORTBbits.RB0
#define EE_PAGE_DEC PORTBbits.RB1
#define EE_PAGE_ERASE PORTBbits.RB2
unsigned int EE_Add=0x0000;
unsigned int counter = 0;
unsigned char writer_data_buffer[]={"0123456789ABCDEF0123456789ABCDEF"};
char reader_data_buffer_H[17];
char reader_data_buffer_L[17];

void main(void) {
    Initial_Configurations();
    I2C_Master_Initialize(I2C_SPEED_400KHz, I2C_SLEW_OFF, I2C_SMBus_OFF);
    I2C_LCD_init(&LCD1, 0x40, LCD_2LINE, LCD_5x8DOTS);
    
    I2C_LCD_clear(LCD1);
    I2C_LCD_set_cursor(LCD1,1,3);
    I2C_LCD_write_string(LCD1,"LCD1 INITIALIZED");
    
    I2C_LCD_set_cursor(LCD1,3,1);
    I2C_LCD_write_string(LCD1,"I2C EEPROM WRITING..");
    I2C_EEPROM_Page_Write(EEPROM1, EE_Add, writer_data_buffer, 32);
    __delay_ms(5);
    for(int i=0;i<32;i++){
        I2C_EEPROM_Byte_Write(EEPROM1, (EE_Add+32)+i, 'A');
        __delay_ms(5);
        I2C_EEPROM_Byte_Write(EEPROM1, (EE_Add+64)+i, 'B');
        __delay_ms(5);
        I2C_EEPROM_Byte_Write(EEPROM1, (EE_Add+96)+i, 'C');
        __delay_ms(5);
        I2C_EEPROM_Byte_Write(EEPROM1, (EE_Add+128)+i, 'D');
        __delay_ms(5);
        I2C_EEPROM_Byte_Write(EEPROM1, (EE_Add+160)+i, 'F');
        __delay_ms(5);
    }
    I2C_LCD_set_cursor(LCD1,3,1);
    I2C_LCD_write_string(LCD1,"I2C EEPROM WRITED.  ");
    __delay_ms(250);
    
    int page_num = 0;
    int old_page_num = -1;
    char spage_num[3];

    while(1){
        if(EE_PAGE_INC==1){
            while(EE_PAGE_INC);
            if(page_num<10) page_num++;
        }else if(EE_PAGE_DEC==1){
            while(EE_PAGE_DEC);
            if(page_num>0) page_num--;
        }else if(EE_PAGE_ERASE==1){
            while(EE_PAGE_ERASE);
            I2C_LCD_clear(LCD1);
            I2C_LCD_write_string(LCD1, "EEPROM PAGE:");
            I2C_LCD_set_cursor(LCD1, 1, 13);
            I2C_LCD_write_string(LCD1, spage_num);
            I2C_LCD_set_cursor(LCD1,3,2);
            I2C_LCD_write_string(LCD1,"ERASING..");
            for(int i=0;i<32;i++){
                I2C_EEPROM_Byte_Write(EEPROM1, EE_Add+(32*page_num)+i, 255);I2C_LCD_set_cursor(LCD1,2,1);
                __delay_ms(5);
            }
            I2C_LCD_set_cursor(LCD1,3,2);
            I2C_LCD_write_string(LCD1,"ERASED COMPLETED.");
            __delay_ms(250);
            old_page_num = -1;
        }
        
        while(page_num != old_page_num){
            I2C_EEPROM_Sequential_Read(EEPROM1, EE_Add+(32*page_num), reader_data_buffer_L, 16);
            I2C_EEPROM_Sequential_Read(EEPROM1, EE_Add+((32*page_num)+16), reader_data_buffer_H, 16);

            sprintf(spage_num, "%d", page_num);

            I2C_LCD_clear(LCD1);
            I2C_LCD_write_string(LCD1, "EEPROM PAGE:");
            I2C_LCD_set_cursor(LCD1, 1, 13);
            I2C_LCD_write_string(LCD1, spage_num);
            
            I2C_LCD_set_cursor(LCD1, 2, 1);
            I2C_LCD_write_string(LCD1, " 0.");
            I2C_LCD_set_cursor(LCD1, 2, 5);
            I2C_LCD_write_string(LCD1, reader_data_buffer_L);
            
            I2C_LCD_set_cursor(LCD1, 3, 1);
            I2C_LCD_write_string(LCD1, "16.");
            I2C_LCD_set_cursor(LCD1, 3, 5);
            I2C_LCD_write_string(LCD1, reader_data_buffer_H);
            
            old_page_num = page_num;
        }
    }
    return;
}
