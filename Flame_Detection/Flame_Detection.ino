#include <ESP8266WiFi.h>

int ledPIN = D1;
int digitalPin=D0;
int AnalogPin=A0;

//BUZZER
int buzzer = D3;

int digitalVal;
int AnalogVal;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPIN,OUTPUT);
  //BUZZER
  pinMode(buzzer,OUTPUT);
  
  pinMode(digitalPin,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalVal=digitalRead(digitalPin);
  if(digitalVal==1){
    digitalWrite(ledPIN,HIGH);
    //BUZZER
    digitalWrite(buzzer,HIGH);
    
    }
  else{
    digitalWrite(ledPIN,LOW);
    digitalWrite(buzzer,LOW);
    }

  AnalogVal=analogRead(AnalogPin);
  Serial.println(AnalogVal);
  delay(2000);

}
