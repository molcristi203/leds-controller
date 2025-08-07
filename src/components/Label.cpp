#include "components/Label.h"

Label::Label(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* txt)
: posX{x}, posY{y}, width{w}, height{h}
{
    strcpy(text,txt);
}

void Label::drawLabel()
{
    UTFT* tft = Controller::GetInstance()->getTFT();
    tft->setColor(LABEL_BACKGROUND_COLOR);
    tft->fillRoundRect(posX, posY, posX + width, posY + height);
    tft->setColor(LABEL_OUTLINE_COLOR);
    tft->drawRoundRect(posX, posY, posX + width, posY + height);

    uint16_t textX = ((width/2) - ((strlen(text) * tft->getFontXsize())/2)) + posX;
    uint16_t textY = (height/2) - (tft->getFontYsize()/2) + posY;

    tft->setColor(LABEL_TEXT_COLOR);
    tft->setBackColor(LABEL_BACKGROUND_COLOR);
    tft->print(text, textX, textY);
}

void Label::setLabelText(const char* text)
{
    strcpy(this->text, text);
    drawLabel();
}