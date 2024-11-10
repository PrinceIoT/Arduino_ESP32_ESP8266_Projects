#include <DHT.h>
#define Type DHT11

int sensePin=2;
DHT HT(sensePin,Type);
float Humidity;
float TempDeC;
float TempF;
int setTime=500;

int dtime=200;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
HT.begin();
delay(setTime);
}

void loop() {
  // put your main code here, to run repeatedly:
Humidity = HT.readHumidity();
TempDeC=HT.readTemperature();
TempF=HT.readTemperature(true);

Serial.print("Humidity: ");
Serial.print(Humidity);
Serial.println("Temperature:");
Serial.print(TempDeC);
Serial.print("C");
Serial.println(TempF);
Serial.print("F");
delay(dtime);

}
