#include "CFG_BMP280.h"
#include "../drivers/CFG_I2C.h"
//------------------------------------------------------------------------------
void ini_bmp280 (void)
{
    I2C_Write(_bmp280_w,_bmp280_ID,_bmp280_r);
    I2C_Read_8bits();
    if (I2C_Read_8bits() == 0x58)
    {

    }
    I2C_Cmd(_bmp280_w,_bmp280_reg_reset,_bmp280_reset);
    I2C_Cmd(_bmp280_w,_bmp280_ctrl_mes,_mode_sleep);
    I2C_Cmd(_bmp280_w,_bmp280_CFG,0x00);
    I2C_Cmd(_bmp280_w,_bmp280_ctrl_mes,0x47);
}
//------------------------------------------------------------------------------
void CALIBRATION_BMP280(void)
{
    unsigned char w;
    for (w = 0; w <6; w++)
    {
        unsigned char a = 0x88 + w;
        I2C_Write(_bmp280_w, a, _bmp280_r);
        cal_data[w] = I2C_Read_8bits();
    }

    dig_T1 = (uint16_t)(cal_data[0] | (cal_data[1] << 8));
    dig_T2 = (int16_t)(cal_data[2] | (cal_data[3] << 8));
    dig_T3 = (int16_t)(cal_data[4] | (cal_data[5] << 8));
}
//------------------------------------------------------------------------------
uint32_t CALCULO_BMP280(void)
{
    I2C_Write(_bmp280_w,_bmp280_temp_msb,_bmp280_r);
    I2C_Read_8bits_3bytes();     
//------------------------------------------------------------------------------
    adc_T = (((uint32_t)DATO_READ_8b_3 << 16) | ((uint32_t)DATO_READ_8b_2 << 8)  | ((uint32_t)DATO_READ_8b_1)) >> 4;
    
    var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;
    temp = (t_fine * 5 + 128) >> 8;  // °C x 100

    return temp;
//******************************************************************************    
}
//******************************************************************************
void CALIBRATION_P_BMP280(void)
{
    unsigned char cal[18];
    unsigned char i;
    
    for (i = 0; i < 18; i++)
    {
        I2C_Write(_bmp280_w, 0x8E + i, _bmp280_r);
        cal[i] = I2C_Read_8bits();
    }

    dig_P1 = (uint16_t)(cal[0] | (cal[1] << 8));
    dig_P2 = (int16_t)(cal[2] | (cal[3] << 8));
    dig_P3 = (int16_t)(cal[4] | (cal[5] << 8));
    dig_P4 = (int16_t)(cal[6] | (cal[7] << 8));
    dig_P5 = (int16_t)(cal[8] | (cal[9] << 8));
    dig_P6 = (int16_t)(cal[10] | (cal[11] << 8));
    dig_P7 = (int16_t)(cal[12] | (cal[13] << 8));
    dig_P8 = (int16_t)(cal[14] | (cal[15] << 8));
    dig_P9 = (int16_t)(cal[16] | (cal[17] << 8));
}
//******************************************************************************
uint32_t CALCULO_PRESION_BMP280(void)
{
    // Leer 3 bytes de presión
    I2C_Write(_bmp280_w, _bmp280_pres_msb, _bmp280_r);
    I2C_Read_8bits_3bytes();

    // Ensamblar 20 bits
    adc_P = (((uint32_t)DATO_READ_8b_3 << 16) |
             ((uint32_t)DATO_READ_8b_2 << 8)  |
             (uint32_t)DATO_READ_8b_1) >> 4;

    // Compensación de presión
    var1_p = ((int64_t)t_fine) - 128000;
    var2_p = var1_p * var1_p * (int64_t)dig_P6;
    var2_p = var2_p + ((var1_p * (int64_t)dig_P5) << 17);
    var2_p = var2_p + (((int64_t)dig_P4) << 35);
    var1_p = ((var1_p * var1_p * (int64_t)dig_P3) >> 8) + ((var1_p * (int64_t)dig_P2) << 12);
    var1_p = (((((int64_t)1) << 47) + var1_p)) * ((int64_t)dig_P1) >> 33;

    if (var1_p == 0)
        return 0; // evitar división por 0

    p = 1048576 - adc_P;
    p = (((p << 31) - var2_p) * 3125) / var1_p;
    var1_p = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2_p = (((int64_t)dig_P8) * p) >> 19;

    p = ((p + var1_p + var2_p) >> 8) + (((int64_t)dig_P7) << 4);

    return (uint32_t)(p / 256); // Pa (Pascales)
}

