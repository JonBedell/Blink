#include <FastLED.h>
#include <Animations.h>

class GameOfLife : public Animation
{
    private:
        // We need 2 frames to write the changes each round
        bool frame1[NUM_STRIPS][NUM_LEDS];
        bool frame2[NUM_STRIPS][NUM_LEDS];

        // Keep pointers to the frames so we can easily swap them each round instead of copying
        bool (*lastRound)[NUM_STRIPS][NUM_LEDS] = &frame1;
        bool (*nextRound)[NUM_STRIPS][NUM_LEDS] = &frame2;

        void GoOneRound()
        {
            // swap last round with next round
            bool (*placeholder)[NUM_STRIPS][NUM_LEDS] = lastRound;
            lastRound = nextRound;
            nextRound = placeholder;

            // Calculate the next round based on the last one
            for (int strip = 0; strip < NUM_STRIPS; strip++)
            {
                for (int led = 0; led < NUM_LEDS; led++)
                {
                    int neighborsAlive = 0;
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            if (i == 0 && j == 0)
                            {
                                continue;
                            }

                            int neighborStrip = (strip + i + NUM_STRIPS) % NUM_STRIPS;
                            int neighborLED = (led + j + NUM_LEDS) % NUM_LEDS;

                            if ((*lastRound)[neighborStrip][neighborLED])
                            {
                                neighborsAlive++;
                            }
                        }
                    }

                    bool isAlive;

                    if (neighborsAlive < 2)
                    {
                        isAlive = false;
                    }
                    else if (neighborsAlive > 3)
                    {
                        isAlive = false;
                    }
                    else if (neighborsAlive == 3)
                    {
                        isAlive = true;
                    }
                    else
                    {
                        isAlive = (*lastRound)[strip][led];
                    }

                    (*nextRound)[strip][led] = isAlive;
                }
            }
        }

    public:
        void draw(CRGB (*canvas)[NUM_STRIPS][NUM_LEDS])
        {
            GoOneRound();
            
            for (int ledIndex = 0; ledIndex < NUM_LEDS; ledIndex++)
            {
                for (int stripIndex = 0; stripIndex < NUM_STRIPS; stripIndex++)
                {
                    if ((*nextRound)[stripIndex][ledIndex])
                    {
                        (*canvas)[stripIndex][ledIndex] = CRGB::Amethyst;
                    }
                    else
                    {
                        (*canvas)[stripIndex][ledIndex] = CRGB::Black;
                    }
                }
            }
        }
};