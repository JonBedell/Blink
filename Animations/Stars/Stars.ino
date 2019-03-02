#include <FastLED.h>
#define PIN 1   // OUTPUT pin WS2812B LED Strip is attached to TODO: Rename to LED_PIN
#define NUM_LEDS 300 // number of LEDs per strip TODO: Rename to NUM_LEDS
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the animation
#define spaceTime 50  //length of star blinking animation
#define starDensity 5

CRGB leds[NUM_LEDS];
CRGB twinkle[spaceTime];
int j = 1;
bool goingDown = false;

//void upAndDown(){
//  if(j==0 || j==spaceTime)
//  {
//    goingDown = !goingDown;
//  }
//  if(goingDown){
//    j++;
//  }else{
//    j--;
//  }
//}

RAND_MAX = NUM_LEDS;



void setup() {  
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS); 
  for(int i=0; i<spaceTime; i++)
  {
    int starlightValue = 200/spaceTime*i;
    //Serial.print((String)starlightValue);
    twinkle[i] = CRGB(starlightValue,starlightValue,starlightValue);
  }
}
void loop(){
  int starLocation = rand();
  
  for (int i=1; i < NUM_LEDS ; i++)
  {
    if(i==starLocation)
    {
      leds[i] = twinkle[j];
    }
  }

  //upAndDown();
  if(j==0 || j==(spaceTime-1))
  {
    goingDown = !goingDown;
  }
  if(goingDown){
    j++;
  }else{
    j--;
  }
  
  FastLED.show();
  delay(delayval);
}
