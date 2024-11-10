#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

#define BAND 915.0

// Replace the following with your own values
#define DEV_EUI "0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x05, 0xBC, 0x5B"
#define APP_EUI "0x26, 0x0B, 0x68, 0xFD"
#define APP_KEY "0xF4, 0x2B, 0xDD, 0xEE, 0x67, 0x0E, 0x9B, 0x0B, 0xC5, 0xA1, 0xD5, 0xA8, 0x92, 0x9F, 0x3E, 0x3B"

RH_RF95 rf95(RFM95_CS, RFM95_INT);
void setup()
{
  Serial.begin(9600);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(100);

  if (!rf95.init())
  {
    Serial.println("RFM95 module init failed");
    while (1);
  }
  Serial.println("RFM95 module init OK!");

  rf95.setFrequency(BAND);

  rf95.setTxPower(23);

  rf95.setThisAddress(DEV_EUI);
  rf95.setHeaderFrom(DEV_EUI);
  rf95.setHeaderTo(APP_EUI);
  rf95.setHeaderId((uint8_t *)APP_KEY);
}

void loop()
{
  
  float temperature = analogRead(A0); // replace with your own sensor reading
  float humidity = 50.0; // replace with your own sensor reading

  String message = "Temperature: " + String(temperature) + "C, Humidity: " + String(humidity) + "%";

  rf95.send((uint8_t *)message.c_str(), message.length());
  rf95.waitPacketSent();
  //Serial.println(temperature);
  Serial.println("Sent: " + message);

  delay(1000);
}
