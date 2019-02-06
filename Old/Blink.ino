//Constants
const int buttonPin = 7;     
const int ledPin =  8;     

//Variables
//int flag=0;
int val = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);          // sets the digital pin 13 as output
  pinMode(buttonPin, INPUT);
}

void loop()
{
    val = digitalRead(buttonPin);
    if (val == HIGH) {
        digitalWrite(ledPin, LOW);
        //flag = 1;
    } else {
        // else if (val == LOW) {
        digitalWrite(ledPin, HIGH);
        //flag = 0;
    }
}