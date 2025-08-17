#ifndef SecondMenuPage_H
#define SecondMenuPage_H

#include "ScreenPage.h"
#include "components/ComplexButton.h"
#include "components/SimpleButton.h"
#include "utils/Controller.h"
#include "utils/LedController.h"

class SecondMenuPage : public ScreenPage
{
    private:
        static constexpr uint16_t MENU_BUTTONS_SPACE = 5u;
        static constexpr uint16_t MENU_BUTTONS_SIZE = 100u;

        SimpleButton previousButton;
        ComplexButton temperatureButton;
        ComplexButton gradientButton;
    public:
        SecondMenuPage();
        void drawPage() override;
        void handleTouch(const InputEvent &event) override;
        void onPageChanged() override;
};

#endif