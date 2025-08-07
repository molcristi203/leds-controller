#ifndef BaseLeds_H
#define BaseLeds_H

#include <FastLED.h>

class BaseLeds
{
    protected:
        CRGB* leds = nullptr;
        uint16_t ledsNumber = 0u;
    public:
        BaseLeds(CRGB* ledsArray, uint16_t ledsNum) : leds{ledsArray}, ledsNumber{ledsNum} {};
        virtual void applyToLeds();
        virtual void refreshLeds();
};

#endif