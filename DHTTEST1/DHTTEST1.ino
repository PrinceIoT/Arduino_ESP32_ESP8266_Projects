#include <DHT.h>;
//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float humi;
float temp; //Stores temperature value
float tempe;

void setup()
{
    Serial.begin(9600);
  dht.begin();

}

void loop()
{
    //Read data and store it to variables hum and temp
    humi = dht.readHumidity();
    hum=humi/100;
    tempe= dht.readTemperature();
    temp=tempe/10;
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(2000); //Delay 2 sec.
}

   
