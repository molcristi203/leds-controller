#ifndef ToggleButton_H
#define ToggleButton_H

#include "SimpleButton.h"

#define TOGGLE_BUTTON_OFF (0U)
#define TOGGLE_BUTTON_ON (1U)

class ToggleButton : public SimpleButton
{
    private:
        static constexpr uint32_t BUTTON_TOGGLE_COLOR = VGA_GREEN;

        uint8_t state = TOGGLE_BUTTON_OFF;
        void (*secondaryPressFunction)();
    public:
        ToggleButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* lbl, uint8_t startState = TOGGLE_BUTTON_OFF);
        boolean handleButtonTouch(const InputEvent &event) override;
        void setSecondaryPressFunction(void (*secondaryPressFunction)());
        void drawButton() override;
        void setState(uint8_t state);
};

#endif