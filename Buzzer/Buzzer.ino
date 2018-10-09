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
void setup() {
  // put your setup code here, to run once:
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
  
 digitalWrite(LED1, HIGH);
 delayMicroseconds(period*PWM_HIGH);
 digitalWrite(LED1, LOW);
 delayMicroseconds(period*(1-PWM_HIGH));


}
