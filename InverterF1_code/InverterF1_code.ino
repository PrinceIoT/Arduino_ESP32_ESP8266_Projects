const int pos = 9;  // The PWM output pin
const int neg = 11;

// Waveform parameters
const float frequency = 40.0;  // Desired frequency in Hz
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

void setup() {
  pinMode(pos, OUTPUT);
  pinMode(neg, OUTPUT);
}

void loop() {
  for(int i = 0;i<100;i++){
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
  for(int i = 0;i<100;i++){
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
  }
  
