//    Shrapnel.h
//library for physics affected dots with a defineable rgb value

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
    private:
        float Location;
        float Velocity;
        float Acceleration;
    //constructor
    Shrapnel(int, int, int, int, int);    
};

Shrapnel::Shrapnel(int s_Red, int s_Green, int s_Blue, int s_Loc, int s_initialVelocity)
{
    Red = s_Red;
    Green = s_Green;
    Blue = s_Blue;
    Loc = s_Loc;
    Velocity = s_initialVelocity;
    Acceleration = 0;
    Location = s_Loc;
}

void Shrapnel::move()
{

}

void Shrapnel::kill()
{
    
}
