#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
int ledPIN = D1;
int digitalPin=D0;
int AnalogPin=A0;

//BUZZER
int buzzer = D3;

int digitalVal;
int AnalogVal;

const char* ssid     = "DESKTOP-02G309U 3929";//Specify wifi username
const char* password = "123456789"; //specify wifi password

const char* host = "api.thingspeak.com";  //From ThingSpeak. Remain constant
const char* APIKey = "AJMFQ0QWRK1L8T25";  //From ThingSpeak Channel

void setup()
{
    Serial.begin(115200);
    delay(10);
    
     // put your setup code here, to run once:
  pinMode(ledPIN,OUTPUT);
  //BUZZER
  pinMode(buzzer,OUTPUT);
  
  pinMode(digitalPin,INPUT);
  //Serial.begin(9600);

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

//int value = 0;

void loop()
{
    delay(5000);
    
    //sensors.requestTemperatures();
    
   // value = sensors.getTempCByIndex(0);//analogRead(A0);
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
  delay(1000);

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/update";
    url += "?api_key=";
    url += APIKey;
    url += "&field2=";
    url += AnalogVal;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
}
