// Include the necessary libraries
#include <Arduino.h>

// Define the pin to which the ZMPT101 sensor is connected
const int zmptSensorPin = A7;  // Replace A1 with the actual pin number //CURRENT A5

// Define the assumed reference voltage
const float referenceVoltage = 4.950;  // Replace 5.0 with the actual reference voltage

// Define the maximum ADC value corresponding to the maximum AC mains voltage
const int maxADCValue = 510;  // Replace 500 with the actual maximum ADC value

// Define the actual AC mains voltage scaling factor
const float voltageScalingFactor = 175.0 / maxADCValue;  // Replace 230.0 with the desired mains voltage

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the raw analog value from the ZMPT101 sensor
  int rawValue = analogRead(zmptSensorPin);

  // Scale the raw value to the actual AC mains voltage
  int voltage = (rawValue * (referenceVoltage / maxADCValue) * voltageScalingFactor) *100;

  // Print both the raw value and the scaled voltage to the serial monitor
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Add a delay to prevent rapid readings
  delay(1000);
}
