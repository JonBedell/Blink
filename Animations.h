#include <FastLED.h>
#include <Constants.h>

class Animation
{
    public:
        int zIndex;
        virtual void draw(CRGB (*canvas)[NUM_STRIPS][NUM_LEDS]);
};


class Rainbow : public Animation
{
    private:
        static const int palletSize = 7;
        const CRGB rainbows[palletSize] = {
            CRGB::Red,
            CRGB::Orange,
            CRGB::Yellow,
            CRGB::Green,
            CRGB::Blue,
            CRGB::Indigo,
            CRGB::Violet
        };

        int frameIndex = 0;

        const CRGB* getBackgroundColor(int frame, int strip, int led)
        {
            int colorIndex = (led + frame + strip) % palletSize;
            return &rainbows[colorIndex];
        }

    public:
        void draw(CRGB (*canvas)[NUM_STRIPS][NUM_LEDS])
        {
            for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++)
            {
                for (int stripIndex = 0; stripIndex < NUM_STRIPS; stripIndex++)
                {
                    (*canvas)[stripIndex][ledIndex] = *getBackgroundColor(frameIndex, stripIndex, ledIndex);
                }
            }

            // Increment frame to next index
            frameIndex = (frameIndex + 1) % palletSize;
        }
};