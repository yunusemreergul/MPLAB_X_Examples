/* 
 * File:   configurations.c
 * Author: YUNUS EMRE ERGUL
 *
 * Created on 30 Eylül 2020 Çar?amba, 23:12
 */


#include "configurations.h"


/*
 * @FUNCTION_DEFINITIONS
 */

void Initial_Configurations(void)   //Initialize Configuration Function
{
    
    /*
     * @SPECIAL_FUNCTION_REGISTERS
     */
    
        //STATUS_Register_Settings

        //OPTION_Register_Settings
            OPTION_REGbits.nRBPU  = SET;
            OPTION_REGbits.INTEDG = SET;
            OPTION_REGbits.T0CS   = CLEAR;
            OPTION_REGbits.T0SE   = CLEAR;
            OPTION_REGbits.PSA    = CLEAR;
            OPTION_REGbits.PS2    = CLEAR;
            OPTION_REGbits.PS1    = CLEAR;
            OPTION_REGbits.PS0    = CLEAR;
            
        //INTCON_Register_Settings
            INTCONbits.GIE  = SET;
            INTCONbits.PEIE = SET;
            INTCONbits.T0IE = CLEAR;
            INTCONbits.INTE = CLEAR;
            INTCONbits.RBIE = CLEAR;
            INTCONbits.T0IF = CLEAR;
            INTCONbits.INTF = CLEAR;
            INTCONbits.RBIF = CLEAR;
            
        //PIE1_Register_Settings
            PIE1bits.EEIE   = SET;
            PIE1bits.CMIE   = CLEAR;
            PIE1bits.RCIE   = CLEAR;
            PIE1bits.TXIE   = CLEAR;
            PIE1bits.CCP1IE = CLEAR;
            PIE1bits.TMR2IE = CLEAR;
            PIE1bits.TMR1IE = CLEAR;
            
        //PIR1_Register_Settings
            PIR1bits.EEIF   = CLEAR;
            PIR1bits.CMIF   = CLEAR;
            PIR1bits.RCIF   = CLEAR;
            PIR1bits.TXIF   = CLEAR;
            PIR1bits.CCP1IF = CLEAR;
            PIR1bits.TMR2IF = CLEAR;
            PIR1bits.TMR1IF = CLEAR;
            
        //PCON_Register_Settings
            
            
            
    /*
     * @I/O_PORTS_REGISTERS
     */
    
        //PORTA_And_TRISA_Register_Settings
            TRISA = 0x07;
            PORTA = 0x00;   //PORTA Clearing
            
        //PORTB_And_TRISB_Register_Settings
            TRISB = 0x00;
            PORTB = 0x00;   //PORTB Clearing
            
            
            
    /*
     * @TIMERS_MODULE_REGISTERS
     */
    
        //TIMER0
            TMR0 = 0x00;    //Timer0 Module's Register
            
        //TIMER1_And_T1CON_Register_Settings
            TMR1 = 0x0000;  //Timer1 Module's Register (TMR1H:TMR1L)
            
            T1CONbits.T1CKPS1 = CLEAR;
            T1CONbits.T1CKPS0 = CLEAR;
            T1CONbits.T1OSCEN = CLEAR;
            T1CONbits.nT1SYNC = CLEAR;
            T1CONbits.TMR1CS  = CLEAR;
            T1CONbits.TMR1ON  = CLEAR;
            
        //TIMER1_And_T2CON_Register_Settings
            TMR2 = 0x00;    //Timer2 Module's Register
            PR2  = 0x00;    //Timer2 Period Register
            
            T2CONbits.TOUTPS3 = CLEAR;
            T2CONbits.TOUTPS2 = CLEAR;
            T2CONbits.TOUTPS1 = CLEAR;
            T2CONbits.TOUTPS0 = CLEAR;
            T2CONbits.TMR2ON  = CLEAR;
            T2CONbits.T2CKPS1 = CLEAR;
            T2CONbits.T2CKPS0 = CLEAR;
            
            
            
    /*
     * @CAPTURE/COMPARE/PWM(CCP)_MODULE_REGISTERS
     */
    
        //CCP1CON_Register_Settings
            CCPR1 = 0x0000; //Capture/Compare/PWM Register1 (CCPR1H:CCPR1L)
            
            CCP1CONbits.CCP1X  = CLEAR;
            CCP1CONbits.CCP1Y  = CLEAR;
            CCP1CONbits.CCP1M3 = CLEAR;
            CCP1CONbits.CCP1M2 = CLEAR;
            CCP1CONbits.CCP1M1 = CLEAR;
            CCP1CONbits.CCP1M0 = CLEAR;
            
            
            
    /*
     * @COMPARATOR_MODULE_REGISTERS 
     */
    
        //CMCON_Register_Settings
            
            CMCONbits.C2OUT = CLEAR;
            CMCONbits.C1OUT = CLEAR;
            CMCONbits.C2INV = CLEAR;
            CMCONbits.C1INV = CLEAR;
            CMCONbits.CIS   = CLEAR;
            //Note: CM<2:0>=111 For Comparator Off Mode (Default Mode)
            CMCONbits.CM2   = SET;
            CMCONbits.CM1   = SET;
            CMCONbits.CM0   = SET;
            
            
            
    /*
     * @VOLTAGE_REFERENCE_MODULE_REGISTERS
     */
      
        //VRCON_Register_Settings
            
            VRCONbits.VREN = CLEAR;
            VRCONbits.VROE = CLEAR;
            VRCONbits.VRR  = CLEAR;
            VRCONbits.VR3  = CLEAR;
            VRCONbits.VR2  = CLEAR;
            VRCONbits.VR1  = CLEAR;
            VRCONbits.VR0  = CLEAR;
}

