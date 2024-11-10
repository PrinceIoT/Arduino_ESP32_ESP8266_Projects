#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(12, 13); // Software Serial pins 12 (RX) & 13 (TX)

void setup() {
  Serial.begin(9600);
  Serial2.begin(115200,SERIAL_8N1);
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println("V");

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println("A");

  Serial.print("Power: ");
  Serial.print(power);
  Serial.println("W");

  Serial.print("Energy: ");
  Serial.print(energy, 3);
  Serial.println("kWh");

  Serial.print("Frequency: ");
  Serial.print(frequency, 1);
  Serial.println("Hz");

  Serial.print("PF: ");
  Serial.println(pf);

  Serial.println();

  // Concatenate the values into a string
  //String dataString = "V:" + String(voltage) + "|C:" + String(current) + "|P:" + String(power) +
                    //  "|E:" + String(energy) + "|F:" + String(frequency) + "|PF:" + String(pf);
                      
  String dataString = String(voltage) + "$" + String(current) + "$" + String(power) +
                      "$" + String(energy) + "$" + String(frequency) + "$" + String(pf);

  // Send the concatenated string to Serial2
  Serial2.println(dataString);

  delay(2000);
}
