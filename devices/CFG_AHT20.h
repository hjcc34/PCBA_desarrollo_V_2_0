#ifndef CFG_AHT20
#define	CFG_AHT20

#include <xc.h>

#define aht20_w         0x70
#define aht20_r         0x71
#define aht20_cmd_ini   0xBE
#define aht20_cmd_1     0x33
#define aht20_cmd_2     0x00
#define aht20_cmd_mes   0xAC
#define aht20_cmd_ini_1 0x08
#define aht20_cmd_ini_2 0x00

uint8_t aht20_medicion,aht20_medicion_read;
uint32_t raw_temperatura,raw_humedad,H;
int32_t T;

void aht20_ini(void);                                                           //Funcion de inicializacion del AHT20
void aht20_mes(void);                                                           //Funcion de medicion (temperatura y humedad del AHT20
void aht20_read(void);                                                          //Funcion de lectura del AHT20
void aht20_cal_temp(void);                                                      //Funcion para calcular temperatura
void aht20_cal_hum(void);                                                       //Funcion para calcular humedad

#endif	/* XC_HEADER_TEMPLATE_H */

