// Version 0.1 - We gone FastLED Test
// Multi-strip initial test game
//Using an array of arrays method from here
//https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
//led pins 1-5
//button pins 8-13


#include "FastLED.h"
#define NUM_STRIPS 5
#define NUM_LEDS 300
#define STRIP1_PIN 2
#define STRIP2_PIN 3
#define STRIP3_PIN 4
#define STRIP4_PIN 5
#define STRIP5_PIN 6

#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation


// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;

//LED strip
// This is an array of an array of leds.  One item for each led in your strip.
CRGB leds[NUM_STRIPS][NUM_LEDS];

void setup() {
//??NOT SURE WHAT THIS DOES BUT IS IN A LOT OF EXAMPLE CODE??? - JON
// Serial.begin(4800);
// while (!Serial) {
//  ; // wait for serial port to connect. Needed for native USB
//}
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);

    //This initializes the LED NUM_STRIPS
    FastLED.addLeds<WS2812B, STRIP1_PIN, RGB>(leds[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP2_PIN, RGB>(leds[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP3_PIN, RGB>(leds[2], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP4_PIN, RGB>(leds[3], NUM_LEDS);
    FastLED.addLeds<WS2812B, STRIP5_PIN, RGB>(leds[4], NUM_LEDS);

    FastLED.show();
}

void loop() {
    for (int i=0;i<NUM_LEDS;i++){
        int redColor = random(0,30);
        int greenColor = random(0,30);
        int blueColor = random(0,30);
        for (int j=0;j<NUM_STRIPS;j++){
            leds[j][i].setRGB(greenColor,redColor,blueColor);
        }
        FastLED.show();
    }
    for (int i=0;i<NUM_LEDS;i++){
        int redColor = 0;
        int greenColor = 0;
        int blueColor = 0;
        for (int j=0;j<NUM_STRIPS;j++){
            leds[j][i].setRGB(greenColor,redColor,blueColor);
        }
        FastLED.show();
    }    


}
