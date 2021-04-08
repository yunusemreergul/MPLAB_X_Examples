/* 
 * File:   configurations.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 30 Eylül 2020 Çar?amba, 23:12
 */

#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif


// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000UL
    
#include <stdint.h>
    
#define SET 1
#define CLEAR 0
    
    
/*
 * @FUNCTION_PROTOTYPES
 */
void Initial_Configurations(void);  //Contains configuration settings
void EEPROM_write(uint8_t address, uint8_t data);
uint8_t EEPROM_read(uint8_t address);
void EEPROM_clear(uint8_t from_address, uint8_t to_address);
uint8_t EEPROM_get_the_next_free_address(uint8_t first_address, uint8_t last_address);

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGURATIONS_H */

