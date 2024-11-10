// ... (include statements)
#include <SoftwareSerial.h>
const int pos = 9;  // The PWM output pin
const int neg = 11;
#define RX_PIN 6
#define TX_PIN 7

float calculatePhaseError(float mainsFreq, float solarFreq);
float performPIControl(float error);
void generateSPWM(float phaseCorrection);
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

SoftwareSerial mySerial(RX_PIN, TX_PIN);

const float proportionalGain = 0.9;  // Proportional gain
const float integralGain = 0.03;     // Integral gain
const int delayTime = 1000;           // Delay time in milliseconds
const float defaultSPWMFrequency = 40.0;  // Default SPWM frequency when mainsAC is not available

void setup() {
  pinMode(pos, OUTPUT);
  pinMode(neg, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available() > 0) {
    String data = mySerial.readString();
    Serial.print(data);

    int index1 = data.indexOf('$');
    int index2 = data.indexOf('$', index1 + 1);

    String frequency_mains = data.substring(0, index1);
    String frequency_solar = data.substring(index1 + 1, index2);

    float mainsFrequency = frequency_mains.toFloat();
    float solarFrequency = frequency_solar.toFloat();

    Serial.print("Frequency Mains: ");
    Serial.println(mainsFrequency);
    Serial.print("Frequency Solar : ");
    Serial.println(solarFrequency);

    // Solar Phase Error
    float phaseError = 0.0;

    if (mainsFrequency > 45.0) {
      phaseError = calculatePhaseError(mainsFrequency, solarFrequency);
      phaseError = performPIControl(phaseError);
      generateSPWM(phaseError);

      if (abs(phaseError) < 0.1) {
        Serial.println("1");
        mySerial.println("1");
      } else {
        Serial.println("0");
        mySerial.println("0");
      }
    } else {
      generateSPWM(defaultSPWMFrequency);
    }

    delay(delayTime); // Delay after processing received data
  }
}

float calculatePhaseError(float mainsFreq, float solarFreq) {
  return (360.0 * (solarFreq - mainsFreq)) / mainsFreq;
}

float performPIControl(float error) {
  static float integral = 0.0;
  integral += error;
  return proportionalGain * error + integralGain * integral;
}

void generateSPWM(float phaseCorrection) {
  for (int i = 0; i < 100; i++) {
    // Positive cycle
    digitalWrite(neg, LOW);
    delayMicroseconds(100 - int(100 * val[i] + phaseCorrection));
    digitalWrite(pos, LOW);
    delayMicroseconds(int(100 * val[i] + phaseCorrection));
    digitalWrite(pos, HIGH);

    // Negative cycle
    digitalWrite(pos, LOW);
    delayMicroseconds(100 - int(100 * val[i] + phaseCorrection));
    digitalWrite(neg, LOW);
    delayMicroseconds(int(100 * val[i] + phaseCorrection));
    digitalWrite(neg, HIGH);
  }
}
