#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//--------------------------------------
// Constants
//--------------------------------------

#define BLYNK_TEMPLATE_ID "TMPLVwJNtot3"
#define BLYNK_TEMPLATE_NAME "Moisture Sensor"
#define BLYNK_AUTH_TOKEN "FNYWkLq_G4F4jk02bYqpuKUSojfYL26K"

char auth[] = "FNYWkLq_G4F4jk02bYqpuKUSojfYL26K";
char ssid[] = "dekut";
char pass[] = "dekut@ict2023";

const int analogPinA0 = A0;

//--------------------------------------
// Objects
//--------------------------------------
BlynkTimer timer;

//--------------------------------------
// Variables
//--------------------------------------
int sensorData;
int output;

void sendSensor()
{

  sensorData = analogRead(A0); //reading the sensor on A0

  if ( isnan(sensorData) ){
    // Serial.println("Failed to read from Hygrometer Soil Moisture sensor!");
    return;
  } else {
    // Serial.println(sensorData);
    // When the plant is watered well the sensor will read a value 380~400, I will keep the 400 
    // value but if you want you can change it below. 
  
    sensorData = constrain(sensorData,400,1023);  //Keep the ranges!
    output = map(sensorData,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
    // Serial.println(output);

    Blynk.virtualWrite(V5, output);
  
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  WiFi.hostname("dekut"); // all my devices have Vikings name (I know it's geek)
  
  timer.setInterval(3000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
