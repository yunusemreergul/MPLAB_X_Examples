/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 20 Eylül 2020 Pazar, 18:37
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
            OPTION_REGbits.PS2    = CLEAR;
            OPTION_REGbits.PS1    = CLEAR;
            OPTION_REGbits.PS0    = CLEAR;
            
        //INTCON_Register_Settings
            INTCONbits.GIE  = SET;
            INTCONbits.PEIE = SET;
            INTCONbits.T0IE = CLEAR;
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
            PIE1bits.TMR1IE = SET;
            
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
            TRISB = 0x40;
            PORTB = 0x00;   //PORTB Clearing
            
            
            
    /*
     * @TIMERS_MODULE_REGISTERS
     */
    
        //TIMER0
            TMR0 = 0x00;    //Timer0 Module's Register
            
        //TIMER1_And_T1CON_Register_Settings
            TMR1 = 49152;  //Timer1 Module's Register (TMR1H:TMR1L)
            
            T1CONbits.T1CKPS1 = CLEAR;
            T1CONbits.T1CKPS0 = CLEAR;
            T1CONbits.T1OSCEN = CLEAR;
            T1CONbits.nT1SYNC = SET;
            T1CONbits.TMR1CS  = SET;
            T1CONbits.TMR1ON  = SET;
            
        //TIMER2_And_T2CON_Register_Settings
}