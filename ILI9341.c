#include "STC8.h"
#include "ILI9341.h"

sbit LCD_CS  = P2^0;
sbit LCD_DC  = P2^1;
sbit LCD_RST = P2^2;
sbit LCD_MOSI= P2^3;
sbit LCD_SCK = P2^4;

void LCD_Delay(unsigned int n){ while(n--); }

void SPI_W(unsigned char d){
    unsigned char i;
    for(i=0;i<8;i++){
        LCD_SCK=0;
        LCD_MOSI = (d & 0x80) ? 1 : 0;
        LCD_SCK=1;
        d<<=1;
    }
}

void LCD_WR_CMD(unsigned char cmd){
    LCD_DC=0; LCD_CS=0;
    SPI_W(cmd);
    LCD_CS=1;
}

void LCD_WR_DATA(unsigned char dat){
    LCD_DC=1; LCD_CS=0;
    SPI_W(dat);
    LCD_CS=1;
}

void LCD_WR_DATA16(unsigned int dat){
    LCD_DC=1; LCD_CS=0;
    SPI_W(dat>>8); SPI_W(dat);
    LCD_CS=1;
}

void ILI9341_Init(){
    LCD_RST=0; LCD_Delay(20000); LCD_RST=1; LCD_Delay(20000);
    LCD_WR_CMD(0x01); LCD_Delay(20000);
    LCD_WR_CMD(0xCF); LCD_WR_DATA(0x00); LCD_WR_DATA(0x83); LCD_WR_DATA(0x30);
    LCD_WR_CMD(0xED); LCD_WR_DATA(0x64); LCD_WR_DATA(0x03); LCD_WR_DATA(0x12); LCD_WR_DATA(0x81);
    LCD_WR_CMD(0xE8); LCD_WR_DATA(0x85); LCD_WR_DATA(0x01); LCD_WR_DATA(0x79);
    LCD_WR_CMD(0xCB); LCD_WR_DATA(0x39); LCD_WR_DATA(0x2C); LCD_WR_DATA(0x00); LCD_WR_DATA(0x34); LCD_WR_DATA(0x02);
    LCD_WR_CMD(0xF7); LCD_WR_DATA(0x20);
    LCD_WR_CMD(0xEA); LCD_WR_DATA(0x00); LCD_WR_DATA(0x00);
    LCD_WR_CMD(0xC0); LCD_WR_DATA(0x26);
    LCD_WR_CMD(0xC1); LCD_WR_DATA(0x11);
    LCD_WR_CMD(0xC5); LCD_WR_DATA(0x35); LCD_WR_DATA(0x3E);
    LCD_WR_CMD(0xC7); LCD_WR_DATA(0xBE);
    LCD_WR_CMD(0x36); LCD_WR_DATA(0x28);
    LCD_WR_CMD(0x3A); LCD_WR_DATA(0x55);
    LCD_WR_CMD(0xB1); LCD_WR_DATA(0x00); LCD_WR_DATA(0x1B);
    LCD_WR_CMD(0xB6); LCD_WR_DATA(0x0A); LCD_WR_DATA(0xA2);
    LCD_WR_CMD(0xF6); LCD_WR_DATA(0x01); LCD_WR_DATA(0x30);
    LCD_WR_CMD(0x26); LCD_WR_DATA(0x01);
    LCD_WR_CMD(0xE0); LCD_WR_DATA(0x0F); LCD_WR_DATA(0x2A); LCD_WR_DATA(0x28); LCD_WR_DATA(0x08); LCD_WR_DATA(0x0E); LCD_WR_DATA(0x08); LCD_WR_DATA(0x54); LCD_WR_DATA(0xA9); LCD_WR_DATA(0x43); LCD_WR_DATA(0x0A); LCD_WR_DATA(0x0F); LCD_WR_DATA(0x00); LCD_WR_DATA(0x00); LCD_WR_DATA(0x00); LCD_WR_DATA(0x00);
    LCD_WR_CMD(0xE1); LCD_WR_DATA(0x00); LCD_WR_DATA(0x15); LCD_WR_DATA(0x17); LCD_WR_DATA(0x07); LCD_WR_DATA(0x11); LCD_WR_DATA(0x06); LCD_WR_DATA(0x2B); LCD_WR_DATA(0x56); LCD_WR_DATA(0x3C); LCD_WR_DATA(0x05); LCD_WR_DATA(0x10); LCD_WR_DATA(0x0F); LCD_WR_DATA(0x3F); LCD_WR_DATA(0x3F); LCD_WR_DATA(0x0F);
    LCD_WR_CMD(0x11); LCD_Delay(20000);
    LCD_WR_CMD(0x29);
}

void ILI9341_SetWindow(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1){
    LCD_WR_CMD(0x2A); LCD_WR_DATA16(x0); LCD_WR_DATA16(x1);
    LCD_WR_CMD(0x2B); LCD_WR_DATA16(y0); LCD_WR_DATA16(y1);
    LCD_WR_CMD(0x2C);
}

void ILI9341_Fill(unsigned int color){
    unsigned int i,j;
    ILI9341_SetWindow(0,0,239,319);
    LCD_DC=1; LCD_CS=0;
    for(i=0;i<320;i++) for(j=0;j<240;j++){ SPI_W(color>>8); SPI_W(color); }
    LCD_CS=1;
}