//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "dekut"
#define WIFI_PASSWORD "dekut@ict2020?"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBRe8fQAa6PQWH3Vt7zrkFLDem_DQ4fZzk"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "dishanotiene19@gmail.com"
#define USER_PASSWORD "Princedisho@otiai001"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://soil-moisture-monitoring-76885-default-rtdb.europe-west1.firebasedatabase.app/"
