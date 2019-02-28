//    Shrapnel.h
//library for physics affected dots with a defineable rgb value

#define MASS 2
#define GRAVITY 15
#define THRUST 200
#define FPS 60

class Shrapnel
{  
    public:
        int Red;
        int Green;
        int Blue;
        int Loc;
        int initialVelocity;
        void move();
        float Location;
        float Velocity;
        float Acceleration; 
        int Mass;
        float oldLocation;
        int oldLoc;
        float oldAcceleration;
        float oldVelocity;
        float oldTime;
        float Time;
        Shrapnel();

        void Move()
{
    oldTime = Time;
    Time = millis();
    oldLoc = Loc;
    oldVelocity = Velocity;
    oldLocation = Location;
    oldAcceleration = Acceleration;

    //Equations
    Acceleration = MASS - GRAVITY;
    Velocity = oldVelocity + ((Time - oldTime)/1000) * Acceleration;
    Location = oldLocation + (.5 * (Velocity + oldVelocity)) * ((Time - oldTime)/1000);

    //shrapnel is on ground & needs to be deleted somehow
    if (Location < 0) {
        Location = 0;
        Acceleration = 0;
        oldAcceleration = 0;
        Velocity = 0;
        oldVelocity = 0;
    }


    //shrapnel has bounced off ceiling
    if (Location > NUM_LEDS - 1 ) {
        Location = NUM_LEDS - 1;
        Acceleration = 0;
        oldAcceleration = 0;
        Velocity = -0.7 * Velocity;
        oldVelocity = -0.7 * Velocity;
    }
    Loc = (int)Location;
}


};

Shrapnel::Shrapnel()
{
    Red = random(0,255);
    Green = random(0,255);
    Blue = random(0,255);
    Loc = 0;
    Velocity = random(0,200) - 100;
    Acceleration = 0;
    Location = 0;
    Time = millis();
}

