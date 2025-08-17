#ifndef Controller_H
#define Controller_H

#include <Arduino.h>
#include <UTFT.h>
#include <URTouch.h>
#include "pages/ScreenPage.h"

enum PagesIds : uint8_t
{
    MENU_PAGE_ID,
    STATIC_PAGE_ID,
    RAINBOW_PAGE_ID,
    SECOND_MENU_PAGE_ID,
    TEMPERATURE_PAGE_ID
};

class Controller
{
    private:
        static constexpr uint8_t MAX_PAGES = 5;

        UTFT* tft = nullptr;
        URTouch* touch = nullptr;

        ScreenPage* pages[MAX_PAGES];
        ScreenPage* currentPage = nullptr;
        ScreenPage* nextPage = nullptr;

        static Controller* instance;
        Controller();
        Controller(const Controller&) = delete;
        Controller& operator=(const Controller&) = delete;

    public:
        static Controller* GetInstance();

        UTFT* getTFT();
        void setTFT(UTFT* tft);

        URTouch* getTouch();
        void setTouch(URTouch* touch);

        ScreenPage* getCurrentPage();
        void setNextPage(PagesIds pageId);
        void changePage();
        void addPage(PagesIds pageId, ScreenPage* page);
};

#endif