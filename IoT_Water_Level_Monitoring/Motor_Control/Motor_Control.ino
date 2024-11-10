int EN1=9;
int IN1=8;
int IN2=7;

int EN2=3;
int IN3=5;
int IN4=4;
void setup() {
  // put your setup code here, to run once:
  pinMode(EN1,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

}
void demoOne(){
  //Turn on Motor A
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  //Set speed to 200 out of possible range of 0-255
  analogWrite(EN1,200);
  //Turn on Motor B
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //Set speed to 200 out of possible range of 0-255
  analogWrite(EN2,200);

  delay(2000);

  // Change motor directions
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  delay(2000);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
void demoTwo(){
  //Function run the motors across a range of possible speeds.
  //Turn on motors
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  //Accelerate from zero to maximum speed
  for(int i=0;i<256;i++){
    analogWrite(EN1,i);
    analogWrite(EN2,i);
    delay(20);
  }
  //Decelerating
    for(int i=255;i>=0;--i){
    analogWrite(EN1,i);
    analogWrite(EN2,i);
    delay(20);
}
//turn off the motors
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  demoOne();
  delay(1000);

  demoTwo();
  delay(1000);
}
