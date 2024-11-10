 int currentPin = A0;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double VoltageValue = 0;



void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  VoltageValue = ((adcVoltage - offsetVoltage) / sensitivity);

  Serial.print("Raw Sensor Value = " );
  Serial.print(adcValue);
  Serial.print("");
  Serial.print("Voltage Value: = ");
  Serial.println(VoltageValue);

  delay(500);

}
