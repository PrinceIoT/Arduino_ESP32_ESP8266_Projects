// FIRST MOTOR
int ENA= 5;
int IN1=6;
int IN2=7;

// SECOND MOTOR
int ENB=10;
int IN3=8;
int IN4=9;

void setup() {
  // FIRST MOTOR
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  // put your setup code here, to run once:
  //MOTOR TWO
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  //MOTORA TO RUN CLOCKWISE AT HIGH SPEED
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,255);
  //delay(500);

  //MOTORB TO RUN CLOCKWISE AT HIGH SPEED
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENB,255);
  delay(500);

  //STOP THE MOTOR
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(200);

  // MOTOR TO RUN COUNTERCLOCKWISE
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,255);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENB,255);
  delay(500);

  //STOP THE MOTOR
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(200);

  // MOTOR TO RUN CLOCKWISE AT FULL SPEED
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,255);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,255);
  delay(10000);
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
