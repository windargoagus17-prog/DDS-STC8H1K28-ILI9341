#ifndef _SI5351_H_
#define _SI5351_H_

#define SI5351_ADDR 0xC0

void Si5351_Init();
void Si5351_SetFreq(unsigned long freq);
void Si5351_WriteReg(unsigned char reg, unsigned char val);
void Si5351_EnableOutput();

#endif