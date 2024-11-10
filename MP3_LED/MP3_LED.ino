// The firmware utilizes MSGEQ7, an IC chip that divides the audio into seven bands. 
//The frequencies are peak detected, and output multiplexed to give a dc representation of the amplitude of each band.


int analogPin = 0; // MSGEQ7 OUT 
int strobePin = 2; // MSGEQ7 STROBE
int resetPin = 4; // MSGEQ7 RESET
int spectrumValue[7];
 

//MSGEQ7 OUT pin produces values of between 50-80 with no input hence we have to filter out the noise as below.
int filterValue = 80;
 
// We connect the LED_pins to the PWM arduino pinsLED pins connected to the PWM pins on the Arduino

int ledPinR = 9;
int ledPinG = 10;
int ledPinB = 11;
 
void setup()
{
  Serial.begin(9600);
  
  pinMode(analogPin, INPUT); //We get the input from the MSEQ7 OUT pin
  
  pinMode(strobePin, OUTPUT); //We write to the MSGEQ7 strobe and reset pins
  pinMode(resetPin, OUTPUT);
 
 
  analogReference(DEFAULT); // Use the dafult analog value of reference voltage as 5v
 
 // We initiate the startup values for the pins
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}
 
void loop()
{
  // Set reset pin low to enable strobe
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
 
  for (int i = 0; i < 7; i++)//The loop is used to get all 7 spectrum values from the MSGEQ7
  {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); // Used to enable get a stabilized output
 
    spectrumValue[i] = analogRead(analogPin);
 
    spectrumValue[i] = constrain(spectrumValue[i], filterValue, 1023);  // Constrain any value above 1023 or below filterValue

    spectrumValue[i] = map(spectrumValue[i], filterValue, 1023, 0, 255);  // Remap the value to a number between 0 and 255
    
    Serial.print(spectrumValue[i]);  // Remove serial stuff after debugging
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);
   }
 
   Serial.println();
 
   // Write the PWM values to the LEDs 
   analogWrite(ledPinR, spectrumValue[1]); 
   analogWrite(ledPinG, spectrumValue[4]); 
   analogWrite(ledPinB, spectrumValue[6]); 
}
