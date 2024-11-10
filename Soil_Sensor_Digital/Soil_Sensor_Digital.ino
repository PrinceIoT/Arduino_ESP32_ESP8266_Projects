int Moisture__dig_signal = 8; //Define the Digital Input on the Arduino for the sensor signal
int Sensor_State = 1; 
void setup() {
  pinMode(Moisture__dig_signal, INPUT); //Step pin as input
  Serial.begin(9600); // Start the serial communication
}
 
void loop() {
  Serial.print("Soil Moisture Level: ");
  Sensor_State = digitalRead(Moisture__dig_signal);
  if (Sensor_State == 1) {
    Serial.println("Wet");
  }
  else {
    Serial.println("Dry");
  }
  delay(200);
}
