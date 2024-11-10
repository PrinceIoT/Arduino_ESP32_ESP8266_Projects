// Arduino Mega 2560 Pro Mini code
#define trigPin 4
#define echoPin 5

void setup() {
  Serial.begin(9600);
  Serial2.begin(115200, SERIAL_8N1); // Initialize Serial2 for communication with ESP32
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // Send the distance to the ESP32 via Serial2
  Serial2.print("D:");
  Serial2.println(distance);

  delay(1000); // Adjust the delay as needed
}
