// Motores
const int M1_out1 = 2;
const int M1_out2 = 3;
const int M1_in = 4;
const int M2_out1 = 5;
const int M2_out2 = 6;
const int M2_in = 7;
const int M3_out1 = 8;
const int M3_out2 = 9;
const int M3_in = 10;


void setup() {
    pinMode(M1_out1, OUTPUT);
    pinMode(M1_out2, OUTPUT);
    pinMode(M2_out1, OUTPUT);
    pinMode(M2_out2, OUTPUT);

    pinMode(M1_in, INPUT);
    pinMode(M2_in, INPUT);

    }

void loop(){
      int pwmValue1 = 150;
     digitalWrite(M1_out1, LOW);
     analogWrite(M1_out2, pwmValue1);
      int pwmValue2 = 170;
     digitalWrite(M2_out1, LOW);
     analogWrite(M2_out2, pwmValue2);
}