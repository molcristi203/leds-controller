#include "leds/StaticLeds.h"

StaticLeds::StaticLeds(CRGB* ledsArray, uint16_t ledsNum)
: BaseLeds(ledsArray, ledsNum)
{}

void StaticLeds::setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    rgb.red = red;
    rgb.green = green;
    rgb.blue = blue;
}

void StaticLeds::getRGB(uint8_t &red, uint8_t &green, uint8_t &blue)
{
    red = rgb.red;
    green = rgb.green;
    blue = rgb.blue;
}

void StaticLeds::applyToLeds()
{
    for (uint16_t i = 0; i < ledsNumber; i++)
    {
        leds[i] = CRGB(rgb.red, rgb.green, rgb.blue);
    }
    FastLED.show();
}

void StaticLeds::refreshLeds()
{}