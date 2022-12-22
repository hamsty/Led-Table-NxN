#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <LedTableNxN.h>
#include <Arduino.h>

LedTableNxN::LedTableNxN(int n, int dataPin, neoPixelType flags) : Adafruit_GFX(n, n)
{
  Serial.begin(115200);
  this->table = new Adafruit_NeoPixel(n * n, dataPin, flags);
  this->table->begin();
  #if MESA == 1
  this->table->show();
  #endif
}

LedTableNxN::~LedTableNxN(void)
{
  if (table)
  {
    free(table);
  }
}

void LedTableNxN::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if (table)
  {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return;

    int16_t t;
    switch (rotation)
    {
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
    if (y % 2 == 1)
    {
      x = WIDTH - x - 1;
    }
    uint8_t red = (color >> 11) << 3;
    uint8_t green = ((color << 5) >> 10) << 2;
    uint8_t blue = ((color << 11) >> 11) << 3;
    uint16_t n = x + (WIDTH * y);
    this->table->setPixelColor(n, red, green, blue);
  }
}

void LedTableNxN::show(void)
{
  this->table->show();
}

uint32_t LedTableNxN::getPixel(int n)
{
  return this->table->getPixelColor(n);
}
