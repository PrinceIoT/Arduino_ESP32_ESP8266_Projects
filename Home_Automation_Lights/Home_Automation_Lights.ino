#define BLYNK_TEMPLATE_ID "TMPLOs1IeJcz"
#define BLYNK_DEVICE_NAME "Home Light Control"
#define BLYNK_AUTH_TOKEN "y_a1sLyVR4vNE7BKCcbAgISro7NnpxNi"

#include <BlynkSimpleEsp8266.h>

// Wifi details. Password and Wifi name. 
char auth[]= BLYNK_AUTH_TOKEN;
const char* ssid="DESKTOP-02G309U 3929";
const char* pass = "123456789";

int Led0_Pin=D0;
int Led1_Pin=D1;
int Led2_Pin=D2;
int Led3_Pin=D3;

BLYNK_WRITE(V0){
  int Pin_Value = param.asInt();
  digitalWrite(Led0_Pin,Pin_Value);
}

BLYNK_WRITE(V1){
  int Pin_Value = param.asInt();
  digitalWrite(Led1_Pin,Pin_Value);
  
}

BLYNK_WRITE(V2){
  int Pin_Value = param.asInt();
  digitalWrite(Led2_Pin,Pin_Value);
}
BLYNK_WRITE(V3){
  int Pin_Value = param.asInt();
  digitalWrite(Led3_Pin,Pin_Value);
}

void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth,ssid,pass);
  Serial.begin(9600);
  pinMode(Led0_Pin,OUTPUT);
  pinMode(Led1_Pin,OUTPUT);
  pinMode(Led2_Pin,OUTPUT);
  pinMode(Led3_Pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

}
