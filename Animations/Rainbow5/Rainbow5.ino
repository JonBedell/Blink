#include <FastLED.h>
#define PIN 1   // OUTPUT pin WS2812B LED Strip is attached to TODO: Rename to LED_PIN
#define NUM_LEDS 300 // number of LEDs per strip TODO: Rename to NUM_LEDS
#define debounceTime 200 // keep those button inputs clean
#define NUM_STRIPS 5    //number of LED strips
#define NUM_LEDS 300    //number of LEDs per strip
#define STRIP1_PIN 2    
#define STRIP2_PIN 3
#define STRIP3_PIN 4
#define STRIP4_PIN 5
#define STRIP5_PIN 6

#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation

//LED strip
// This is an array of an array of leds.  One item for each led in your strip.
CRGB leds[NUM_STRIPS][NUM_LEDS];

//Color Library for Rainbow
CRGB rainbows[14] = {
  CRGB::Red,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Indigo,
  CRGB::Violet,
  CRGB::Red,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Indigo,
  CRGB::Violet
};
//int iterator = 0;
int iterators[NUM_STRIPS];


void setup() { 
    //FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS); 
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);

    //Populate iterator array
    for(int i=0; i<NUM_STRIPS; i++){
        iterators[i]=i;
    }

    //This initializes the LED NUM_STRIPS
    FastLED.addLeds<WS2812B, STRIP1_PIN, RGB>(leds[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP2_PIN, RGB>(leds[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP3_PIN, RGB>(leds[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP4_PIN, RGB>(leds[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP5_PIN, RGB>(leds[4], NUM_LEDS);

    FastLED.setBrightness( 50 );
    FastLED.show();
}
void loop(){
    for (int i=0; i < NUM_LEDS ; i++)
    {
        leds[0][i] = rainbows[(i%7)+iterators[0]];
        leds[1][i] = rainbows[(i%7)+iterators[1]];
        leds[2][i] = rainbows[(i%7)+iterators[2]];
        leds[3][i] = rainbows[(i%7)+iterators[3]];
        leds[4][i] = rainbows[(i%7)+iterators[4]];
    }
    for(int i=0; i < NUM_STRIPS ; i++){
        if (iterators[i] < 6)
        {
            iterators[i]++;
        }
        else
        {
            iterators[i] = 0;
        }
    }
    FastLED.show();
    delay(delayval);
}
