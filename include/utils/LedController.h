#ifndef LedController_H
#define LedController_H

#include <FastLED.h>
#include <Arduino.h>
#include "Types.h"
#include "leds/BaseLeds.h"
#include "leds/StaticLeds.h"
#include "leds/RainbowLeds.h"

enum LedsEffects : uint8_t
{
    LEDS_STATIC,
    LEDS_RAINBOW
};

class LedController
{
    private:
        static constexpr uint8_t PIN_STRIP_RELAY = A8;
        static constexpr uint8_t PIN_STRIP_DATA = 8;
        static constexpr uint8_t PIN_LAMP_RELAY = A9;
        static constexpr uint8_t PIN_LAMP_DATA = 9;
        static constexpr uint16_t NUM_STRIP_LEDS = 20;

        CRGB leds1[NUM_STRIP_LEDS];

        StaticLeds staticLeds;
        RainbowLeds rainbowLeds;
        BaseLeds* currentLeds = nullptr;

        volatile uint8_t relayStripState = LOW;
        volatile uint8_t relayLampState = LOW;

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

        void toggleStripRelay();
        void toggleLampRelay();

        void increaseRainbowSpeed();
        void decreaseRainbowSpeed();
        uint8_t getHueChangeDelayIndex();
};

#endif