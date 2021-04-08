/* 
 * File:   I2C_LCD_v2.0.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 06 Haziran 2020 Cumartesi, 17:14
 * Version: v2.0
 * Version Information: - LCD backlight functions are handled specific to the LCD address.
 *                      - LCD objects are identified by I2C_LCD_t type.
 *                      - The LCD object in I2C_LCD_t type is configured with the 'I2C_LCD_init();' function.
 */

#include"I2C_LCD_v2.0.h"
#include "PCF8574_IO_Expander_v1.0.h"

/*@I2C_SERIAL_LCD_DISPLAY_DEVELOPMENT_FUNCTIONS*/
    //LCD Library Development Functions Prototype
        static void LCD_data_sender(I2C_LCD_t LCD_Obj, uint8_t data, p_I2C_IO_Expander_Writer_t callback_function);
        static void (*p_LCD_data_sender)(I2C_LCD_t, uint8_t, p_I2C_IO_Expander_Writer_t) = &LCD_data_sender;
         
        static void LCD_send_commad(I2C_LCD_t LCD_Obj, unsigned char cmd);
        static void (*p_LCD_send_commad)(I2C_LCD_t, unsigned char) = &LCD_send_commad;

    static void LCD_data_sender(I2C_LCD_t LCD_Obj, uint8_t data, p_I2C_IO_Expander_Writer_t callback_function){
        callback_function(LCD_Obj.Address, (data&0xF0) | Lcd_RS_State | Lcd_RW_State | LCD_E_ON  | LCD_Obj.BackLight_State);
        callback_function(LCD_Obj.Address, (data&0xF0) | Lcd_RS_State | Lcd_RW_State | LCD_E_OFF | LCD_Obj.BackLight_State);
        callback_function(LCD_Obj.Address, ((data<<4)&0xF0) | Lcd_RS_State | Lcd_RW_State |LCD_E_ON  | LCD_Obj.BackLight_State);
        callback_function(LCD_Obj.Address, ((data<<4)&0xF0) | Lcd_RS_State | Lcd_RW_State |LCD_E_OFF | LCD_Obj.BackLight_State);
    }

    static void LCD_send_commad(I2C_LCD_t LCD_Obj, unsigned char cmd){
        Lcd_RS_State = LCD_RS_COMMAND;
        p_LCD_data_sender(LCD_Obj, cmd, p_I2C_IO_Expander_Writer);
    }
        
/*@I2C_SERIAL_LCD_DISPLAY_CONTROL_FUNCTIONS*/
    void I2C_LCD_write_char(I2C_LCD_t LCD_Obj, unsigned char chr){
        Lcd_RS_State = LCD_RS_DATA;
        p_LCD_data_sender(LCD_Obj, chr, p_I2C_IO_Expander_Writer);
    }

    void I2C_LCD_write_string(I2C_LCD_t LCD_Obj, char *str){
        uint8_t i;
        for(i=0;str[i]!='\0';i++){
            if(str[i]=='\n') p_LCD_send_commad(LCD_Obj, (LCD_LINE2 - 1));
            I2C_LCD_write_char(LCD_Obj, str[i]);
        }
    }

    void I2C_LCD_clear(I2C_LCD_t LCD_Obj){
        p_LCD_send_commad(LCD_Obj, LCD_CLEAR_DISPLAY);
        LCD_delay;
    }

    void I2C_LCD_return_home(I2C_LCD_t LCD_Obj){
        p_LCD_send_commad(LCD_Obj, LCD_RETURN_HOME);
        LCD_delay;
    }

    void I2C_LCD_entry_mode(I2C_LCD_t LCD_Obj, uint8_t I_or_D, uint8_t S){
        p_LCD_send_commad(LCD_Obj, LCD_ENTRY_MODE_SET | I_or_D | S);
        LCD_delay;
    }

    void I2C_LCD_display_on_off_control(I2C_LCD_t LCD_Obj, uint8_t D, uint8_t C, uint8_t B){
        p_LCD_send_commad(LCD_Obj, LCD_DISPLAY_ON_OFF_CONTROL | D | C | B);
        LCD_delay;
    }

    void I2C_LCD_cursor_or_display_shift(I2C_LCD_t LCD_Obj, uint8_t S_or_C, uint8_t R_or_L){
        p_LCD_send_commad(LCD_Obj, LCD_CURSOR_OR_DISOLAY_SHIFT | S_or_C | R_or_L);
        LCD_delay;
    }

    void I2C_LCD_init(I2C_LCD_t *LCD_Obj_Add, uint8_t I2C_LCD_Address, uint8_t N, uint8_t F){
        LCD_Obj_Add->Address = I2C_LCD_Address;
        LCD_Obj_Add->BackLight_State = LCD_BACKLIGHT_ON;
        
        p_LCD_send_commad(*LCD_Obj_Add, 0x32);
        LCD_delay;
        p_LCD_send_commad(*LCD_Obj_Add, LCD_FUNCTION_SET | LCD_4BIT_MODE | N | F);
        I2C_LCD_display_on_off_control(*LCD_Obj_Add, LCD_DISPLAY_ON, LCD_CURSOR_OFF, LCD_BLINK_OFF);
        I2C_LCD_entry_mode(*LCD_Obj_Add, LCD_ENTRY_LEFT, LCD_ENTRY_SHIFT_DECREMENT);
        p_LCD_send_commad(*LCD_Obj_Add, LCD_LINE1);
    }

    void I2C_LCD_set_cursor(I2C_LCD_t LCD_Obj, uint8_t row, uint8_t colomn){
        switch(row){
            case 1:
                p_LCD_send_commad(LCD_Obj, LCD_LINE1 + colomn-1); break;
            case 2:
                p_LCD_send_commad(LCD_Obj, LCD_LINE2 + colomn-1); break;
            case 3:
                p_LCD_send_commad(LCD_Obj, LCD_LINE3 + colomn-1); break;
            case 4:
                p_LCD_send_commad(LCD_Obj, LCD_LINE4 + colomn-1); break;    
        }
    }
    
    void I2C_LCD_BackLight_ON(I2C_LCD_t *LCD_Obj_Add){
        LCD_Obj_Add->BackLight_State = LCD_BACKLIGHT_ON;
    }
    
    void I2C_LCD_BackLight_OFF(I2C_LCD_t *LCD_Obj_Add){
        LCD_Obj_Add->BackLight_State= LCD_BACKLIGHT_OFF;
    }
