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
#define THRUST 15
#define GRAVITY 10

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

/*Rocket Class
Class that sets a dot in a specific locatio on the LED strip
*/
class Rocket {
    public:
        //location values
        int Loc;
        int Mass;
        int Height;
        //colors (RGB)
        int Red;
        int Green;
        int Blue;
        int Thrust;

        int Boost()
        {
            Thrust = THRUST;
        }

        int endBoost()
        {
            Thrust = 0;
        }
    //Constructor
    Rocket(int, int, int, int);
};
/**
 * Rocket Constructor
 * @param loc - location on LED strip
 * @param red - red value (0-255)
 * @param green - green value (0-255)
 * @param blue - blue value (0-255)
 * */
Rocket::Rocket(int loc, int red, int green, int blue)
{
    Loc = loc;
    Mass = 100;
    Height = 1; //change this later to be adjustable
    Red = red;
    Green = green;
    Blue = blue;
    Thrust = 0;
}

/*Target Class
Class that sets a series of dots in a specific location on the LED strip
*/

class Target {
    public:
        int Loc;
        int Height;
        int Red;
        int Green;
        int Blue;
        int Time;
        bool inTarget;

        //Constructor
        Target(int,int,int,int,int);
};
Target::Target(int loc, int height, int red, int green, int blue)
{
    Loc = loc;
    Height = height;
    Red = red;
    Green = green;
    Blue = blue;
    Time = 0;
    inTarget = false;
    }

//Making Objects
// Buttons 
Button Up(13);
// Dots on Strip
Rocket player(0,255,0,0);
Target target(200,10,0,0,155);
// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = 0; 
int gameState = 0;
long time = 0;


//heatmap palette to be used for rocket exhaust
DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     0,  0,  0,   //black
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

CRGBPalette16 heatPalette = heatmap_gp;

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
              for (int i=player.Loc; i>-1; i--){
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
                delay(animationDelay);
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
    for (int i = target.Loc; i < target.Loc + target.Height; i++){
        leds[i].setRGB(target.Red, target.Green, target.Blue); // Target
    }
    
    FastLED.show();
    time = millis();
}

//Game Loop
void loop() {
     // read the state of the pushbutton value:
    buttonUpState = Up.read();
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    // If Button is pressed, current Dot is removed, and player location is +1'd
    if (buttonUpState == HIGH) {
        // move player up:
        player.Boost();
        }

    player.Loc = player.Loc + (((player.Thrust - GRAVITY) * (time * time))/player.Mass);
    if (player.Loc < 0) {
        player.Loc = 0;
    }

    if (player.Loc > target.Loc && player.Loc < target.Loc + target.Height && target.inTarget == false) {
        target.inTarget = true;
        target.Time = millis();
    }

    if (player.Loc < target.Loc && player.Loc > target.Loc + target.Height) {
        target.inTarget = false;
        target.Time = 0;
    }
    
    if (target.inTarget == true && millis() - target.Time > 3000) {
        gameState = 1;
    }

    //Reset pixel locations to current locations (i.e. if Button was pressed)
    leds[player.Loc].setRGB( player.Red, player.Green, player.Blue); // Player.
    FastLED.show();
    checkWin();
    player.endBoost();
    time = millis();
    };
