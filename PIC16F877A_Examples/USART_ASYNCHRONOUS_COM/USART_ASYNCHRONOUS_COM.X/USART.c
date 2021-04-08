/*
 * File:   USART.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 04 Kas?m 2020 Çar?amba, 17:49
 */


#include "USART.h"


/*
 * @FUNCTION_DEFINITIONS
 */
    //Set_BaudRate_Function
    uint8_t Set_BaudRate(uint32_t BaudRateValue)
    {
        uint8_t SPRBG_BRGH0, SPRBG_BRGH1;
        uint32_t ERROR_BRGH0, ERROR_BRGH1;

        SPRBG_BRGH0 = (_XTAL_FREQ/(64*BaudRateValue))-1;
        SPRBG_BRGH1 = (_XTAL_FREQ/(16*BaudRateValue))-1;

        ERROR_BRGH0 = labs(BaudRateValue - (_XTAL_FREQ/(64*(SPRBG_BRGH0 + 1))));
        ERROR_BRGH1 = labs(BaudRateValue - (_XTAL_FREQ/(16*(SPRBG_BRGH1 + 1))));

        if(ERROR_BRGH1 >= ERROR_BRGH0)
        {
            TXSTAbits.BRGH = CLEAR;
            return SPRBG_BRGH0;
        }
        else
        {
            TXSTAbits.BRGH = SET;
            return SPRBG_BRGH1;
        }
    }
    
    //UART_Initialize_Function
    void Initialize_UART(uint32_t BaudRate)
    {
        //Setting I/O Pins For UART
        TRISCbits.TRISC6 = CLEAR;
        TRISCbits.TRISC7 = SET;

        //Setting SPBRG Register And TXSTAbits.BRGH Bit
        SPBRG = Set_BaudRate(BaudRate); //BaudRate Set

        //USART Mode Select bit (Synchronous / Asynchronous)
        TXSTAbits.SYNC = CLEAR; //Asynchronous Mode Selected
        //Serial Port Enable bit
        RCSTAbits.SPEN = SET;   //Serial Port Enabled

        //9-bit Transmit Enable bit (TXSTAbits.TX9D: 9th bit of Transmit Data, can be Parity bit)
        TXSTAbits.TX9 = CLEAR;  //Selected 8-bit Transmission 
        //9-bit Recieve Enable bit (RCSTAbits.RX9D: 9th bit of Received Data (can be parity bit but must be calculated by user firmware).)
        RCSTAbits.RX9 = CLEAR;  //Selects 8-bit reception


        //Transmit Enable bit
        TXSTAbits.TXEN = SET;   //Transmit Enabled
        //Continuous Receive Enable bit
        RCSTAbits.CREN = SET;   //Enables continuous receive
    }


    //UART_TX_Interrupt_Enable_Function
    void UART_TXIE_Enable(void)
    {
        PIE1bits.TXIE = SET;  //UART Transmit Interrupt Enabled
    }
    //UART_TX_Interrupt_Disable_Function
    void UART_TXIE_Disable(void)
    {
        PIE1bits.TXIE = CLEAR;  //UART Transmit Interrupt Disabled
    }
    //UART_Send_Char_Function
    void UART_Send_Char(char chr)
    {
        while(!TXSTAbits.TRMT); //Transmit Shift Register Status bit control (TXSTAbits.TRMT = 1: TSR empty, TXSTAbits.TRMT = 0: TSR full)
        TXREG = chr;
    }
    //UART_Send_String_Function
    void UART_Send_String(char* str)
    {
        while(*str) UART_Send_Char(*str++);
    }


    //UART_RX_Interrupt_Enable_Function
    void UART_RCIE_Enable(void)
    {
        PIE1bits.RCIE = SET;    //UART Recieve Interrupt Enabled
    }
    //UART_RX_Interrupt_Disable_Function
    void UART_RCIE_Disable(void)
    {
        PIE1bits.RCIE = CLEAR;    //UART Recieve Interrupt Disabled
    }
    //UART_Read_Char_Function
    char UART_Read_Char(void)
    {

        if(RCSTAbits.OERR)  //Overrun Error bit control (RCSTAbits.OERR = 1: Overrun error (can be cleared by clearing bit CREN), RCSTAbits.OERR = 0: No overrun error)
        {
            RCSTAbits.CREN = CLEAR; //Disables continuous receive
            RCSTAbits.CREN = SET;   //Enables continuous receive
        }

        if(PIR1bits.RCIF)   //USART Receive Interrupt Flag bit control (PIR1bits.RCIF = 1: The USART receive buffer is full, PIR1bits.RCIF = 0: The USART receive buffer is empty)
        {
            return RCREG;   //USART Receive Register returned to UART_Read_Char Function
            PIR1bits.RCIF = CLEAR;
        }
        else
            return 0;
    }


    //UART_Send_Char_Function_With_Printf_Function_For_Usage
    void putch(unsigned char chr)
    {
        UART_Send_Char(chr);
    }
