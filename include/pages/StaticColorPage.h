#ifndef StaticColorPage_H
#define StaticColorPage_H

#include "pages/ScreenPage.h"
#include "components/ColorWheel.h"
#include "components/SimpleButton.h"
#include "utils/LedController.h"

class StaticColorPage : public ScreenPage
{
    private:
        ColorWheel colorWheel;
        SimpleButton menuButton;
    public:
        StaticColorPage();
        void drawPage() override;
        void handleTouch(const InputEvent &event) override;
        void onPageChanged() override;
};

#endif