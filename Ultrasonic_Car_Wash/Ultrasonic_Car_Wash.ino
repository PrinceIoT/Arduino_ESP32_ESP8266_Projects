
const int trigPin = 13;//D7
const int echoPin = 14;//D5;
#define Relay_Pin 5 //D1

//define sound velocity in cm/uS
#define SOUND_VELOCITY 000.034
//tank capacity in litres
#define TANK_CAPACITY 2000;


long duration;
float distance_cm;
float Capacity_litres;


void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(Relay_Pin,OUTPUT);
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
  distance_cm = duration * SOUND_VELOCITY/2;

  //Calculate tank capacity
  Capacity_litres=(distance_cm*2000)/1194;

  //Control
  if(distance_cm > 716){
    digitalWrite(Relay_Pin,HIGH);
  }
  else{
    digitalWrite(Relay_Pin,LOW);
  }
 
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (m): ");
  Serial.println(distance_cm);
  Serial.print("Tank Capacity (Litres): ");
  Serial.println(Capacity_litres);
  Serial.println("Done");
  
  
  delay(5000);
}
