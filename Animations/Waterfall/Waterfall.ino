#include <FastLED.h>
#define PIN 1   // OUTPUT pin WS2812B LED Strip is attached to TODO: Rename to LED_PIN
#define NUM_LEDS 300 // number of LEDs per strip TODO: Rename to NUM_LEDS
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation

// map<string, int> colorPalette = new map<string, int>();
// colorPalette["red"] = CHSV(69,69,69);

CRGB leds[NUM_LEDS];
void setup() { FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS); }
void loop() {
    for(int i=0; i<NUM_LEDS; i++){
        if(i%3 ==0){
            leds[i] = CRGB::Cyan;
        }else{
            leds[i] = CRGB::Blue;
        }
    }
    FastLED.show();
    delay(delayval);
    for(int i=0; i<NUM_LEDS; i++){
        if(i%3 ==1){
            leds[i] = CRGB::Cyan;
        }else{
            leds[i] = CRGB::Blue;
        }
    }
    FastLED.show();
    delay(delayval);
    for(int i=0; i<NUM_LEDS; i++){
        if(i%3 ==2){
            leds[i] = CRGB::Cyan;
        }else{
            leds[i] = CRGB::Blue;
        }
    }
    FastLED.show();
    delay(delayval);
    // leds = CRGB::Yellow;
    // fastLED.show();
    // delay(50);
}