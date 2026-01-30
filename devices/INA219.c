#include "CFG_INA219.h"
#include "../drivers/CFG_I2C.h"

//---------------------------CFG INA219-----------------------------------------
void CFG_INA219_32V_3A(void)
{
    I2C_CFG_REG(0x80,0x00,0xB9,0x9F);
    I2C_Stop();
    I2C_CFG_REG(0x80,0x05,0x10,0x62);                                           
    I2C_Stop();
}
//-------------------------Lectura BUS voltaje----------------------------------
void Lectura_Bus_VDC_INA219(void)
{
    I2C_PUNTERO(0x80,0x02);
    I2C_Stop();
    I2C_Lectura(0x81);
    I2C_Stop();
    __delay_us(10);
    
}
//-------------------------Lectura Corriente------------------------------------
void Lectura_corriente_INA219(void)
{
    I2C_PUNTERO(0x80,0x04);
    I2C_Stop();
    I2C_Lectura(0x81);
    I2C_Stop();
    __delay_us(10);
}
//-------------------------Lectura Potencia-------------------------------------
void Lectura_potencia_INA219(void)
{
    I2C_PUNTERO(0x80,0x03);
    I2C_Stop();
    I2C_Lectura(0x81);
    I2C_Stop();
    __delay_us(10);
}
//------------------------------------------------------------------------------
void Resultado_INA219(void)
{
    ResultadoINA = (I2CDATOMSB<<8) | I2CDATOLSB;
    ResultadoINA = ResultadoINA>>3;
    ResultadoINA *= 4;
}
//------------------------------------------------------------------------------
int Resultado_INA219_A_P(void)
{
    I2CDATOMSB = I2CDATOMSB<<8;
    ResultadoINA_A = I2CDATOMSB + I2CDATOLSB;
    ResultadoINA_P = I2CDATOMSB + I2CDATOLSB;
    ResultadoINA_P *= 2;
    signo = I2CDATOMSB + I2CDATOLSB;
    return signo;
}
