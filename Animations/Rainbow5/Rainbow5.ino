#include <FastLED.h>
#include <Rainbow.h>

Rainbow rainbow;

void setup()
{ 
    setupLEDStrips();
}

void loop()
{
    rainbow.draw(&leds);

    showFrame();
}
