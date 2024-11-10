int Moisture_signal = A0; //Define the Analog pin# on the Arduino for the soil moisture sensor signal
 
void setup() {
  Serial.begin(9600); // Start the serial communication
}
 
void loop() {
  int Moisture = analogRead(Moisture_signal);
  Serial.print("Soil Moisture Level: ");
  Serial.println(Moisture);
  delay(200);
}
