int floatVoltage;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int SensorValue = analogRead(A0);
  floatVoltage=SensorValue*(5.0/1024);
  Serial.println(floatVoltage);
  delay(200);

}
