/* 
 * File:   configurations.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 05 Kas?m 2020 Per?embe, 17:30
 */


#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif



// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000UL

#include <stdint.h>

#define SET   1
#define CLEAR 0

/*
 * @FUNCTION_PROTOTYPES
 */
void Initial_Configurations(void);  //Contains configuration settings



#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGURATIONS_H */

