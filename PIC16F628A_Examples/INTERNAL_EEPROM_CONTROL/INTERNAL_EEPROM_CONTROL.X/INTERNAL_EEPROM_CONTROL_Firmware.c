/*
 * File:   INTERNAL_EEPROM_CONTROL_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 30 Eylül 2020 Çar?amba, 23:12
 */


/*@DATA EEPROM MEMORY
 * Three function have been written in configurations.c for EEPROM writing, reading and clearing.
        void EEPROM_write(uint8_t address, uint8_t data);
        uint8_t EEPROM_read(uint8_t address);   //This function returns the value stored in the address.
        void EEPROM_clear(uint8_t from_address, uint8_t to_address);

 * One Binary Searching function has been in configurations.c for search free address.
        uint8_t EEPROM_get_the_next_free_address(uint8_t first_address, uint8_t last_address);  //This function returns the next free address.

 * PORTB used to show counter value and address value. (PORTB is input.)
 * PORTA<0:2> used to input for counter and save to address. (PORTA<0:2> is input.)
 * PORTA<3> used for EEPROM Led. (PORTA<3> is output.)
 * EEPROM interrupt used for EEPROM_write blink.

 * When PORTAbits.RA0 is pressed, its counter increments.
 * When PORTAbits.RA1 is pressed, its counter decreases.
 * When PORTAbits.RA2 is pressed, if the counter value displayed on the PORTB is different from the last recorded value, it will be saved to EEPROM.
 * While PORTAbits.RA2 is pressed for recording, the EEPROM Led lights up and the address to be recorded on the PORTB is written.
 * The blinking of the EEPROM Led indicates that the counter value has been saved.
 * If the last saved counter value has not changed, the counter value is not saved to EEPROM.
 */

#include "configurations.h"

/*
 * @INTERRUPT_FUNCTION
 */
void __interrupt() ISR(void)
{
    if(PIR1bits.EEIF && PIE1bits.EEIE)
    { 
        for(uint8_t i=0; i<6 ; i++)
        {
            PORTAbits.RA3 = ~PORTAbits.RA3;
            __delay_ms(50);
        }
        PIR1bits.EEIF = 0;
    }
}

/*
 * @MAIN_FUNCTION
 */
void main(void) {
    
    uint8_t first_addr = 0x00, last_addr = 0x7F, address;
    uint8_t counter;
    
    Initial_Configurations();
    
    address = EEPROM_get_the_next_free_address(first_addr, last_addr);
    counter = EEPROM_read(address-1);
    
    while(1)
    {
        if(PORTAbits.RA0)
        {
            while(PORTAbits.RA0);
            counter++;
        }
        
        if(PORTAbits.RA1)
        {
            while(PORTAbits.RA1);
            counter--;
        }
        
        if(PORTAbits.RA2)
        {
            PORTAbits.RA3 = SET;
            PORTB = address;
            while(PORTAbits.RA2);
            if(counter!=EEPROM_read(address-1))
            {
                EEPROM_write(address, counter);
                if(address!=last_addr) address++;
                else {EEPROM_clear(first_addr, last_addr);   address=first_addr;}
            }
            PORTAbits.RA3 = CLEAR;
        }
        
        PORTB = counter;
    }
    return;
}
