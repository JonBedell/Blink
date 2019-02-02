//This file is what we use in the tinkerCAD drawing of moving the light with buttons towards a goal
// Version 0.2 - We gone OOP'd
//Link: https://www.tinkercad.com/things/1R8qPQe4sb5-led-w-buttons/editel?sharecode=Vn1hbirx4j2s2nK6gWdwb0B2oMcUVibSb7WXxpyg8gc=

#include <Adafruit_NeoPixel.h>
#define PIN 1	 // input pin Neopixel is attached to
#define NUMPIXELS 30 // number of neopixels in Ring
#define debounceTime 200

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
        //location value
        int Loc;
        //colors (RGB)
        int Red;
        int Green;
        int Blue;
    //Constructor
    Dot(int, int, int, int);
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
}

//Making Objects
// Buttons 
Button B(10);
Button A(11);
Button Right(12);
Button Up(13);
Button Left(9);
Button Down3(8);
// Dots on Strip
Dot player(0,255,0,0);
Dot target(10,0,0,255);
// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = 0; 
int buttonDownState = 0;
//LED strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // timing delay

void setup() {
//??NOT SURE WHAT THIS DOES BUT IS IN A LOT OF EXAMPLE CODE??? - JON
// Serial.begin(4800);
// while (!Serial) {
//  ; // wait for serial port to connect. Needed for native USB
//}
    // Initialize the NeoPixel library.
    pixels.begin(); 
    // initialize the pushbutton pin as an input:
    //Dot player(0,255,0,0);
    //Dot target(10,0,0,255);
    pixels.setPixelColor(player.Loc, player.Red, player.Green, player.Blue); // Player.
    pixels.setPixelColor(target.Loc, pixels.Color(target.Red, target.Green, target.Blue));
    pixels.show();
}

void loop() {


    // read the state of the pushbutton value:
    buttonUpState = Up.read();
    buttonDownState = Down.read();

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    // If Button is pressed, current Dot is removed, and player location is +1'd
    if (buttonUpState == HIGH && player.Loc < 21) {
        // move player up:
        pixels.setPixelColor(player.Loc, pixels.Color(0, 0, 0)); // erase old.
        player.Loc++;
    }
    buttonDownState = Down.read();
    if (buttonDownState == HIGH && player.Loc > 0) {
        // move player down:
        pixels.setPixelColor(player.Loc, pixels.Color(0, 0, 0)); // erase old.
        player.Loc--;
    }
    //Reset pixel locations to current locations (i.e. if Button was pressed)
    pixels.setPixelColor(player.Loc, pixels.Color(player.Red, player.Green, player.Blue)); // Player.
    pixels.setPixelColor(target.Loc, pixels.Color(target.Red, target.Green, target.Blue)); // Target.
    pixels.show();

//Win state
    if (player.Loc == target.Loc) {
        for (int i=player.Loc; i<NUMPIXELS; i++){
            int redColor = random(0,255);
            int greenColor = random(0,255);
            int blueColor = random(0,255);
            pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
            pixels.show();
            delay(50);
        }
        for (int i=player.Loc; i>-1; i--){
            int redColor = random(0,255);
            int greenColor = random(0,255);
            int blueColor = random(0,255);
            pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
            pixels.show();
            delay(50);
        }
        for (int i=0; i<NUMPIXELS; i++){
            redColor = 0;
            greenColor = 0;
            blueColor = 0;
            pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
            pixels.show();
        }

    //Restart game
    player.Loc = random(0,NUMPIXELS);
    target.Loc = random(0,NUMPIXELS);
    }
}