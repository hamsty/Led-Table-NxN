#include <Adafruit_GFX.h>
#include <FastLed.h>

class LedTableNxN: public Adafruit_GFX {

    public:
        LedTableNxN(int16 n);
        ~LedTableNxN(void);
        void drawPixel(int16_t x, int16_t y, uint16_t color);
        void show();

    private:
        CRGB *table;

}