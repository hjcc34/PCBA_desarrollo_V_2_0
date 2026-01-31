/*
 * File:   HC_05.c
 * Author: Hermes Colmenares
 *
 * Created on 15 de noviembre de 2025, 17:13
 */


#include "CFG_HC_05.h"
#include "../drivers/CFG_UART.h"

//----------------------- Comunicacion MASTER con HC-05-------------------------
void COM_HC_05_MASTER(void)
    {
    TRISBbits.TRISB5 = 1;                                                       //Entrada de HC-05 conectado    
    EN_HC_05 = 1;                                                               //habilito HC-05
    __delay_ms(10);                                                             //espero 10ms
    HC_05_ON = 1;                                                               //alimento HC-05    
    __delay_ms(10);                                                             //espero 10ms 
    }
//-------------------------Version del HC-05------------------------------------
void CFG_HC_05(void)
{
    Uart_Send_String("AT+ROLE=0\r\n");
}
