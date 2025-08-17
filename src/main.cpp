#include <Arduino.h>
#include <FastLED.h>
#include <UTFT.h>
#include <URTouch.h>
#include <Colorwheel.h>
#include <math.h>

#define LEFT_OFFSET (10)
#define UP_OFFSET   (19)
#define COLOR_WHEEL_SCALE (2)
#define NUM_LEDS (10)
#define DATA_PIN (A9)

UTFT myGLCD(ILI9341_8, 38, 39, 40, 41);
URTouch myTouch(6, 5, 4, 3, 2);

boolean touched = false;

CRGB leds[NUM_LEDS];

template <typename T> T remap(T oldVal, T oldMin, T oldMax, T newMin, T newMax)
{
  return (newMax - newMin) * (oldVal - oldMin) / (oldMax - oldMin) + newMin;
}

void drawColorWheel()
{
  myGLCD.drawBitmap(LEFT_OFFSET, UP_OFFSET, COLOR_WHEEL_SIZE, COLOR_WHEEL_SIZE, const_cast<unsigned int*>(colorwheel), COLOR_WHEEL_SCALE);
}

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

boolean getColorAtPoint(int16_t x, int16_t y, uint8_t& red, uint8_t& green, uint8_t& blue)
{
  uint16_t radius = COLOR_WHEEL_SIZE * COLOR_WHEEL_SCALE / 2;
  int16_t newX = x - LEFT_OFFSET - radius;
  int16_t newY = y - UP_OFFSET - radius;

  double length = sqrt(newX * newX + newY * newY);
  if (length < radius)
  {
    double hue = fmod2(degrees(atan2(newX, newY)), 360.0);
    double saturation = remap<float>(length, 0, radius - 1, 0, 1);
    double redd = 0.0, greend = 0.0, blued = 0.0;

    HSVtoRGB(hue, saturation, 1.0, redd, greend, blued);

    red = (uint8_t)(redd * 255);
    green = (uint8_t)(greend * 255);
    blue = (uint8_t)(blued * 255);

    return true;
  }
  return false;
}

void generateColorWheel()
{
  for (uint16_t y = 0; y < COLOR_WHEEL_SIZE * COLOR_WHEEL_SCALE; y++)
  {
    for (uint16_t x = 0; x < COLOR_WHEEL_SIZE * COLOR_WHEEL_SCALE; x++)
    {
      uint8_t red = 0, green = 0, blue = 0;
      getColorAtPoint(x + LEFT_OFFSET, y + UP_OFFSET, red, green, blue);
      myGLCD.setColor(red, green, blue);
      myGLCD.drawPixel(x + LEFT_OFFSET, y + UP_OFFSET);
    }

  }

}

void ledsSetStaticColor(CRGB rgb)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = rgb;
  }
  FastLED.show();
}

void ledSetRainbow()
{
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255));
  delay(100);
}

void chooseColor(uint16_t x, uint16_t y)
{
  uint8_t red = 0, green = 0, blue = 0;
  getColorAtPoint(x, y, red, green, blue);
  myGLCD.setColor(red, green, blue);
  myGLCD.fillRect(300, 319, 200, 219);
  ledsSetStaticColor(CRGB(red, green, blue));
}

void setup()
{
  Serial.begin(9600);

  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);
  drawColorWheel();

  delay(500);

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  ledsSetStaticColor(CRGB::White);
}

void loop()
{
  // ledSetRainbow();

  if (myTouch.dataAvailable())
  {
    if (!touched)
    {
      touched = true;

      myTouch.read();
      int16_t x = myTouch.getX();
      int16_t y = myTouch.getY();

      drawColorWheel();
      myGLCD.setColor(VGA_BLACK);
      myGLCD.drawCircle(x, y, 10);
      chooseColor(x, y);
    }
  }
  else
  {
    touched = false;
  }
}
