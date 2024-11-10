int buzzer=11;
int LDR=A0;
int LED1=7;
int LED2=6;
int sensorValue=0;

int LaserPin=3;

void setup() {
  // put your setup code here, to run once:
pinMode(LDR,INPUT); 

pinMode(7,OUTPUT); 

pinMode(6,OUTPUT); 
pinMode(LaserPin,OUTPUT);

pinMode(buzzer,OUTPUT); 

digitalWrite(7,HIGH); 
digitalWrite(LaserPin,HIGH);

digitalWrite(6,LOW);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue=analogRead(LDR); 

if(sensorValue<=1000) 

{

digitalWrite(buzzer,HIGH); 

{tone(9,3047,400); noTone(8); } 

digitalWrite(7,HIGH); 

}

 else { 

digitalWrite(buzzer,LOW); 

digitalWrite(7,LOW); 

} 

sensorValue=1000; 

}
