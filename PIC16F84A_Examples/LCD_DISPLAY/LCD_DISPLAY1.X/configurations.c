/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 23 May?s 2020 Cumartesi, 23:26
 */

#include "configurations.h"

/*
 *** FUNCTION_DEFINITIONS*******************************************************
 */
void Initial_Configurations(void)
{
    //OPTION_REGISTER_SETTINGS
    
    
    //INTCON_REGISTER_SETTINGS
    
    
    //TIMER0_MODULE_REGISTER(TMR0)
    
    
    //IO_PORT_SETTING
    TRISA = 0x00;
    TRISB = 0x00;
    
    //IO_PORT_CLEARING
    PORTA = 0x00;
    PORTB = 0x00;
}
/*FUNCTION_DEFINITIONS_ENDED*/
