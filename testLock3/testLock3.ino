int Num;
int Num1;
int w[8];
int w1[8];
volatile int a;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  Serial.println("HI");

}
void writeNew(int q[]){
  Serial.println("N");
  for (int i = 0; i < 8; i++) {
    Serial.println(q[i]);
  }
  Serial.println("N1");
}
void loop() {
  if (Serial3.available()) {
    a = Serial3.read();
    delay(1);
    if (Num1 >= 1) {
      w1[Num1 - 1] = a;
      Num1++;
    }
    if (a == 126) {
      Num1 = 1;
    }
    if (Num1 == 9) {
      writeNew(w1);
    }
  } else {
    Num1 = 0;
  }
}
