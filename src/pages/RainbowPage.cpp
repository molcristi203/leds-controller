#include "pages/RainbowPage.h"

static void backToMenu()
{
    Controller::GetInstance()->setNextPage(MENU_PAGE_ID);
}

static void staticRainbowFunc()
{
    LedController::GetInstance()->changeRainbowLedsType(STATIC_RAINBOW);
}

static void dynamicRainbowFunc()
{
    LedController::GetInstance()->changeRainbowLedsType(DYNAMIC_RAINBOW);
}

RainbowPage::RainbowPage()
: staticRainbowButton(RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "Static"),
dynamicRainbowButton(RAINBOW_BUTTONS_SPACE * 2 + RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "Dynamic"),
menuButton(RAINBOW_BUTTONS_SPACE * 3 + RAINBOW_BUTTONS_SIZE * 2, RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "Menu")
{
    menuButton.setPressFunction(&backToMenu);
    staticRainbowButton.setPressFunction(&staticRainbowFunc);
    dynamicRainbowButton.setPressFunction(&dynamicRainbowFunc);
}

void RainbowPage::drawPage()
{
    staticRainbowButton.drawButton();
    dynamicRainbowButton.drawButton();
    menuButton.drawButton();
}

void RainbowPage::handleTouch(const InputEvent &event)
{
    if (staticRainbowButton.handleButtonTouch(event))
    {
        return;
    }
    if (dynamicRainbowButton.handleButtonTouch(event))
    {
        return;
    }
    if (menuButton.handleButtonTouch(event))
    {
        return;
    }
}

void RainbowPage::onPageChanged()
{}