#include "leds/RainbowLeds.h"

RainbowLeds::RainbowLeds(CRGB* ledsArray, uint16_t ledsNum)
: BaseLeds(ledsArray, ledsNum)
{}

void RainbowLeds::applyToLeds()
{
    initialHue = 0;
    if (rainbowType == STATIC_RAINBOW)
        fill_rainbow(leds, ledsNumber, 0, 0);
    else
        fill_rainbow(leds, ledsNumber, 0, deltaHue);
    FastLED.show();
    hueChangeTime = millis();
}

void RainbowLeds::refreshLeds()
{
    if ((millis() - hueChangeTime) > hueChangeDelay)
    {
        initialHue += 5;
        if (rainbowType == STATIC_RAINBOW)
            fill_rainbow(leds, ledsNumber, initialHue, 0);
        else
            fill_rainbow(leds, ledsNumber, initialHue, deltaHue);
        FastLED.show();
        hueChangeTime = millis();
    }
}

void RainbowLeds::changeRainbowType(RainbowTypes rainbowType)
{
    this->rainbowType = rainbowType;
    applyToLeds();
}