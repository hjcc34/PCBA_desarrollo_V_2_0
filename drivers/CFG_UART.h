/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CFG_UART_H
#define	CFG_UART_H

#include <xc.h>                                                                 // include processor files - each processor file is guarded.
#include <string.h>


#define LF          0x0A
#define CR          0x0D
#define CN          0x00

volatile char buffer_rx[20];
volatile char buffer_rx_v[80];
volatile uint8_t index_rx = 0;
volatile uint8_t hay_cadena = 0;

char RXDATO;
//------------------------------------------------------------------------------
void Uart_Init(void);
short Uart_Available(void);
void Uart_Send_Char(char txData);
void Uart_Send_String(char *info);
char Uart_Read(void);
void Uart_Read_String(char* Buf, unsigned int s_buf);
void Uart_Read_Substring(char* cp, char* vc, unsigned int inc, unsigned int fn);
void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size);
void putch(char c);
#endif	/* CFG_UART_H */