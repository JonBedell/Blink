#include <FastLED.h>

struct Canvas
{
    CRGB** leds;
    size_t stripCount;
    size_t stripLength;
};

class Animation
{
    public:
        virtual void draw(Canvas* canvas);
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
        void draw(Canvas* canvas)
        {
            for (int ledIndex = 0; ledIndex < canvas->stripLength; ledIndex++)
            {
                for (int stripIndex = 0; stripIndex < canvas->stripCount; stripIndex++)
                {
                    canvas->leds[stripIndex][ledIndex] = *getBackgroundColor(0, stripIndex, ledIndex);
                }
            }

            // Increment frame to next index
            frameIndex = (frameIndex + 1) % palletSize;
        }
}