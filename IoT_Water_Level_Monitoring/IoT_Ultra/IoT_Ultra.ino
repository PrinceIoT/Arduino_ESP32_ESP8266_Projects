

#define BLYNK_TEMPLATE_ID "TMPLnUMJfUOy"
#define BLYNK_DEVICE_NAME "IoT Water Monitoring System"
#define BLYNK_AUTH_TOKEN "n8uaBp1jzTLYG5x0AEiPsAgwA0_eB6Ui"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#include<HCSR04.h>
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define trig D0  // Trig pin
#define echo D1
# define dist

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "eduroam";
char pass[] = "E022-01-0817/2019";

char auth[] = BLYNK_AUTH_TOKEN;

//HCSR04 hc(trig,echo);

BlynkTimer timer;

void sendSensor()
{
  int c = dist();
  if ( c == 0 ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V5, c);  // select virtual pin (v5) in blynk app
  
 
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();   
  }
