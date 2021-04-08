/*
 * File:   CCP_MODULE_PWM_MODE_Firmware.c
 * Author: YUNUS EMRE ERGUL 
 *
 * Created on 23 Eylül 2020 Çar?amba, 21:07
 */


/*@CCP1 MODULE PWM MODE
 * For PWM : Fpwm = 10000Hz = 10KHz, Initial PWM DutyCycle = %50.
 * 
 *           PWM mode selected in CCP1CON<3:0> register.
 *           PORTB<3:0> set output for CCP1/RB3.
 *           Timer2 prescaler 1:4 and TMR2 valude 0.
 * 
 * For Fpwm: PWM period = [(PR2) + 1] x 4 x (Tosc) x (TIMER2PrescaleValue)
 * 
 *           PR2 value was found to be 125.
 * 
 * For PwmDcyc: PWM duty cycle = (CCPR1L:CCP1CON<5:4>) x (Tosc) x (TIMER2PrescaleValue)
 * 
 *           (CCPR1L:CCP1CON<5:4>)=DutyCycle Value. (DutyCycle value is Max:500 and Min:0 for this PWM settings.)
 *           CCP1CON<4> = DutyCycleValue & 1
 *           CCP1CON<5> = DutyCycleValue & 2
 *           CCPR1L     = DutyCycleValue >> 2
 * 
 *           DutyCycleValue was found to be 250 for DutyCycle%50.
 */


#include "configurations.h"
#include <stdint.h>

volatile uint16_t duty = 250;
volatile uint16_t old_duty = 0;

/*
 * @INTERRUPT_FUNCTION
 */
void __interrupt() ISR(void)
{
    if(INTCONbits.RBIF && INTCONbits.RBIE)
    {
        if(PORTBbits.RB6 && (duty<500)) duty+=20;
        if(PORTBbits.RB7 && (duty>0))   duty-=20;
        
        INTCONbits.RBIF = 0;
    }
}

/*
 * @MAIN_FUNCTION
 */
void main(void) {
    
    Initial_Configurations();
    
    
    while(1)
    {
        if(old_duty != duty)
        {
            old_duty = duty;
            CCP1CONbits.CCP1Y = duty&1;
            CCP1CONbits.CCP1X = duty&2;
            CCPR1L = duty>>2;
        }
        PORTBbits.RB0 = ~PORTBbits.RB0;
        __delay_ms(500);
    }
    return;
}