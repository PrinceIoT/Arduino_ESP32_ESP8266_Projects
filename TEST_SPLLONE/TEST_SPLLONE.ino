#include "Arduino.h"

const int pos = 9;  // The PWM output pin for the waveform
const int neg = 11; // Conflict: This pin is used for the beeper in the second code

// Waveform parameters
const float frequency = 50.0;  // Desired frequency in Hz
const float amplitude = 255.0; // Amplitude of the waveform (0-255)
int fr = 73;

const float val[100] = {0.03141, 0.06279, 0.09411, 0.12533, 0.15643, 0.18738, 0.21814, 0.24869, 0.27901, 0.30902, 
                         0.33874, 0.36812, 0.39715, 0.42578, 0.45399, 0.48175, 0.50904, 0.53583, 0.56208, 0.58779, 
                         0.61291, 0.63742, 0.66131, 0.68455, 0.70711, 0.72897, 0.75011, 0.77051, 0.79016, 0.80902, 
                         0.82708, 0.84433, 0.86074, 0.87631, 0.89101, 0.90483, 0.91775, 0.92978, 0.94088, 0.95106, 
                         0.96030, 0.96858, 0.97591, 0.98227, 0.98768, 0.99211, 0.99556, 0.99803, 0.99952, 1.00000, 
                         0.99952, 0.99803, 0.99556, 0.99211, 0.98768, 0.98227, 0.97591, 0.96858, 0.96030, 0.95106, 
                         0.94088, 0.92978, 0.91775, 0.90483, 0.89101, 0.87631, 0.86074, 0.84433, 0.82708, 0.80902, 
                         0.79016, 0.77051, 0.75011, 0.72897, 0.70711, 0.68455, 0.66131, 0.63742, 0.61291, 0.58779, 
                         0.56208, 0.53583, 0.50904, 0.48175, 0.45399, 0.42578, 0.39715, 0.36812, 0.33874, 0.30902, 
                         0.27901, 0.24869, 0.21814, 0.18738, 0.15643, 0.12533, 0.09411, 0.06279, 0.03141, 0.00000};

// Zero-crossing detection pins
#define zeroPointPinSolar 3 // Change this to the appropriate pin for solar zero crossing
#define zeroPointPinAC 2    // Change this to the appropriate AC pin

// Beeper pin
#define beepPin 8 // Using the neg pin for the beeper

volatile unsigned int zpCounterSolar;
volatile unsigned int zpCounterAC;

void setup() {
  Serial.begin(9600);

  // Initialise beeper
  pinMode(beepPin, OUTPUT);
  beep();

  // Initialise zero point counters (100 counts per second)
  zpCounterSolar = 0;
  zpCounterAC = 0;

  // Interrupt on pin for solar zero point threshold
  pinMode(zeroPointPinSolar, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(zeroPointPinSolar), zeroPointDetectSolar, FALLING);

  // Interrupt on pin for AC zero point threshold
  pinMode(zeroPointPinAC, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(zeroPointPinAC), zeroPointDetectAC, FALLING);

  // All done
  Serial.println("Setup complete");
}

void loop() {
  // Your combined logic here

  for (int i = 0; i < 100; i++) {
    digitalWrite(neg,LOW);
    int a = 0;
    int tym = int(fr*val[i]);
    int on_tym = fr-tym;
      digitalWrite(pos,LOW);
      delayMicroseconds(on_tym);
      digitalWrite(pos,HIGH);
      delayMicroseconds(int(tym));
      a++;
  }

  for (int i = 0; i < 100; i++) {
    digitalWrite(pos,LOW);
    int a = 0;
    int tym = int(fr*val[i]);
    int on_tym = fr-tym;
      digitalWrite(neg,LOW);
      delayMicroseconds(on_tym);
      digitalWrite(neg,HIGH);
      delayMicroseconds(int(tym));
      a++;
  }

  // If we have exactly 1 second's worth of counters for either solar or AC
  // then beep and reset counters
  if (zpCounterSolar > 99 || zpCounterAC > 99) {
    zpCounterSolar = 0;
    zpCounterAC = 0;
    beep();
  }
}

void zeroPointDetectSolar() {
  // Update solar zero crossing counter
  zpCounterSolar++;
}

void zeroPointDetectAC() {
  // Update AC zero crossing counter
  zpCounterAC++;
}

void beep() {
  digitalWrite(beepPin, HIGH);
  delay(500);
  digitalWrite(beepPin, LOW);

  Serial.println("Solar Counter: " + String(zpCounterSolar) + " | AC Counter: " + String(zpCounterAC));
}
