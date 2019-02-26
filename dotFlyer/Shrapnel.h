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
        void kill();
        float Location;
        float Velocity;
        float Acceleration;
    //constructor
    Shrapnel(int);    
};

Shrapnel::Shrapnel(int s_Loc)
{
    Red = random(0,255);
    Green = random(0,255);
    Blue = random(0,255);
    Loc = s_Loc;
    Velocity = random(0,200) - 100;
    Acceleration = 0;
    Location = s_Loc;
}

void Shrapnel::move()
{

}

void Shrapnel::kill()
{
    
}
