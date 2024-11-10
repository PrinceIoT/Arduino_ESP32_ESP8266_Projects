const int pos = 9;               // The PWM output pin for SPWM
const int neg = 11;              // The PWM output pin for SPWM
const int mainsZeroCross = 2;    // Digital pin for mains AC zero crossing detection
const int solarZeroCross = 3;    // Digital pin for solar AC zero crossing detection


volatile unsigned long mainsZCDetectedTime = 0;  // Timestamp of mains zero crossing
volatile unsigned long solarZCDetectedTime = 0;  // Timestamp of solar zero crossing
float mainsVoltage,mainsFrequency;
float solarVoltage;
boolean synchronizationStatus = false;

#include <SoftwareSerial.h>
#define RX_PIN 6
#define TX_PIN 7
SoftwareSerial mySerial(RX_PIN, TX_PIN);
String status;

int desiredFrequency = 50;
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
  pinMode(solarZeroCross, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(mainsZeroCross), detectMainsZeroCross, FALLING);
  attachInterrupt(digitalPinToInterrupt(solarZeroCross), detectSolarZeroCross, FALLING);
  
  Serial.begin(9600);
  mySerial.begin(115200);
}

void loop() {
  // Read mains voltage and frequency
  
  mainsFrequency = 50.0;
  // Check if mains parameters are available
  if (mainsZeroCross >0.0) {
    // Implement SPLL to synchronize solar AC signal with mains AC signal
    unsigned long startTime = micros();  // Record the start time of the cycle
    unsigned long elapsedTime = 0;
    float phaseError = 0;

    while (true) {  // Endless loop to keep checking phase error
      // Calculate phase error in degrees (-180 to 180)
      phaseError = calculatePhaseError();
      // Constrain phaseError within the range -180 to 180 degrees
      //phaseError = constrain(phaseError, -180, 180);

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

      // Check for synchronization
      if (abs(phaseError) < 200.0) {
        status = "";
        status ="1";
        synchronizationStatus = true;
        Serial.println("Synchronization Successful (1)");
        Serial.println(status);
        mySerial.println(status);
      } else {
        status = "";
        status = "2";
        synchronizationStatus = false;
        Serial.println("Synchronization Failed (0)");
        Serial.println(status);
        mySerial.println(status);
        
      }
    }
  } else {
    // Mains parameters are not available, use a hardcoded frequency for solar signal
    solarFrequency = 40.0;

    // Generate solar signal with a hardcoded frequency
    while (true) {
      // Adjust SPWM phase based on hardcoded frequency
      status = "";
      status = "3";
      int on_tym = int(100 * val[0]);
      int off_tym = 100 - on_tym;

      // Generate synchronized SPWM signals
      digitalWrite(neg, LOW);
      digitalWrite(pos, LOW);
      delayMicroseconds(off_tym);
      digitalWrite(pos, HIGH);
      delayMicroseconds(on_tym);

      synchronizationStatus = true;
      Serial.println("Synchronization Successful (1)");
      Serial.println(status);
      mySerial.println(status);
    }
  }
}

void detectMainsZeroCross() {
  mainsZCDetectedTime = micros();
}

void detectSolarZeroCross() {
  solarZCDetectedTime = micros();
}

float calculatePhaseError() {
  // Calculate phase error logic based on mains and solar zero crossing timestamps and frequencies
  float mainsCycleTime = 1000000.0 / mainsFrequency;    // Duration of one mains cycle in microseconds
  float phaseError = ((mainsZCDetectedTime - solarZCDetectedTime) / mainsCycleTime) * 180.0;  // Phase error in degrees
  Serial.print("phaseError: ");
  Serial.println(phaseError);
  Serial.print("mainsCycleTime:");
  Serial.println(mainsCycleTime);
  Serial.print("mainsZCDetectedTime:");
  Serial.println(mainsZCDetectedTime);
  Serial.print("solarZCDetectedTime:");
  Serial.println(solarZCDetectedTime);
  Serial.println();
  return phaseError;
}
