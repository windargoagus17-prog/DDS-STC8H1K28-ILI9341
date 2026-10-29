#ifndef _STC8_H_
#define _STC8_H_

// STC8H1K28 Register Define untuk Keil C51
sfr P0 = 0x80;
sfr P1 = 0x90;
sfr P2 = 0xA0;
sfr P3 = 0xB0;
sfr P4 = 0xC0;
sfr P5 = 0xC8;
sfr P6 = 0xE8;
sfr P7 = 0xF8;

sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P1M1 = 0x91;
sfr P1M0 = 0x92;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;

sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;

#endif