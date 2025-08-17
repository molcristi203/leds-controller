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
    LedController::GetInstance()->toggleStripRelay();
}

static void toggleLamp()
{
    LedController::GetInstance()->toggleLampRelay();
}

static void theaterButtonFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_THEATER);
}

static void nextButtonFunc()
{
    Controller::GetInstance()->setNextPage(SECOND_MENU_PAGE_ID);
}

MenuPage::MenuPage() :
    staticButton(MENU_BUTTONS_SPACE, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Static"),
    rainbowButton(MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Rainbow"),
    stripToggleButton(MENU_BUTTONS_SPACE, MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Strip"),
    lampToggleButton(MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Lamp"),
    theaterButton(MENU_BUTTONS_SPACE * 3 + MENU_BUTTONS_SIZE * 2, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Theater"),
    nextButton(MENU_BUTTONS_SPACE * 3 + MENU_BUTTONS_SIZE * 2, MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Next")
{
    staticButton.setPressFunction(&shortStaticButtonFunc);
    staticButton.setHoldFunction(&longStaticButtonFunc);
    rainbowButton.setPressFunction(&shortRainbowButtonFunc);
    rainbowButton.setHoldFunction(&longRainbowButtonFunc);
    stripToggleButton.setPressFunction(&toggleStrip);
    stripToggleButton.setSecondaryPressFunction(&toggleStrip);
    lampToggleButton.setPressFunction(&toggleLamp);
    lampToggleButton.setSecondaryPressFunction(&toggleLamp);
    theaterButton.setPressFunction(&theaterButtonFunc);
    nextButton.setPressFunction(&nextButtonFunc);
}

void MenuPage::drawPage()
{
    staticButton.drawButton();
    rainbowButton.drawButton();
    stripToggleButton.drawButton();
    lampToggleButton.drawButton();
    theaterButton.drawButton();
    nextButton.drawButton();
}

void MenuPage::handleTouch(const InputEvent &event)
{
    if (staticButton.handleButtonTouch(event))
        return;
    if (rainbowButton.handleButtonTouch(event))
        return;
    if (stripToggleButton.handleButtonTouch(event))
        return;
    if (lampToggleButton.handleButtonTouch(event))
        return;
    if (theaterButton.handleButtonTouch(event))
        return;
    if (nextButton.handleButtonTouch(event))
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
