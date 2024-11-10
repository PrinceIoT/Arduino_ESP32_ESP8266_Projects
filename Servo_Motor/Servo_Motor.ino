#include <Servo.h>
Servo s1;

void setup() {
  // put your setup code here, to run once:
s1.attach(2);

}

void loop() {
  // put your main code here, to run repeatedly:
s1.write(90);
delay(500);

}
