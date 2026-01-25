/*
 * File:   oled_ssd1306.c
 * Author: Hermes Colmenares
 *
 * Created on 18 de octubre de 2025, 16:33
 */


#include "CFG_OLED_SSD1306.h"
#include "../drivers/CFG_I2C.h"

//------------------------------------------------------------------------------
void OLED_Command(unsigned char comando) 
{
    I2C_Start();
    I2C_Write_(OLED_ADDR);
    I2C_Write_(comando);
    I2C_Write_(comando);
    I2C_Stop();
}
//------------------------------------------------------------------------------
void OLED_Data(unsigned char data) 
{
    I2C_Start();
    I2C_Write_(OLED_ADDR);
    I2C_Write_(DAT);
    I2C_Write_(data);
    I2C_Stop();
}
//------------------------------------------------------------------------------
void OLED_Init(void) 
{
    __delay_ms(50);

    OLED_Command(0xAE); // Display OFF
    OLED_Command(0xD5); OLED_Command(0x80); // Set display clock divide
    OLED_Command(0xA8); OLED_Command(0x3F); // Multiplex ratio (1/64)
    OLED_Command(0xD3); OLED_Command(0x00); // Display offset
    OLED_Command(0x40); // Start line = 0
    OLED_Command(0x8D); OLED_Command(0x14); // Enable charge pump
    OLED_Command(0x20); OLED_Command(0x00); // Horizontal addressing mode
    OLED_Command(0xA1); // Segment remap
    OLED_Command(0xC0); // COM scan direction
    OLED_Command(0xDA); OLED_Command(0x12); // COM pins hardware config
    OLED_Command(0x81); OLED_Command(0x7F); // Contrast
    OLED_Command(0xD9); OLED_Command(0xF1); // Pre-charge period
    OLED_Command(0xDB); OLED_Command(0x40); // VCOMH deselect level
    OLED_Command(0xA4); // Resume to RAM content
    OLED_Command(0xA6); // Normal display
    OLED_Command(0xAF); // Display ON

    __delay_ms(50);
}
// ------------------- Limpiar pantalla -------------------
void OLED_Clear(void) 
{
    for (uint8_t page = 0; page < 8; page++) 
    {
        OLED_Command(0xB0 + page);
        OLED_Command(0x00);
        OLED_Command(0x10);
        for (uint8_t col = 0; col < 128; col++) 
        {
            OLED_Data(0x00);
        }
    }
}
// ------------------- Posicionar cursor -------------------
void OLED_SetCursor(uint8_t x, uint8_t y) 
{
    OLED_Command(0xB0 + y);
    OLED_Command(((x & 0xF0) >> 4) | 0x10);
    OLED_Command(x & 0x0F);
}
// ------------------- Mostrar caracteres -------------------
void OLED_PrintChar(char c) 
{
    if (c < 32 || c > 126) c = ' ';  // Rango seguro del font definido
    for (uint8_t i = 0; i < 5; i++) 
    {
        OLED_Data(font5x8[c - 32][i]);
    }
    OLED_Data(0x00); // Espacio entre letras
}
//------------------------------------------------------------------------------
void OLED_PrintString(const char *str) 
{
    while (*str) 
    {
        OLED_PrintChar(*str++);
    }
}
//------------------------------------------------------------------------------
