// Pin configuration
const int pirPin = 12; // PIR sensor OUT pin

// Variables
int count = 0; // Object count
unsigned long lastDetectionTime = 0; // Time of last detection

// Constants
const unsigned long resetTime = 60000; // Reset time in milliseconds (1 minute)

void setup() {
  pinMode(pirPin, INPUT);
  Serial.begin(9600); // Initialize serial communication (optional)
}

void loop() {
  int pirState = digitalRead(pirPin);

  // Check for a change in PIR sensor state
  if (pirState == HIGH) {
    unsigned long currentTime = millis();

    // Check if enough time has passed since the last detection
    if (currentTime - lastDetectionTime >= resetTime) {
      // Reset the count if 1 minute has elapsed
      count = 0;
      Serial.println("Count reset");
    }

    // Increment count and update last detection time
    count++;
    lastDetectionTime = currentTime;

    Serial.print("Count: ");
    Serial.println(count); // Print count to the serial monitor (optional)

    delay(5000); // Delay to avoid multiple counts for the same object
  }
}
