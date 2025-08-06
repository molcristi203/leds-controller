#include "utils/Controller.h"

extern uint8_t SmallFont[];

Controller* Controller::instance{nullptr};

Controller::Controller()
{}

Controller* Controller::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Controller();
    }
    return instance;
}

UTFT *Controller::getTFT()
{
    return tft;
}

void Controller::setTFT(UTFT *tft)
{
    this->tft = tft;
    this->tft->setFont(SmallFont);
}

URTouch *Controller::getTouch()
{
    return touch;
}

void Controller::setTouch(URTouch *touch)
{
    this->touch = touch;
}

ScreenPage *Controller::getCurrentPage()
{
    return currentPage;
}

void Controller::setNextPage(PagesIds pageId)
{
    nextPage = pages[pageId];
}

void Controller::changePage()
{
    if (nextPage != nullptr)
    {
        if (currentPage != nullptr)
            currentPage->onPageChanged();
        currentPage = nextPage;
        nextPage = nullptr;
        tft->clrScr();
        currentPage->drawPage();
    }
}

void Controller::addPage(PagesIds pageId, ScreenPage* page)
{
    pages[pageId] = page;
}
