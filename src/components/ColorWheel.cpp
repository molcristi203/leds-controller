#include "components/ColorWheel.h"

ColorWheel::ColorWheel(uint16_t posX, uint16_t posY)
{
    this->posX = posX;
    this->posY = posY;
    colorWheelCenterX = posX + COLOR_WHEEL_RADIUS;
    colorWheelCenterY = posY + COLOR_WHEEL_RADIUS;
}

void ColorWheel::setCallbackFunction(void (*callbackFunction)(uint8_t red, uint8_t green, uint8_t blue))
{
    this->callbackFunction = callbackFunction;
}

void ColorWheel::drawColorWheel()
{
    Controller* controller = Controller::GetInstance();
    UTFT* tft = controller->getTFT();
    tft->drawBitmap(posX, posY, COLOR_WHEEL_SIZE, COLOR_WHEEL_SIZE, const_cast<unsigned int*>(colorwheel), COLOR_WHEEL_SCALE);
    float wheelX = remap<float>(colorPosX, -1.0f, 1.0f, (float)posX, (float)(colorWheelCenterX + COLOR_WHEEL_RADIUS)), wheelY = remap<float>(colorPosY, -1.0f, 1.0f, (float)posY, (float)(colorWheelCenterY + COLOR_WHEEL_RADIUS));
    drawSelectCircle((uint16_t)(wheelX), (uint16_t)(wheelY));
}

void ColorWheel::drawSelectCircle(uint16_t x, uint16_t y)
{
    Controller* controller = Controller::GetInstance();

    controller->getTFT()->setColor(VGA_BLACK);
    controller->getTFT()->drawCircle(x, y, SELECT_CIRCLE_RADIUS);
}

boolean ColorWheel::selectColorFromWheel(int16_t x, int16_t y)
{
    Controller* controller = Controller::GetInstance();

    int16_t newX = x - posX - COLOR_WHEEL_RADIUS;
    int16_t newY = y - posY - COLOR_WHEEL_RADIUS;

    double length = sqrt(newX * newX + newY * newY);
    if (length < COLOR_WHEEL_RADIUS)
    {
        controller->getTFT()->drawBitmap(posX, posY, COLOR_WHEEL_SIZE, COLOR_WHEEL_SIZE, const_cast<unsigned int*>(colorwheel), COLOR_WHEEL_SCALE);

        double hue = fmod2(degrees(atan2(newX, newY)), 360.0);
        double saturation = remap<double>(length, 0.0, (double)(COLOR_WHEEL_RADIUS - 1), 0.0f, 1.0f);
        double redd = 0.0, greend = 0.0, blued = 0.0;

        HSVtoRGB(hue, saturation, 1.0, redd, greend, blued);

        uint8_t red = (uint8_t)(redd * 255);
        uint8_t green = (uint8_t)(greend * 255);
        uint8_t blue = (uint8_t)(blued * 255);

        drawSelectCircle(x, y);

        colorPosX = remap<float>(x, (float)posX, (float)(colorWheelCenterX + COLOR_WHEEL_RADIUS), -1.0f, 1.0f);
        colorPosY = remap<float>(y, (float)posY, (float)(colorWheelCenterY + COLOR_WHEEL_RADIUS), -1.0f, 1.0f);

        this->red = red;
        this->blue = blue;
        this->green = green;

        if (callbackFunction != nullptr)
        {
            (*callbackFunction)(red, green, blue);
        }

        return true;
    }
    return false;
}

void ColorWheel::setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void ColorWheel::setColorPos(float colorPosX, float colorPosY)
{
    this->colorPosX = colorPosX;
    this->colorPosY = colorPosY;
}
