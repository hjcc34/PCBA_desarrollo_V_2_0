/**
  ******************************************************************************
  * @file    drivers/ADC.c
  * @author  Equipo de Desarrollo
  * @date    2024-06-15
  * @brief   Configuracion y manejo del ADC
  ******************************************************************************
  */
#include "CFG_ADC.h"

//--------------------------Configuracion ADC-----------------------------------
void ADC_Configuracion(void)
{
    //ADCON1
    ADCON1bits.PCFG = 14;                                                       //Activa AN0 Entrada analogica
    //ADCON0
    ADCON0bits.CHS = 0;
    //ADCON2
    ADCON2bits.ACQT = 4;                                                        //A/D Acquisition Time Select bits 8 Tad
    ADCON2bits.ADCS = 3;                                                        //Clock conversion FOSC/Frc
    ADCON2bits.ADFM = 1;                                                        //Justificacion a la derecha
    //ADCON0
    ADCON0bits.ADON = 1;
}
//---------------------------Conversor para AN1---------------------------------
void ConversorAD_PWM_AN0(void)
{
    ADCON0bits.CHS0 = 0;
    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE == 1)
    {
        
    }
    dato_adc = ((uint16_t)ADRESH << 8) | ADRESL;
    dato_adc_mv = (uint32_t)dato_adc * 5000 / 1023;
    //DATOADCL_PWM_AN1 = ADRESL;
    //DATOADCL_PWM2_AN1 = ADRESL;
    //DATOADCL_PWM3_AN1 = ADRESL;
    //DATOADCH_PWM_AN1 = ADRESH;
//********************************Valor total***********************************
    //DATOADCL_PWM_AN1 = DATOADCL_PWM_AN1>>2;
    //DATOADCH_PWM_AN1 = DATOADCH_PWM_AN1<<6;
    //DATOADC_PWM_AN1 = DATOADCL_PWM_AN1 + DATOADCH_PWM_AN1;
//******************************CCP1CON Y***************************************
    //DATOADCL_PWM2_AN1 = DATOADCL_PWM2_AN1<<7;
//****************************CCP1CON X*****************************************
    //DATOADCL_PWM3_AN1 = DATOADCL_PWM3_AN1<<7;
    //DATOADCL_PWM3_AN1 /= 10000000; 
}
//---------------------------Conversor para AN3---------------------------------
