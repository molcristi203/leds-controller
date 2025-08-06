#include "pages/MenuPage.h"

static void shortStaticButtonFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_STATIC);
}

static void longStaticButtonFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_STATIC);
    Controller::GetInstance()->setNextPage(STATIC_PAGE_ID);
}

static void shortRainbowButtonFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_RAINBOW);
}

static void longRainbowButtonFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_RAINBOW);
    Controller::GetInstance()->setNextPage(RAINBOW_PAGE_ID);
}

static void toggleStrip()
{
    LedController::GetInstance()->toggleLedRelay1();
}

MenuPage::MenuPage() :
    staticButton(MENU_BUTTONS_SPACE, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Static"),
    rainbowButton(MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Rainbow"),
    stripToggleButton(MENU_BUTTONS_SPACE, MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Strip")
{
    staticButton.setPressFunction(&shortStaticButtonFunc);
    staticButton.setHoldFunction(&longStaticButtonFunc);
    rainbowButton.setPressFunction(&shortRainbowButtonFunc);
    rainbowButton.setHoldFunction(&longRainbowButtonFunc);
    stripToggleButton.setPressFunction(&toggleStrip);
    stripToggleButton.setSecondaryPressFunction(&toggleStrip);
}

void MenuPage::drawPage()
{
    staticButton.drawButton();
    rainbowButton.drawButton();
    stripToggleButton.drawButton();
}

void MenuPage::handleTouch(const InputEvent &event)
{
    if (staticButton.handleButtonTouch(event))
        return;
    if (rainbowButton.handleButtonTouch(event))
        return;
    if (stripToggleButton.handleButtonTouch(event))
        return;
}

void MenuPage::onPageChanged()
{
    InputEvent event =
    {
    .posX = 0,
    .posY = 0,
    .eventType = INPUT_RELEASE
    };
    handleTouch(event);
}
