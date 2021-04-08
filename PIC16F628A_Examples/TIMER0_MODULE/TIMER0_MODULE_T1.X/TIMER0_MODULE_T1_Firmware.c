/*
 * File:   TIMER0_MODULE_T1_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 17 Eylül 2020 Per?embe, 00:15
 */

/*@TIMER0 MODULE TIMER MODE
 * Prescaler value is 1:256 for Timer0.
 * Timer0 Clock Source is Internal clock [FOSC/4].
 * TMR0 value is 0.
 * Interrupt time: Tout = [Prescaler x(255 - TMR0)]/[FOSC/4] = [256x(255-0)]/[20Mhz/4] = 13.056 ms.
 */

#include "configurations.h"

/*
 * @INTERRUPT_FUNCTION
 */
void __interrupt() ISR(void)
{
    if(INTCONbits.T0IF && INTCONbits.T0IE)
    {
        PORTAbits.RA0 = ~PORTAbits.RA0;
    }
    TMR0 = 0;
    INTCONbits.T0IF = CLEAR;
}

/*
 * @MAIN_FUNCTION
 */
void main(void) {
    
    Initial_Configurations();
    
    while(1)
    {
        PORTB += 1;
        __delay_ms(500);
    }
    return;
}
