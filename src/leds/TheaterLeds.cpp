#include "leds/TheaterLeds.h"

TheaterLeds::TheaterLeds(CRGB* ledsArray, uint16_t ledsNum)
: BaseLeds(ledsArray, ledsNum) {};

void TheaterLeds::applyToLeds()
{
    uint16_t i = 0, j = 0;
    boolean ledOn = true;
    while (i < ledsNumber)
    {
        if (ledOn)
        {
            if (j < ledsOnLength)
            {
                leds[i] = CRGB::White;
                i++;
                j++;
            }
            else
            {
                ledOn = false;
                j = 0;
            }
        }
        else
        {
            if (j < ledsOffLength)
            {
                leds[i] = CRGB::Black;
                i++;
                j++;
            }
            else
            {
                ledOn = true;
                j = 0;
            }
        }
    }
    FastLED.show();
}

void TheaterLeds::refreshLeds()
{

}