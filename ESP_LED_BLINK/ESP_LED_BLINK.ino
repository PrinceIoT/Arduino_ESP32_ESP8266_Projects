int LED_PIN = D0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  //Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN,HIGH);
  delay(500);
  digitalWrite(LED_PIN,LOW);
  delay(100);
}
