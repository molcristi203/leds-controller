#include "components/SimpleButton.h"

SimpleButton::SimpleButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *lbl)
: posX{x}, posY{y}, width{w}, height{h}, label{lbl} {}

void SimpleButton::drawButton()
{
    UTFT* tft = Controller::GetInstance()->getTFT();
    tft->setColor(BUTTON_BACKGROUND_COLOR);
    tft->fillRoundRect(posX, posY, posX + width, posY + height);
    tft->setColor(BUTTON_OUTLINE_COLOR);
    tft->drawRoundRect(posX, posY, posX + width, posY + height);

    uint16_t textX = ((width/2) - ((strlen(label) * tft->getFontXsize())/2)) + posX;
    uint16_t textY = (height/2) - (tft->getFontYsize()/2) + posY;

    tft->setColor(BUTTON_TEXT_COLOR);
    tft->setBackColor(BUTTON_BACKGROUND_COLOR);
    tft->print(label, textX, textY);
}

boolean SimpleButton::handleButtonTouch(const InputEvent &event)
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
                        if (pressFunction != nullptr)
                        {
                            (*pressFunction)();
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

void SimpleButton::setPressFunction(void (*pressFunction)(void))
{
    this->pressFunction = pressFunction;
}

void SimpleButton::highlightButton()
{
    UTFT* tft = Controller::GetInstance()->getTFT();
    tft->setColor(BUTTON_HIGHLIGHT_COLOR);
    tft->fillRoundRect(posX, posY, posX + width, posY + height);
    tft->setColor(BUTTON_TEXT_COLOR);
    tft->drawRoundRect(posX, posY, posX + width, posY + height);

    uint16_t textX = ((width/2) - ((strlen(label) * tft->getFontXsize())/2)) + posX;
    uint16_t textY = (height/2) - (tft->getFontYsize()/2) + posY;

    tft->setBackColor(BUTTON_HIGHLIGHT_COLOR);
    tft->print(label, textX, textY);
}
