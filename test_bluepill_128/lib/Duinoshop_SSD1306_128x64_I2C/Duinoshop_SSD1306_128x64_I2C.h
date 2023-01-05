/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers
*********************************************************************/
#ifndef _Duinoshop_SSD1306_128x64_I2C_
#define _Duinoshop_SSD1306_128x64_I2C_

#include "Arduino.h"
#include <Adafruit_GFX.h>

#define USE_SOFTWIRE          1

#define SSD1306_I2C_ADDRESS   0x3C	// 011110+SA0+RW - 0x3C or 0x3D
// Address for 128x32 is 0x3C
// Address for 128x64 is 0x3D (default) or 0x3C (if SA0 is grounded)

#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64
  
  
#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_DISPLAYON           0xAF
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_CHARGEPUMP          0x8D
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COLUMNADDR          0x21
#define SSD1306_PAGEADDR            0x22
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETCONTRAST         0x81
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7

#define BLACK 0
#define WHITE 1
#define INVERSE 2

#define SSD1306_BLACK 0
#define SSD1306_WHITE 1
#define SSD1306_INVERSE 2


class DuinoShop_SSD1306 : public Adafruit_GFX
{
   public:
      //-- constructeur
      DuinoShop_SSD1306();
      
      //-- initialisation de l'ecran et de l'I2C
      void begin( uint8_t i2caddr = SSD1306_I2C_ADDRESS );
      void command(uint8_t c) ;
      void display(void) ;
      void invertDisplay(bool invert) ;
      void clearDisplay(void) ;
      void drawPixel(int16_t x, int16_t y, uint16_t color) ;
};

#endif /* _Duinoshop_SSD1306_128x64_I2C_ */
