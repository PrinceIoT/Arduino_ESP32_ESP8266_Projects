#include <OneWire.h>
#include <DallasTemperature.h>

//Data wire
#define ONE_WIRE_BUS_PIN 4

OneWire oneWire(ONE_WIRE_BUS_PIN);

DallasTemperature sensors(&oneWire);
const int turbidityPin = A0; // Analog pin to which the turbidity sensor is connected


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Initialize the sensor
  sensors.begin();


}

void loop(void) {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();

 

   int turbidityValue = analogRead(turbidityPin);

  //  use index allows to read from multiple sensors
   float turbidity = map(turbidityValue, 0, 1023, 0, 300); // Adjust the mapping based on your sensor's specifications
   float pHValue = map(turbidityValue, 0, 300, 7, 4);
   

  Serial.print("Turbidity: ");
  Serial.println(turbidity);
  
  Serial.print(" | Water pH: ");
  Serial.println(pHValue);
  
  Serial.print("Degrees Celsius: ");
  Serial.println(sensors.getTempCByIndex(0));

  Serial.println();
  //Serial.print("Temperature by Freints");
  //Serial.println(sensors.getTempFByIndex(0));
  
  delay(1000);
  
}
