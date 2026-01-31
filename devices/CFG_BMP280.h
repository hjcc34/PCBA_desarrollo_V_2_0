/* 
 * File:   CFG_BMP280.h
 * Author: Familia CS
 *
 * Created on 22 de noviembre de 2024, 21:15
 */

#ifndef BMP280_H
#define BMP280_H

#include <xc.h>

#define _bmp280_w           0xEE
#define _bmp280_r           0xEF
#define _habilta_SPI        0x01
#define _bmp280_reset       0xB6
#define _bmp280_CFG         0xF5
#define _bmp280_ctrl_mes    0xF4
#define _bmp280_status      0xF3
#define _bmp280_reg_reset   0xE0
#define _bmp280_ID          0xD0
#define _mode_sleep         0x00
#define _bmp280_temp_xlsb   0xFC
#define _bmp280_temp_lsb    0xFB
#define _bmp280_temp_msb    0xFA
#define _bmp280_pres_xlsb   0xF9
#define _bmp280_pres_lsb    0xF8
#define _bmp280_pres_msb    0xF7

uint16_t dig_T1;
int16_t dig_T2, dig_T3;

int32_t var1, var2, t_fine, temp;

int32_t adc_T = 0;

uint8_t cal_data[3];

// Calibración presión
uint16_t dig_P1;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

// Cálculo
int64_t var1_p, var2_p, p;
uint32_t adc_P;


void CALIBRATION_BMP280(void);
uint32_t CALCULO_BMP280(void);
void ini_bmp280 (void);
void CALIBRATION_P_BMP280(void);
uint32_t CALCULO_PRESION_BMP280(void);

#endif	/* CFG_BMP280_H */

