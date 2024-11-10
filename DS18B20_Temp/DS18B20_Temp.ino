#include <OneWire.h>
#include <DallasTemperature.h>

//Data wire
#define ONE_WIRE_BUS_PIN 4

OneWire oneWire(ONE_WIRE_BUS_PIN);

DallasTemperature sensors(&oneWire);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Initialize the sensor
  sensors.begin();

}

void loop(void) {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();

  Serial.print("Degrees Celsius: ");

  //  use index allows to read from multiple sensors
  
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("Temperature by Freints");
  Serial.println(sensors.getTempFByIndex(0));
  delay(5000);
  
}
