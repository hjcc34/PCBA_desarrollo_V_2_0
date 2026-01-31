
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#define _XTAL_FREQ 48000000UL

#include <xc.h>                                                                 // include processor files - each processor file is guarded.

#define EN_HC_05      PORTBbits.RB2
#define STATE_HC_05   PORTBbits.RB5
#define HC_05_ON      LATAbits.LATA1

uint8_t contador_en_HC05,HC05_enlazado;

void COM_HC_05_MASTER(void);
void CFG_HC_05(void);

#endif	/* XC_HEADER_TEMPLATE_H */

