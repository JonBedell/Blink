/*Dot Class
Class that sets a dot in a specific location on the LED strip
*/
class Dot {
    public:
        //location values
        int xLoc;
        int yLoc;
        bool LocUp;
        //colors (RGB)
        int Red;
        int Green;
        int Blue;
    //Constructor
    Dot(int, int, int, int, int);

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

/*     //attack
    void attack()
    {
        // indicate attack is charging
        int attackChargeTime = millis()
        for (int i=target.xLoc; i<target.xLoc+5; i++){
            leds[i] = CRGB::DarkRed;
        }
        for (int i=target.xLoc; i>target.xLoc-5; i--){
            leds[i] = CRGB::DarkRed
        }
        //indicate attack charge complete
        if attackChargeTime < 2000{
            for (int i=target.xLoc; i<target.xLoc+5; i++){
                leds[i] = CRGB::Red;
        }
        for (int i=target.xLoc; i>target.xLoc-5; i--){
                leds[i] = CRGB::Red
        }
        }
        //begin attack
        for (int i=target.xLoc; i<target.xLoc+15; i++){
            leds[i] = CRGB::White;
        }
        for (int i=target.xLoc; i>target.xLoc-15; i--){
            leds[i] = CRGB::White
        }
        }
        //end attack
        for (int i=target.xLoc; i<target.xLoc+15; i++){
             //fade to black by 25% per iteration
             leds[i].fadeToBlackBy( 64 );
        }
        for (int i=target.xLoc; i>target.xLoc-15; i--){
             leds[i].fadeToBlackBy( 64 );
        }
        }
    }    */

};
/**
 * Dot Constructor
 * @param x - location on LED strip
 * @param red - red value (0-255)
 * @param green - green value (0-255)
 * @param blue - blue value (0-255)
 * */
Dot::Dot(int x, int y, int red, int green, int blue)
{
    xLoc = x;
    yLoc = y;
    Red = red;
    Green = green;
    Blue = blue;
    LocUp = true;
}
