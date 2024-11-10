
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL7JcYmB6P"
#define BLYNK_DEVICE_NAME "LED BLINKD"
#define BLYNK_AUTH_TOKEN "bj3tulFSLoYTAfOuadf-itDqdCRWKeTB"

#include <BlynkSimpleEsp8266.h>

// Wifi details. Password and Wifi name. 
char auth[]= BLYNK_AUTH_TOKEN;
char ssid[]="eduroam";
char pass[]="E022-01-0817/2019";

int Led_Pin=D0;
BLYNK_WRITE(V0){
  int Pin_Value = param.asInt();
  digitalWrite(Led_Pin,Pin_Value);
}
void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth,ssid,pass);
  Serial.begin(9600);
  pinMode(Led_Pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

}
