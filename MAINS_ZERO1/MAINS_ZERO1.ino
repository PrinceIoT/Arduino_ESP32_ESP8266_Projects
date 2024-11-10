const int zeroCrossingPin = 2;   // Digital pin for zero-crossing detection
const int analogInputPin = A0;   // Analog pin for reading AC mains voltage

void setup() {
  Serial.begin(9600);             // Initialize serial communication
  pinMode(zeroCrossingPin, INPUT_PULLUP);  // Set the zero-crossing pin as INPUT_PULLUP
  attachInterrupt(digitalPinToInterrupt(zeroCrossingPin), zeroCrossingInterrupt, FALLING);
}

void loop() {
  // Your main loop code can go here
}

void zeroCrossingInterrupt() {
  static unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  // To avoid printing too frequently, consider using a time threshold
  if (currentMillis - lastMillis >= 10) {
    // Read and print the analog value from pin A0
    int analogValue = analogRead(analogInputPin);
    Serial.print("Analog Value at Zero Crossing: ");
    Serial.println(analogValue);

    // Update the lastMillis value
    lastMillis = currentMillis;
  }
}
