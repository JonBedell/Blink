//    shrapnel.h
//library for physics affected dots with a defineable rgb value
//header file


#ifndef shrapnel_h
#define shrapnel_h

class shrapnel
{  
    public:
        shrapnel(int s_Red, int s_Green, int s_Blue, int s_Loc, int s_initialVelocity);
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
};

#endif
