int bt1 = 2, bt2 = 3;
int bs1 = 0, bs2 = 0;
int o1 = 10, o2 = 9;
int del = 10;
void setup() {
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(o1, OUTPUT);
  pinMode(o2, OUTPUT);
}

void loop() {
  bs1 = digitalRead(bt1); delay(del);
  bs2 = digitalRead(bt2); delay(del);

  if (bs1 == HIGH) {
    digitalWrite(o1, HIGH);
  }
  else if (bs1 == LOW) {
    digitalWrite(o1, LOW);
  }

  if (bs2 == HIGH) {
    digitalWrite(o2, HIGH);
  }
  else if (bs2 == LOW) {
    digitalWrite(o2, LOW);
  }
}
