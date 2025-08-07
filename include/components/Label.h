#ifndef Label_H
#define Label_H

#include "Arduino.h"
#include <UTFT.h>
#include "utils/Controller.h"

class Label
{
    public:
        static constexpr uint8_t MAX_LABEL_LENGTH = 32;

        Label(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* txt);
        void drawLabel();
        void setLabelText(const char* text);
    private:
        static constexpr uint32_t LABEL_BACKGROUND_COLOR = VGA_BLACK;
        static constexpr uint32_t LABEL_OUTLINE_COLOR = VGA_BLACK;
        static constexpr uint32_t LABEL_TEXT_COLOR = VGA_WHITE;

        char text[MAX_LABEL_LENGTH] = {0};
        uint16_t posX = 0u, posY = 0u, width = 0u, height = 0u;
};

#endif