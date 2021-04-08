/* 
 * File:   USART.h
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 04 Kas?m 2020 Çar?amba, 17:54
 */

/*@USART_ Ascynchronous_Serial_Communication_Library_For_PIC16F877A
 * 
 * You should add the configuration.h file for register definition and configuration define.
 * Initialize UART and baud rate with " Initialize_UART(uint32_t BaudRate); " function.
 * If reading operation with interrupt, the " UART_RCIE_Enable(void); " function should be called. Then " Global Interrupt Enable bit " and " Peripheral Interrupt Enable bit " must be set.
 * 
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "configurations.h"     //Added by user.
    
#include <stdint.h>
#include <stdlib.h>

/*
 * @FUNCTION_PROTOTYPES
 */
void Initialize_UART(uint32_t BaudRate);

void UART_TXIE_Enable(void);
void UART_TXIE_Disable(void);
void UART_Send_Char(char chr);
void UART_Send_String(char* str);

void UART_RCIE_Enable(void);
void UART_RCIE_Disable(void);
char UART_Read_Char(void);


#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

