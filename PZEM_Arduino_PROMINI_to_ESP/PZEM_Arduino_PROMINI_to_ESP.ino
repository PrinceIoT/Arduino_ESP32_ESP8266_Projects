#include <PZEM004Tv30.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

PZEM004Tv30 pzem(12, 13); // Software Serial pin 12 (RX) & 13 (TX)
//PZEM004Tv30 pzem(4, 5); // Software Serial pin 4 (RX) & 5 (TX)
//SoftwareSerial mySerial(4, 5); // RX, TX

//PZEM004Tv30 pzem(mySerial);

void setup() {
  Serial.begin(9600);
  Serial2.begin(115200, SERIAL_8N1);
}

void loop() {
  float voltage = pzem.voltage();
  if (voltage != NAN) {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
  }

  float current = pzem.current();
  if (current != NAN) {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }

  float power = pzem.power();
  if (current != NAN) {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");
  } else {
    Serial.println("Error reading power");
  }

  float energy = pzem.energy();
  if (current != NAN) {
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");

  } else {
    Serial.println("Error reading energy");
  }

  float frequency = pzem.frequency();
  if (current != NAN) {
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }

  float pf = pzem.pf();
  if (current != NAN) {
    Serial.print("PF: ");
    Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }
  Serial.println();

  String sensorData = String(voltage) + "|" + String(current) + "|" + String(power) + "|" + String(energy)+ "|" + String(frequency)+ "|" + String(pf);
  Serial.println(sensorData);


  Serial2.print("V:");
  Serial2.println(voltage);
 
  Serial2.print("C:");
  Serial2.println(current);
  
  Serial2.print("P:");
  Serial2.println(power);
  
  Serial2.print("E:");
  Serial2.println(energy);
  
  Serial2.print("F:");
  Serial2.println(frequency);
  Serial2.print("$");
  
  Serial2.print("PF:");
  Serial2.println(pf);  
  Serial2.println();
  
//
  Serial2.print(voltage);
  Serial2.print("$");
  Serial2.print(current);
  Serial2.print("$");
  Serial2.print(energy);
  Serial2.print("$");
  Serial2.print(power);
  Serial2.print("$");
  Serial2.print(frequency);
  Serial2.print("$");
  Serial2.print(pf);
  
  Serial2.println();
 
  
  delay(2000);
}
