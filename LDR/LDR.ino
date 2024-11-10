//const int ledPin = 13;

const int ldrPin = A0;
const int ldrPin1 = A1;

void setup() {

Serial.begin(9600);

pinMode(ldrPin, INPUT);
pinMode(ldrPin1, INPUT);

}

void loop() {

int ldr = analogRead(ldrPin);
int ldr1 = analogRead(ldrPin1);

if(ldr < 500){
  Serial.print("LINES IN PHASE: ");
  }
else {
    Serial.print("LINES NOT IN PHASE: ");
    }
Serial.println(ldr);

Serial.println("Done");
delay(2000);

}
