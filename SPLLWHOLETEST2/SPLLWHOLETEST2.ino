#include "Arduino.h"

// The pin to which we connect the full wave rectified voltage
#define zeroPointPinSolar 3 // Change this to the appropriate pin for solar zero crossing
#define zeroPointPinAC 2    // Change this to the appropriate AC pin

// Beeper pin
#define beepPin 11

// Waveform parameters
const int pos = 9;  // The PWM output pin for positive half-cycle
const int neg = 10; // The PWM output pin for negative half-cycle
const float frequencyAC = 50.0; // Mains frequency
const float amplitude = 255.0; // Amplitude of the AC waveform (0-255)

// Counters for zero crossings
volatile unsigned int zpCounterSolar;
volatile unsigned int zpCounterAC;

// Flags for synchronization
bool isMainsAvailable = false;
bool isSynchronized = false;

// PI Control parameters
const float Kp = 0.1; // Proportional gain
const float Ki = 0.01; // Integral gain

float integralTerm = 0.0;                 

// Lookup table for sine wave
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

// Forward declarations of all functions
void zeroPointDetectSolar();
void zeroPointDetectAC();
void beep();
void generateWaveform(float phaseAdjustment);

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
  pinMode(zeroPointPinAC, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(zeroPointPinAC), zeroPointDetectAC, FALLING);

  // Waveform generation pins
  pinMode(pos, OUTPUT);
  pinMode(neg, OUTPUT);

  // All done
  Serial.println("Setup complete");
}

void loop() {
  // Check if Mains parameters are available
  if (zpCounterAC > 100) {
    isMainsAvailable = true;
  } else {
    isMainsAvailable = false;
  }

  // Check for synchronization
  if (isMainsAvailable) {
    float mainsFrequency = 100.0 * zpCounterAC / frequencyAC; // Calculate mains frequency
    float solarFrequency = 100.0 * zpCounterSolar / frequencyAC; // Assume solar frequency is the same as mains

    float phaseError = mainsFrequency - solarFrequency; // Calculate phase error

    // PI Control
    float proportionalTerm = Kp * phaseError;
    integralTerm += Ki * phaseError;

    // Calculate the phase adjustment based on PI control output
    float phaseAdjustment = proportionalTerm + integralTerm;

    // Check if the phase error is within a tolerance (adjust as needed)
    if (abs(phaseError) < 0.1) {
      isSynchronized = true;
      Serial.println("Synchronized: 1");
    } else {
      isSynchronized = false;
      Serial.println("Synchronized: 0");

      // Adjust the phase of the solar waveform using PI control
      generateWaveform(phaseAdjustment);
    }
  }

  // Your additional control logic goes here
  if (isSynchronized) {
    // Perform actions when synchronized
    // For example, control an inverter, send power to the grid, etc.
    // This is a placeholder, replace it with your actual logic
    Serial.println("Inverter synchronized with Mains");
  } else {
    // Perform actions when not synchronized
    // For example, keep generating power but not sending it to the grid
    Serial.println("Generating waveform with PI control");
  }

  // Reset counters
  zpCounterSolar = 0;
  zpCounterAC = 0;

  // Generate AC waveform
  generateWaveform(0.0); // No phase adjustment when synchronized
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
}

void generateWaveform(float phaseAdjustment) {
  // Generate positive half-cycle
  for (int i = 0; i < 100; i++) {
    analogWrite(pos, amplitude * val[i]);
    delayMicroseconds(200); // Adjust delay as needed
  }

  // Introduce phase adjustment by delaying the negative half-cycle
  delayMicroseconds(phaseAdjustment);

  // Generate negative half-cycle
  for (int i = 0; i < 100; i++) {
    analogWrite(neg, amplitude * val[i]);
    delayMicroseconds(200); // Adjust delay as needed
  }
}
