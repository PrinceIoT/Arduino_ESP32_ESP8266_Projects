#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 10
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  if(!rf95.init()){
    Serial.println("RFM95 module initialization.");
    while(1);
  }
  Serial.println("Initialization successfully done");
  rf95.setFrequency(868.0);
  rf95.setTxPower(23);
  }

void loop() {
  // put your main code here, to run repeatedly:
  const char*message = "Hello, World";
  rf95.send((uint8_t*)message,strlen(message));
  rf95.waitPacketSent();

  Serial.println("Message sent");

  delay(1000);

}
