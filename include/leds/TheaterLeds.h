#ifndef TheaterLeds_H
#define TheaterLeds_H

#include "BaseLeds.h"

class TheaterLeds : public BaseLeds
{
    private:
        static constexpr uint16_t ledsOnLength = 2u;
        static constexpr uint16_t ledsOffLength = 4u;
    public:
        TheaterLeds(CRGB* ledsArray, uint16_t ledsNum);
        void applyToLeds() override;
        void refreshLeds() override;
};

#endif