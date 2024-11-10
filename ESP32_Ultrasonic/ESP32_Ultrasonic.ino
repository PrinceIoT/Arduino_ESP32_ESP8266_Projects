// ESP32 code

#define RX_PIN 16
#define TX_PIN 17

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the distance data from Arduino Mega
    String data = Serial.readStringUntil('\n');
    Serial2.println(data); // Send data to the Arduino Mega using Serial2
    Serial.print("Sent Data to Mega: ");
    Serial.println(data);
  }

  if (Serial2.available() > 0) {
    // Read data from Arduino Mega via Serial2
    String dataFromMega = Serial2.readStringUntil('\n');
    Serial.print("Received Data from Mega: ");
    Serial.println(dataFromMega);
    // You can process the data or take any action here
  }
}
