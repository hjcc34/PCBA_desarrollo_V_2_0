/* 
 * File:   CFG_BCD_TO_DEC_TO_BCD.h
 * Author: Familia CS
 *
 * Created on 12 de noviembre de 2024, 11:07
 */

#ifndef CFG_BCD_TO_DEC_TO_BCD_H
#define	CFG_BCD_TO_DEC_TO_BCD_H

#include <xc.h>

unsigned char decenas,unidades,DEC_BCD_RESULTADO,decenasH,unidadesH,decenasH10,unidad,decena,centena,millar,unmillar,dosmillar;

unsigned int variableU,variableD,variableC,variableM,variableUM,variableDM;

void BCD_TO_DEC (uint8_t dato);
void DEC_TO_LCD (unsigned char dato);
unsigned char DEC_TO_HEX (unsigned char dato);
void CONVERSOR_HEX_DEC(unsigned int variable);

#endif	/* CFG_BCD_TO_DEC_TO_BCD_H */

