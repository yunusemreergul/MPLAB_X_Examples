/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 23 Eylül 2020 Çar?amba, 21:07
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
            INTCONbits.RBIE = SET;
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
            TRISB = 0xF0;
            PORTB = 0x00;   //PORTB Clearing
            
            
            
    /*
     * @TIMERS_MODULE_REGISTERS
     */
    
        //TIMER0
            TMR0 = 0x00;    //Timer0 Module's Register
            
        //TIMER1_And_T1CON_Register_Settings
            TMR1 = 0x0001;  //Timer1 Module's Register (TMR1H:TMR1L)
            
            T1CONbits.T1CKPS1 = CLEAR;
            T1CONbits.T1CKPS0 = CLEAR;
            T1CONbits.T1OSCEN = CLEAR;
            T1CONbits.nT1SYNC = CLEAR;
            T1CONbits.TMR1CS  = CLEAR;
            T1CONbits.TMR1ON  = CLEAR;
            
        //TIMER1_And_T2CON_Register_Settings
            TMR2 = 0x00;    //Timer2 Module's Register
            PR2  = 125;    //Timer2 Period Register
            
            T2CONbits.TOUTPS3 = CLEAR;
            T2CONbits.TOUTPS2 = CLEAR;
            T2CONbits.TOUTPS1 = CLEAR;
            T2CONbits.TOUTPS0 = CLEAR;
            T2CONbits.TMR2ON  = SET;
            T2CONbits.T2CKPS1 = CLEAR;
            T2CONbits.T2CKPS0 = SET;
            
            
    /*
     * @CAPTURE/COMPARE/PWM(CCP)_MODULE_REGISTERS
     */
    
        //CCP1CON_Register_Settings
            CCPR1 = 0x0000; //Capture/Compare/PWM Register1 (CCPR1H:CCPR1L)
            
            CCP1CONbits.CCP1X  = CLEAR;
            CCP1CONbits.CCP1Y  = CLEAR;
            CCP1CONbits.CCP1M3 = SET;
            CCP1CONbits.CCP1M2 = SET;
            CCP1CONbits.CCP1M1 = CLEAR;
            CCP1CONbits.CCP1M0 = CLEAR;
            
}