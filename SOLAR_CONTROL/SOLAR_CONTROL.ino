
const int pos = 9;               
const int neg = 11;              
const int mainsZeroCross = 2;    
const int solarZeroCross = 3;    

volatile unsigned long mainsZCDetectedTime = 0;  
volatile unsigned long solarZCDetectedTime = 0;  
float mainsFrequency;
float solarFrequency;
boolean synchronizationStatus = false;

#include <SoftwareSerial.h>
#define RX_PIN 6
#define TX_PIN 7
SoftwareSerial mySerial(RX_PIN, TX_PIN);
String status;

const float amplitude = 255.0; 
const float frequency = 50.0;  
const float caes_frequency = 40.0;
int fr; 

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
  mainsFrequency = 50.0;
  
  if (mainsZeroCross > 0) {
    fr = period(frequency);
    generateSPWMWaveforms(frequency);
  } else {
    fr = periodc(caes_frequency);
    generateCAESWaveforms();
  }
}

void generateSPWMWaveforms(float currentFrequency) {
  unsigned long startTime = micros();  
  unsigned long elapsedTime = 0;
  float phaseError = 0;

  while (true) {
    phaseError = calculatePhaseError(); // phase error function
    int phaseAdjustment = map(phaseError, -180, 180, -50, 50);  // Constrain the phase error to between -180 to 180 and adjust it to with 100 seconds 

    for (int i = 0; i < 100; i++) {
      digitalWrite(neg, LOW);
      int on_tym = int(fr * val[i]) + phaseAdjustment;
      int off_tym = fr - on_tym;
      digitalWrite(pos, LOW);
      delayMicroseconds(off_tym);
      digitalWrite(pos, HIGH);
      delayMicroseconds(on_tym);
    }

    elapsedTime = micros() - startTime;

    if (abs(phaseError) < 200.0) {
      status = "1";
      synchronizationStatus = true;
      Serial.println("Synchronization Successful (1)");
      Serial.println(status);
      mySerial.println(status);
    } else {
      status = "2";
      synchronizationStatus = false;
      Serial.println("Synchronization Failed (0)");
      Serial.println(status);
      mySerial.println(status);
    }
  }
}

void generateCAESWaveforms() {
  while (true) {
    for(int i = 0; i < 100; i++) {
      digitalWrite(neg, LOW);
      int tym = int(fr * val[i]);
      int on_tym = fr - tym;
      digitalWrite(pos, LOW);
      delayMicroseconds(on_tym);
      digitalWrite(pos, HIGH);
      delayMicroseconds(int(tym));
    }
    
    for(int i = 0; i < 100; i++) {
      digitalWrite(pos, LOW);
      int tym = int(fr * val[i]);
      int on_tym = fr - tym;
      digitalWrite(neg, LOW);
      delayMicroseconds(on_tym);
      digitalWrite(neg, HIGH);
      delayMicroseconds(int(tym));
    }
  }
}

void detectMainsZeroCross() {
  mainsZCDetectedTime = micros();
}

void detectSolarZeroCross() {
  solarZCDetectedTime = micros();
}

int period(float frequency) {
  float pr = 1000000 / (frequency * 200);
  int fin = pr - 97;  // Adjust as needed
  return fin;
}

int periodc(float caes_frequency) {
  float pr = 1000000 / (caes_frequency * 200);
  int fin = pr - 6;  // Adjust as needed
  return fin;
}

float calculatePhaseError() {
  float mainsCycleTime = 1000000.0 / mainsFrequency;    
  float solarCycleTime = 1000000.0 / solarFrequency;    
  float phaseError = ((mainsZCDetectedTime - solarZCDetectedTime) / mainsCycleTime) * 180.0;  
  
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
