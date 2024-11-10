const int zmptPin = A7; // Analog pin connected to ZMPT101B sensor
const float voltageReference = 5.0; // Reference voltage of the microcontroller (in volts)
const float sensorSensitivity = 1.0; // Sensitivity of the ZMPT101B sensor (in volts per volt)

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(zmptPin); // Read analog voltage from ZMPT101B sensor
  float voltage = (sensorValue / 512.0) * voltageReference; // Convert sensor value to voltage
  float actualVoltage = voltage / sensorSensitivity; // Calculate actual AC voltage

  Serial.print("Raw Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(", Voltage: ");
  Serial.println(actualVoltage);

  delay(1000); // Delay for 1 second before reading again
}
