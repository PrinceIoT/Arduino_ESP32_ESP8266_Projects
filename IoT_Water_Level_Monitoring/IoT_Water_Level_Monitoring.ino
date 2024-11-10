
#define BLYNK_TEMPLATE_ID "TMPLnUMJfUOy"
#define BLYNK_DEVICE_NAME "IoT Water Monitoring System"
#define BLYNK_AUTH_TOKEN "n8uaBp1jzTLYG5x0AEiPsAgwA0_eB6Ui"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#include<HCSR04.h>
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define trig D0   // Trig pin
#define echo D1 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "dekut";
char pass[] = "dekut@ict2020?";

char auth[] = BLYNK_AUTH_TOKEN;

int depth =300;

BlynkTimer timer;
 
void waterlevel()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  long level= depth-cm;
  if (level<0)
  level=0;
  level = map(level,0,depth-3,0,100);
  
  Blynk.virtualWrite(V0, level);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, waterlevel);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();

}
