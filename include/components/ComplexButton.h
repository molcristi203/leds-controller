#ifndef ComplexButton_H
#define ComplexButton_H

#include "SimpleButton.h"

class ComplexButton : public SimpleButton
{
    private:
        static constexpr uint64_t BUTTON_HOLD_TIME = 750u;

        boolean held = false;
        void (*holdFunction)(void) = nullptr;
    public:
        ComplexButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* lbl);
        boolean handleButtonTouch(const InputEvent &event) override;
        void setHoldFunction(void (*holdFunction)(void));
};

#endif