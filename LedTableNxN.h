#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

typedef class LedTableNxN LedTableNxN;

class LedTableNxN : public Adafruit_GFX
{

public:
    LedTableNxN(int n, int dataPin, neoPixelType flags);
    ~LedTableNxN(void);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void show(void);
    uint32_t getPixel(int n);

private:
    Adafruit_NeoPixel *table;
};