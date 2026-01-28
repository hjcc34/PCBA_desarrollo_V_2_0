/*
 * File:   RS-232.c
 * Author: Familia CS
 *
 * Created on 1 de mayo de 2025, 23:19
 */

#include "CFG_UART.h"

//------------------------------------------------------------------------------
void Uart_Init(void)
{
    TRISCbits.TRISC6  = 0;                                                      // TX salida
    TRISCbits.TRISC7  = 0;                                                      // RX entrada    
    TXSTAbits.SYNC    = 0;                                                      // modo as�ncrono    
    BAUDCONbits.BRG16 = 0;                                                      // generador 16 bits
    TXSTAbits.BRGH    = 1;                                                      // alta velocidad
    SPBRGH = 0;
    SPBRG  = 77;                                                                 // 38400 baudios @ 48 MHz    
    RCSTAbits.SPEN = 1;                                                         // habilitar puerto serie
    RCSTAbits.CREN = 1;                                                         // recepci�n continua
    TXSTAbits.TXEN = 1;                                                         // habilitar transmisi�n
}
//------------------------------------------------------------------------------
short Uart_Available(void)                                                      // Funcion de verificacion si ha recibido datos
{
    return PIR1bits.RCIF ? 1 : 0;
}
//------------------------------------------------------------------------------
void Uart_Send_Char(char txData)                                                // Funcion para transmitir caracteres
{
    while(TXSTAbits.TRMT == 0);
    TXREG = txData;
}
//------------------------------------------------------------------------------
void Uart_Send_String(char *info)                                               // Funcion para transmitir una cadena de caracteres
{
    while(*info)
    {
        Uart_Send_Char(*info++);
    }
}
//------------------------------------------------------------------------------
char Uart_Read(void)                                                            // Funcion para recibir caracteres
{
    while(PIR1bits.RCIF == 0);
    if(RCSTAbits.OERR == 1)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    PIR1bits.RCIF = 0;
    return RCREG;
}
//------------------------------------------------------------------------------
void Uart_Read_String(char* Buf, unsigned int s_buf)
{
    unsigned int i = 0;
    char c;

    // Limpiar buffer antes de usarlo
    //memset(Buf, 0, s_buf);

    while(1)
    {
        c = Uart_Read();

        if(c == '\n')  // Fin de l�nea
            break;

        if(c == '\r')  // Ignorar carriage return
            continue;

        if(i < s_buf - 1)
        {
            Buf[i++] = c;
        }
    }

    Buf[i] = '\0';   // Terminar la cadena
}

//------------------------------------------------------------------------------ 
void Uart_Read_Substring(char* cp, char* vc, unsigned int inc, unsigned int fn) // Funcion para descomponer cadenas de caracteres con incio y fin.
{
    int pt = 0;
    for(int lt=inc; lt<=fn; lt++)
    {
        vc[pt] = cp[lt];
        pt++;
    }
    vc[pt] = '\0';
}
//------------------------------------------------------------------------------
void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size)
{
    unsigned int i = 0;
    char c;

    while(i < st_size - 1)   // Dejamos espacio para el NULL
    {
        c = Uart_Read();
        buf[i++] = c;

        if(c == stop_c)
            break;
    }

    buf[i] = '\0'; // terminador
}

//------------------------------------------------------------------------------
void putch(char c) 
{
    while(!TRMT); // Espera a que el UART est� listo
    TXREG = c;    // Env�a el car�cter por UART
}
