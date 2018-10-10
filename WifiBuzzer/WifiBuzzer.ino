#include <ArduinoJson.h>
const int M1_out1 = 2;
const int M1_out2 = 3;
const int M2_out1 = 5;
const int M2_out2 = 6;
const int M3_out1 = 8;
const int M3_out2 = 9;
const int U1_echo = 23;
const int U1_trig = 22;
const int U2_trig = 35;
const int U2_echo = 47;
const int U3_trig = A14;
const int U3_echo = A15;
const int U3_vcc = A13;
const int INF_A = 34;
const int LED1 = 46;
const int BUZZER = A12;

int period = 1000; //us
float PWM_HIGH = 1;
int activeButton = -1;
int freq = 60;
int pwm = 0;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
void setup() {

  Serial.begin(57600);
  Serial3.begin(57600);
  
  pinMode(BUZZER, OUTPUT);
  pinMode(M1_out1, OUTPUT);
  pinMode(M1_out2, OUTPUT);
  pinMode(M2_out1, OUTPUT);
  pinMode(M2_out2, OUTPUT);
  pinMode(M3_out1, OUTPUT);
  pinMode(M3_out2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(INF_A, OUTPUT);

  
 digitalWrite(M1_out1, LOW);
 digitalWrite(M1_out2, LOW);
 digitalWrite(M2_out1, LOW);
 digitalWrite(M2_out2, LOW);
 digitalWrite(M3_out1, LOW);
 digitalWrite(M3_out2, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
 if (activeButton ==0)
 {
   tone(BUZZER, freq);
  }
  else if(activeButton ==1)
  {
    noTone(BUZZER);
    digitalWrite(LED1, HIGH);
   delayMicroseconds(period*pwm/100.0);
   digitalWrite(LED1, LOW);
   delayMicroseconds(period*(1-pwm/100.0));
    }
  else{
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
    delay(1000);
    }
 
 

}

void serialEvent3() {
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
    // add it to the inputString:
    inputString += inChar;
    if (inChar == '}') {
      stringComplete = true;
    }
    Serial3.flush();
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
      
    
  }

   if (stringComplete) {
     Serial.print(inputString);;
     StaticJsonBuffer<200> jsonBuffer;
     JsonObject& root = jsonBuffer.parseObject(inputString);
     activeButton        = root["ActiveButton"];
     if (activeButton != -1){
        pwm = root["PWM"];
        freq= root["Frequency"];
        Serial.println(pwm);
        Serial.println(freq);
     }
     else{
        Serial.println("Cliente no conectado");
     }
      // clear the string:
      inputString = "";
      stringComplete = false;
    }

 
  
}
