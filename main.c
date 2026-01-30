/**
 * @file main.c
 * @author Hermes Colmenares
 * @date 2026-01-25
 * @brief Main function
 */

#include <xc.h>
#include "CFG_PIC18F2550/CFG_PIC18F2550.h"
#include "drivers/CFG_I2C.h"
#include "drivers/CFG_PWM.h"
#include "drivers/CFG_ADC.h"
#include "drivers/CFG_UART.h"
#include "display/CFG_OLED_SSD1306.h"
#include "devices/CFG_DS1307.h"

int main()
{
    TRISA = 1;                                                                  //               
    TRISC = 0;                                                                  //
    TRISB = 0;                                                                  //
    LATA = 0; LATB = 0; LATC = 0;                                               //Limpiar todos los puertos
    CMCON = 0x07;                                                               //DESACTIVA LOS COMPARADORES y Desactiva entradas analogicas
    INTCON2bits.RBPU = 0;    
//************************* Configurar Timer0 **********************************
    T0CONbits.TMR0ON = 0; T0CONbits.T08BIT = 0; T0CONbits.T0CS = 0; T0CONbits.T0SE = 0;             //Desactiva el TIMER0, modo 16bits,  reloj interno del ciclo de la instrucci�n
    T0CONbits.PSA = 0;                                                          // Usa prescaler
    T0CONbits.T0PS = 6;                                                         // 1:128
    INTCONbits.TMR0IF = 0;                                                      //Limpio bandera de insterrupcion TIMER0
//-------------------------- CFG 2 TIMER0 --------------------------------------
    TMR0H	 = 0x48;
    TMR0L	 = 0xE5;     
    INTCONbits.TMR0IE = 1;                                                      //Habilito interrupci�n por desbordamiento del TMR0    
    T0CONbits.TMR0ON = 1;                                                       //Enciendo TIMER0     
//******************** Interrupciones generales activados **********************
    IPR1 = 0;
    IPR2 = 0;
    INTCON2bits.TMR0IP = 1;                                                     //Alta priotidad a desbordamiento de TMR0
    INTCON2bits.RBIP = 0;                                                       //RB Port Change Interrupt Priority bit
    INTCON3 = 0;
    PIE2bits.HLVDIE = 0;                                                        //High/Low-Voltage Detect Interrupt Enable bit 
    INTCONbits.GIE = 1;                                                         //Activo interrupciones enmascarables
    INTCONbits.PEIE = 1;                                                        //Activo interrupciones de perif�ricos
//***************************Inicializar I2C************************************
    I2C_Initialize();
//***************************Inicializar PWM************************************
    PWM_Inicializar();
//***************************Inicializar ADC************************************
    ADC_Configuracion();
//***************************Inicializar UART************************************
    Uart_Init();
//************************** Configuracion OLED ********************************
    OLED_Init();
    OLED_Clear();
//-------------------------Configuracion DS1307---------------------------------    
    CFG_DS1307();                
//***************************** Inicio de programa *****************************
    while (1)
    {

    }
    return 0;
}
