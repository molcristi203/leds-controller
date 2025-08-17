#ifndef TemperatureLeds_H
#define TemperatureLeds_H

#include "BaseLeds.h"
#include "utils/Types.h"

class TemperatureLeds : public BaseLeds
{
    private:
        RGBstruct rgb = {
            .red = 255u,
            .green = 255u,
            .blue = 255u
        };
    public:
        TemperatureLeds(CRGB* ledsArray, uint16_t ledsNum);
        void setRGB(uint8_t red, uint8_t green, uint8_t blue);
        void getRGB(uint8_t &red, uint8_t &green, uint8_t &blue);
        void applyToLeds() override;
        void refreshLeds() override;
};

#endif