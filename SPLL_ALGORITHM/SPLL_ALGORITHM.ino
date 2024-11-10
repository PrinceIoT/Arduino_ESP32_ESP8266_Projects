const int pos = 9;               // The PWM output pin for SPWM
const int neg = 11;              // The PWM output pin for SPWM
const int mainsZeroCross = 2;    // Digital pin for mains AC zero crossing detection
const int solarVoltagePin = A0;  // Analog pin for solar voltage sensor
const int mainsVoltagePin = A1;  // Analog pin for mains voltage sensor
const int solarCurrentPin = A2;  // Analog pin for solar current sensor
const int mainsCurrentPin = A3;  // Analog pin for mains current sensor

volatile unsigned long mainsZCDetectedTime = 0;  // Timestamp of mains zero crossing
volatile unsigned long solarZCDetectedTime = 0;  // Timestamp of solar zero crossing
float mainsVoltage, mainsCurrent, mainsFrequency;
float solarVoltage, solarCurrent, solarFrequency;

 // Your SPWM lookup table
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

void setup() {
  pinMode(pos, OUTPUT);
  pinMode(neg, OUTPUT);
  pinMode(mainsZeroCross, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(mainsZeroCross), detectMainsZeroCross, FALLING);
  
  Serial.begin(9600);
}

void loop() {
  // Read mains and solar voltage, current, and frequency
  mainsVoltage = analogRead(mainsVoltagePin) * (5.0 / 1023.0) * 220.0;  // Convert analog reading to voltage (assuming 5V reference and 220V mains)
  mainsCurrent = analogRead(mainsCurrentPin) * (5.0 / 1023.0) * 30.0;   // Convert analog reading to current (assuming 5V reference and 30A max current)
  mainsFrequency = 1000000.0 / (mainsZCDetectedTime / 2);                 // Calculate mains frequency (assuming half-cycle duration in microseconds)
  
  solarVoltage = analogRead(solarVoltagePin) * (5.0 / 1023.0) * 220.0;  // Convert analog reading to voltage (assuming 5V reference and 220V max solar voltage)
  solarCurrent = analogRead(solarCurrentPin) * (5.0 / 1023.0) * 10.0;   // Convert analog reading to current (assuming 5V reference and 10A max current)
  solarFrequency = 1000000.0 / (solarZCDetectedTime / 2);                // Calculate solar frequency (assuming half-cycle duration in microseconds)

  // Implement SPLL to synchronize solar AC signal with mains AC signal
  unsigned long startTime = micros();  // Record the start time of the cycle
  unsigned long elapsedTime = 0;
  float phaseError = 0;

  while (elapsedTime < 20000) {  // Synchronize for 20ms (50 Hz)
    // Calculate phase error in degrees (-180 to 180)
    phaseError = calculatePhaseError();

    // Adjust SPWM phase based on phase error
    int phaseAdjustment = map(phaseError, -180, 180, -50, 50);  // Map phase error to phase adjustment (-50 to 50 microseconds)

    // Generate synchronized SPWM signals
    for (int i = 0; i < 100; i++) {
      digitalWrite(neg, LOW);
      int on_tym = int(100 * val[i]) + phaseAdjustment;
      int off_tym = 100 - on_tym;
      digitalWrite(pos, LOW);
      delayMicroseconds(off_tym);
      digitalWrite(pos, HIGH);
      delayMicroseconds(on_tym);
    }

    elapsedTime = micros() - startTime;
  }

  // Print readings to Serial Monitor
  Serial.print("Mains Voltage: ");
  Serial.print(mainsVoltage);
  Serial.print("V, Mains Current: ");
  Serial.print(mainsCurrent);
  Serial.print("A, Mains Frequency: ");
  Serial.print(mainsFrequency);
  Serial.print("Hz, Solar Voltage: ");
  Serial.print(solarVoltage);
  Serial.print("V, Solar Current: ");
  Serial.print(solarCurrent);
  Serial.print("A, Solar Frequency: ");
  Serial.print(solarFrequency);
  Serial.println("Hz");
}

void detectMainsZeroCross() {
  mainsZCDetectedTime = micros();
}

float calculatePhaseError() {
  // Calculate phase error logic based on mains and solar zero crossing timestamps
  
   float mainsCycleTime = mainsZCDetectedTime / 2.0;    // Duration of one mains cycle in microseconds
   float solarCycleTime = solarZCDetectedTime / 2.0;    // Duration of one solar cycle in microseconds
   float phaseError = ((mainsCycleTime - solarCycleTime) / mainsCycleTime) * 180.0;  // Phase error in degrees
   return phaseError;
}
