void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int SensorValue=analogRead(A0);
  Serial.print("SensorValue is: ");
  Serial.println(SensorValue);
  delay(1000);

}
