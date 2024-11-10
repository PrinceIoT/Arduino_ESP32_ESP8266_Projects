int Moisture_Signal = A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int Moisture=analogRead(Moisture_Signal);
  Serial.print("Moisture level: ");
  Serial.println(Moisture);
  delay(5000);

}
