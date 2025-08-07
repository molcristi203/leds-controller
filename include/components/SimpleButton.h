#ifndef SimpleButton_H
#define SimpleButton_H

#include <Arduino.h>
#include "utils/InputEvent.h"
#include <UTFT.h>
#include "utils/Controller.h"

class SimpleButton
{
    protected:
        static constexpr uint64_t BUTTON_PRESS_TIME = 100u;
        static constexpr uint32_t BUTTON_BACKGROUND_COLOR = VGA_BLUE;
        static constexpr uint32_t BUTTON_OUTLINE_COLOR = VGA_WHITE;
        static constexpr uint32_t BUTTON_HIGHLIGHT_COLOR = VGA_AQUA;
        static constexpr uint32_t BUTTON_TEXT_COLOR = VGA_WHITE;

        uint16_t posX = 0u, posY = 0u, width = 0u, height = 0u;
        const char* label = nullptr;
        boolean pressed = false;
        uint64_t pressTime = 0u;

        virtual void highlightButton();
        void (*pressFunction)(void) = nullptr;
    public:
        SimpleButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* lbl);
        virtual void drawButton();
        virtual boolean handleButtonTouch(const InputEvent &event);
        void setPressFunction(void (*pressFunction)(void));
};

#endif