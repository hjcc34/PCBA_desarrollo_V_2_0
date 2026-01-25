/* 
 * File:   CFG_I2C.h
 * Author: Familia CS
 *
 * Created on 10 de noviembre de 2024, 0:14
 */

#ifndef CFG_I2C_H
#define	CFG_I2C_H

#define _XTAL_FREQ 48000000UL

#include <xc.h>                                                                 // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdbool.h>

#define read_datos_max  6

int8_t read_datos[read_datos_max];

uint8_t DATO_I2C_8bits,re,byte_6,byte_5,byte_4,byte_3,byte_2,byte_1,byte_0,ack,enable_w,byte_3_t,byte_3_h;

uint32_t DATO_READ_8b_3,DATO_READ_8b_2,DATO_READ_8b_1;

long I2CDATOLSB,I2CDATOMSB;

void I2C_Check(void);                                                           
void I2C_Write(uint8_t DirW,uint8_t CmdW,uint8_t DirW2);
int8_t I2C_Read_8bits(void);
void I2C_Read_8bits_3bytes(void);
void I2C_Read_8bits_Nbytes(uint8_t Nbytes);
void I2C_Cmd(unsigned char Dir,unsigned char Cfg,unsigned char Cmd);
void I2C_Initialize(void);
void I2C_Stop(void);
void I2C_Start(void);
void I2C_Write_(uint8_t direccion);
void I2C_Rstart(void);
void I2C_Lec_fin(void);
uint8_t I2C_RCEP(void);
void I2C_Lec_seg(void);
void I2C_PUNTERO(unsigned char address, unsigned char puntero);
void I2C_CFG_REG(unsigned char address,unsigned char registro,unsigned char dataM,unsigned char dataL);
void I2C_Lectura(uint8_t address);

#endif	/* CFG_I2C_H */

