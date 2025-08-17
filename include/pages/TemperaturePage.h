#ifndef TemperaturePage_H
#define TemperaturePage_H

#include "pages/ScreenPage.h"
#include "components/SimpleButton.h"
#include "utils/LedController.h"
#include "utils/Controller.h"

class TemperaturePage : public ScreenPage
{
    private:
        static constexpr uint16_t BUTTONS_SPACE = 5;
        static constexpr uint16_t BUTTONS_SIZE = 100;

        SimpleButton color1Button;
        SimpleButton color2Button;
        SimpleButton color3Button;
        SimpleButton color4Button;
        SimpleButton color5Button;
        SimpleButton menuButton;
    public:
        TemperaturePage();
        void drawPage() override;
        void handleTouch(const InputEvent &event) override;
        void onPageChanged() override;
};

#endif