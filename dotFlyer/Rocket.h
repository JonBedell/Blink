//Rocket Class
//Class that sets a dot in a specific locatio on the LED strip

#define MASS 2
#define GRAVITY 15
#define THRUST 200

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
        }

        void endBoost()
        {
            Thrust = 0;
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

            //rocket has slammed into ground and exploded
            if (Location <= 0 && Velocity > 100) {
                Exploded = true;
                Location = 0;
                Acceleration = 0;
                oldAcceleration = 0;
                Velocity = 0;
                oldVelocity = 0;
            }

            //rocket has bounced off ground
            if (Location <= 0 && Velocity < 100) {
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
