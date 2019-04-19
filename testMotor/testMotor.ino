// Motores
const int M1_out1 = 2;
const int M1_out2 = 3;
const int M1_in = 4;
const int M2_out1 = 8;
const int M2_out2 = 9;
const int M2_in = 10;
const int M3_out1 = 8;
const int M3_out2 = 9;
const int M3_in = 10;



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
unsigned long lastTimeInterrupt = 0;
int encoderCounter;
float encoderPeriod;
const int maxCount = 10;
bool encoderFlag;
int minTimeEncoder = 1000; // 1000 microsegundos, max velocidty encoder

void setup() {
    pinMode(master_button, INPUT_PULLUP);
    pinMode(LED1, OUTPUT);
    pinMode(encoder_right, INPUT_PULLUP);
    pinMode(encoder_right_vcc, INPUT);
    pinMode(encoder_left, INPUT_PULLUP);;
    pinMode(M1_out1, OUTPUT);
    pinMode(M1_out2, OUTPUT);
    pinMode(M2_out1, OUTPUT);
    pinMode(M2_out2, OUTPUT);

    pinMode(M1_in, INPUT);
    pinMode(M2_in, INPUT);

     digitalWrite(LED1, HIGH); 
  
    attachInterrupt(digitalPinToInterrupt(encoder_right), Encoder, FALLING);
    encoderCounter = 0;
    encoderFlag = false;
    Serial.begin(57600);
}

void loop() {
    int pwmValue1 = 200;
     digitalWrite(M1_out1, LOW);
     analogWrite(M1_out2, pwmValue1);
      int pwmValue2 = 200;
     digitalWrite(M2_out1, LOW);
     analogWrite(M2_out2, pwmValue2);
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

    if (abs(micros()-lastTimeInterrupt)>minTimeEncoder) // Filtrar ruido de activacion
    {
        encoderCounter++;
        ledState = !ledState;
        if(encoderCounter == maxCount){
            encoderCounter = 0;
            
            encoderPeriod = (micros()-encoderTime)/(1.0*(maxCount-1));
            encoderFlag = true;
            }
        if(encoderCounter == 1){
            encoderTime = micros();
            }
    }
   lastTimeInterrupt = micros();
  
  }

