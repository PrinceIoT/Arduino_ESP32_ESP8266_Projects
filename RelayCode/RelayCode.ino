int RelayPin =6;
void setup() {
  // put your setup code here, to run once:
  pinMode(RelayPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RelayPin,LOW);
  delay(3000);

  digitalWrite(RelayPin,HIGH);
  delay(3000);

}
