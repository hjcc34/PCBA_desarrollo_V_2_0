/* 
 * File:   CFG_INA219.h
 * Author: Familia CS
 *
 * Created on 11 de enero de 2025, 19:15
 */

#ifndef CFG_INA219_H
#define	CFG_INA219_H

#include <xc.h>

int ResultadoINA_A,ResultadoINA_A_NEG;

int signo,ResultadoINA_P;

uint16_t ResultadoINA,RESULTADOI_N;

uint8_t signo_amp;

void CFG_INA219_32V_3A(void);
void Lectura_Bus_VDC_INA219(void);
void Lectura_corriente_INA219(void);
void Lectura_potencia_INA219(void);
void Resultado_INA219(void);
int Resultado_INA219_A_P(void);

#endif	/* CFG_INA219_H */
