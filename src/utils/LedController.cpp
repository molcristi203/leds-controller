#include "utils/LedController.h"

LedController* LedController::instance{nullptr};

LedController::LedController()
: staticLeds(leds1, NUM_STRIP_LEDS), rainbowLeds(leds1, NUM_STRIP_LEDS)
{
    FastLED.addLeds<WS2812B, PIN_STRIP_DATA, GRB>(leds1, NUM_STRIP_LEDS);
    FastLED.setBrightness(10);
    currentLeds = &staticLeds;
    currentLeds->applyToLeds();

    pinMode(PIN_STRIP_RELAY, OUTPUT);
    digitalWrite(PIN_STRIP_RELAY, relayStripState);
    pinMode(PIN_LAMP_RELAY, OUTPUT);
    digitalWrite(PIN_LAMP_RELAY, relayStripState);
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

void LedController::toggleStripRelay()
{
    if (relayStripState == LOW)
    {
        relayStripState = HIGH;
    }
    else
    {
        relayStripState = LOW;
    }
    digitalWrite(PIN_STRIP_RELAY, relayStripState);
}

void LedController::toggleLampRelay()
{
    if (relayLampState == LOW)
    {
        relayLampState = HIGH;
    }
    else
    {
        relayLampState = LOW;
    }
    digitalWrite(PIN_STRIP_RELAY, relayLampState);
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

void LedController::increaseRainbowSpeed()
{
    uint8_t index = rainbowLeds.getHueChangeDelayIndex();
    if (index < rainbowLeds.MAX_DELAYS - 1)
    {
        index++;
        rainbowLeds.setHueChangeDelayIndex(index);
    }
}

void LedController::decreaseRainbowSpeed()
{
    uint8_t index = rainbowLeds.getHueChangeDelayIndex();
    if (index > 0)
    {
        index--;
        rainbowLeds.setHueChangeDelayIndex(index);
    }
}

uint8_t LedController::getHueChangeDelayIndex()
{
    return rainbowLeds.getHueChangeDelayIndex();
}
