#include <UTFT.h>
#include <URTouch.h>
#include "utils/LedController.h"
#include <Arduino.h>
#include <math.h>
#include "utils/Controller.h"
#include "pages/StaticColorPage.h"
#include "pages/RainbowPage.h"
#include "pages/MenuPage.h"

static UTFT myGLCD(ILI9341_8, 38, 39, 40, 41);
static URTouch myTouch(6, 5, 4, 3, 2);

static Controller* controller;
static LedController* ledController;
static StaticColorPage staticColorPage;
static MenuPage menuPage;
static RainbowPage rainbowPage;

void setup()
{
  Serial.begin(9600);

  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();

  delay(500);

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);

  ledController = LedController::GetInstance();

  controller = Controller::GetInstance();

  controller->setTFT(&myGLCD);
  controller->setTouch(&myTouch);

  controller->addPage(MENU_PAGE_ID, &menuPage);
  controller->addPage(STATIC_PAGE_ID, &staticColorPage);
  controller->addPage(RAINBOW_PAGE_ID, &rainbowPage);
  controller->setNextPage(MENU_PAGE_ID);
  controller->changePage();
}

void loop()
{
  static uint16_t lastX = 0, lastY = 0;
  uint16_t x = 0, y = 0;
  static boolean touched = false;

  if (myTouch.dataAvailable())
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if (x != 0xFFFF && y != 0xFFFF)
    {
      lastX = x;
      lastY = y;
      if (!touched)
      {
        touched = true;
        InputEvent event =
        {
          .posX = lastX,
          .posY = lastY,
          .eventType = INPUT_PRESS
        };
        controller->getCurrentPage()->handleTouch(event);
      }
      else
      {
        InputEvent event =
        {
          .posX = lastX,
          .posY = lastY,
          .eventType = INPUT_HOLD
        };
        controller->getCurrentPage()->handleTouch(event);
      }
    }
  }
  else
  {
    if (touched)
    {
      touched = false;
      InputEvent event =
      {
        .posX = lastX,
        .posY = lastY,
        .eventType = INPUT_RELEASE
      };
      controller->getCurrentPage()->handleTouch(event);
    }
  }

  controller->changePage();

  ledController->refreshLeds();
}
