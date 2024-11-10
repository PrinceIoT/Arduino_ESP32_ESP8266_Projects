#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>

//Data wire
#define ONE_WIRE_BUS_PIN  D4

OneWire oneWire(ONE_WIRE_BUS_PIN);

DallasTemperature sensors(&oneWire);

//Flame Sensor
int ledPIN = D1;
int digitalPin=D0;
int AnalogPin=A0;
//BUZZER
int buzzer = D3;
int digitalVal;
int AnalogVal;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Initialize the sensor
  sensors.begin();

  //Buzzer
  pinMode(ledPIN,OUTPUT);
  pinMode(digitalPin,INPUT);
  //BUZZER
  pinMode(buzzer,OUTPUT);

}

void loop(void) {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();

  Serial.print("Degrees Celsius: ");

  //  use index allows to read from multiple sensors
  
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("Temperature by Freints");
  Serial.println(sensors.getTempFByIndex(0));
  delay(5000);

//Flame Sensor
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
  Serial.print("Analog Flame Intensity: ");
  Serial.println(AnalogVal);
  delay(2000);
  
}
