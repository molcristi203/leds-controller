#ifndef RainbowLeds_H
#define RainbowLeds_H

#include "BaseLeds.h"

enum RainbowTypes : uint8_t
{
    STATIC_RAINBOW,
    DYNAMIC_RAINBOW
};

class RainbowLeds : public BaseLeds
{
    private:
        static constexpr uint8_t hueIncrement = 3;
        static constexpr uint8_t deltaHue = 3;
        static constexpr uint64_t hueChangeDelay = 100;

        uint8_t initialHue = 0;
        uint64_t hueChangeTime = 0;
        RainbowTypes rainbowType = STATIC_RAINBOW;
    public:
        RainbowLeds(CRGB* ledsArray, uint16_t ledsNum);
        void applyToLeds() override;
        void refreshLeds() override;
        void changeRainbowType(RainbowTypes rainbowType);
};

#endif