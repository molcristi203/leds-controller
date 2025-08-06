#ifndef ScreenPage_H
#define ScreenPage_H

#include <UTFT.h>
#include <URTouch.h>
#include "utils/InputEvent.h"

class ScreenPage
{
    public:
        virtual void drawPage();
        virtual void handleTouch(const InputEvent &event);
        virtual void onPageChanged();
};

#endif