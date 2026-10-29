#ifndef _ILI9341_H_
#define _ILI9341_H_

#define LCD_W 240
#define LCD_H 320

void ILI9341_Init();
void ILI9341_Fill(unsigned int color);
void ILI9341_SetCursor(unsigned int x, unsigned int y);
void ILI9341_DrawString(unsigned char x, unsigned char y, char *str, unsigned int color, unsigned int bg);
void ILI9341_DrawFreq(unsigned long freq);

// Warna
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0

#endif