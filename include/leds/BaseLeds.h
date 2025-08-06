#ifndef BaseLeds_H
#define BaseLeds_H

#include <FastLED.h>

class BaseLeds
{
    protected:
        CRGB* leds;
        uint16_t ledsNumber;
    public:
        BaseLeds(CRGB* ledsArray, uint16_t ledsNum) : leds{ledsArray}, ledsNumber{ledsNum} {};
        virtual void applyToLeds();
        virtual void refreshLeds();
};

#endif