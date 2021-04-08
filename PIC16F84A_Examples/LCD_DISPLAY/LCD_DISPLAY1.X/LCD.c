/* 
 * File:   LCD.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 06 Haziran 2020 Cumartesi, 17:14
 */

#include"LCD.h"

//LCD Library Development Functions Prototype
static void LCD_data_sender(uint8_t data);
static void LCD_send_commad(unsigned char cmd);

/*@LCD_DISPLAY_CONTROL_FUNCTIONS*/

    static void LCD_data_sender(uint8_t data){
    #if (defined(LCD_D0) && defined(LCD_D1) && defined(LCD_D2) && defined(LCD_D3) && defined(LCD_D4) && defined(LCD_D5) && defined(LCD_D6) && defined(LCD_D7))
        LCD_E = clear;
        LCD_D0 =  data&0x01;
        LCD_D1 = (data>>1)&0x01;
        LCD_D2 = (data>>2)&0x01;
        LCD_D3 = (data>>3)&0x01;
        LCD_D4 = (data>>4)&0x01;
        LCD_D5 = (data>>5)&0x01;
        LCD_D6 = (data>>6)&0x01;
        LCD_D7 = (data>>7)&0x01;
        LCD_E = set;
        LCD_delay;
        LCD_E = clear;
    #elif (!defined(LCD_D0) && !defined(LCD_D1) && !defined(LCD_D2) && !defined(LCD_D3) && defined(LCD_D4) && defined(LCD_D5) && defined(LCD_D6) && defined(LCD_D7))
        LCD_E = clear;
        LCD_D4 = (data>>4)&0x01;
        LCD_D5 = (data>>5)&0x01;
        LCD_D6 = (data>>6)&0x01;
        LCD_D7 = (data>>7)&0x01;
        LCD_E = set;
        LCD_delay;
        LCD_E = clear;
        LCD_D4 =  data&0x01;
        LCD_D5 = (data>>1)&0x01;
        LCD_D6 = (data>>2)&0x01;
        LCD_D7 = (data>>3)&0x01;
        LCD_E = set;
        LCD_delay;
        LCD_E = clear;
    #else
    #error 'LCD pins not correctly defined!'
    #endif
    }

    static void LCD_send_commad(unsigned char cmd){
        LCD_RS = clear;
        LCD_data_sender(cmd);
    }

    void LCD_send_char(unsigned char chr){
        LCD_RS = clear;
        LCD_RS = set;
        LCD_data_sender(chr);
    }

    void LCD_send_string(char *str){
        uint8_t i;
        for(i=0;str[i]!='\0';i++){
            if(str[i]=='\n') LCD_send_commad(LCD_LINE2 - 1);
            LCD_send_char(str[i]);
        }
    }

    void LCD_clear(void){
        LCD_send_commad(LCD_CLEAR_DISPLAY);
        LCD_delay;
    }

    void LCD_return_home(void){
        LCD_send_commad(LCD_RETURN_HOME);
        LCD_delay;
    }

    void LCD_entry_mode(uint8_t I_or_D, uint8_t S){
        LCD_send_commad(LCD_ENTRY_MODE_SET | I_or_D | S);
        LCD_delay;
    }

    void LCD_display_on_off_control(uint8_t D, uint8_t C, uint8_t B){
        LCD_send_commad(LCD_DISPLAY_ON_OFF_CONTROL | D | C | B);
        LCD_delay;
    }

    void LCD_cursor_or_display_shift(uint8_t S_or_C, uint8_t R_or_L){
        LCD_send_commad(LCD_CURSOR_OR_DISOLAY_SHIFT | S_or_C | R_or_L);
        LCD_delay;
    }

    void LCD_init(uint8_t DL, uint8_t N, uint8_t F){
        if (DL == LCD_8BIT_MODE){
            LCD_send_commad(LCD_FUNCTION_SET | DL | N | F);
            LCD_delay;
        }else if (DL == LCD_4BIT_MODE){
            LCD_send_commad(LCD_FUNCTION_SET | DL | N | F);
            LCD_E = set;
            LCD_delay;
            LCD_E = clear;
            LCD_send_commad(LCD_FUNCTION_SET | DL | N | F);
            LCD_delay;
        }
        LCD_display_on_off_control(LCD_DISPLAY_ON, LCD_CURSOR_ON, LCD_BLINK_OFF);
        LCD_entry_mode(LCD_ENTRY_LEFT, LCD_ENTRY_SHIFT_DECREMENT);
        LCD_send_commad(LCD_LINE1);
        LCD_delay;
    }

    void LCD_set_cursor(uint8_t row, uint8_t colomn){
        switch(row){
            case 1:
                LCD_send_commad(LCD_LINE1 + colomn-1); break;
            case 2:
                LCD_send_commad(LCD_LINE2 + colomn-1); break;
            case 3:
                LCD_send_commad(LCD_LINE3 + colomn-1); break;
            case 4:
                LCD_send_commad(LCD_LINE4 + colomn-1); break;    
        }
    }
    