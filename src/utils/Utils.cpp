#include "utils/Utils.h"

double fmod2(double x, double y)
{
  double r = fmod(x, y);
  if (r < 0) r += y;
  return r;
}

void HSVtoRGB(double hue, double saturation, double value, double& red, double& green, double& blue)
{
  double maxim = value;
  double chroma = saturation * value;
  double minim = maxim - chroma;
  double huep;

  if (hue >= 300.0)
  {
    huep = (hue - 360.0) / 60.0;
  }
  else
  {
    huep = hue / 60.0;
  }

  if (huep < 1)
  {
    if (huep < 0)
    {
      red = maxim;
      green = minim;
      blue = green - huep * chroma;
    }
    else
    {
      red = maxim;
      blue = minim;
      green = blue + huep * chroma;
    }
  }
  else if (huep < 3)
  {
    if (huep - 2 < 0)
    {
      green = maxim;
      blue = minim;
      red = blue - (huep - 2) * chroma;
    }
    else
    {
      red = minim;
      green = maxim;
      blue = red + (huep - 2) * chroma;
    }
  }
  else
  {
    if (huep - 4 < 0)
    {
      red = minim;
      blue = maxim;
      green = red - (huep - 4) * chroma;
    }
    else
    {
      green = minim;
      blue = maxim;
      red = green + (huep - 4) * chroma;
    }
  }
}
