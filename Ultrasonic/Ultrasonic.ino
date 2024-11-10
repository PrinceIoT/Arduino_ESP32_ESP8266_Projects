
int Trig_pin=9;
int Echo_pin=8;

float duration_us,distance_cm;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trig_pin,OUTPUT);
  pinMode(Echo_pin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Trig_pin,HIGH);
  delay(10);
  digitalWrite(Trig_pin,LOW);

  //Pulse Duration
  duration_us=pulseIn(Echo_pin,HIGH);

  //Calculate distance
  distance_cm=0.017*duration_us;

  //Print
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.print("cm");

  delay(500);
  

}
