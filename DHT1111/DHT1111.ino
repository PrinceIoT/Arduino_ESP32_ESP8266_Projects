 #include "DHT.h"  
 #include "ESP8266WiFi.h"
 
 DHT dht2(D0,DHT11);  
 void setup()  
 {  
  Serial.begin(9600);  
 }  
 void loop()  
 {  
   Serial.println("Temperature in C:");  
   Serial.println((dht2.readTemperature( )));  
   Serial.println("Humidity in C:");  
   Serial.println((dht2.readHumidity()));  
   delay(1000);  
 }  
