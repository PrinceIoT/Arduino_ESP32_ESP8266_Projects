//Program to 

//* Code for generating Modified Sine Wave*//

void setup() {

  // Setting  all four MOSFET as output

pinMode(2, OUTPUT); //  A+ gate of Q1 MOSFET 

pinMode(3, OUTPUT); // A- gate of Q2 MOSFET 


pinMode(4, OUTPUT); // B+ gate of Q3 MOSFET 

pinMode(5, OUTPUT); // B- gate of Q4 MOSFET 

}


void loop() {

  // put your main code here, to run repeatedly:

 // Initially all pin 2,3,4 and 5 are low 

  digitalWrite(2, HIGH);  // ON Q1 MOSFET

  delay(1);              //generate a delay of 1ms for zero level at the output

  digitalWrite(4, LOW);  // OFF Q3 MOSFET

  delayMicroseconds(1);  // generate a dead time of 1us



  digitalWrite(5, HIGH);  // ON Q4 MOSFET

  delay(9);               //generate a delay of 9ms for positive voltage(+12V) at the output

  digitalWrite(5, LOW);  // OFF Q4 MOSFET

  delayMicroseconds(1);  // generate a dead time of 1us

  

  digitalWrite(4, HIGH);  // ON Q3 MOSFET

  delay(1);                //generate a delay of 1ms for zero level at the output

  digitalWrite(2, LOW);  // OFF Q1 MOSFET

  delayMicroseconds(1);  // generate a dead time of 1us

  

  digitalWrite(3, HIGH);  // ON Q2 MOSFET

  delay(9); //9              //generate a delay of 9ms for negative voltage(-12V) at the output

  digitalWrite(3, LOW);  // OFF Q2 MOSFET

  delayMicroseconds(1);  // generate a dead time of 1us

}  
