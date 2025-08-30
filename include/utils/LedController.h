#ifndef LedController_H
#define LedController_H

#include <FastLED.h>
#include <Arduino.h>
#include "Types.h"
#include "leds/BaseLeds.h"
#include "leds/StaticLeds.h"
#include "leds/RainbowLeds.h"
#include "leds/TheaterLeds.h"
#include "leds/TemperatureLeds.h"

enum LedsEffects : uint8_t
{
    LEDS_STATIC,
    LEDS_RAINBOW,
    LEDS_THEATER,
    LEDS_TEMPERATURE
};

class LedController
{
private:
    static constexpr uint8_t PIN_STRIP_RELAY = A8;
    static constexpr uint8_t PIN_STRIP_DATA = 8;
    static constexpr uint8_t PIN_LAMP_RELAY = A9;
    static constexpr uint8_t PIN_LAMP_DATA = 9;
    static constexpr uint16_t NUM_STRIP_LEDS = 600u;
    static constexpr uint16_t NUM_LAMP_LEDS = 43u;
    static constexpr uint8_t NUM_TOTAL_STRIPS = 2u;
    static constexpr uint8_t LED_BRIGHTNESS = 128u;

    CRGB ledsStrip[NUM_STRIP_LEDS];
    CRGB ledsLamp[NUM_LAMP_LEDS];

    StaticLeds staticLeds[NUM_TOTAL_STRIPS];
    RainbowLeds rainbowLeds[NUM_TOTAL_STRIPS];
    TheaterLeds theaterLeds[NUM_TOTAL_STRIPS];
    TemperatureLeds temperatureLeds[NUM_TOTAL_STRIPS];
    BaseLeds *currentLeds[NUM_TOTAL_STRIPS] = {nullptr, nullptr};

    volatile uint8_t relayStripState = LOW;
    volatile uint8_t relayLampState = LOW;

    static LedController *instance;
    LedController();
    LedController(const LedController &) = delete;
    LedController &operator=(const LedController &) = delete;

public:
    static constexpr uint8_t STRIP_INDEX = 0u;
    static constexpr uint8_t LAMP_INDEX = 1u;

    static LedController *GetInstance();

    void setStaticRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t index);
    void getStaticRGB(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t index);

    void setTemperatureRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t index);
    void getTemperatureRGB(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t index);

    void changeRainbowLedsType(RainbowTypes rainbowType, uint8_t index);

    void changeLedsEffect(LedsEffects ledsEffect, uint8_t index);
    void refreshLeds(uint8_t index);

    void toggleStripRelay();
    void toggleLampRelay();

    void increaseRainbowSpeed(uint8_t index);
    void decreaseRainbowSpeed(uint8_t index);
    uint8_t getHueChangeDelayIndex(uint8_t index);
};

#endif