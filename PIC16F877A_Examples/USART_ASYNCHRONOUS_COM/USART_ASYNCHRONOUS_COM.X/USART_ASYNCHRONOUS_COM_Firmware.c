/*
 * File:   USART_ASYNCHRONOUS_COM_Firmware.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 04 Kas?m 2020 Çar?amba, 17:49
 */


/*@USART_Ascynchronous_Serial_Port_Example
 */


#include "configurations.h"
#include "USART.h"
#include <stdio.h>  //This library added for usage 'printf' function.

char UART_RX_Buffer;

/*
 * @INTERRUPT_FUNCTION
 */
void __interrupt() ISR(void)
{
    UART_RX_Buffer = UART_Read_Char();
}

/*
 * @MAIN_FUNCTION
 */
void main(void) {

    Initial_Configurations();
    
    Initialize_UART(9600);
    
    UART_RCIE_Enable();
    
    printf("UART Initalized\r\r");
    UART_Send_String("Input '1' or '0' for PORTB\r");
    
    while(1)
    {
        
        //UART_RX_Buffer = UART_Read_Char();
        
        if(UART_RX_Buffer == '1')
        {
            PORTB = 0xFF;
        }
        if(UART_RX_Buffer == '0')
        {
            PORTB = 0x00;
        }
    }
    return;
}
