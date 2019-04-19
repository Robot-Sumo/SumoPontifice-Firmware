// Arduino Nano
//Comandos del dispositivo
#define setLED_RGB 1; // Poner LED_RGB en un color determinado
#define setBearingVector 2; // Poner punto de referencia de direccion y velocidad
#define getBatteryState 3;  // Leer voltaje de las baterias y enviar al master
#define startDistanceMeasure 4; // comando que solicita empezar a medir el dezplazamiento en las ruedas
#define getDistanceMeasure 5; // enviar al master el dezplazamiento medido en las ruedas

// direcciones dispositivos conectados al puerto serial

#define masterDeviceAddress 2;
#define pantiltDeviceAddress 255;
#define thisDeviceAddress 1 ;
// *** Configuracion de pines ***
// Drivers Motores

// Driver 1 , izquierdo (Motor rueda derecha)
const int in1= 11; // pwm1
const int in2 = 9; // pwm2
const int diag = 10; // Diag (señal de sobre corriente)

// Driver 2 , derecho(B) (Motor rueda izquierda)
const int in1bAux= A0; // pwm1
const int in2bAux = A1; // pwm2
const int in1b = 6; // pwm1, activado hacia adelante
const int in2b = 5; // pwm2, activado hacia atrás
const int diagb = 4; // Diag (señal de sobre corriente)

// Voltaje de las baterias
const int vbatt1 = A6;
const int vbatt2 = A7;


// Encoders
const int enc1 = 2; // Encoder rueda izquierda
const int enc2 = 3; // Encoder rueda derecha

// LEDS
const int led1 = 13;

const int led_Rpin = 7;
const int led_Gpin = 8; // 8
const int led_Bpin = 12;
enum colores
{
rojo,
verde,
azul,
amarillo,
turquesa,
morado,
blanco,
off
};

// estados del dispositivo
int currentState, lastState;
bool goToPwm, goToStop;
enum states
{
    setPWM,
    idle,
    stop
};


// Variables
bool direction;
int pwmRightWheel = 0;
int pwmLeftWheel= 0;
unsigned long timeArriveCommand;

// Variables
String dataFromMaster= "";         // a String to hold incoming data

void setup() { 
 

  // Setting pin modes
  // Inputs
  pinMode(diag, INPUT);
  pinMode(diagb, INPUT);
  pinMode(in1bAux, INPUT); // Debe declarase siempre como entrada
  pinMode(in2bAux, INPUT); // Debe declarase siempre como entrada
  pinMode(enc1, INPUT); // Debe declarase siempre como entrada
  pinMode(enc2, INPUT); // Debe declarase siempre como entrada

  // Outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1b, OUTPUT);
  pinMode(in2b, OUTPUT);

  pinMode(led_Rpin, OUTPUT);
  pinMode(led_Gpin, OUTPUT);
  pinMode(led_Bpin, OUTPUT);
  pinMode(led1, OUTPUT);



  Serial.begin(9600);

  ledColor(off);
  goToPwm = false;
  goToStop = true;
  currentState = idle;
  timeArriveCommand = millis();
  pwmLeftWheel = 0;
  pwmRightWheel = 0;
  direction = true;

}

void loop() { 

  StateMachine();


  


}



void StateMachine()
{
    
    switch (currentState) {
        case states::idle:
            if( (millis()-timeArriveCommand) > 1500)
            {
                goToStop = true;
                timeArriveCommand = millis();

            }
            if(goToStop) 
            {
                goToStop = false;
                currentState = states::stop;
            }
            if(goToPwm) 
            {
                goToPwm = false;
                currentState = states::setPWM;
            }
              
            break;

        case states::stop:
            setPwm(0, 0, 1);
            ledColor(rojo);
            currentState = idle;
            break;
        case states::setPWM:
            setPwm(pwmLeftWheel, pwmRightWheel, direction);
            currentState = idle;
            break;
            

        

    }
}


void setPwm(uint8_t pwmLeftWheel, uint8_t pwmRightWheel, bool direction)
{

    if(direction) // forward
    {
        analogWrite(in1, pwmRightWheel);
        digitalWrite(in2, LOW);
        analogWrite(in1b, pwmLeftWheel);
        digitalWrite(in2b, LOW);
        ledColor(verde);
    }
    else  // reverse
    {
        analogWrite(in2, pwmRightWheel);
        digitalWrite(in1, LOW);
        analogWrite(in2b, pwmLeftWheel);
        digitalWrite(in1b, LOW);
        ledColor(azul);
    }
    
}


void ledColor(int color)
{
    switch(color)
    {
        case azul :
            digitalWrite(led_Rpin, LOW);
            digitalWrite(led_Gpin, LOW);
            digitalWrite(led_Bpin, HIGH);
            break;
        case rojo:
            digitalWrite(led_Rpin, HIGH);
            digitalWrite(led_Gpin, LOW);
            digitalWrite(led_Bpin, LOW); 
            break;
        case morado:
            digitalWrite(led_Rpin, HIGH);
            digitalWrite(led_Gpin, LOW);
            digitalWrite(led_Bpin, HIGH);
            break;
        case turquesa:
            digitalWrite(led_Rpin, LOW);
            digitalWrite(led_Gpin, HIGH);
            digitalWrite(led_Bpin, HIGH);
            break;
        case blanco:
            digitalWrite(led_Rpin, HIGH);
            digitalWrite(led_Gpin, HIGH);
            digitalWrite(led_Bpin, HIGH);
            break;
        case amarillo:
            digitalWrite(led_Rpin, HIGH);
            digitalWrite(led_Gpin, HIGH);
            digitalWrite(led_Bpin, LOW);
            break;
        case verde:
            digitalWrite(led_Rpin, LOW);
            digitalWrite(led_Gpin, HIGH);
            digitalWrite(led_Bpin, LOW);
            break;
        case off:
            digitalWrite(led_Rpin, LOW);
            digitalWrite(led_Gpin, LOW);
            digitalWrite(led_Bpin, LOW);
            break;


    }
    
}

void serialEvent() {
  char inChar;
  while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read();
    // add it to the inputString:
    dataFromMaster += inChar;
    }
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if(inChar == '\n')
    {
        //setCommand(dataFromMaster);

        if (dataFromMaster[0] == 1)
        {   
            pwmLeftWheel = dataFromMaster[2];
            pwmRightWheel = dataFromMaster[3];
            direction = (dataFromMaster[4] == 1); // forward o reverse
            goToPwm = true;
            timeArriveCommand = millis();
        }
        dataFromMaster ="";
    }
    
    
  
}

/*
void setCommand(String dataFromMaster )
{
    if(int(dataFromMaster[0]) == 1) // Address
    {
        switch(int(dataFromMaster[1])) //command
        {
            case setLED_RGB :
                ledColor(dataFromMaster[2]); // set color
                break;
            case setBearingVector:
                int bearx = dataFromMaster[2];
                int beary = dataFromMaster[3];
                int speed = dataFromMaster[4];
                
                break;

        }
    }
 
  
}
*/
