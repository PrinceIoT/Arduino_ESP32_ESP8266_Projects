#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); // SoftwareSerial communication with Pro Mini
}

void loop() {
  // Send sync value of 1 to Pro Mini
  mySerial.write(1);

  delay(1000); // Wait for 1 second before sending again
}
