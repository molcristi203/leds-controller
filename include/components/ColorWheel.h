#ifndef ColorWheel_H
#define ColorWheel_H

#include <ColorWheelImage.h>
#include "utils/Controller.h"
#include "utils/Utils.h"

#define SELECT_CIRCLE_RADIUS (10)

class ColorWheel
{
    private:
        static constexpr uint8_t COLOR_WHEEL_SCALE = 2u;
        static constexpr uint8_t COLOR_WHEEL_RADIUS = COLOR_WHEEL_SIZE * COLOR_WHEEL_SCALE / 2u;

        uint8_t red = 0u, green = 0u, blue = 0u;
        uint16_t colorWheelCenterX = 0u, colorWheelCenterY = 0u;
        uint16_t posX = 0u, posY = 0u;
        float colorPosX = 0.0f, colorPosY = 0.0f;

        void (*callbackFunction)(uint8_t red, uint8_t green, uint8_t blue) = nullptr;
        void drawSelectCircle(uint16_t x, uint16_t y);
    public:
        ColorWheel(uint16_t posX, uint16_t posY);
        void setCallbackFunction(void (*callbackFunction)(uint8_t red, uint8_t green, uint8_t blue));
        void drawColorWheel();
        boolean selectColorFromWheel(int16_t x, int16_t y);
        void setRGB(uint8_t red, uint8_t green, uint8_t blue);
        void setColorPos(float colorPosX, float colorPosY);
};

#endif