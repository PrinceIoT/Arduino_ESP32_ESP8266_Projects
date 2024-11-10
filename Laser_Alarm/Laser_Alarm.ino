//define pins used
int Laser_Pin =3;
int Buzzer_Pin=11;
int Button_Pin=12;
int LDR_Pin=A0;

int LaserThreshold =100;


void setup() {
  // put your setup code here, to run once:

  pinMode(Laser_Pin,OUTPUT);
  pinMode(Button_Pin,INPUT_PULLUP);
  Serial.begin(9600);
}
boolean alarmstate=false;

void loop() {
  // put your main code here, to run repeatedly:
  if (! alarmstate){
    delay(1000);
    digitalWrite(Laser_Pin,HIGH);
   // delay(1000);
    delay(10);

    unsigned long startTime=millis();
    while(millis()-startTime < 1000){
      int sensorValue = analogRead(LDR_Pin);
      Serial.println(sensorValue);
      if(sensorValue > LaserThreshold){
        alarmstate = true;
        break;
        }
        delay(10);
      }
      digitalWrite(Laser_Pin,LOW);
    }else{
      tone(Buzzer_Pin,440);
      if (! digitalRead(Button_Pin)){
        alarmstate=false;
        noTone(Buzzer_Pin);
        }
        delay(10);
      }
  

}
