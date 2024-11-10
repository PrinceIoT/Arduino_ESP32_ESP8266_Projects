#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLVwJNtot3"
#define BLYNK_TEMPLATE_NAME "Moisture Sensor"
#define BLYNK_AUTH_TOKEN "FNYWkLq_G4F4jk02bYqpuKUSojfYL26K"

// Set the Wi-Fi credentials
char ssid[] = "Gabe";
char pass[] = "matplotlib2.0";

// Set the Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi!");

  // Connect to Blynk
//  Blynk.begin(auth)//, WiFi.status);
  Serial.println("Connected to Blynk!");
}

void loop() {
  // Run the Blynk event loop
  Blynk.run();
}
