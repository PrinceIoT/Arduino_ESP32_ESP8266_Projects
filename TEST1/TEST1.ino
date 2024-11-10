#include "Arduino.h"

// The pin to which we connect the full wave rectified voltage
#define zeroPointPinSolar 3 // Change this to the appropriate pin for solar zero crossing

// Beeper pin
#define beepPin 11

// The counter we update in the Interrupt Service Routine (ISR)
// which must be marked as volatile
volatile unsigned int zpCounterSolar;
volatile unsigned int zpCounterAC;

// Forward declarations of all functions
void zeroPointDetectSolar();
void zeroPointDetectAC();
void beep();

// Setup    Setup     Setup
void setup() {
  Serial.begin(115200);

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
  pinMode(2, INPUT_PULLUP); // Change this to the appropriate AC pin
  attachInterrupt(digitalPinToInterrupt(2), zeroPointDetectAC, FALLING);

  // All done
  Serial.println("Setup complete");
}

// Loop just for demo
void loop() {
  // If we have exactly 1 second's worth of counters for either solar or AC
  // then beep and reset counters
  if (zpCounterSolar > 99 || zpCounterAC > 99) {
    zpCounterSolar = 0;
    zpCounterAC = 0;
    beep();
  }
}

// This is the ISR for solar zero crossing
void zeroPointDetectSolar() {
  // Update solar zero crossing counter
  zpCounterSolar++;
}

// This is the ISR for AC zero crossing
void zeroPointDetectAC() {
  // Update AC zero crossing counter
  zpCounterAC++;
}

// Beep just for demo
void beep() {
  digitalWrite(beepPin, HIGH);
  delay(500);
  digitalWrite(beepPin, LOW);

  Serial.println("Solar Counter: " + String(zpCounterSolar) + " | AC Counter: " + String(zpCounterAC));
}
