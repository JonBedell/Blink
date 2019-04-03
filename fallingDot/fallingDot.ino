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

//CLASSES 
#include "Button.h"
#include "Dot.h"

// Buttons 
Button B(10);
Button A(11);
Button Right(12);
Button Up(13);
Button Left(9);
Button Down(8);

// Dots on Strip
Dot player(3,0,255,0,0);
Dot target(3,20,0,0,255);

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
    // initialize the pushbutton pin as an input:
    //Dot player(0,255,0,0);
    //Dot target(10,0,0,255);
    leds[player.xLoc][player.yLoc].setRGB( player.Red, player.Green, player.Blue); // Player.
    leds[target.xLoc][target.yLoc].setRGB(target.Red, target.Green, target.Blue); // Player.
    //Many options for ways to set color see below
    //https://github.com/FastLED/FastLED/wiki/Controlling-leds
    FastLED.show();
}

void loop() {
    delay(delayval);

    // read the state of the pushbutton value:
    Up.read();
    Down.read();
    Left.read();
    Right.read();
    A.read();
    B.read();

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    // If Button is pressed, current Dot is removed, and player location is +1'd
    if (Up.State == HIGH && player.yLoc < (NUM_LEDS-1)) {
        // move player up:
        leds[player.xLoc][player.yLoc] = CRGB::Black; //erase old location
        player.yLoc++;
        player.LocUp = true;
    }
    buttonDownState = Down.read();
    if (Down.State == HIGH && player.yLoc > 0) {
        // move player down:
        leds[player.xLoc][player.yLoc] = CRGB::Black; //erase old location
        player.yLoc--;
        player.LocUp = false;
    }
    if (Left.State == HIGH && player.xLoc > 0) {
        // move player down:
        leds[player.xLoc][player.yLoc] = CRGB::Black; //erase old location
        player.XLoc--;
        player.LocUp = false;
    }
    if (Right.State == HIGH && player.xLoc > NUM_STRIPS-1) {
        // move player down:
        leds[player.xLoc][player.yLoc] = CRGB::Black; //erase old location
        player.XLoc++;
        player.LocUp = false;
    }        
    // Read B Button for color change
    if (B.State == HIGH) {
        // move player down:
        player.colorCycle();
    }

 //Draw pixels
    leds[player.xLoc][player.yLoc].setRGB( player.Red, player.Green, player.Blue); // Player.
    leds[target.xLoc][target.yLoc].setRGB(target.Red, target.Green, target.Blue); // Target (not used unless target has move conditions)
    FastLED.show();

//Win state
    if (player.Loc == target.Loc) {
        int upDot = target.Loc + .5 * target.Height;
        int downDot = target.Loc + .5 * target.Height;
        int upFin = 0;
        int downFin = 0;
        // two way color fill across entire strip 
        while (upFin + downFin != 2)
            {
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                if (upFin == 0){
                    leds[upDot].setRGB( greenColor, redColor, blueColor);
                    FastLED.show();
                    upDot = upDot + 1;
                    if (upDot > NUM_LEDS){
                        upFin = 1;
                    }
                }
                if (downFin == 0){
                    leds[downDot].setRGB( greenColor, redColor, blueColor);
                    FastLED.show();
                    downDot = downDot - 1;
                    if (downDot < 0){
                        downFin = 1; 
                    }
                }

                //delay(animationDelay);
        }

    //Restart game
    player.xLoc = random(0,NUM_LEDS-1);
    player.yLoc = random(0,NUM_STRIPS-1);   
    target.xLoc = random(0,NUM_STRIPS-1); 
    target.yLoc = random(0,NUM_LEDS-1);
    }
}
