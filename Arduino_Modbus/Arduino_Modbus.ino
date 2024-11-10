#include <ModbusIP.h>
#include <Modbus.h>
#include <Ethernet.h>
#include <SPI.h>

int setPoint;
const int setPoint_IR = 100;
ModbusIP mb;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  byte mac [] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  byte ip[] = {172,16,41,240};
  mb.config (mac, ip);
  
  mb.addIreg(setPoint_IR);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  mb.task ();
  setPoint = analogRead(A0);
  mb.Ireg(setPoint_IR, setPoint);
  Serial.print("sensorValue = ");
  Serial.println(setPoint);

  delay(1000);
}
