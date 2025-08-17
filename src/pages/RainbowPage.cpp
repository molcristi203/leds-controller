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

static void increaseSpeedFunc()
{
    LedController::GetInstance()->increaseRainbowSpeed();
}

static void decreaseSpeedFunc()
{
    LedController::GetInstance()->decreaseRainbowSpeed();
}

RainbowPage::RainbowPage()
: staticRainbowButton(RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "Static"),
dynamicRainbowButton(RAINBOW_BUTTONS_SPACE * 2 + RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "Dynamic"),
menuButton(RAINBOW_BUTTONS_SPACE * 3 + RAINBOW_BUTTONS_SIZE * 2, RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "Menu"),
decreaseSpeedButton(RAINBOW_BUTTONS_SPACE, RAINBOW_BUTTONS_SPACE * 2 + RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "-"),
increaseSpeedButton(RAINBOW_BUTTONS_SPACE * 3 + RAINBOW_BUTTONS_SIZE * 2, RAINBOW_BUTTONS_SPACE * 2 + RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "+"),
speedLabel(RAINBOW_BUTTONS_SPACE * 2 + RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SPACE * 2 + RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, RAINBOW_BUTTONS_SIZE, "2")

{
    menuButton.setPressFunction(&backToMenu);
    staticRainbowButton.setPressFunction(&staticRainbowFunc);
    dynamicRainbowButton.setPressFunction(&dynamicRainbowFunc);
    increaseSpeedButton.setPressFunction(&increaseSpeedFunc);
    decreaseSpeedButton.setPressFunction(&decreaseSpeedFunc);
}

void RainbowPage::drawPage()
{
    staticRainbowButton.drawButton();
    dynamicRainbowButton.drawButton();
    menuButton.drawButton();
    decreaseSpeedButton.drawButton();
    increaseSpeedButton.drawButton();
    speedLabel.drawLabel();
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
    if (increaseSpeedButton.handleButtonTouch(event))
    {
        updateLabel();
        return;
    }
    if (decreaseSpeedButton.handleButtonTouch(event))
    {
        updateLabel();
        return;
    }
}

void RainbowPage::onPageChanged()
{
    InputEvent event =
    {
    .posX = 0,
    .posY = 0,
    .eventType = INPUT_RELEASE
    };
    handleTouch(event);
}

void RainbowPage::updateLabel()
{
    unsigned int newIndex = LedController::GetInstance()->getHueChangeDelayIndex() + 1u;
    char newLabel[Label::MAX_LABEL_LENGTH] = {0};
    snprintf(newLabel, Label::MAX_LABEL_LENGTH, "%u", newIndex);
    speedLabel.setLabelText(newLabel);
}