#ifndef MenuPage_H
#define MenuPage_H

#include "ScreenPage.h"
#include "utils/Controller.h"
#include "components/ComplexButton.h"
#include "components/ToggleButton.h"
#include "utils/LedController.h"

class MenuPage : public ScreenPage
{
    private:
        static const uint16_t MENU_BUTTONS_SPACE = 5u;
        static const uint16_t MENU_BUTTONS_SIZE = 100u;

        ComplexButton staticButton;
        ComplexButton rainbowButton;
        ToggleButton stripToggleButton;
        ToggleButton lampToggleButton;
    public:
        MenuPage();
        void drawPage() override;
        void handleTouch(const InputEvent &event) override;
        void onPageChanged() override;
};

#endif