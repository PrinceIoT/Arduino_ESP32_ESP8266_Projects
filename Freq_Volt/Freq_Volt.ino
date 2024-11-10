#define volt_in A0    //analog voltage read pin
volatile uint16_t t_period;
uint16_t ADC_value = 0;
float volt, freq;

void isr()
{
  t_period = TCNT1; //store TCNT1 value in t_period
  TCNT1 = 0;    //reset Timer1
  ADC_value = analogRead(volt_in);  //read analog voltage
}

float get_freq()
{
  uint16_t timer = t_period;
  if(timer==0)
    return 0;     // to avoid division by zero
  else
    return 16000000.0/(8UL*timer); // frequency is given by f = clk_freq/(prescaler*timeperiod)
}

void setup()
{
  TCCR1A = 0;
  TCCR1B = bit(CS11); //set prescaler to 8
  TCNT1 = 0;    //reset Timer1 value
  TIMSK1 = bit(TOIE1);  //enable Timer1 overflow interrupt
  EIFR |= bit(INTF0); // clear INT0 interrupt flag
  Serial.begin(9600);
}

void loop()
{
  attachInterrupt(0, isr, RISING);  //enable external interrupt (INT0)
  delay(1000);
  detachInterrupt(0);
  freq = get_freq();
  volt = ADC_value*0.33;
  String buf;
  buf += String(freq, 3);
  buf += F("Hz\t");
  buf += String(volt);
  buf += F("Volts");
  Serial.println(buf);
}
