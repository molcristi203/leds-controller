#pragma once

#include <avr/pgmspace.h>

#define COLOR_WHEEL_SIZE (101)

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned int colorwheel[0x27D9] PROGMEM;

#ifdef __cplusplus
}
#endif