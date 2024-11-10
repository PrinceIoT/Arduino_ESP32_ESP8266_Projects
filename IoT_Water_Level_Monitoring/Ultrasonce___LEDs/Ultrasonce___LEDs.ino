
int echoPin=4;
int trigPin=2;

int BLUELED=7;
int REDLED=8;
int GREENLED=12;
int WHITELED=13;


long duration=0;
int distance=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);

  pinMode(BLUELED,OUTPUT);
  pinMode(REDLED,INPUT);
  pinMode(GREENLED,OUTPUT);
  pinMode(WHITELED,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin,LOW);
 
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.017;
  Serial.print("Distance: " );
  Serial.println(distance);
  //Serial.print("cm");

  if (distance < 200){
    digitalWrite(BLUELED,HIGH);
    }
  else{
    digitalWrite(BLUELED,LOW);
    }

  if (distance < 400){
    digitalWrite(REDLED,HIGH);
    }
  else{
    digitalWrite(REDLED,LOW);
    }

  if (distance < 600){
    digitalWrite(GREENLED,HIGH);
    }
  else{
    digitalWrite(GREENLED,LOW);
    }

  if (distance > 900){
    digitalWrite(WHITELED,HIGH);
    }
  else{
    digitalWrite(WHITELED,LOW);
    }
  }
