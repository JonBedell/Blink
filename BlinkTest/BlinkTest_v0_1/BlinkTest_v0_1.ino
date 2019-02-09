//This file is what we use in the tinkerCAD drawing of moving the light with buttons towards a goal
//Not compatibale with tinkerCad
// Version 0.1 - We gone FastLED Test


#include <FastLED.h>
#define PIN 1   // OUTPUT pin WS2812B LED Strip is attached to TODO: Rename to LED_PIN
#define NUMPIXELS 300 // number of LEDs per strip TODO: Rename to NUM_LEDS
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation

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
        bool LocUp;
        //colors (RGB)
        int Red;
        int Green;
        int Blue;
    //Constructor
    Dot(int, int, int, int);

    //Cycles thru colors of player
    void colorCycle()
    {
        //store old color values        
        int oldBlue = Blue;
        int oldGreen = Green;
        int oldRed = Red;
        //replace color values
        Blue = oldRed;
        Green = oldBlue;
        Red = oldGreen;
    //Add more colors thru map or array or something                
    }     

//    //attack
//    void attack()
//    {
//        // indicate attack is charging
//        int attackChargeTime = millis()
//        for (int i=target.Loc; i<target.Loc+5; i++){
//            leds[i] = CRGB::DarkRed;
//        }
//        for (int i=target.Loc; i>target.Loc-5; i--){
//            leds[i] = CRGB::DarkRed
//        }
//        //indicate attack charge complete
//        if attackChargeTime < 2000{
//            for (int i=target.Loc; i<target.Loc+5; i++){
//                leds[i] = CRGB::Red;
//        }
//        for (int i=target.Loc; i>target.Loc-5; i--){
//                leds[i] = CRGB::Red
//        }
//        }
//        //begin attack
//        for (int i=target.Loc; i<target.Loc+15; i++){
//            leds[i] = CRGB::White;
//        }
//        for (int i=target.Loc; i>target.Loc-15; i--){
//            leds[i] = CRGB::White
//        }
//        }
//        //end attack
//        for (int i=target.Loc; i<target.Loc+15; i++){
//             //fade to black by 25% per iteration
//             leds[i].fadeToBlackBy( 64 );
//        }
//        for (int i=target.Loc; i>target.Loc-15; i--){
//             leds[i].fadeToBlackBy( 64 );
//        }
//        }
//    }   

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
    LocUp = true;
}

//Making Objects
// Buttons 
Button B(10);
Button A(11);
Button Right(12);
Button Up(13);
Button Left(9);
Button Down(8);
// Dots on Strip
Dot player(0,255,0,0);
Dot target(10,0,0,255);
// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = 0; 
int buttonDownState = 0;
int buttonBState = 0;
//LED strip
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUMPIXELS];

void setup() {
//??NOT SURE WHAT THIS DOES BUT IS IN A LOT OF EXAMPLE CODE??? - JON
// Serial.begin(4800);
// while (!Serial) {
//  ; // wait for serial port to connect. Needed for native USB
//}
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);
    FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUMPIXELS);
    // initialize the pushbutton pin as an input:
    //Dot player(0,255,0,0);
    //Dot target(10,0,0,255);
    leds[player.Loc].setRGB( player.Red, player.Green, player.Blue); // Player.
    leds[target.Loc].setRGB(target.Red, target.Green, target.Blue); // Player.
    //Many options for ways to set color see below
    //https://github.com/FastLED/FastLED/wiki/Controlling-leds
    FastLED.show();
}

void loop() {
    delay(delayval);

    // read the state of the pushbutton value:
    buttonUpState = Up.read();
    buttonDownState = Down.read();
    buttonBState = B.read();

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    // If Button is pressed, current Dot is removed, and player location is +1'd
    if (buttonUpState == HIGH && player.Loc < (NUMPIXELS-1)) {
        // move player up:
        leds[player.Loc] = CRGB::Black; //erase old location
        player.Loc++;
        player.LocUp = true;
    }
    buttonDownState = Down.read();
    if (buttonDownState == HIGH && player.Loc > 0) {
        // move player down:
        leds[player.Loc] = CRGB::Black; //erase old location
        player.Loc--;
        player.LocUp = false;
    }
    // Read B Button for color change
    if (buttonBState == HIGH) {
        // move player down:
        player.colorCycle();
    }

    //Reset pixel locations to current locations (i.e. if Button was pressed)
    leds[player.Loc].setRGB( player.Red, player.Green, player.Blue); // Player.
    leds[target.Loc].setRGB(target.Red, target.Green, target.Blue); // Target (not used unless target has move conditions)
    FastLED.show();

//Win state
    if (player.Loc == target.Loc) {
        if(player.LocUp)
        {
            for (int i=player.Loc; i<NUMPIXELS; i++){
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
                delay(animationDelay);
            }
            for (int i=player.Loc; i>-1; i--){
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
                delay(animationDelay);
            }
            for (int i=0; i<NUMPIXELS; i++){
                redColor = 0;
                greenColor = 0;
                blueColor = 0;
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
            }
        } else {
            for (int i=player.Loc; i>-1; i--){
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
                delay(animationDelay);
            }
            for (int i=player.Loc; i<NUMPIXELS; i++){
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
                delay(animationDelay);
            }
            for (int i=NUMPIXELS; i>-1; i--){
                redColor = 0;
                greenColor = 0;
                blueColor = 0;
                leds[i].setRGB( redColor, greenColor, blueColor);
                FastLED.show();
            }
        }

    //Restart game
    player.Loc = random(0,NUMPIXELS);
    target.Loc = random(0,NUMPIXELS);
    }
}
