/*
 * File:   AHT0.c
 * Author: Hermes Colmenares
 *
 * Created on 19 de diciembre de 2025, 22:50
 */


#include "CFG_AHT20.h"
#include "../drivers/CFG_I2C.h"

//********************* Funcion de comunicacion con AHT20 **********************
void aht20_ini (void)
{
    I2C_Start();                                                                //Envio start
    I2C_Write_(0x70);                                                           //Direccion 0x38 + bit 0 = 0 de escritura
    //I2C_Write_(aht20_cmd_ini);                                                  //Envio de comando de inicializacion
    //I2C_Write_(aht20_cmd_ini_1);                                                //Envio de comando de inicializacion palabra 1
    //I2C_Write_(aht20_cmd_ini_2);                                                //Envio de comando de inicializacion palabra 2
    I2C_Stop();                                                                 //Envio stop
}
//***************** Funcion de medicion temperatura//humedad *******************
void aht20_mes(void)
{
    I2C_Start();                                                                //Envio start
    I2C_Write_(aht20_w);                                                        //Envio de direccion de escritura
    I2C_Write_(aht20_cmd_mes);                                                  //Envio comando de medicion
    I2C_Write_(aht20_cmd_1);                                                    //Envio comando 1 de medicion 0x33
    I2C_Write_(aht20_cmd_2);                                                    //Envio comando 2 de medicon
    I2C_Stop();                                                                 //Envio stop    
}
//************************ Funcion para medir humedad **************************
void aht20_cal_hum(void) 
{
    byte_1 = read_datos[1];
    byte_2 = read_datos[2];
    byte_3_h = read_datos[3];
    raw_humedad = ((uint32_t)byte_1 << 12) | ((uint32_t)byte_2 << 4) | ((byte_3_h & 0xF0) >> 4);
    H = (uint32_t)(((uint64_t)raw_humedad * 10000) / 1048576);                  // 10000 = 100 * 100 centésimas        
}
//******************** Funcion para medir temperatura **************************
void aht20_cal_temp(void)
{
    byte_3_t = read_datos[3];
    byte_4 = read_datos[4];
    byte_5 = read_datos[5];    
    raw_temperatura = ((uint32_t)(byte_3_t & 0x0F) << 16) | ((uint32_t)byte_4 << 8) | byte_5;
    T = ((int32_t)(((uint64_t)raw_temperatura * 20000) / 1048576) - 5000);
}
