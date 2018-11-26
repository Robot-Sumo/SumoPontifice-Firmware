// Ultrasonido
const int U1_echo = 23;
const int U1_trig = 22;
const int U2_trig = 35;
const int U2_echo = 47;
const int U3_trig = A14;
const int U3_echo = A15;
const int U3_vcc = A13;
//Arriba del pin a0 const int U4_vcc
const int U5_trig = A0;
const int U5_echo = A1;
const int U5_gnd = A2;

const int U4_vcc = A3;
const int U4_trig = A4; // blanco
const int U4_echo = A5; // verde
const int U4_gnd = A6;

const int max_distance = 150 ; // cm


void setup() {
  // initialize serial:
  Serial.begin(57600);
  pinMode(U1_trig, OUTPUT);
  pinMode(U1_echo, INPUT);
  pinMode(U2_trig, OUTPUT);
  pinMode(U2_echo, INPUT);
  pinMode(U3_trig, OUTPUT);
  pinMode(U3_echo, INPUT);
  pinMode(U3_vcc, INPUT);
  pinMode(U4_trig, OUTPUT);
  pinMode(U4_echo, INPUT);
  pinMode(U4_gnd, INPUT);
  pinMode(U4_vcc, INPUT);
  pinMode(U5_trig, OUTPUT);
  pinMode(U5_echo, INPUT);
  pinMode(U5_gnd, INPUT);
  

}
void loop() {
  // print the string when a newline arrives:

    float d1;
    float d2;
    float d3;
    float d4;
    float d5;

    trigger(U5_trig);
    d5 =  float(echo(U5_echo))/58.0;

    trigger(U4_trig);
    d4 = float(echo(U4_echo)/58.0);

    trigger(U2_trig);
    d3 = float(echo(U2_echo))/58.0;

    Serial.print("Distance 5 = ");
    Serial.print(d5);

    Serial.print("\t Distance 4 = ");
    Serial.print(d4);

    Serial.print("\t Distance 3 = ");
    Serial.println(d3);
    delay(1000);
    

}


void trigger(const int trigger_pin){
   digitalWrite(trigger_pin, LOW); /* Por cuestión de estabilización del sensor*/
   delayMicroseconds(5);
   digitalWrite(trigger_pin, HIGH); /* envío del pulso ultrasónico*/
   delayMicroseconds(10);
   digitalWrite(trigger_pin, LOW); /* Por cuestión de estabilización del sensor*/
  }
  
unsigned long echo(const int echo_pin){
  unsigned long tiempo_temp;
  tiempo_temp=pulseIn(echo_pin, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/

  return tiempo_temp;
  }
