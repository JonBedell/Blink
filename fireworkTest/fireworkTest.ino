// Dot flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone and land to win
// Graph of expected outputs can be found here
// https://docs.google.com/spreadsheets/d/1KmZhmGb0J_XdEv5SdoHkTPB8KuGs9kxIDECwj5WWMT0/edit#gid=1271681145
// Version 0.1


#include <FastLED.h>

#define LED_PIN 1   // OUTPUT pin WS2812B LED Strip is attached to input is GRB not RGB
#define NUM_LEDS 300 // number of LEDs per strip
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 10 //controls the speed of the win animation


#include "Firework.h"

//Making Objects 
Firework firework1;
//Firework firework2;
//Firework firework3;

//LED strip
CRGB leds[NUM_LEDS]; // This is an array of leds.  One item for each led in your strip.

// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int loopCounter = 0;
int flame1 = 0;
int flame2 = 0;
int flame3 = 0;
int flame4 = 0;

void writeFlameAway(int boostLoc){
    flame1 = boostLoc - 1;
    flame2 = boostLoc - 2;
    flame3 = boostLoc - 3;
    flame4 = boostLoc - 4; 
    leds[flame1].setRGB(0,0,0);
    leds[flame2].setRGB(0,0,0);
    leds[flame3].setRGB(0,0,0);
    leds[flame4].setRGB(0,0,0);  
} 

void writeFlame(int boostLoc){
    flame1 = boostLoc - 1;
    flame2 = boostLoc - 2;
    flame3 = boostLoc - 3;
    flame4 = boostLoc - 4; 
    leds[flame1].setRGB(150,150,0);
    leds[flame2].setRGB(30,100,0);
    leds[flame3].setRGB(5,40,0);
    leds[flame4].setRGB(0,10,0);
}

void initializeBackground()
    {
        CRGB bgColor[NUM_LEDS];
        blueColor = 100;
        for (int i = 0; i < 50; i++){
            bgColor[i].setRGB(0,0,blueColor);
        }
        for (int i = 50; i < 150; i++){
            bgColor[i].setRGB(0,0,blueColor);
            blueColor = blueColor - 1;
        }
        for (int i = 150; i < NUM_LEDS; i++){
            bgColor[i].setRGB(0,0,0);
    }

void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
    {
    if( cur == target) return;
    
    if( cur < target ) {
        uint8_t delta = target - cur;
        delta = scale8_video( delta, amount);
        cur += delta;
    } else {
        uint8_t delta = cur - target;
        delta = scale8_video( delta, amount);
        cur -= delta;
    }
    }

CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
    {
    nblendU8TowardU8( cur.red,   target.red,   amount);
    nblendU8TowardU8( cur.green, target.green, amount);
    nblendU8TowardU8( cur.blue,  target.blue,  amount);
    return cur;
    }

void fadeTowardColor( CRGB* L, uint16_t N, const CRGB& bgColor, uint8_t fadeAmount)
    {
    for( uint16_t i = 0; i < N; i++) {
        fadeTowardColor( L[i], bgColor, fadeAmount);
    }
    }

void writeBackground()
    {
        blueColor = 100;
        for (int i = 0; i < 50; i++){
            leds[i].setRGB(0,0,blueColor);
        }
        for (int i = 50; i < 150; i++){
            leds[i].setRGB(0,0,blueColor);
            blueColor = blueColor - 1;
        }
        for (int i = 150; i < NUM_LEDS; i++){
            leds[i].setRGB(0,0,0);
        }
    }



void setup() {
    //Serial.begin(9600);
    //while (!Serial) {
    //    ; // wait for serial port to connect. Needed for native USB
    //}
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
    //initialize LED Strip
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
    //set player on strip
    
    writeBackground();
    leds[firework1.Loc].setRGB(firework1.Green,firework1.Red,firework1.Blue);
    //leds[firework2.Loc].setRGB(firework2.Green,firework2.Blue,firework2.Red);
    //leds[firework3.Loc].setRGB(firework3.Green,firework3.Blue,firework3.Red);

    FastLED.show(); 
}

//Game Loop
void loop() {

    //remove old fireworks & flames
    writeBackground();

    //firework 1
    firework1.Move();
    leds[firework1.Loc].setRGB(firework1.Green,firework1.Red,firework1.Blue);
    if (firework1.Exploded == false){
    writeFlame(firework1.Loc);
    }

    FastLED.show();
    //set frame at which explosion occurs
  
    //burst animations

    if (firework1.Exploded == true){
        int redColor = random(0,255);
        int greenColor = random(0,255);
        int blueColor = random(0,255);
        leds[firework1.Loc].setRGB(greenColor,redColor,blueColor);
        if (firework1.burstFin == false){
            for (int i = firework1.Loc; i < firework1.Loc + 20; i++ ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
        for (int i = firework1.Loc; i > firework1.Loc - 20; i-- ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
        firework1.burstFin = true;
        }
    }
    

    FastLED.show();

    //reset fireworks if burst animation has completed
    if (firework1.burstFin == true){
        firework1.Reset();
    }
        };
