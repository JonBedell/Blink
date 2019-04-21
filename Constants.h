#include <FastLED.h>

#define FRAME_SPEED 25 //controls the "speed" of the animation in millis

#define NUM_STRIPS 5    //number of LED strips
#define NUM_LEDS 300    //number of LEDs per strip

// LED Strip Pin Addresses
#define STRIP1_PIN 2    
#define STRIP2_PIN 3
#define STRIP3_PIN 4
#define STRIP4_PIN 5
#define STRIP5_PIN 6


//LED strip
// This is an array of an array of leds.  One item for each led in your strip.
CRGB leds[NUM_STRIPS][NUM_LEDS];

void setupLEDStrips() { 
    //FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS); 
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
   	FastLED.delay(2000);

    //This initializes the LED NUM_STRIPS
    FastLED.addLeds<WS2812B, STRIP1_PIN, RGB>(leds[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP2_PIN, RGB>(leds[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP3_PIN, RGB>(leds[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP4_PIN, RGB>(leds[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP5_PIN, RGB>(leds[4], NUM_LEDS);

    FastLED.setBrightness(50);
    FastLED.show();
}

unsigned long lastFrame = 0;
void showFrame()
{
    unsigned long frameDelta = millis() - lastFrame;

    // only wait for the time remaining on this frame
    if (frameDelta < FRAME_SPEED)
    {
        FastLED.delay(FRAME_SPEED - frameDelta);
    }
    // we've already spent longer on this frame than we ever meant to wait
    else
    {
        FastLED.show();
    }

    lastFrame = millis();
}