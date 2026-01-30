#include "CFG_DS1307.h"
#include "../drivers/CFG_I2C.h"
#include "../utils/CFG_BCD_TO_DEC_TO_BCD.h"
#include "../display/CFG_LCD_16x2.h"

//******************************************************************************
//****************************CFG DS1307 1seg***********************************
//******************************************************************************                                                                
    void CFG_DS1307()
{
    // Configurar salida de 1 seg
    I2C_Start();
    I2C_Write_(_Dir_DS1307_W);
    I2C_Write_(_Registro_Ctr);
    I2C_Write_(_Salida_1seg);
    I2C_Stop();

    // Borrar registros
    for(int i = 0; i < sizeof(registros); i++)
    {
        I2C_Start();
        I2C_Write_(_Dir_DS1307_W);
        I2C_Write_(registros[i]);
        I2C_Write_(0x00);
        I2C_Stop();        
    }    
}
//******************************************************************************
//**************************** READ DS1307 *************************************
//******************************************************************************
void READ_DS1307(uint8_t type,uint8_t eje_x,uint8_t eje_y,unsigned char caracter)
{
    I2C_Write(_Dir_DS1307_W,type,_Dir_DS1307_R);
    I2C_Read_8bits();
    BCD_TO_DEC(DATO_I2C_8bits);
    if (eje_x >= 1)
    {
        Lcd_pos_x(eje_x);
        Lcd_Write_Char(unidades);
        Lcd_pos_x(eje_x -= 1);
        Lcd_Write_Char(decenas);
        if (caracter == ':' | caracter == '/' | caracter == '-')
            {
                Lcd_pos_x(eje_x -= 1);
                Lcd_Write_Char(caracter);
            }
    }
    if (eje_y >=1)
    {
        Lcd_pos_y(eje_y);
        Lcd_Write_Char(unidades);
        Lcd_pos_y(eje_y -= 1);
        Lcd_Write_Char(decenas);
        if (caracter == ':' | caracter == '/' | caracter == '-')
            {
                Lcd_pos_y(eje_y -= 1);
                Lcd_Write_Char(caracter);
            }         
    }
}
