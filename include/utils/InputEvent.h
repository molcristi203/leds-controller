#ifndef InputEvent_H
#define InputEvent_H

#include <Arduino.h>

enum EventType : uint8_t
{
    INPUT_NONE,
    INPUT_PRESS,
    INPUT_RELEASE,
    INPUT_HOLD
};

struct InputEvent
{
    uint16_t posX;
    uint16_t posY;
    EventType eventType;
};


#endif