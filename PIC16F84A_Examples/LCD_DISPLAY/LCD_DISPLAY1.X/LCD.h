/* 
 * File:   LCD.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 06 Haziran 2020 Cumartesi, 17:14
 */

/*@LCD_DISPLAY
 * You must define your crytal frequency in lcd.h file. 
 *  For example: #define _XTAL_FREQ 4000000
 * 
 * You must define LCD Pins definations in LCD.h file.
 *  For example: #define LCD_D0  PORTBbits.RB0
 *
 * You should set the defined pins as outputs.
 *  For example: TRISB = 0x00;
 *
 * For LCD initial settings, you must call the LCD_init() function 
 * in the main() function with the correct parameters.
 *  For examle: void main(void) {
                                    .
                                    .
                                    LCD_init(LCD_4BIT_MODE, LCD_2LINE, LCD_5x8DOTS);
                                    .
                                    .
 *                              }
 */

#ifndef LCD_H
#define	LCD_H

#include "configurations.h"     //Added by user.

#ifdef	__cplusplus
extern "C" {
#endif
    
#define USE_I2C_LCD
    
/*@DEFINITIONS*/
    //LCD Delay Defination
        #define LCD_delay __delay_us(1550)

    //LCD Pins Definitions
        //Data Pins
            //#define LCD_D0  PORTBbits.RB0     //USER DEFINE
            //#define LCD_D1  PORTBbits.RB1     //USER DEFINE
            //#define LCD_D2  PORTBbits.RB2     //USER DEFINE
            //#define LCD_D3  PORTBbits.RB3     //USER DEFINE
            #define LCD_D4  PORTBbits.RB4       //USER DEFINE
            #define LCD_D5  PORTBbits.RB5       //USER DEFINE
            #define LCD_D6  PORTBbits.RB6       //USER DEFINE
            #define LCD_D7  PORTBbits.RB7       //USER DEFINE

        //Control Pins
            #define LCD_RW  //Not using         //USER DEFINE
            #define LCD_RS  PORTAbits.RA0       //USER DEFINE
            #define LCD_E   PORTAbits.RA2       //USER DEFINE
    
    //LCD Instruction Definitions
        // LCD Commands
            #define LCD_CLEAR_DISPLAY 0x01          // 0b00000001
            #define LCD_RETURN_HOME 0x02            // 0b00000010
            #define LCD_ENTRY_MODE_SET 0x04         // 0b00000100
            #define LCD_DISPLAY_ON_OFF_CONTROL 0x08 // 0b00001000
            #define LCD_CURSOR_OR_DISOLAY_SHIFT 0x10// 0b00010000
            #define LCD_FUNCTION_SET 0x20           // 0b00100000
            #define LCD_SET_CGRAMADDR 0x40          // 0b01000000
            #define LCD_SET_DDRAMADDR 0x80          // 0b10000000

        // Flags For Display Entry Mode
            #define LCD_ENTRY_RIGHT 0x00
            #define LCD_ENTRY_LEFT 0x02             // 0b00000010
            #define LCD_ENTRY_SHIFT_DECREMENT 0x00
            #define LCD_ENTRY_SHIFT_INCREMENT 0x01  // 0b00000001

        // Flags For Display On/Off Control
            #define LCD_DISPLAY_ON 0x04             // 0b00000100
            #define LCD_DISPLAY_OFF 0x00            // 0b00000000
            #define LCD_CURSOR_ON 0x02              // 0b00000010
            #define LCD_CURSOR_OFF 0x00             // 0b00000000
            #define LCD_BLINK_ON 0x01               // 0b00000001
            #define LCD_BLINK_OFF 0x00              // 0b00000000

        // Flags For Display/Cursor Shift
            #define LCD_DISPLAY_MOVE 0x08           // 0b00001000
            #define LCD_CURSOR_MOVE 0x00            // 0b00000000
            #define LCD_MOVE_RIGHT 0x04             // 0b00000100
            #define LCD_MOVE_LEFT 0x00              // 0b00000000

        // Flags For Function Set
            #define LCD_8BIT_MODE 0x10              // 0b00010000
            #define LCD_4BIT_MODE 0x00              // 0b00000000
            #define LCD_2LINE 0x08                  // 0b00001000
            #define LCD_1LINE 0x00                  // 0b00000000
            #define LCD_5x10DOTS 0x04               // 0b00000100
            #define LCD_5x8DOTS 0x00                // 0b00000000

        // Lines
            #define LCD_LINE1 0x80                  // 0b10000000
            #define LCD_LINE2 0xC0                  // 0b11000000
            #define LCD_LINE3 0x94                  // 0b10010100
            #define LCD_LINE4 0xD4                  // 0b11010100

        //Set and Clear Definations  
            #define set 1
            #define clear 0

 
/*@FUNCTION_PROTOTYPES*/
    //LCD_Function_Prototypes
        void LCD_send_char(unsigned char chr);                              //LCD_send_char(char type data);
        void LCD_send_string(char *str);                                    //LCD_send_string(string type data);
        void LCD_clear(void);                                               //LCD_clear();
        void LCD_return_home(void);                                         //LCD_return_home();
        void LCD_entry_mode(uint8_t I_or_D, uint8_t S);                     //LCD_entry_mode(LCD_ENTRY_RIGHT/LCD_ENTRY_LEFT, LCD_ENTRY_SHIFT_INCREMENT/LCD_ENTRY_SHIFT_DECREMENT);
        void LCD_display_on_off_control(uint8_t D, uint8_t C, uint8_t B);   //LCD_display_on_off_control(LCD_DISPLAY_ON/LCD_DISPLAY_OFF, LCD_CURSOR_ON/LCD_CURSOR_OFF, LCD_BLINK_ON/LCD_BLINK_OFF);
        void LCD_cursor_or_display_shift(uint8_t S_or_C, uint8_t R_or_L);   //LCD_cursor_or_display_shift(LCD_DISPLAY_MOVE/LCD_CURSOR_MOVE, LCD_MOVE_RIGHT/LCD_MOVE_LEFT);
        void LCD_init(uint8_t DL, uint8_t N, uint8_t F);                    //LCD_init(LCD_8BIT_MODE/LCD_4BIT_MODE, LCD_2LINE/LCD_1LINE, LCD_5x10DOTS/LCD_5x8DOTS);
        void LCD_set_cursor(uint8_t row, uint8_t colomn);                   //LCD_set_cursor(row value, colomn value);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

