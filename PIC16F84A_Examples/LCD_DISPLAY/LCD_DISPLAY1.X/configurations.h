/* 
 * File:   configurations.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 23 May?s 2020 Cumartesi, 23:26
 */

#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H

#include<xc.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    

// PIC16F84A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000          //USER DEFINE
   
/*
 *** FUNCTION_PROTOTYPES********************************************************
 */
void Initial_Configurations(void);
/*FUNCTION_PROTOTYPES_ENDED*/
    

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGURATIONS_H */
