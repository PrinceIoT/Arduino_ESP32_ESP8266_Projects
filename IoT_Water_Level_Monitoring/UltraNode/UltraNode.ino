
#include <ESP8266WiFi.h>

#define echoPin D0
#define trigPin D1

long duration=0;
int distance=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin,LOW);
 
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.017;
  Serial.print("Distance: " );
  Serial.println(distance);
  //Serial.print("cm");

}
