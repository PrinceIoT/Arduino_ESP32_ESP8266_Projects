//Blynk Fire Alarm Notification
#define BLYNK_TEMPLATE_ID "TMPLcWTQLHFT"
#define BLYNK_TEMPLATE_NAME "Fire"
#define BLYNK_AUTH_TOKEN "B2lc-KV-uTEDgkhpQASwRtJf4A1sAP4i"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 
BlynkTimer timer;
char auth[] = "B2lc-KV-uTEDgkhpQASwRtJf4A1sAP4i"; //Auth code sent via Email
char ssid[] = "dekut "; //Wifi name
char pass[] = "dekut@ict2023"; //Wifi Password
int flag=0;
void notifyOnFire()
{
int isButtonPressed = digitalRead(D1); // falme sensor connected D1 pin
if (isButtonPressed==1 && flag==0) 
{
Serial.println("Fire DETECTED");
Blynk.notify("Alert : Fire detected");
flag=1;
}
else if (isButtonPressed==0)
{
flag=0;
}
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(D1,INPUT_PULLUP);
timer.setInterval(1000L,notifyOnFire); 
}
void loop()
{
Blynk.run();
timer.run();
}
