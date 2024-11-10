int sensorPin = A0;
int sensorInput;
double temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorInput=analogRead(sensorPin);
  temp = (double)sensorInput/1024;
  temp = (temp*5)-0.5;
  temp = temp*100;

  Serial.print("Current Temperature: ");
  Serial.println(temp);
  

}
