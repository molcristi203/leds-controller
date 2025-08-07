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
        fill_rainbow(leds, ledsNumber, 0, DELTA_HUE);
    FastLED.show();
    hueChangeTime = millis();
}

void RainbowLeds::refreshLeds()
{
    if ((millis() - hueChangeTime) > HUE_CHANGE_DELAYS[hueChangeDelayIndex])
    {
        initialHue += HUE_INCREMENT;
        if (rainbowType == STATIC_RAINBOW)
            fill_rainbow(leds, ledsNumber, initialHue, 0);
        else
            fill_rainbow(leds, ledsNumber, initialHue, DELTA_HUE);
        FastLED.show();
        hueChangeTime = millis();
    }
}

void RainbowLeds::changeRainbowType(RainbowTypes rainbowType)
{
    this->rainbowType = rainbowType;
    applyToLeds();
}

uint8_t RainbowLeds::getHueChangeDelayIndex()
{
    return hueChangeDelayIndex;
}

void RainbowLeds::setHueChangeDelayIndex(uint8_t hueChangeDelayIndex)
{
    this->hueChangeDelayIndex = hueChangeDelayIndex;
}