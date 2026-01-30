/*
 * File:   LCD_16x2.c
 * Author: Familia CS
 *
 * Created on 4 de junio de 2025, 22:15
 */

#include "CFG_LCD_16x2.h"

//------------------------------------------------------------------------------
//------------------------------decodificaodor----------------------------------
//--------------------------Nible alto y nible bajo-----------------------------
//------------------------------------------------------------------------------
void Lcd_cmd_data(unsigned char datos, unsigned char cmd_data) 
{
    unsigned char nhigh, nlow;

    nhigh = datos >> 4;
    nlow  = datos & 0x0F;

    // ----- Nibble alto -----
    Dato_D4 = (nhigh >> 0) & 1;
    Dato_D5 = (nhigh >> 1) & 1;
    Dato_D6 = (nhigh >> 2) & 1;
    Dato_D7 = (nhigh >> 3) & 1;

    Dato_RS = cmd_data;
    Dato_E = 1; __delay_ms(15); Dato_E = 0;

    // ----- Nibble bajo -----
    Dato_D4 = (nlow >> 0) & 1;
    Dato_D5 = (nlow >> 1) & 1;
    Dato_D6 = (nlow >> 2) & 1;
    Dato_D7 = (nlow >> 3) & 1;

    Dato_RS = cmd_data;
    Dato_E = 1; __delay_ms(15); Dato_E = 0;
}
//------------------------------------------------------------------------------
//--------------------------INICIALIZACION 4 BITS-------------------------------
//------------------------------------------------------------------------------
void Lcd_inicio(void)
{
    __delay_ms(20);
    RS_DIR = 0; E_DIR  = 0; D4_DIR = 0; D5_DIR = 0; D6_DIR = 0; D7_DIR = 0;
    Lcd_cmd_data(_mode_8bits_0x30,cmd);__delay_ms(20);
    Lcd_cmd_data(_mode_8bits_0x30,cmd);__delay_us(500);
    Lcd_cmd_data(_mode_8bits_0x30,cmd);__delay_us(500);
    Lcd_cmd_data(_mode_4bits_0x20,cmd);__delay_us(500);
    Lcd_cmd_data(_4b_2lin_5x8_,cmd);
    Lcd_cmd_data(_ON_LCD,cmd);
    Lcd_cmd_data(_CFG_in,cmd);
    Lcd_cmd_data(_LCD_CLEAR,cmd);
}
//******************************************************************************
void Lcd_Write_String(const char *a)
{
    while(*a)
        Lcd_Write_Char(*a++);
}
//******************************************************************************
void Lcd_Write_Char(unsigned char a)
{
    Lcd_cmd_data(a,dat);
}
//******************************************************************************
void Lcd_pos_x(unsigned char POSx)
{
    if(POSx < 1) POSx = 1;
    if(POSx > 16) POSx = 16;
    Lcd_cmd_data(0x80 + POSx - 1, cmd);
}   
//******************************************************************************
void Lcd_pos_y(unsigned char POSy)
{
    if(POSy < 1) POSy = 1;
    if(POSy > 16) POSy = 16;
    Lcd_cmd_data(0xC0 + POSy - 1, cmd);
}
//******************************************************************************
void Caracter_0(void) 
{
    for (contador2=0;contador2<9;contador2++)
    {
        Envio_control(caracter0_direccion[contador2]);
        Envio_data(caracter0_datos[contador2]);
    }
}
//******************************************************************************
void Caracter_1(void) 
{
    for (contador2=0;contador2<9;contador2++)
    {
        Envio_control(caracter1_direccion[contador2]);
        Envio_data(caracter1_datos[contador2]);
    }
}
//******************************************************************************
void Caracter_2(void) 
{
    for (contador2=0;contador2<9;contador2++)
    {
        Envio_control(caracter2_direccion[contador2]);
        Envio_data(caracter2_datos[contador2]);
    }
}
//**************************ENVIO CONTROL***************************************
void Envio_control(unsigned char q)
{
    Dato_RS = 0;
    __delay_us(100);
//    PORTD = q;
    __delay_us(100);
    Dato_E = 1;
    __delay_ms(1);
    Dato_E = 0;
    __delay_ms(1);
}
//*************************ENVIO DATA*******************************************
void Envio_data(unsigned char t)
{
    Dato_RS = 1;
//    PORTD = t;
    Dato_E = 1;
    __delay_ms(1);
    Dato_E = 0;
    __delay_ms(1);
}
