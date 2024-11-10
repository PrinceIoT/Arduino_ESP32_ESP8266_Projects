#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(100);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("RFM95 module initialization failed.");
    while (1);
  }
  Serial.println("RFM95 module initialization successful.");
  rf95.setFrequency(915.0);
  rf95.setTxPower(23);
}

void loop() {
  while (0);
  const char *message = "Hello, world!";
  rf95.send((uint8_t *)message, strlen(message));
  rf95.waitPacketSent();
  Serial.println("Message sent.");
  delay(1000);
}
