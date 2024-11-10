int output1=7; // Pin 7 is set as an output1
int output2=8; // Pin 8 is set as an output2
void setup() {
 pinMode(output1,OUTPUT); // Output 1 is set as an OUTPUT
 pinMode(output2,OUTPUT); // Output 2 is set as an OUTPUT
 }
void loop() {
digitalWrite(output1,LOW); // Take the output1 to LOW level of 0V
 delayMicroseconds(1600); //delay for a period of 1.6mS
 digitalWrite(output1,HIGH); // Take the output1 to HIGH level of +5V
 delayMicroseconds(6800); //delay for a period of 6.8mS
 digitalWrite(output1,LOW); // Take the output1 to LOW level of 0V
delayMicroseconds(1600); //delay for a period of 1.6mS
 digitalWrite(output2,LOW); // Take the output2 to LOW level of 0V
 delayMicroseconds(1600); //delay for a period of 1.6mS
 digitalWrite(output2,HIGH); //Take the output2 to HIGH level of +5V
 delayMicroseconds(6800); //delay for a period of 6.8mS
digitalWrite(output2,LOW); // Take the output2 to LOW level of 0V
delayMicroseconds(1600); //delay for a period of 1.6mS
}
