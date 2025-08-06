#ifndef Utils_H
#define Utils_H

#include <math.h>

double fmod2(double x, double y);
void HSVtoRGB(double hue, double saturation, double value, double& red, double& green, double& blue);
template <typename T> T remap(T oldVal, T oldMin, T oldMax, T newMin, T newMax)
{
  return (newMax - newMin) * (oldVal - oldMin) / (oldMax - oldMin) + newMin;
}

#endif