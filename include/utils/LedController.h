#ifndef LedController_H
#define LedController_H

#include <FastLED.h>
#include <Arduino.h>
#include "Types.h"
#include "leds/BaseLeds.h"
#include "leds/StaticLeds.h"
#include "leds/RainbowLeds.h"

#define PIN_LED_RELAY1 A8
#define PIN_LED_DATA1 8
#define NUM_LEDS1 20

enum LedsEffects : uint8_t
{
    LEDS_STATIC,
    LEDS_RAINBOW
};

class LedController
{
    private:
        CRGB leds1[NUM_LEDS1];

        StaticLeds staticLeds;
        RainbowLeds rainbowLeds;
        BaseLeds* currentLeds = nullptr;

        volatile uint8_t relay1State = LOW;

        static LedController* instance;
        LedController();
        LedController(const LedController&) = delete;
        LedController& operator=(const LedController&) = delete;
    public:
        static LedController* GetInstance();

        void setStaticRGB(uint8_t red, uint8_t green, uint8_t blue);
        void getStaticRGB(uint8_t &red, uint8_t &green, uint8_t &blue);

        void changeRainbowLedsType(RainbowTypes rainbowType);

        void changeLedsEffect(LedsEffects ledsEffect);
        void refreshLeds();

        void toggleLedRelay1();
};

#endif