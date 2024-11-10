#include <SoftwareSerial.h>

// Define the RX and TX pins for the software serial communication
// You can choose any digital pins for RX and TX
#define RX_PIN 6
#define TX_PIN 7

// Create a SoftwareSerial object
SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup() {
  // Start serial communication with the computer
  Serial.begin(9600);
 
  // Start software serial communication with another device
  mySerial.begin(9600);
}

void loop() {
  // Read data from the software serial port
  if (mySerial.available() > 0) {
    String data = mySerial.readString();
    // Print the received data to the Serial Monitor
    Serial.println(data);
    int index1 = data.indexOf('$');
    int index2 = data.indexOf('$', index1 + 1);
   
    String frequency_mains = data.substring(0, index1);
    String frequency_solar = data.substring(index1 + 1, index2);
  
    float freq_mains = frequency_mains.toFloat();
    float freq_solar = frequency_solar.toFloat();

    Serial.print("Frequency Mains: ");
    Serial.println(freq_mains);
    Serial.print("Frequency Solar : ");
    Serial.println(freq_solar);

    delay(1500);

    mySerial.println("1");
    
  }

  

}
