// LED PINS
#define LED_1 2
#define LED_2 3
#define LED_3 4
#define LED_4 5
#define LED_5 6
#define sensorPin A0
// LED Boolean Status
bool ledPin_1_Status;
bool ledPin_2_Status;
bool ledPin_3_Status;
bool ledPin_4_Status;
bool ledPin_5_Status;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(LED_3,OUTPUT);
  pinMode(LED_4,OUTPUT);
  pinMode(LED_5,OUTPUT);

  pinMode(sensorPin,INPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue=analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue > 100)
      ledPin_1_Status = 1;
  if (sensorValue > 200)
      ledPin_2_Status = 1;
  if (sensorValue > 300)
      ledPin_3_Status = 1;
  if (sensorValue > 400)
      ledPin_4_Status = 1;
  if (sensorValue > 500)
      ledPin_5_Status = 1;

  if(ledPin_1_Status == 1 || ledPin_2_Status == 1 || ledPin_3_Status == 1 || ledPin_4_Status == 1 || ledPin_5_Status == 1)

  if (sensorValue > 105 || sensorValue < 207)
      digitalWrite(LED_1,HIGH);
  if (sensorValue > 206 || sensorValue < 300)
      digitalWrite(LED_2,HIGH);
  if (sensorValue > 301 || sensorValue < 400)
      digitalWrite(LED_3,HIGH);
  if (sensorValue > 401 || sensorValue < 537)
      digitalWrite(LED_4,HIGH);
  if (sensorValue > 538 || sensorValue < 1000)
      digitalWrite(LED_5,HIGH);
  delay(500);

  ledPin_1_Status=0;
  ledPin_2_Status=0;
  ledPin_3_Status=0;
  ledPin_4_Status=0;
  ledPin_5_Status=0;

  digitalWrite(LED_1,LOW);
  digitalWrite(LED_2,LOW);
  digitalWrite(LED_3,LOW);
  digitalWrite(LED_4,LOW);
  digitalWrite(LED_5,LOW);
}
