/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 05 Kas?m 2020 Per?embe, 17:30
 */


#include "configurations.h"


/*
 * @FUNCTION_DEFINITIONS
 */

void Initial_Configurations(void)  //Initialize Configuration Function
{
    /*
     * @SPECIAL_FUNCTION_REGISTER
     */
    
        //STATUS_Register_Settings
        //OPTION_REG_Register_Settings
            INTCONbits.PEIE = SET;
            INTCONbits.GIE = SET;
        
        //INTCON_Register_Settings
        //PIE1_Register_Settings
        //PIR1_Register_Settings
        //PIE2_Register_Settings
        //PIR2_Register_Settings
        //PCON_Register_Settings
    
    /*
     * @I/O_PORTS_REGISTER
     */
    
        //PORTA_And_the_TRISA_Register_Settings
        //PORTB_And_the_TRISB_Register_Settings
            TRISB = 0x00;
            PORTB = 0x00;
        
        //PORTC_And_the_TRISC_Register_Settings
        //PORTD_And_the_TRISD_Register_Settings
        //PORTE_And_the_TRISE_Register_Settings
    
    /*
     * @TIMERS_MODULE_REGISTER
     */
    
        //TIMER0
        //TIMER1_And_T1CON_Register_Settings
        //TIMER2_And_T2CON_Register_Settings
    
    /*
     * @CAPTURE/COMPARE/PWM (CCP)_MODULES_REGISTER
     */
    
        //CCP1CON_Register_Settings
        //CCP2CON_Register_Settings

}
