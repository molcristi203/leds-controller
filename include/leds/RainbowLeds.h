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
    public:
        static constexpr uint8_t MAX_DELAYS = 3u;
        RainbowLeds(CRGB* ledsArray, uint16_t ledsNum);
        void applyToLeds() override;
        void refreshLeds() override;
        void changeRainbowType(RainbowTypes rainbowType);
        uint8_t getHueChangeDelayIndex();
        void setHueChangeDelayIndex(uint8_t hueChangeDelayIndex);

    private:
        static constexpr uint8_t HUE_INCREMENT = 3u;
        static constexpr uint8_t DELTA_HUE = 3u;
        uint64_t HUE_CHANGE_DELAYS[MAX_DELAYS] = {75u, 50u, 25u};

        uint8_t initialHue = 0u;
        uint64_t hueChangeTime = 0u;
        uint8_t hueChangeDelayIndex = 1u;
        RainbowTypes rainbowType = STATIC_RAINBOW;
};

#endif