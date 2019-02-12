// Dot flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone to win
// Obstacles: marching ant animation zones apply force to dot in certain directions
//bombs blow up your dot
//moving targets
// Version 0.1


#include <FastLED.h>
#define LED_PIN 1   // OUTPUT pin WS2812B LED Strip is attached to
#define NUM_LEDS 300 // number of LEDs per strip
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation
#define JUMPBOOST 50

//CLASSES 

/* 
Button Class
creates an object that can read whether or not the button is pressed
*/
class Button {
//Arduino pin button is connected to
int _pin;
public:
    //Constructor
    Button(int);
    //Functions
    /**Reads the current state of the button
     * @return - HIGH(1/pressed) or LOW(0/unpressed)
     * */ 
    int read()
    {
    return digitalRead(_pin);
    }
};
/**
 * Button Constructor
 * @pin number of pin buton is connected to
 */
Button::Button(int pin)
    {
        pinMode(pin, INPUT);
        _pin = pin;
    }

/*Dot Class
Class that sets a dot in a specific locatio on the LED strip
*/
class Dot {
    public:
        //location values
        int Loc;
        int Acceleration;
        int Time;
        //colors (RGB)
        int Red;
        int Green;
        int Blue;
    //Constructor
    Dot(int, int, int, int);

    //Add acceleration to player
    void jump()
    {
        //add JUMPBOOST value to players acceleration
        Acceleration += JUMPBOOST;
        Time = 0;
    }     

};
/**
 * Dot Constructor
 * @param loc - location on LED strip
 * @param red - red value (0-255)
 * @param green - green value (0-255)
 * @param blue - blue value (0-255)
 * */
Dot::Dot(int loc, int red, int green, int blue)
{
    Loc = loc;
    Red = red;
    Green = green;
    Blue = blue;
    Acceleration = 0;
}

//Making Objects
// Buttons 
Button Up(13);
// Dots on Strip
Dot player(0,255,0,0);
Dot target(10,0,0,255);
// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = 0; 
int gameState = 0;

//LED strip
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

void checkWin();

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
    if (targetTime >= 3000) {
            for (int i=player.Loc; i>-1; i--){
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
                delay(animationDelay);
            }
    }

        //Restart game
        player.Loc = random(0,NUM_LEDS);
        target.Loc = random(0,NUM_LEDS);
    }
};

void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
    //initialize LED Strip
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
    //set player on strip
    leds[player.Loc].setRGB( player.Red, player.Green, player.Blue); // Player.
    leds[target.Loc].setRGB(target.Red, target.Green, target.Blue); // Target
    FastLED.show();
}

//Game Loop
void loop() {
    delay(delayval);

    // read the state of the pushbutton value:
    buttonUpState = Up.read();

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    // If Button is pressed, current Dot is removed, and player location is +1'd
    if (buttonUpState == HIGH) {
        // move player up:
        player.jump();
    }




    //Reset pixel locations to current locations (i.e. if Button was pressed)
    leds[player.Loc].setRGB( player.Red, player.Green, player.Blue); // Player.
    FastLED.show();
    checkWin(gameState);
    };
