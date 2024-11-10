#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLuw8pgMc5"
#define BLYNK_DEVICE_NAME "LED BLINK"
#define BLYNK_AUTH_TOKEN "VraMG0YNxIhV_SgtZx1EN_9jz-SPBnDW"

//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
