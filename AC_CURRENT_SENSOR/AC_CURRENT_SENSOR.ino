/*ACS712 Current Sensor Demo
   By miliohm.com
*/
#include "ACS712.h"
ACS712 sensor(ACS712_05B, A3);
//ACS712_20A sensor(ACS712_05B, A3);
//ACS712_30A sensor(ACS712_05B, A3);
void setup() {
  Serial.begin(9600);
  sensor.calibrate();
}
void loop() {
  float I = sensor.getCurrentAC();
//ignoring the value below 0.09
  if (I < 0.09) {
    I = 0;
  }
  Serial.println( I);
  delay(300);
}
