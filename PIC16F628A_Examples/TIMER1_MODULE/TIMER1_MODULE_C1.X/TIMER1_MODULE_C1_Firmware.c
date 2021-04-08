/*
 * File:   TIMER1_MODULE_C1_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 20 Eylül 2020 Pazar, 18:37
 */

/*@TIMER1 MODULE COUNTER MODE
 * Timer1 Asynchronous Counter Mode.
 * Prescaler value is 1:1 for Timer1.
 * Timer1 Clock Source is External clock 32.768Khz.
 * TMR1 value is 49152.
 * Interrupt time: Tout = [Prescaler x(65536 - TMR1)]/[EXTCLK] = [1x(65536-49152)] / [32.768Khz] = 500ms.
 */

#include "configurations.h"

/*
 * @INTERRUPT_FUNCTION
 */
void __interrupt() ISR(void)
{
    if(PIR1bits.TMR1IF && PIE1bits.TMR1IE)
    {
        PORTAbits.RA0 = ~PORTAbits.RA0;
    }
    TMR1 = 49152;
    PIR1bits.TMR1IF = CLEAR;
}

/*
 * @MAIN_FUNCTION
 */
void main(void) {
    
    Initial_Configurations();
    
    while(1)
    {
        PORTBbits.RB0 = ~PORTBbits.RB0;
        __delay_ms(100);
    }
    return;
}