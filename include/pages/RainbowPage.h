#ifndef RainbowPage_H
#define RainbowPage_H

#include "ScreenPage.h"
#include "components/SimpleButton.h"
#include "utils/LedController.h"
#include "components/Label.h"

class RainbowPage : public ScreenPage
{
    private:
        static constexpr uint16_t RAINBOW_BUTTONS_SPACE = 5;
        static constexpr uint16_t RAINBOW_BUTTONS_SIZE = 100;

        SimpleButton staticRainbowButton;
        SimpleButton dynamicRainbowButton;
        SimpleButton menuButton;
        SimpleButton decreaseSpeedButton;
        SimpleButton increaseSpeedButton;
        Label speedLabel;
    public:
        RainbowPage();
        void drawPage() override;
        void handleTouch(const InputEvent &event) override;
        void onPageChanged() override;
        void updateLabel();
};

#endif