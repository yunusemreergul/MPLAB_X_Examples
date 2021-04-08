/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 19 Ocak 2021 Sal?, 07:21
 */

#include "configurations.h"

/*@FUNCTION_DEFINITIONS*/

    //Initialize Configuration Function
    void Initial_Configurations(void){

        /*@SPECIAL_FUNCTION_REGISTER*/

            //STATUS_Register_Settings
            //OPTION_REG_Register_Settings
                INTCONbits.PEIE = CLEAR;
                INTCONbits.GIE = CLEAR;

            //INTCON_Register_Settings
            //PIE1_Register_Settings
            //PIR1_Register_Settings
            //PIE2_Register_Settings
            //PIR2_Register_Settings
            //PCON_Register_Settings

        /*@I/O_PORTS_REGISTER*/

            //PORTA_And_the_TRISA_Register_Settings
                //TRISA = 0x00;
                //PORTA = 0x00;
            //PORTB_And_the_TRISB_Register_Settings
                TRISB = 0xFF;
                PORTB = 0x00;

            //PORTC_And_the_TRISC_Register_Settings
            //PORTD_And_the_TRISD_Register_Settings
                //TRISD = 0x00;
                //PORTD = 0x00;
            //PORTE_And_the_TRISE_Register_Settings

        /*@TIMERS_MODULE_REGISTER*/

            //TIMER0
            //TIMER1_And_T1CON_Register_Settings
            //TIMER2_And_T2CON_Register_Settings

        /*@CAPTURE/COMPARE/PWM (CCP)_MODULES_REGISTER*/

            //CCP1CON_Register_Settings
            //CCP2CON_Register_Settings
    }
