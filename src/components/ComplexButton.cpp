#include "components/ComplexButton.h"

ComplexButton::ComplexButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* lbl)
: SimpleButton(x, y, w, h, lbl)
{}

boolean ComplexButton::handleButtonTouch(const InputEvent &event)
{
    switch (event.eventType)
    {
        case INPUT_PRESS:
            if ((event.posX >= posX) && (event.posX <= posX + width) && (event.posY > posY) && (event.posY < posY + height))
            {
                pressed = true;
                pressTime = millis();
                highlightButton();
                return true;
            }
            break;
        case INPUT_HOLD:
            if ((event.posX >= posX) && (event.posX <= posX + width) && (event.posY > posY) && (event.posY < posY + height))
            {
                if (pressed)
                {
                    if ((millis() - pressTime > BUTTON_HOLD_TIME) && (!held))
                    {
                        if (holdFunction != nullptr)
                        {
                            (*holdFunction)();
                            drawButton();
                            held = true;
                        }
                    }
                    return true;
                }
            }
            else
            {
                if (pressed || held)
                {
                    pressed = false;
                    held = false;
                    drawButton();
                }
            }
            break;
        case INPUT_RELEASE:
            if ((event.posX >= posX) && (event.posX <= posX + width) && (event.posY > posY) && (event.posY < posY + height))
            {
                if (pressed)
                {
                    if ((millis() - pressTime < BUTTON_HOLD_TIME || holdFunction == nullptr) && (millis() - pressTime > BUTTON_PRESS_TIME))
                    {
                        if (pressFunction != nullptr)
                        {
                            (*pressFunction)();
                        }
                    }
                    held = false;
                    drawButton();
                    return true;
                    break;
                }
            }
            else
            {
                if (pressed || held)
                {
                    pressed = false;
                    held = false;
                    drawButton();
                }
            }
            break;
        default:
            break;
    }

    return false;
}

void ComplexButton::setHoldFunction(void (*holdFunction)(void))
{
    this->holdFunction = holdFunction;
}