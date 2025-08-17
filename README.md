# LED Controller

This project is an LED controller based on an Arduino Mega board, which will be used to light up a room. It features a 2.4 inch touch screen display, with a resolution of 240x320px, which is used to change the settings for the LEDs. The LEDs used are WS2812B NeoPixel LEDs, which are individual addressable and can be used to create various animations. Three strips are used - two 5m strips that are connected to one another and are placed around the room, and one 1m strip that is used for a lamp.

Some of the settings for LEDs that are present on the first page include:
- Static - all the LEDs are the same color
- Rainbow - all the LEDS cycle between the rainbow collors
- Theater - a pattern of on and off leds, where multiple leds are on then the following leds are off and the pattern repeats for the rest of the strip
- Strip - is used to toggle on and off the 10m led strip
- Lamp - is used to toggle on and off the 1m led strip for the lamp

![Menu with 6 blue square buttons in a 2x3 grid](/assets/menu1.jpg)

---

The static LEDs setting offers the possibility to choose the color from a color wheel.

![RGB color wheel](/assets/static.jpg)

---

The rainbow LEDs setting allows the possibility to choose between two types of animations: static - all the leds are the same color, dynamic - each led is a different color which is at a small hue difference from the ones near it.

![Menu with 5 blue square buttons and a number in a 2x3 grid](/assets/rainbow.jpg)

---

The second menu page offers the possibility to choose between temperature and gradient(not yet implemented) settings. The temperature setting offers presets for warm and cold colors including - Candle, Tungsten, Daylight, Cloudy, Shade, based on black-body radiation.

![Menu with 3 blue square buttons](/assets/menu2.jpg)

---

The libraries used are [UTFT](http://www.rinkydinkelectronics.com/library.php?id=51), [URTouch](http://www.rinkydinkelectronics.com/library.php?id=92) and [FastLED](https://fastled.io/).