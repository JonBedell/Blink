#include <FastLED.h>
#define PIN 1   // OUTPUT pin WS2812B LED Strip is attached to TODO: Rename to LED_PIN
#define NUM_LEDS 300 // number of LEDs per strip TODO: Rename to NUM_LEDS
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation

// map<string, int> colorPalette = new map<string, int>();
// colorPalette["red"] = CHSV(69,69,69);

CRGB leds[NUM_LEDS];
// CRGB rainbows[7];
// rainbows[0] = CRGB::Red;
// rainbows[1] = CRGB::Orange;
// rainbows[2] = CRGB::Yellow;
// rainbows[3] = CRGB::Green;
// rainbows[4] = CRGB::Blue;
// rainbows[5] = CRGB::Indigo;
// rainbows[6] = CRGB::Violet;
int iterator = 0;

void setup() { 
    FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS); 
    
}
void loop()
{
    for (int i = iterator; i < NUM_LEDS; i+7)
    {
        leds[i] = CRGB::Red;
        leds[i+1] = CRGB::Orange;
        leds[i+2] = CRGB::Yellow;
        leds[i+3] = CRGB::Green;
        leds[i+4] = CRGB::Blue;
        leds[i+5] = CRGB::Indigo;
        leds[i+6] = CRGB::Violet;
    }
    if (iterator < 6)
    {
        iterator++;
    }
    else
    {
        iterator = 0;
    }
}