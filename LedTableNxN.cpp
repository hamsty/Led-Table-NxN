#include <Adafruit_GFX.h>
#include <FastLed.h>

LedTableNxN::LedTableNxN(ESPIChipsets CHIPSET, int data_pin, int16 n): Adafruit_GFX(n,n){
    table = new CRGB(n*n);
    FastLED.addLeds<CHIPSET, data_pin>(table, n*n);
}

LedTableNxN::~LedTableNxN(void){
    if(table){
        free(table);
    }
}

LedTableNxN::drawPixel(void){
    if (table) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;

    int16_t t;
    switch (rotation) {
    case 1:
      t = x;
      x = WIDTH - 1 - y;
      y = t;
      break;
    case 2:
      x = WIDTH - 1 - x;
      y = HEIGHT - 1 - y;
      break;
    case 3:
      t = x;
      x = y;
      y = HEIGHT - 1 - t;
      break;
    }
    uint8_t red= color >> 11;
    uint8_t green = (color << 5)>>10;
    uint8_t blue = (color << 11)>>11 ;  

    CRGB newcolor =  CRGB(red, green, blue);
    if(y % 2 == 1)
        table[(11-x) + y * WIDTH] = newcolor;
    else
        table[x + y * WIDTH] = newcolor;

    LedTableNxN::show(void){
        FastLED.show();
    }
}


