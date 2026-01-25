#include "CFG_PWM.h"

void PWM_Inicializar(void)
{
    CCP1CONbits.CCP1M = 0x0C;                                                   // Modo PWM
    CCP2CONbits.CCP2M = 0x0C;                                                   // Modo PWM
    PR2 = 255;                                                                  // Frecuencia PWM ~5kHz con Fosc 48MHz
    T2CONbits.T2CKPS = 11;                                                       // Prescaler 1:4
    T2CONbits.TMR2ON = 1;                                                       // Encender Timer2
    CCPR1L = 128;
    CCPR2L = 0;
    CCP1CONbits.DC1B = 0;
    CCP2CONbits.DC2B = 0;
}
//------------------------------------------------------------------------------
void PWM_IN_AN1()
{
    T2CONbits.TMR2ON = 1;                                                       //Enciende PWM
//******************************************************************************
    if (DATOADCL_PWM2_AN1 == 0x80)
    {
        CCP1CONbits.DC1B1 = 1;
    }
    if (DATOADCL_PWM2_AN1 == 0)
    {
        CCP1CONbits.DC1B1 = 0;
    }
//******************************************************************************
    if (DATOADCL_PWM3_AN1 == 1)
    {
        CCP1CONbits.DC1B0 = 1;
    }
    if (DATOADCL_PWM3_AN1 == 0)
    {
        CCP1CONbits.DC1B0 = 0;
    }
    CCPR1L = DATOADC_PWM_AN1;
}
//------------------------------------------------------------------------------
void PWM_IN_AN3(void)
{
    T2CONbits.TMR2ON = 1;                                                       //Enciende PWM
//******************************************************************************
    if (DATOADCL_PWM2_AN3 == 0x80)
    {
        CCP1CONbits.DC1B1 = 1;
    }
    if (DATOADCL_PWM2_AN3 == 0)
    {
        CCP1CONbits.DC1B1 = 0;
    }
//******************************************************************************
    if (DATOADCL_PWM3_AN3 == 1)
    {
        CCP1CONbits.DC1B0 = 1;
    }
    if (DATOADCL_PWM3_AN3 == 0)
    {
        CCP1CONbits.DC1B0 = 0;
    }
    DATOADC_PWM_AN3 = ~DATOADC_PWM_AN3;
    DATOADC_PWM_AN3 -= 120;
    CCPR2L = DATOADC_PWM_AN3;
}
//******************************************************************************
void PWM_sin_50hz(void)
{
        for(uint8_t i = 0; i < SINE_SAMPLES; i++)
        {
            PWM_SetDuty10(sine_table[i]);
            __delay_us(156);
        }
}
//******************************************************************************
void PWM_SetDuty10(uint16_t duty)
{
    if(duty > 1023) duty = 1023;

    CCPR1L = duty >> 2;              // 8 MSB
    CCP1CONbits.DC1B = duty & 0x03;  // 2 LSB
}

