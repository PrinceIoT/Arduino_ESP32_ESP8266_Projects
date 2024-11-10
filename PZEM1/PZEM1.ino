#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

PZEM004Tv30 pzem(15, 14);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("V\tCurrent: ");
  Serial.print(current);
  Serial.println("A");

  delay(5000); // Adjust the delay as needed
}
