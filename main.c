/*
 * DDS-STC8H1K28-ILI9341-SI5351
 * MCU: STC8H1K28 @ 24MHz
 * Display: ILI9341 2.8" SPI 240x320
 * DDS: Si5351A I2C
 */

#include "STC8.h"

// --- Pin ILI9341 SPI ---
sbit LCD_CS  = P2^0;
sbit LCD_DC  = P2^1;
sbit LCD_RST = P2^2;
sbit LCD_MOSI= P2^3;
sbit LCD_SCK = P2^4;

// --- Pin Si5351 I2C (bit-bang) ---
sbit SI_SDA = P1^0;
sbit SI_SCL = P1^1;

// --- Variabel ---
unsigned long freq = 10000000; // 10 MHz default

void delay_ms(unsigned int ms){
    unsigned int i,j;
    for(i=0;i<ms;i++) for(j=0;j<1200;j++);
}

// I2C Bit-Bang
void I2C_Start(){ SI_SDA=1; SI_SCL=1; SI_SDA=0; SI_SCL=0; }
void I2C_Stop(){ SI_SDA=0; SI_SCL=1; SI_SDA=1; }
void I2C_Write(unsigned char d){
    unsigned char i;
    for(i=0;i<8;i++){ 
        SI_SDA = (d & 0x80)?1:0; 
        SI_SCL=1; SI_SCL=0; d<<=1;
    }
    SI_SDA=1; SI_SCL=1; SI_SCL=0; // ACK
}

void Si5351_WriteReg(unsigned char reg, unsigned char val){
    I2C_Start();
    I2C_Write(0xC0); // Address Si5351
    I2C_Write(reg);
    I2C_Write(val);
    I2C_Stop();
}

void Si5351_Init(){
    // Init Si5351 25MHz XTAL
    Si5351_WriteReg(3, 0xFF); // Disable outputs
    Si5351_WriteReg(16, 0x4F); // CLK0 drive
    // ... setting PLLA
    Si5351_WriteReg(26, 0x00); // PLLA 900MHz
    Si5351_WriteReg(27, 0x01);
    Si5351_WriteReg(28, 0x00);
    Si5351_WriteReg(29, 0x0C);
    Si5351_WriteReg(30, 0x00);
    Si5351_WriteReg(31, 0x00);
    Si5351_WriteReg(32, 0x00);
    Si5351_WriteReg(33, 0x00);
}

void Si5351_SetFreq(unsigned char clk, unsigned long f){
    // Simplified: Set CLK0 freq
    // Rumus lengkap pakai Multisynth, ini contoh set 10MHz
    // Nanti kita lengkapi di file si5351.c
    unsigned long div = 900000000UL / f;
    Si5351_WriteReg(42, (div & 0xFF));
    Si5351_WriteReg(43, (div>>8) & 0xFF);
    Si5351_WriteReg(44, 0x00);
    Si5351_WriteReg(45, 0x00);
}

void ILI9341_Init(){
    LCD_RST=0; delay_ms(100); LCD_RST=1; delay_ms(100);
    // Init command ILI9341
}

void main(){
    P1M0=0; P1M1=0; P2M0=0; P2M1=0;
    Si5351_Init();
    Si5351_SetFreq(0, freq);
    ILI9341_Init();
    while(1){
        // baca encoder rotary, update freq, tampil di ILI9341
    }
}