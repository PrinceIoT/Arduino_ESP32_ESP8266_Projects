int LedPin=13;
int PirPin=12;
int holdPir=0;
int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
  pinMode(PirPin,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  holdPir=digitalRead(PirPin);
  if(holdPir==HIGH){
    count ++;
    digitalWrite(LedPin,HIGH);
    Serial.println("Motion Sensored");
    Serial.print(count);
    delay(5000);
    }
    else{
    digitalWrite(LedPin,LOW);
    }

}
