#include "pages/SecondMenuPage.h"

static void previousButtonFunc()
{
    Controller::GetInstance()->setNextPage(MENU_PAGE_ID);
}

static void shortTemperatureFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_TEMPERATURE);
}

static void longTemperatureFunc()
{
    LedController::GetInstance()->changeLedsEffect(LEDS_TEMPERATURE);
    Controller::GetInstance()->setNextPage(TEMPERATURE_PAGE_ID);
}

SecondMenuPage::SecondMenuPage() :
    previousButton(MENU_BUTTONS_SPACE, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Previous"),
    temperatureButton(MENU_BUTTONS_SPACE * 2 + MENU_BUTTONS_SIZE, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Temperature"),
    gradientButton(MENU_BUTTONS_SPACE * 3 + MENU_BUTTONS_SIZE * 2, MENU_BUTTONS_SPACE, MENU_BUTTONS_SIZE, MENU_BUTTONS_SIZE, "Gradient")
{
    previousButton.setPressFunction(&previousButtonFunc);
    temperatureButton.setPressFunction(&shortTemperatureFunc);
    temperatureButton.setHoldFunction(&longTemperatureFunc);
}

void SecondMenuPage::drawPage()
{
    previousButton.drawButton();
    temperatureButton.drawButton();
    gradientButton.drawButton();
}

void SecondMenuPage::handleTouch(const InputEvent &event)
{
    if (previousButton.handleButtonTouch(event))
        return;
    if (temperatureButton.handleButtonTouch(event))
        return;
    if (gradientButton.handleButtonTouch(event))
        return;
}

void SecondMenuPage::onPageChanged()
{
    InputEvent event =
    {
    .posX = 0,
    .posY = 0,
    .eventType = INPUT_RELEASE
    };
    handleTouch(event);
}
