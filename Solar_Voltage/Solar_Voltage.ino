/* ReadAnalogVoltage 0 to 50 Volts - blog.circuits4you.com

   Reads an analog input on pin 0, converts it to voltage, and prints the  

   result to the serial monitor.

   Graphical representation is available using serial plotter   (Tools >   

   Serial Plotter menu)*/



// the setup routine runs once when you press reset:

void setup() {

  // initialize serial communication at 9600 bits per second:

  Serial.begin(9600);

}



// the loop routine runs over and over again forever:

void loop() {

  // read the input on analog pin 0:

  int sensorValue = analogRead(A9);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 50V):

  int voltage = sensorValue * (5.0 / 1024.0)*3.4; //voltage = value * (5.0/1023) * ((R1 + R2)/R2);

  // print out the value you read:
  Serial.println(sensorValue);

  Serial.print("Voltage: ");

  Serial.print(voltage);

  Serial.println(" V");

  delay(1000);

}
