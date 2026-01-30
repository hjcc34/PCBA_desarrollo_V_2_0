/* 
 * File:   CFG_DS1307.h
 * Author: Familia CS
 *
 * Created on 10 de noviembre de 2024, 12:53
 */

#ifndef CFG_DS1307_H
#define	CFG_DS1307_H

#include <xc.h>

#define   _Dir_DS1307_W     0xD0
#define   _Dir_DS1307_R     0xD1
#define   _Salida_1seg      0x90
#define   _Registro_Ctr     0x07
#define   _Registro_Seg     0x00
#define   _Registro_Min     0x01
#define   _Registro_Hor     0x02
#define   _Registro_DiaSe   0x03
#define   _Registro_Dia     0x04
#define   _Registro_Mes     0x05
#define   _Registro_Ano     0x06
#define   _Registro_Stop    0x80
#define   _Registro_Borrar  0x00
#define   _Registro_AM_PM   0x40
    
#define   Hora              7
#define   Minutos           10
#define   Segundos          13
#define   AM_PM             16
#define   Dia_Semana        4    
#define   Dia               7
#define   Mes               10
#define   Ano               13
#define   pos_X             1
#define   pos_Y             2
#define   pos_dia_sem       3
#define   pos_meses         4    
#define   Hora_limite_24    24
#define   Hora_limite_12    13
#define   Minutos_limite    60
#define   Segundos_limite   60
#define   Dia_limite        32
#define   Mes_limite        13
#define   Ano_limite        81
#define   Dia_semana_limite 8
#define   AM_PM_limite      3

const unsigned char registros[] = {_Registro_Seg,_Registro_Min,_Registro_Hor,_Registro_Dia,_Registro_Mes,_Registro_Ano};
    
void CFG_DS1307 (void);
void READ_DS1307(uint8_t type,uint8_t eje_x,uint8_t eje_y,unsigned char caracter);

#endif	/* CFG_DS1307_H */
