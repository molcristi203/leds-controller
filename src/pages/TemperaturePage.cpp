#include "pages/TemperaturePage.h"

static void color1ButtonFunc()
{
    LedController::GetInstance()->setTemperatureRGB(255, 147, 41);
}

static void color2ButtonFunc()
{
    LedController::GetInstance()->setTemperatureRGB(255, 187, 120);
}

static void color3ButtonFunc()
{
    LedController::GetInstance()->setTemperatureRGB(255, 238, 227);
}

static void color4ButtonFunc()
{
    LedController::GetInstance()->setTemperatureRGB(235, 238, 255);
}

static void color5ButtonFunc()
{
    LedController::GetInstance()->setTemperatureRGB(214, 225, 255);
}

static void menuButtonFunc()
{
    Controller::GetInstance()->setNextPage(MENU_PAGE_ID);
}

TemperaturePage::TemperaturePage() :
    color1Button(BUTTONS_SPACE, BUTTONS_SPACE, BUTTONS_SIZE, BUTTONS_SIZE, "Candle"),
    color2Button(BUTTONS_SPACE * 2 + BUTTONS_SIZE, BUTTONS_SPACE, BUTTONS_SIZE, BUTTONS_SIZE, "Tungsten"),
    color3Button(BUTTONS_SPACE, BUTTONS_SPACE * 2 + BUTTONS_SIZE, BUTTONS_SIZE, BUTTONS_SIZE, "Daylight"),
    color4Button(BUTTONS_SPACE * 2 + BUTTONS_SIZE, BUTTONS_SPACE * 2 + BUTTONS_SIZE, BUTTONS_SIZE, BUTTONS_SIZE, "Cloudy"),
    color5Button(BUTTONS_SPACE * 3 + BUTTONS_SIZE * 2, BUTTONS_SPACE, BUTTONS_SIZE, BUTTONS_SIZE, "Shade"),
    menuButton(BUTTONS_SPACE * 3 + BUTTONS_SIZE * 2, BUTTONS_SPACE * 2 + BUTTONS_SIZE, BUTTONS_SIZE, BUTTONS_SIZE, "Menu")
{
    color1Button.setPressFunction(&color1ButtonFunc);
    color2Button.setPressFunction(&color2ButtonFunc);
    color3Button.setPressFunction(&color3ButtonFunc);
    color4Button.setPressFunction(&color4ButtonFunc);
    color5Button.setPressFunction(&color5ButtonFunc);
    menuButton.setPressFunction(&menuButtonFunc);
}

void TemperaturePage::drawPage()
{
    color1Button.drawButton();
    color2Button.drawButton();
    color3Button.drawButton();
    color4Button.drawButton();
    color5Button.drawButton();
    menuButton.drawButton();
}

void TemperaturePage::handleTouch(const InputEvent &event)
{
    if (color1Button.handleButtonTouch(event))
        return;
    if (color2Button.handleButtonTouch(event))
        return;
    if (color3Button.handleButtonTouch(event))
        return;
    if (color4Button.handleButtonTouch(event))
        return;
    if (color5Button.handleButtonTouch(event))
        return;
    if (menuButton.handleButtonTouch(event))
        return;
}

void TemperaturePage::onPageChanged()
{
    InputEvent event =
    {
    .posX = 0,
    .posY = 0,
    .eventType = INPUT_RELEASE
    };
    handleTouch(event);
}