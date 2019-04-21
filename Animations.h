#include <FastLED.h>
#include <Constants.h>

class Animation
{
    public:
        int zIndex;
        virtual void draw(CRGB (*canvas)[NUM_STRIPS][NUM_LEDS]);
};