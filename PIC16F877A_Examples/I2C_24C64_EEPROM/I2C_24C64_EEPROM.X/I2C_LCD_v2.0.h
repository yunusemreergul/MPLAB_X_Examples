/* 
 * File:   I2C_LCD_v2.0.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 06 Haziran 2020 Cumartesi, 17:14
 * Version: v2.0
 * Version Information: - LCD backlight functions are handled specific to the LCD address.
 *                          I2C_LCD_BackLight_ON(I2C_LCD_t *LCD_Obj_Add);
 *                          I2C_LCD_BackLight_OFF(I2C_LCD_t *LCD_Obj_Add);
 * 
 *                          For example: I2C_LCD_BackLight_OFF(&LCD1);
 * 
 *                      - LCD objects are identified by I2C_LCD_t type.
 *                      - The LCD object in I2C_LCD_t type is configured with the 'I2C_LCD_init();' function.
 */

/*@I2C_LCD_DISPLAY
 * You must be include your configurations.h file in I2C_LCD.h file. 
 *  For example: #include "configurations.h"
 * 
 * You must be define I2C LCD object with 'I2C_LCD_t' type in main source file.
 *  For example: I2C_LCD_t LCD1;
 *
 * You must set the I2C_Master_Initialize in the 'main()' function.
 *  For example: I2C_Master_Initialize(I2C_SPEED_100KHz, I2C_SLEW_OFF, I2C_SMBus_OFF);
 *
 * For I2C_LCD initial settings, you must call the I2C_LCD_init() function 
 * in the 'main()2 function with the correct parameters.
 *  For examle: void main(void) {
                                    .
                                    .
                                    I2C_LCD_init(&LCD1, 0x40, LCD_2LINE, LCD_5x8DOTS);
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
    
/*@DEFINITIONS*/
    //LCD Delay Definition
    #define LCD_delay __delay_us(1550)

    //I2C LCD Definitions And Variables
    #define LCD_RS_COMMAND 0x00
    #define LCD_RS_DATA 0x01

    #define LCD_WRITE 0x00
    //#define LCD_READ 0x02//Not Using

    #define LCD_E_OFF 0x00
    #define LCD_E_ON 0x04

    #define LCD_BACKLIGHT_OFF 0x00
    #define LCD_BACKLIGHT_ON 0x08

    typedef struct I2C_LCD{
        unsigned char Address;
        unsigned char BackLight_State;
    }I2C_LCD_t;

    unsigned char Lcd_RS_State;
    const unsigned char Lcd_RW_State = LCD_WRITE;
    unsigned char BackLight_State = LCD_BACKLIGHT_ON;
    
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
    void I2C_LCD_write_char(I2C_LCD_t LCD_Obj, unsigned char chr);                            //LCD_send_char(char type data);
    void I2C_LCD_write_string(I2C_LCD_t LCD_Obj, char *str);                                  //LCD_send_string(string type data);
    void I2C_LCD_clear(I2C_LCD_t LCD_Obj);                                                    //LCD_clear(LCD_Obj);
    void I2C_LCD_return_home(I2C_LCD_t LCD_Obj);                                              //LCD_return_home(LCD_Obj);
    void I2C_LCD_entry_mode(I2C_LCD_t LCD_Obj, uint8_t I_or_D, uint8_t S);                    //LCD_entry_mode(LCD_Obj, LCD_ENTRY_RIGHT/LCD_ENTRY_LEFT, LCD_ENTRY_SHIFT_INCREMENT/LCD_ENTRY_SHIFT_DECREMENT);
    void I2C_LCD_display_on_off_control(I2C_LCD_t LCD_Obj, uint8_t D, uint8_t C, uint8_t B);  //LCD_display_on_off_control(LCD_Obj, LCD_DISPLAY_ON/LCD_DISPLAY_OFF, LCD_CURSOR_ON/LCD_CURSOR_OFF, LCD_BLINK_ON/LCD_BLINK_OFF);
    void I2C_LCD_cursor_or_display_shift(I2C_LCD_t LCD_Obj, uint8_t S_or_C, uint8_t R_or_L);  //LCD_cursor_or_display_shift(LCD_Obj, LCD_DISPLAY_MOVE/LCD_CURSOR_MOVE, LCD_MOVE_RIGHT/LCD_MOVE_LEFT);
    void I2C_LCD_init(I2C_LCD_t *LCD_Obj_Add, uint8_t I2C_LCD_Address, uint8_t N, uint8_t F); //LCD_init(LCD_Obj_Add, I2C_LCD_Address, LCD_2LINE/LCD_1LINE, LCD_5x10DOTS/LCD_5x8DOTS);
    void I2C_LCD_set_cursor(I2C_LCD_t LCD_Obj, uint8_t row, uint8_t colomn);                  //LCD_set_cursor(LCD_Obj, row value, colomn value);
    void I2C_LCD_BackLight_ON(I2C_LCD_t *LCD_Obj_Add);                                        //I2C_LCD_BackLight_ON(LCD_Obj_Add);
    void I2C_LCD_BackLight_OFF(I2C_LCD_t *LCD_Obj_Add);                                       //I2C_LCD_BackLight_OFF(LCD_Obj_Add);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */
