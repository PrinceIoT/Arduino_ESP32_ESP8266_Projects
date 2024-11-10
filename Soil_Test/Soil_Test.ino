#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Set the Wi-Fi credentials
const char* ssid="DESKTOP-02G309U 3929";
const char* pass = "123456789";

// Set the Blynk authentication token
char auth[] = "FNYWkLq_G4F4jk02bYqpuKUSojfYL26K";

#define BLYNK_TEMPLATE_ID "TMPLVwJNtot3"
#define BLYNK_TEMPLATE_NAME "Moisture Sensor"
#define BLYNK_AUTH_TOKEN "FNYWkLq_G4F4jk02bYqpuKUSojfYL26K"

// Set the virtual pin for the soil moisture sensor
#define SOIL_MOISTURE_SENSOR_VPIN V5

// Set the pin for the soil moisture sensor
#define SOIL_MOISTURE_SENSOR_PIN A0

void setup()
{
  // Start serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

  // Set the soil moisture sensor pin as an input
  pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);
}

void loop()
{
  // Read the value from the soil moisture sensor
  int soil_moisture = analogRead(SOIL_MOISTURE_SENSOR_PIN);

  // Send the soil moisture value to Blynk
  Blynk.virtualWrite(SOIL_MOISTURE_SENSOR_VPIN, soil_moisture);

  // Wait for 1 second before reading the sensor again
  delay(1000);
}
