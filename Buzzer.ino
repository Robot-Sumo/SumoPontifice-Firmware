const int buzzer = 22;
const int M1_out1 = 2;
const int M1_out2 = 3;
const int M2_out1 = 5;
const int M2_out2 = 6;
const int M3_out1 = 8;
const int M3_out2 = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  pinMode(M1_out1, OUTPUT);
  pinMode(M1_out2, OUTPUT);
  pinMode(M2_out1, OUTPUT);
  pinMode(M2_out2, OUTPUT);
  pinMode(M3_out1, OUTPUT);
  pinMode(M3_out2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(M1_out1, HIGH);
 digitalWrite(M1_out2, LOW);
 digitalWrite(M2_out1, HIGH);
 digitalWrite(M2_out2, LOW);
 digitalWrite(M3_out1, HIGH);
 digitalWrite(M3_out2, LOW);


}
