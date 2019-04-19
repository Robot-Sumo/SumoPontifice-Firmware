// Arduino Nano

// *** Configuracion de pines ***
// Drivers Motores

// Driver 1 , izquierdo (Motor rueda derecha)
const int in1= 4; // pwm1
const int in2 = 5; // pwm2
const int diag = 2; // Diag (señal de sobre corriente)
const int in1b = 6;
const int in2b = 7;


// Encoders
const int enc1 = 5; // Encoder rueda izquierda
const int enc2 = 6; // Encoder rueda derecha

bool led;



int pwmValue = 0;


int encoderCounter;
float encoderPeriod;
const int maxCount = 10;
bool encoderFlag;

// Variables will change:
int ledState = LOW; 
unsigned long encoderTime = 0;  


char pwmRight = 0;
char pwmLeft = 0;
char pwmForward = 1;
char lastPwmRight = 0;
char lastPwmLeft = 0;





String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() { 
 


  // Outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(diag, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(diag), Diag, RISING);
  led = LOW;
   encoderCounter = 0;
  encoderFlag = false;

  Serial.begin(9600);
    // reserve 200 bytes for the inputString:
  inputString.reserve(200);


}

void loop() { 

   //ledColor(rojo);
  

  if(encoderFlag){
      encoderFlag = false;
      Serial.println(encoderPeriod, 4);
      }
   if (stringComplete) {
   
   if(inputString[0] == 1 ) // Direccion de este dispositivo
   {
      if (inputString[1] == 1) // Set PWM command
      {
        pwmRight = inputString[2];
        pwmLeft = inputString[3];
        pwmForward = inputString[4];
        
     }
    
    
   }
   
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  
  if(pwmRight != lastPwmRight ) // rueda derecha
  { 
    if(pwmForward == 0) // Reversa
    {
      analogWrite(in2, pwmRight);
      digitalWrite(in1, LOW);
    }

    else // Hacia adelante
    {
      analogWrite(in1, pwmRight);
      digitalWrite(in2, LOW);
    }
   
   }


   if(pwmLeft != lastPwmLeft ) // rueda derecha
  { 
    if(pwmForward == 0) // Reversa
    {
      analogWrite(in2b, pwmLeft);
      digitalWrite(in1b, LOW);
    }

    else // Hacia adelante
    {
      analogWrite(in1b, pwmLeft);
      digitalWrite(in2b, LOW);
    }
   
   }

   lastPwmRight = pwmRight;
   lastPwmLeft = pwmLeft;
  


  

  

  


  

      
    

    
    

 



 

}

void Diag()
{
   encoderCounter++;
  ledState = !ledState;
    digitalWrite(LED_BUILTIN,ledState);
  if(encoderCounter == maxCount){
      encoderCounter = 0;
      
      encoderPeriod = (millis()-encoderTime)/(1.0*(maxCount-1));
      encoderFlag = true;
    }
   if(encoderCounter == 1){
    encoderTime = millis();
    }
  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if(inChar == '\n') stringComplete = true;
    
  }
}
