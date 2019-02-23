// Dot flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone to win
// Obstacles: marching ant animation zones apply force to dot in certain directions
// bombs blow up your dot
// moving targets
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
        float Location;
        float oldLocation;
        int oldLoc;
        float Thrust;
        float Velocity;
        float Acceleration;
        float oldAcceleration;
        float oldVelocity;
        float oldThrust;
        float oldTime;
        float Time;
        bool Exploded;

        void Boost()
        {
            Thrust = THRUST;
            Red = 255;
            Blue = 0;
        }

        void endBoost()
        {
            Thrust = 0;
            Red = 0;
            Blue = 255;
        }

        void Move()
        {
            oldTime = Time;
            Time = millis();
            oldLoc = Loc;
            oldThrust = Thrust;
            oldVelocity = Velocity;
            oldLocation = Location;
            oldAcceleration = Acceleration;

            //Equations
            //Acceleration [A] = (.5 * (Thrust + Previous Thrust))/mass-gravity
            Acceleration = ( .5 * (Thrust + oldThrust))/ Mass - GRAVITY;
            //will essentially be one of 3 values:
            //                  no thrust Acceleration = -GRAVITY
            //                  thrust initializing or ending = about 40% max thrust
            //                  full thrust = 100% thrust

            //Velocity [V] = Vp + delta T/1000 * Acceleration [A]
            //equation is for seconds millis() returns an unsigned long in milliseconds
            Velocity = oldVelocity + ((Time - oldTime)/1000) * Acceleration;
            //needs to be min limited to 0 when position = 0
            //should probably have a terminal velocity since we only have 300px to work with

            //Position [Y] = Position Previous [Yp] + 0.5 * (Velocity [V] + Velocity Previous [Vp]) * delta T
            Location = oldLocation + (.5 * (Velocity + oldVelocity)) * ((Time - oldTime)/1000);
            //needs to be min limited to 0

            //rocket is on ground
            if (Location < 0) {
                Location = 0;
                Acceleration = 0;
                oldAcceleration = 0;
                Velocity = 0;
                oldVelocity = 0;
            }
            //rocket has slammed into ceiling and exploded
            if (Location > NUM_LEDS - 1 && Velocity > 100) {
                Exploded = true;
                Location = 0;
                Acceleration = 0;
                oldAcceleration = 0;
                Velocity = 0;
                oldVelocity = 0;
            }

            //rocket has bounced off ceiling
            if (Location > NUM_LEDS - 1 && Velocity < 100) {
                Location = NUM_LEDS - 1;
                Acceleration = 0;
                oldAcceleration = 0;
                Velocity = -0.7 * Velocity;
                oldVelocity = -0.7 * Velocity;
            }
            // if (Loc == 0) {
            //     Acceleration = 0;
            // }
            Loc = (int)Location;
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
Rocket::Rocket(int loc, int green, int red, int blue)
{
    Loc = loc;
    Mass = MASS;
    Height = 1; //change this later to be adjustable
    Red = red;
    Green = green;
    Blue = blue;
    Thrust = 0;
    Velocity = 0;
    Acceleration = 0;
    Exploded = false;
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
Target::Target(int loc, int height, int green, int red, int blue)
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
Rocket player(0,0,0,255);
Target target(100,15,55,0,0);
// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = 0; 
int gameState = 0;
long time = millis();


// //heatmap palette to be used for rocket exhaust
// DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
//   0,     0,  0,  0,   //black
// 128,   255,  0,  0,   //red
// 224,   255,255,  0,   //bright yellow
// 255,   255,255,255 }; //full white

// CRGBPalette16 heatPalette = heatmap_gp;

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
                leds[i].setRGB( greenColor, redColor, blueColor);
                FastLED.show();
                //delay(animationDelay);
            }
  

        //Restart game
        player.Loc = 0;
        player.Location = 0;
        target.Loc = random(0,100)+100;
        target.Height = random(0,15)+5;
    }
};

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
    for (int i = target.Loc; i < target.Loc + target.Height; i++){
        leds[i].setRGB(target.Green, target.Red, target.Blue); // Target
    }
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
    if (target.inTarget == true){
        leds[player.oldLoc].setRGB(target.Green,target.Red,target.Blue);
    }
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
