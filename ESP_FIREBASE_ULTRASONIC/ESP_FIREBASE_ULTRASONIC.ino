//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

// Define your Firebase credentials and database URL
#define FIREBASE_HOST "https://ultrasonicdata-f4e25-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyBcXW-CfstG0m7CRimQb_FfNqZw-xEcluw"

const int trigPin = 12;
const int echoPin = 14;
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;

// Insert your network credentials
#define WIFI_SSID "dekut"
#define WIFI_PASSWORD "dekut@ict2023"

FirebaseData firebaseData;  // Declare Firebase data object globally
FirebaseConfig firebaseConfig;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an 

    // Connect to Wi-Fi
    WiFi.begin("your-ssid", "your-password");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    firebaseConfig.host = FIREBASE_HOST;
    firebaseConfig.auth = FIREBASE_AUTH;
     //Firebase.begin(&firebaseConfig, &firebaseData);
    // Initialize Firebase
    //Firebase.begin(firebaseConfig.host, firebaseConfig.auth);
}

void loop() {

      // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  //distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  if (Firebase.setInt(firebaseData, "/distanceCm", distanceCm)) {
    Serial.println("Data sent to Firebase: " + String(distanceCm));
    } else {
      Serial.println("Error sending data to Firebase");
    }

    delay(1000); // Send data every second
}
