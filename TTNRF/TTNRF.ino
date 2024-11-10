#include <SPI.h>
#include <RH_RF95.h>
#include <lmic.h>
#include <hal/hal.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

// TTN
static const u1_t PROGMEM DEVEUI[8]={ '70B3D57ED005BC5B' };
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}

static const u1_t PROGMEM APPEUI[8]={ 'n/a' };
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}

static const u1_t PROGMEM APPKEY[16] = { 'F42BDDEE670E9B0BC5A1D5A8929F3E3B' };
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

void setup() {
  // initialize RFM95W
  Serial.begin(9600);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
}

static osjob_t sendjob;
void do_send(osjob_t* j){
  // read sensor data and pack into payload
  int humidity=analogRead(A0);
  //float temperature = ...;
  //int SensorValue = ...;
  uint8_t payload[1];
 // payload[0] = (uint8_t)(temperature * 10);
  payload[1] = (uint8_t)(humidity * 10);
  //payload[2] = 0;
 // payload[3] = 0;
  
  // send payload using RFM95W
  rf95.send(payload, sizeof(payload));
  rf95.waitPacketSent();

  // schedule next send
  os_setTimedCallback(j, os_getTime()+sec2osticks(30), do_send);
}
