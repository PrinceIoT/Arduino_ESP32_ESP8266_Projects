#include <OneWire.h>
#include <DallasTemperature.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
const char* ssid     = "Dishan";//Specify wifi username
const char* password = "123456789"; //specify wifi password

const char* host = "api.thingspeak.com";  //From ThingSpeak. Remain constant
const char* APIKey = "55T6PIEEDA1XI3JR";  //From ThingSpeak 
//Data wire
#define ONE_WIRE_BUS_PIN 4

OneWire oneWire(ONE_WIRE_BUS_PIN);

DallasTemperature sensors(&oneWire);
const int turbidityPin = A0; // Analog pin to which the turbidity sensor is connected


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Initialize the sensor
  sensors.begin();

  // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop(void) {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();
  float Water_Temp = sensors.getTempCByIndex(0);
  int turbidityValue = analogRead(turbidityPin);

  //  use index allows to read from multiple sensors
  float turbidity = map(turbidityValue, 0, 1023, 0, 300); // Adjust the mapping based on your sensor's specifications
  float pHValue = map(turbidityValue, 0, 300, 7, 4);

     // Create URL for ThingSpeak update
  String url = "http://";
  url += host;
  url += "/update?api_key=";
  url += APIKey;
  url += "&field1=";
  url += String(turbidity);
  url += "&field2=";
  url += String(pHValue);
  url += "&field3=";
  url += String(Water_Temp);

     // Send HTTP GET request to ThingSpeak
  WiFiClient client;
  HTTPClient http;

  if (http.begin(client, url)) {
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
      Serial.println("Sensor data sent to ThingSpeak successfully");
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Unable to connect to ThingSpeak");
  }
  
  Serial.print("Turbidity: ");
  Serial.println(turbidity);
  
  Serial.print(" | Water pH: ");
  Serial.println(pHValue);
  
  Serial.print("Degrees Celsius: ");
  Serial.println(Water_Temp);

  Serial.println();
  //Serial.print("Temperature by Freints");
  //Serial.println(sensors.getTempFByIndex(0));
  
  delay(500);
  
}
