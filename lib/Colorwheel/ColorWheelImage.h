#pragma once

#include <avr/pgmspace.h>

#define COLOR_WHEEL_SIZE (101u)
#define COLOR_WHEEL_ARRAY_SIZE (COLOR_WHEEL_SIZE * COLOR_WHEEL_SIZE)

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned int colorwheel[COLOR_WHEEL_ARRAY_SIZE] PROGMEM;

#ifdef __cplusplus
}
#endif