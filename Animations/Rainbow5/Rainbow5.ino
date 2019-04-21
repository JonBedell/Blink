#include <FastLED.h>
#include <Animations.h>

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
