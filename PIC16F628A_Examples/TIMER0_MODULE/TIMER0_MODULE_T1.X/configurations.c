/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 17 Eylül 2020 Per?embe, 00:16
 */

#include "configurations.h"


/*
 * @FUNCTION_DEFINITIONS
 */
void Initial_Configurations(void)
{
    
    /*
     * @SPECIAL_FUNCTION_REGISTERS
     */
    
        //STATUS_Register_Settings

        //OPTION_Register_Settings
            OPTION_REGbits.nRBPU  = SET;
            OPTION_REGbits.INTEDG = SET;
            OPTION_REGbits.T0CS   = CLEAR;
            OPTION_REGbits.T0SE   = CLEAR;
            OPTION_REGbits.PSA    = CLEAR;
            OPTION_REGbits.PS2    = SET;
            OPTION_REGbits.PS1    = SET;
            OPTION_REGbits.PS0    = SET;
            
        //INTCON_Register_Settings
            INTCONbits.GIE  = SET;
            INTCONbits.PEIE = CLEAR;
            INTCONbits.T0IE = SET;
            INTCONbits.INTE = CLEAR;
            INTCONbits.RBIE = CLEAR;
            INTCONbits.T0IF = CLEAR;
            INTCONbits.INTF = CLEAR;
            INTCONbits.RBIF = CLEAR;
            
        //PIE1_Register_Settings
            PIE1bits.EEIE   = CLEAR;
            PIE1bits.CMIE   = CLEAR;
            PIE1bits.RCIE   = CLEAR;
            PIE1bits.TXIE   = CLEAR;
            PIE1bits.CCP1IE = CLEAR;
            PIE1bits.TMR2IE = CLEAR;
            PIE1bits.TMR1IE = CLEAR;
            
        //PIR1_Register_Settings
            PIR1bits.EEIF   = CLEAR;
            PIR1bits.CMIF   = CLEAR;
            PIR1bits.RCIF   = CLEAR;
            PIR1bits.TXIF   = CLEAR;
            PIR1bits.CCP1IF = CLEAR;
            PIR1bits.TMR2IF = CLEAR;
            PIR1bits.TMR1IF = CLEAR;
            
        //PCON_Register_Settings
            
            
            
    /*
     * @I/O_PORTS_REGISTERS
     */
    
        //PORTA_And_TRISA_Register_Settings
            TRISA = 0x00;
            PORTA = 0x00;   //PORTA Clearing
            
        //PORTB_And_TRISB_Register_Settings
            TRISB = 0x00;
            PORTB = 0x00;   //PORTB Clearing
            
            
            
    /*
     * @TIMERS_MODULE_REGISTERS
     */
    
        //TIMER0
            TMR0 = 0x00;    //Timer0 Module?s Register
            
        //TIMER1_And_T1CON_Register_Settings
            
        //TIMER2_And_T2CON_Register_Settings
}