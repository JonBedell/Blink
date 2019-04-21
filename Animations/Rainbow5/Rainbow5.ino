#include <FastLED.h>
#include <Animations.h>

#define debounceTime 200 // keep those button inputs clean

// LED Strip Pin Addresses
#define STRIP1_PIN 2    
#define STRIP2_PIN 3
#define STRIP3_PIN 4
#define STRIP4_PIN 5
#define STRIP5_PIN 6

#define NUM_COLORS 7    //number of colors in da rainbow :)

#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation

//LED strip
// This is an array of an array of leds.  One item for each led in your strip.
CRGB leds[NUM_STRIPS][NUM_LEDS];

Rainbow rainbow;

void setup() { 
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

void loop(){
    rainbow.draw(&leds);

    FastLED.show();
    FastLED.delay(delayval);
}