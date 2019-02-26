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
#define MASS 2
#define GRAVITY 15
#define THRUST 200
#define FPS 60

#include "Rocket.h"
#include "Shrapnel.h"
#include "Button.h"
#include "Target.h"


//Making Objects 
Button Up(13); //Buttons go here
Rocket player(0,0,0,255); //the player 
Target target(100,15,55,0,0); //the target

// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = 0; 
int gameState = 0;
long time = millis();

//LED strip
CRGB leds[NUM_LEDS]; // This is an array of leds.  One item for each led in your strip.

void checkWin() {
    if(gameState == 0) {
        // do nothing
    } else if (gameState == 2) {
        // Lose state
        //change this to a fill
        for (int i = 0; i < NUM_LEDS; i++){
            leds[i].setRGB( 255, 0, 0);
            FastLED.show();
            delay(animationDelay);
        }

        //Restart game
        player.Loc = random(0,NUM_LEDS);
        target.Loc = random(0,NUM_LEDS);

    } else if (gameState == 1) {
        //Win state
        //initialize a few variables for the win animation
        int upDot = target.Loc + .5 * target.Height;
        int downDot = target.Loc + .5 * target.Height;
        int upFin = 0;
        int downFin = 0;
        // two way color fill across entire strip 
        //we freeze right here...
        while (upFin + downFin != 2){
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
        for (int i = 0; i < NUM_LEDS; i++){
        leds[i].setRGB(0,0,0);
        }
        //Restart game
        target.Loc = random(0,100)+100;
        target.Height = random(0,15)+5;
        target.Step = target.Height/6;
        player.Velocity = 0;
        player.oldVelocity = 0;
        player.Acceleration = 0;
        player.oldAcceleration = 0;
    writeTarget();
    FastLED.show();   
    gameState = 0; 
    }
}

void writeTarget() // Target fill
    {
    for (int i = target.Loc+1; i < target.Loc + target.Height; i++){
        leds[i].setRGB(10, 0, 0); 
    }
    //fill interior as target time is reached
    if (target.inTarget == true){
    if (millis() - target.Time > 500){
            for (int i = target.Loc+1; i < target.Loc + target.Step; i++){
                leds[i].setRGB(target.Green, target.Red, target.Blue); 
            }
            for (int i = target.Loc + target.Height; i > target.Loc + target.Height - target.Step; i--){
                leds[i].setRGB(target.Green, target.Red, target.Blue); 
            }
    }
    if (millis() - target.Time > 1500){
            for (int i = target.Loc+1; i < target.Loc + 2 * target.Step; i++){
                leds[i].setRGB(target.Green, target.Red, target.Blue); 
            }
            for (int i = target.Loc + target.Height; i > target.Loc + target.Height - 2 * target.Step; i--){
                leds[i].setRGB(target.Green, target.Red, target.Blue); 
            }
    }
    if (millis() - target.Time > 2500){
            for (int i = target.Loc+1; i < target.Loc + target.Height; i++){
                leds[i].setRGB(target.Green, target.Red, target.Blue); 
            }
    }
    }
    // Target bookends
    leds[target.Loc].setRGB(target.Green, target.Red, target.Blue); 
    leds[target.Loc+target.Height].setRGB(target.Green,target.Red, target.Blue);
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
    leds[player.Loc].setRGB( player.Green, player.Red, player.Blue); // Player.
    writeTarget();
    FastLED.show();    
    //FastLED.setMaxRefreshRate(FPS);
}

//Game Loop
void loop() {
    time = millis();
     // read the state of the pushbutton value:
    buttonUpState = Up.read();
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    // If Button is pressed, current Dot is removed, and player location is +1'd
    if (buttonUpState == HIGH) {
        // move player up:
        player.Boost();
        }
    if (buttonUpState == LOW){
        player.endBoost();
        }
    
    player.Move();

    if (player.Exploded == true){
        for (int i = NUM_LEDS; i > NUM_LEDS - 15; i--){
            redColor = 255;
            leds[i].setRGB( 0, redColor, 0);
            FastLED.show();
            redColor = redColor - 17;
            delay(animationDelay);
        }
        for (int j = 10; j > 0; j--){
            for (int i = NUM_LEDS; i > NUM_LEDS - 15; i--){
                leds[i].fadeToBlackBy( 64 );
                FastLED.show();
                delay(animationDelay-5);
            }
        }
        for (int i = NUM_LEDS; i > NUM_LEDS - 15; i--){
            leds[i].setRGB( 0, 0, 0);
        }
        player.Exploded = false;
    }

    if (player.Loc > target.Loc && player.Loc < target.Loc + target.Height && target.inTarget == false) {
        target.inTarget = true;
        target.Time = millis();
        }

    if (player.Loc < target.Loc || player.Loc > target.Loc + target.Height) {
        target.inTarget = false;
         }
    
    if (target.inTarget == true && millis() - target.Time > 3000) {
        gameState = 1;
        }


    leds[player.oldLoc].setRGB(0,0,0);// Remove old player dots
    writeTarget(); //displays target
    leds[player.Loc].setRGB( player.Green, player.Red, player.Blue); // Player.

    FastLED.show();
    checkWin();

    //Serial prints for debugging


 /*    Serial.print(player.Loc);  // prints a label
    Serial.print("\t");         // prints a tab

    Serial.print(player.oldLoc);  // prints a label
    Serial.print("\t");         // prints a tab

    Serial.print(player.Location);
    Serial.print("\t");

    Serial.print(player.Acceleration);
    Serial.print("\t");

    Serial.print(player.Velocity);
    Serial.print("\t");

    Serial.print(player.Thrust);
    Serial.print("\t");

    Serial.print(player.Time-player.oldTime);
    Serial.println(); */


    };
