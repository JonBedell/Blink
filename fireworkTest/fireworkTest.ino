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
#define NUM_FIREWORKS


#include "Firework.h"

//Making Objects 
//Firework firework[f];
//Firework firework2;
//Firework firework3;
Firework firework[NUM_FIREWORKS];

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
    leds[firework[f].Loc].setRGB(firework[f].Green,firework[f].Red,firework[f].Blue);
    //leds[firework2.Loc].setRGB(firework2.Green,firework2.Blue,firework2.Red);
    //leds[firework3.Loc].setRGB(firework3.Green,firework3.Blue,firework3.Red);

    FastLED.show(); 
}

//Game Loop
void loop() {

    //remove old fireworks & flames
    writeBackground();

for (int f = 0; f < NUM_FIREWORKS; f++){
    firework[f].Move();
    //write firework[f]
    leds[firework[f].Loc].setRGB(firework[f].Green,firework[f].Red,firework[f].Blue);
    
    if (firework[f].Exploded == false){
    writeFlame(firework[f].Loc);
    } else {
        redColor = random(0,255);
        greenColor = random(0,255);
        blueColor = random(0,255);
        leds[firework[f].Loc].setRGB(greenColor,redColor,blueColor);
        if (firework[f].burstFin == false){
            for (int i = firework[f].Loc; i < firework[f].Loc + firework[f].loopCounter; i++ ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
        for (int i = firework[f].Loc; i > firework[f].Loc - firework[f].loopCounter; i-- ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
            if (firework[f].slowDown >= 2){
                firework[f].loopCounter = firework[f].loopCounter + 1;
                firework[f].slowDown = 0;
            } else {firework[f].slowDown = firework[f].slowDown + 1;
            }
        if (firework[f].loopCounter == 12){
            firework[f].burstFin = true;
        }
        }
    }
    //reset fireworks if burst animation has completed
    if (firework[f].burstFin == true){
        firework[f].Reset();
    }
}


/*     firework2.Move();
    //write firework2
    leds[firework2.Loc].setRGB(firework2.Green,firework2.Red,firework2.Blue);
    
    if (firework2.Exploded == false){
    writeFlame(firework2.Loc);
    } else {
        redColor = random(0,255);
        greenColor = random(0,255);
        blueColor = random(0,255);
        leds[firework2.Loc].setRGB(greenColor,redColor,blueColor);
        if (firework2.burstFin == false){
            for (int i = firework2.Loc; i < firework2.Loc + firework2.loopCounter; i++ ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
        for (int i = firework2.Loc; i > firework2.Loc - firework2.loopCounter; i-- ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
            if (firework2.slowDown >= 2){
                firework2.loopCounter = firework2.loopCounter + 1;
                firework2.slowDown = 0;
            } else {firework2.slowDown = firework2.slowDown + 1;
            }
        if (firework2.loopCounter == 12){
            firework2.burstFin = true;
        }
        }
    }
    //reset fireworks if burst animation has completed
    if (firework2.burstFin == true){
        firework2.Reset();
    }




    firework3.Move();
    //write firework3
    leds[firework3.Loc].setRGB(firework3.Green,firework3.Red,firework3.Blue);
    
    if (firework3.Exploded == false){
    writeFlame(firework3.Loc);
    } else {
        redColor = random(0,255);
        greenColor = random(0,255);
        blueColor = random(0,255);
        leds[firework3.Loc].setRGB(greenColor,redColor,blueColor);
        if (firework3.burstFin == false){
            for (int i = firework3.Loc; i < firework3.Loc + firework3.loopCounter; i++ ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
        for (int i = firework3.Loc; i > firework3.Loc - firework3.loopCounter; i-- ){
                leds[i].setRGB(greenColor,redColor,blueColor);
            }
            if (firework3.slowDown >= 2){
                firework3.loopCounter = firework3.loopCounter + 1;
                firework3.slowDown = 0;
            } else {firework3.slowDown = firework3.slowDown + 1;
            }
        if (firework3.loopCounter == 12){
            firework3.burstFin = true;
        }
        }
    }
    //reset fireworks if burst animation has completed
    if (firework3.burstFin == true){
        firework3.Reset();
    } */
        FastLED.show();
        };
