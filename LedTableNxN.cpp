#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <LedTableNxN.h>

LedTableNxN::LedTableNxN(int data_pin, int n, neoPixelType flags) : Adafruit_GFX(n, n)
{
  this->table = new Adafruit_NeoPixel(n * n, data_pin, flags);
  this->table->begin();
  this->table->show();
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
    uint8_t red = color >> 11;
    uint8_t green = (color << 5) >> 10;
    uint8_t blue = (color << 11) >> 11;
    if (y % 2 == 1)
      this->table->setPixelColor((11 - x) + y * WIDTH, red, green, blue);
    else
      this->table->setPixelColor(x + y * WIDTH, red, green, blue);
  }
}

void LedTableNxN::show(void)
{
  this->table->show();
}
