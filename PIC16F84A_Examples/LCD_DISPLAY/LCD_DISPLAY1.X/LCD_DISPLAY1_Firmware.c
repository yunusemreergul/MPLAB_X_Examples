/*
 * File:   LCD_DISPLAY1_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 23 May?s 2020 Cumartesi, 23:26
 */

#include "configurations.h"
#include "LCD.h"
#include <stdlib.h>


void main(void) {
    
    Initial_Configurations();
    
    int8_t sayi=0;
    char s[1];
    
    LCD_init(LCD_4BIT_MODE, LCD_2LINE, LCD_5x8DOTS);
    LCD_clear();
    
    LCD_set_cursor(1,2);
    LCD_send_char('Y');
    __delay_ms(200);
    LCD_send_char('U');
    __delay_ms(200);
    LCD_send_char('N');
    __delay_ms(200);
    LCD_send_char('U');
    __delay_ms(200);
    LCD_send_char('S');
    __delay_ms(200);
    LCD_send_string(" EMRE");
    __delay_ms(200);
    LCD_set_cursor(2,5);
    LCD_send_string("ERGUL");
    __delay_ms(500);
    
    
    for(int i=0;i<4;i++)
    {
        LCD_cursor_or_display_shift(LCD_DISPLAY_MOVE,LCD_MOVE_RIGHT);
        __delay_ms(500);
        if (i==3)
        {
            for(int i=0;i<2;i++)
            {
                LCD_cursor_or_display_shift(LCD_DISPLAY_MOVE,LCD_MOVE_LEFT);
                __delay_ms(500);
            }
        }
    }
    __delay_ms(500);

    while(1)
    {
        LCD_clear();
        LCD_send_string("SAYI=");
        itoa(s,sayi,10);                //itoa(char * str, int value, int base); //Intager to string converter.
        if(sayi>9) LCD_set_cursor(1,6);
        else LCD_set_cursor(1,7);
        LCD_send_string(s);
        __delay_ms(500);
        sayi++;
        if(sayi>20) sayi=0;
    }
    return;
}
