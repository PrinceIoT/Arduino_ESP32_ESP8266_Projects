int Relay_Pin=5;//D2
void setup() {
  // put your setup code here, to run once:
  pinMode(Relay_Pin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Relay_Pin,HIGH);
  delay(5000);
  digitalWrite(Relay_Pin,LOW);
  delay(1000);
  

}
