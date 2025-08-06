#include "pages/StaticColorPage.h"

static void colorCallback(uint8_t red, uint8_t green, uint8_t blue)
{
    LedController::GetInstance()->setStaticRGB(red, green, blue);
}

static void backToMenu()
{
    Controller::GetInstance()->setNextPage(MENU_PAGE_ID);
}

StaticColorPage::StaticColorPage() :
    colorWheel(0, 19),
    menuButton(220, 19, 60, 60, "Menu")
{
    colorWheel.setCallbackFunction(&colorCallback);
    menuButton.setPressFunction(&backToMenu);
}

void StaticColorPage::drawPage()
{
    colorWheel.drawColorWheel();
    menuButton.drawButton();
}

void StaticColorPage::handleTouch(const InputEvent &event)
{
    if (event.eventType == INPUT_PRESS)
    {
        if (colorWheel.selectColorFromWheel(event.posX, event.posY))
        {
            return;
        }
    }

    if (menuButton.handleButtonTouch(event))
    {
        return;
    }
}

void StaticColorPage::onPageChanged()
{
    InputEvent event =
    {
    .posX = 0,
    .posY = 0,
    .eventType = INPUT_RELEASE
    };
    handleTouch(event);
}
