#include "utils/LedController.h"

LedController* LedController::instance{nullptr};

LedController::LedController()
: staticLeds(leds1, NUM_LEDS1), rainbowLeds(leds1, NUM_LEDS1)
{
    FastLED.addLeds<WS2812B, PIN_LED_DATA1, GRB>(leds1, NUM_LEDS1);
    FastLED.setBrightness(10);
    currentLeds = &staticLeds;
    currentLeds->applyToLeds();
    pinMode(PIN_LED_RELAY1, OUTPUT);
    digitalWrite(PIN_LED_RELAY1, relay1State);
}

LedController* LedController::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new LedController();
    }
    return instance;
}

void LedController::setStaticRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    staticLeds.setRGB(red, green, blue);
    staticLeds.applyToLeds();
}

void LedController::getStaticRGB(uint8_t &red, uint8_t &green, uint8_t &blue)
{
    staticLeds.getRGB(red, green, blue);
}

void LedController::toggleLedRelay1()
{
    if (relay1State == LOW)
    {
        relay1State = HIGH;
    }
    else
    {
        relay1State = LOW;
    }

    Serial.println(relay1State);
    digitalWrite(PIN_LED_RELAY1, relay1State);
}

void LedController::changeLedsEffect(LedsEffects ledsEffect)
{
    switch (ledsEffect)
    {
        case LEDS_STATIC:
            currentLeds = &staticLeds;
            break;
        case LEDS_RAINBOW:
            currentLeds = &rainbowLeds;
            break;
        default:
            break;
    }
    currentLeds->applyToLeds();
}

void LedController::refreshLeds()
{
    currentLeds->refreshLeds();
}

void LedController::changeRainbowLedsType(RainbowTypes rainbowType)
{
    rainbowLeds.changeRainbowType(rainbowType);
}
