#define LED_PIN1 2
#define LED_PIN2 3

#define sensorPin A0
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
  pinMode(sensorPin,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue > 40 && sensorValue < 100 )
     digitalWrite(LED_PIN1,HIGH);
     //delay(500);
  if (sensorValue <40 )
     digitalWrite(LED_PIN2,HIGH);
     //delay(500);
  else 
     digitalWrite(LED_PIN1,LOW);
     digitalWrite(LED_PIN2,LOW);
  delay(500);
}
