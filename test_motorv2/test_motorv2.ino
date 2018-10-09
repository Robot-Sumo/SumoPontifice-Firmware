/*
 Debounce

 Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 a minimum delay between toggles to debounce the circuit (i.e. to ignore
 noise).

 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached from pin 2 to +5V
 * 10K resistor attached from pin 2 to ground

 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components for this example.


 created 21 November 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Limor Fried
 modified 28 Dec 2012
 by Mike Walters
 modified 30 Aug 2016
 by Arturo Guadalupi


 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Debounce
 */

// constants won't change. They're used here to
// set pin numbers:


const int in1 = 4;
const int in2 = 5;
const int encoder = 2;

const int pot=A0;
int rotacion = 0;
const int buttonPin = 22;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long encoderTime = 0;    // the debounce time; increase if the output flickers
int encoderCounter;
float encoderPeriod;
const int maxCount = 20;
bool encoderFlag;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(encoder, INPUT_PULLUP);

// Rotacion incial - Foward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(LED_BUILTIN, rotacion); 
  
  attachInterrupt(digitalPinToInterrupt(encoder), Encoder, RISING);
  // set initial LED state
  digitalWrite(ledPin, ledState);
  encoderCounter = 0;
  encoderFlag = false;
  Serial.begin(9600);
}

void loop() {
  // read the state of the switch into a local variable:
   int potValue = analogRead(pot); //Lectura potenciometro
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
        rotacion = rotacion +1;  
        if (rotacion == 4) rotacion = 0;
     }
    }
  }

  // set the LED:
  if (rotacion == 0){
          digitalWrite(in1, LOW);
          analogWrite(in2, pwmValue);
          delay(20);
        }
  if (rotacion == 1){
          digitalWrite(in1, HIGH);
          digitalWrite(in2, HIGH);
         
          delay(20);
       }
  if (rotacion == 2){
          digitalWrite(in2, LOW);
          analogWrite(in1, pwmValue);
         
          delay(20);
       }
   if (rotacion == 3){
          digitalWrite(in1, LOW);
          digitalWrite(in2, LOW);
         
          delay(20);
       }

    if(encoderFlag){
      encoderFlag = false;
      Serial.println(encoderPeriod, 4);
      }
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}


void Encoder(){
  encoderCounter++;

  if(encoderCounter == maxCount){
      encoderCounter = 0;
      
      encoderPeriod = (millis()-encoderTime)/(1.0*(maxCount-1));
      encoderFlag = true;
    }
   if(encoderCounter == 1){
    encoderTime = millis();
    }
  
  
  }

