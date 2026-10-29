/*
 * si5351.c - Driver Si5351A untuk STC8H1K28
 * XTAL 25MHz, PLLA 900MHz
 * CLK0 output
 */

#include "STC8.h"
#include "si5351.h"

sbit SI_SDA = P1^0;
sbit SI_SCL = P1^1;

void I2C_Delay(){
    unsigned char i=5;
    while(i--);
}

void I2C_Start(){
    SI_SDA=1; I2C_Delay(); SI_SCL=1; I2C_Delay();
    SI_SDA=0; I2C_Delay(); SI_SCL=0;
}

void I2C_Stop(){
    SI_SDA=0; I2C_Delay(); SI_SCL=1; I2C_Delay();
    SI_SDA=1; I2C_Delay();
}

bit I2C_WriteByte(unsigned char d){
    unsigned char i;
    for(i=0;i<8;i++){
        SI_SDA = (d & 0x80) ? 1 : 0;
        I2C_Delay(); SI_SCL=1; I2C_Delay(); SI_SCL=0;
        d <<=1;
    }
    SI_SDA=1; I2C_Delay(); SI_SCL=1; I2C_Delay();
    SI_SCL=0;
    return 0;
}

void Si5351_WriteReg(unsigned char reg, unsigned char val){
    I2C_Start();
    I2C_WriteByte(0xC0);
    I2C_WriteByte(reg);
    I2C_WriteByte(val);
    I2C_Stop();
}

void Si5351_Init(){
    // Disable all outputs
    Si5351_WriteReg(3, 0xFF);
    
    // Power down
    Si5351_WriteReg(16, 0x80);
    
    // PLLA = 900MHz : 36 * 25MHz
    // P1=36, P2=0, P3=1
    Si5351_WriteReg(26, 0x00);
    Si5351_WriteReg(27, 0x01);
    Si5351_WriteReg(28, 0x00);
    Si5351_WriteReg(29, 0x0E);
    Si5351_WriteReg(30, 0x00);
    Si5351_WriteReg(31, 0x00);
    Si5351_WriteReg(32, 0x00);
    Si5351_WriteReg(33, 0x00);
    
    // Multisynth reset
    Si5351_WriteReg(177, 0xA0);
    
    // Enable CLK0, PLLA source, 8mA drive, integer mode
    Si5351_WriteReg(16, 0x4F);
    
    // Enable output
    Si5351_WriteReg(3, 0xFE);
}

void Si5351_SetFreq(unsigned long freq){
    // freq dalam Hz
    // PLLA = 900MHz
    // Divider = PLLA / freq
    // Untuk freq > 1MHz, pakai integer divider
    
    unsigned long divider;
    unsigned char r_div = 0;
    unsigned long freq_out = freq;
    
    if(freq < 1000000UL){
        // Pakai R divider untuk frek rendah
        // R = 64 untuk < 1MHz
        r_div = 6; // /64
        freq_out = freq * 64;
    }
    
    if(freq_out == 0) freq_out = 1000;
    
    divider = 900000000UL / freq_out;
    if(divider < 8) divider = 8;
    if(divider > 900) divider = 900;
    
    // Multisynth0: registers 42-49
    unsigned long p1 = 128 * divider - 512;
    unsigned char p1_h = (p1 >> 16) & 0x03;
    
    Si5351_WriteReg(42, (p1 >> 8) & 0xFF);
    Si5351_WriteReg(43, p1 & 0xFF);
    Si5351_WriteReg(44, 0x00 | p1_h);
    Si5351_WriteReg(45, 0x00);
    Si5351_WriteReg(46, 0x00);
    Si5351_WriteReg(47, 0x00);
    Si5351_WriteReg(48, 0x00);
    Si5351_WriteReg(49, 0x00);
    
    // R divider di reg 44
    if(r_div){
        unsigned char curr = 0;
        curr |= (r_div << 4);
        Si5351_WriteReg(44, (p1_h | (r_div << 4)));
    }
    
    // PLL reset
    Si5351_WriteReg(177, 0xA0);
}