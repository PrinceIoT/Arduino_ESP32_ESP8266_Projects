
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#define ONE_WIRE_BUS 2  //pin 2 of arduino

    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature sensors(&oneWire);

    void setup(void)
    {
    Serial.begin(9600);
  
    Serial.println();
    sensors.begin(); 

    }
    void loop(void)
    {
    
    sensors.requestTemperatures();
    delay(100);
    float temp=sensors.getTempCByIndex(0);
    String sam= String(temp);
    //Serial.println(sam);
    if(sam == "-127.00")
    {
// do nothing
    }
    else{
    Serial.print("Temperature : ");
    //Serial.println(sensors.getTempCByIndex(0));
    Serial.print (sam);
    Serial.println();
    //delay(200);

    } 
   
    //delay(1000);
    }
