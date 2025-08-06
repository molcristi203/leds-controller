#include "components/ToggleButton.h"

ToggleButton::ToggleButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *lbl, uint8_t startState)
: SimpleButton(x, y, w, h, lbl), state{startState} {}

boolean ToggleButton::handleButtonTouch(const InputEvent &event)
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
                    return true;
                }
            }
            else
            {
                if (pressed)
                {
                    pressed = false;
                    drawButton();
                }
            }
            break;
        case INPUT_RELEASE:
            if ((event.posX >= posX) && (event.posX <= posX + width) && (event.posY > posY) && (event.posY < posY + height))
            {
                if (pressed)
                {
                    if (millis() - pressTime > BUTTON_PRESS_TIME)
                    {
                        if (state == TOGGLE_BUTTON_OFF)
                        {
                            if (pressFunction != nullptr)
                            {
                                (*pressFunction)();
                            }

                            state = TOGGLE_BUTTON_ON;
                        }
                        else
                        {
                            if (secondaryPressFunction != nullptr)
                            {
                                (*secondaryPressFunction)();
                            }

                            state = TOGGLE_BUTTON_OFF;
                        }
                    }
                    drawButton();
                    return true;
                    break;
                }
            }
            else
            {
                if (pressed)
                {
                    pressed = false;
                    drawButton();
                }
            }
            break;
        default:
            break;
    }

    return false;
}

void ToggleButton::setSecondaryPressFunction(void (*secondaryPressFunction)())
{
    this->secondaryPressFunction = secondaryPressFunction;
}

void ToggleButton::drawButton()
{
    UTFT* tft = Controller::GetInstance()->getTFT();
    if (state == TOGGLE_BUTTON_ON)
    {
        tft->setColor(VGA_GREEN);
        tft->setBackColor(VGA_GREEN);
    }
    else
    {
        tft->setColor(VGA_BLUE);
        tft->setBackColor(VGA_BLUE);
    }

    tft->fillRoundRect(posX, posY, posX + width, posY + height);
    tft->setColor(VGA_WHITE);
    tft->drawRoundRect(posX, posY, posX + width, posY + height);

    uint16_t textX = ((width/2) - ((strlen(label) * tft->getFontXsize())/2)) + posX;
    uint16_t textY = (height/2) - (tft->getFontYsize()/2) + posY;

    tft->print(label, textX, textY);
}

void ToggleButton::setState(uint8_t state)
{
    this->state = state;
}
