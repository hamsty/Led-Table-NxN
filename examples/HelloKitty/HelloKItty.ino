#include <FS.h>
#include <FastLED.h>
#include <SPIFFS.h>
#include <LedTableNxN.h>

#define DATA_PIN 36

LedTableNxN display(NEOPIXEL, DATA_PIN, 12);

void setup()
{
    Serial.begin(115200);
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    fs::File hello_kitty = SPIFFS.open("/kitty12.bin");
    uint8_t buffer[2];
    hello_kitty.read(buffer,2);
    uint16_t height;
    memcpy(&height, buffer, sizeof(uint16_t));
    hello_kitty.read(buffer,2);
    uint16_t width;
    memcpy(&width, buffer, sizeof(uint16_t));
    uint16_t bitmap [width*height];
    hello_kitty.read((uint8_t*)bitmap, width*height);
    display.drawRGBBitmap(0, 0, bitmap, width,
                     height);
    display.show();
    Serial.printf("%us %us", height, width);
}

void loop()
{
}
