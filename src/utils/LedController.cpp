#include "utils/LedController.h"

LedController *LedController::instance{nullptr};

LedController::LedController() : staticLeds{StaticLeds(ledsStrip, NUM_STRIP_LEDS),
                                            StaticLeds(ledsLamp, NUM_LAMP_LEDS)},
                                 rainbowLeds{RainbowLeds(ledsStrip, NUM_STRIP_LEDS),
                                             RainbowLeds(ledsLamp, NUM_LAMP_LEDS)},
                                 theaterLeds{TheaterLeds(ledsStrip, NUM_STRIP_LEDS),
                                             TheaterLeds(ledsLamp, NUM_LAMP_LEDS)},
                                 temperatureLeds{TemperatureLeds(ledsStrip, NUM_STRIP_LEDS),
                                                 TemperatureLeds(ledsLamp, NUM_LAMP_LEDS)}

{
    pinMode(PIN_STRIP_RELAY, OUTPUT);
    digitalWrite(PIN_STRIP_RELAY, relayStripState);
    pinMode(PIN_LAMP_RELAY, OUTPUT);
    digitalWrite(PIN_LAMP_RELAY, relayLampState);

    delay(200);

    FastLED.addLeds<WS2812B, PIN_STRIP_DATA, GRB>(ledsStrip, NUM_STRIP_LEDS);
    FastLED.addLeds<WS2812B, PIN_LAMP_DATA, GRB>(ledsStrip, NUM_LAMP_LEDS);
    FastLED.setBrightness(LED_BRIGHTNESS);

    currentLeds[STRIP_INDEX] = &staticLeds[STRIP_INDEX];
    currentLeds[STRIP_INDEX]->applyToLeds();

    currentLeds[LAMP_INDEX] = &staticLeds[LAMP_INDEX];
    currentLeds[LAMP_INDEX]->applyToLeds();
}

LedController *LedController::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new LedController();
    }
    return instance;
}

void LedController::setStaticRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t index)
{
    staticLeds[index].setRGB(red, green, blue);
    staticLeds[index].applyToLeds();
}

void LedController::getStaticRGB(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t index)
{
    staticLeds[index].getRGB(red, green, blue);
}

void LedController::setTemperatureRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t index)
{
    temperatureLeds[index].setRGB(red, green, blue);
    temperatureLeds[index].applyToLeds();
}

void LedController::getTemperatureRGB(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t index)
{
    temperatureLeds[index].getRGB(red, green, blue);
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
    delay(200);
    currentLeds[STRIP_INDEX]->applyToLeds();
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
    digitalWrite(PIN_LAMP_RELAY, relayLampState);
    delay(200);
    currentLeds[LAMP_INDEX]->applyToLeds();
}

void LedController::changeLedsEffect(LedsEffects ledsEffect, uint8_t index)
{
    switch (ledsEffect)
    {
    case LEDS_STATIC:
        currentLeds[index] = &staticLeds[index];
        break;
    case LEDS_RAINBOW:
        currentLeds[index] = &rainbowLeds[index];
        break;
    case LEDS_THEATER:
        currentLeds[index] = &theaterLeds[index];
        break;
    case LEDS_TEMPERATURE:
        currentLeds[index] = &temperatureLeds[index];
    default:
        break;
    }
    currentLeds[index]->applyToLeds();
}

void LedController::refreshLeds(uint8_t index)
{
    currentLeds[index]->refreshLeds();
}

void LedController::changeRainbowLedsType(RainbowTypes rainbowType, uint8_t index)
{
    rainbowLeds[index].changeRainbowType(rainbowType);
}

void LedController::increaseRainbowSpeed(uint8_t index)
{
    uint8_t indexLoop = rainbowLeds[index].getHueChangeDelayIndex();
    if (indexLoop < rainbowLeds[index].MAX_DELAYS - 1)
    {
        indexLoop++;
        rainbowLeds[index].setHueChangeDelayIndex(index);
    }
}

void LedController::decreaseRainbowSpeed(uint8_t index)
{
    uint8_t indexLoop = rainbowLeds[index].getHueChangeDelayIndex();
    if (indexLoop > 0)
    {
        indexLoop--;
        rainbowLeds[index].setHueChangeDelayIndex(index);
    }
}

uint8_t LedController::getHueChangeDelayIndex(uint8_t index)
{
    return rainbowLeds[index].getHueChangeDelayIndex();
}
