class Firework {
    public:
        //location values
        int Loc;
        int Height; //picel height where the firework explodes
        int Speed; //pixels per second
        //colors (RGB)
        int Red;
        int Green;
        int Blue;
        bool Exploded;
        bool burstFin;
        int explodeFrame;
        long Time;
        long oldTime;

    void Move()
    {
        if (Exploded == false){
        oldTime = Time;
        Time = millis();
        Loc = Loc + Speed * (Time - oldTime);
        if (Loc >= Height){
            Exploded = true;
            }
        }
    }

    void Reset()
    {
        Loc = 0;
        Speed = random(1,20);
        Height = random(0,200)+50;
        Red = random(0,255);
        Green = random(0,255);
        Blue = random(0,255);
        Exploded = false;
        explodeFrame = -1;
        burstFin = false;
    }

    //Constructor
    Firework();
};
/**
 * Firework Constructor
 * @param loc - location on LED strip
 * @param red - red value (0-255)
 * @param green - green value (0-255)
 * @param blue - blue value (0-255)
 * */
Firework::Firework()
{
    explodeFrame = -1;
    Loc = 0;
    Speed = random(1,20);
    Height = random(0,200)+50;
    Red = random(0,255);
    Green = random(0,255);
    Blue = random(0,255);
    Exploded = false;    
    burstFin = false;
}


 /*     int upDot = target.Loc + .5 * target.Height;
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
            } */