//INTERNAL_EEPROM_CONTROL_FUNCTIONS

    void EEPROM_write(uint8_t address, uint8_t data)    //EEPROM_Write_Function
    {
        uint8_t GIE_Last_State;
        while(EECON1bits.WR);
        EEADR = address;
        EEDATA = data;
        EECON1bits.WREN = SET;
        GIE_Last_State = INTCONbits.GIE;
        INTCONbits.GIE = CLEAR;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = SET;
        INTCONbits.GIE = GIE_Last_State;
        EECON1bits.WREN = CLEAR;
    }

    uint8_t EEPROM_read(uint8_t address)    //EEPROM_Read_Function
    {
        uint8_t data;
        EEADR = address;
        EECON1bits.RD = SET;
        data= EEDATA;
        return data;
    }

    void EEPROM_clear(uint8_t from_address, uint8_t to_address) //EEPROM_Clear_Function
    {
        uint8_t clear_address_value=0x00;
        for(uint8_t address_to_be_cleared = from_address ; address_to_be_cleared <= to_address ; address_to_be_cleared++)
        {
            EEPROM_write(address_to_be_cleared, clear_address_value);
        }
    }

    uint8_t EEPROM_get_the_next_free_address(uint8_t first_address, uint8_t last_address)   //EEPROM_Binary_Search_Function_For_Free_Address_Searching
    {
        uint8_t clear_address_value=0x00;

        if(first_address==last_address) return first_address;

        if((EEPROM_read(last_address)==clear_address_value))
        {
            if((EEPROM_read(last_address-1)!=clear_address_value)) return last_address;
        }
        else {EEPROM_clear(first_address, last_address); return first_address;};

        if((EEPROM_read(first_address)==clear_address_value)&&(EEPROM_read(first_address+1)==clear_address_value)) return first_address;


        while((last_address-first_address)>1)
        {
            uint8_t middle_address =(first_address + last_address)/2;
            if((EEPROM_read(middle_address)==clear_address_value))
            {
                if((EEPROM_read(middle_address-1)!=clear_address_value))
                {
                    if((EEPROM_read(middle_address+1)==clear_address_value)) return middle_address;
                    else first_address = middle_address+1;
                }
                else last_address = middle_address;
            }
            else first_address = middle_address;
        }
    }
