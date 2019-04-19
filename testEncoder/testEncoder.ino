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


// Encoders
const int encoder_right = 20;//Rueda derecha, E1
const int encoder_right_vcc = 21;// Alimentacion encoders;
const int encoder_left = 18;

// Boton
const int master_button = 19;
//Led
const int LED1 = 34;

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState = HIGH;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long encoderTime = 0;    // the debounce time; increase if the output flickers
int encoderCounter;
float encoderPeriod;
const int maxCount = 30;
bool encoderFlag;

void setup() {
  pinMode(master_button, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(encoder_right, INPUT_PULLUP);
  pinMode(encoder_right_vcc, INPUT);
  pinMode(encoder_left, INPUT_PULLUP);;

  digitalWrite(LED1, HIGH); 
  
  attachInterrupt(digitalPinToInterrupt(encoder_right), Encoder, RISING);
  encoderCounter = 0;
  encoderFlag = false;
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(master_button);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        Serial.println("activado");
        ledState = !ledState;
     }
    }
  }
   if(encoderFlag){
      encoderFlag = false;
      Serial.println(encoderPeriod, 4);
      }
  digitalWrite(LED1, digitalRead(encoder_right));
      // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;


}


void Encoder(){
  encoderCounter++;
  ledState = !ledState;
  if(encoderCounter == maxCount){
      encoderCounter = 0;
      
      encoderPeriod = (millis()-encoderTime)/(1.0*(maxCount-1));
      encoderFlag = true;
    }
   if(encoderCounter == 1){
    encoderTime = millis();
    }
  
  
  }

