inline void digitalWriteDirect(int pin, boolean val){
  if(val) g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  else    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}

inline int digitalReadDirect(int pin){
  return !!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin);
}


void InitializeEncoder()
{
  attachInterrupt(ENCODER_A_INTERRUPT_PIN, EncoderAInterrupt, RISING);
  attachInterrupt(ENCODER_B_INTERRUPT_PIN, EncoderBInterrupt, RISING);  
  pinMode(ENCODER_A_DIRECTION_PIN, INPUT);   
  pinMode(ENCODER_B_DIRECTION_PIN, INPUT);   
}

void EncoderAInterrupt() {
  byte direction = digitalReadDirect(ENCODER_A_DIRECTION_PIN);
  long t = micros();
  if(direction == LOW)
  {
    EncoderAInterruptPeriod = EncoderAInterruptTime - t;
    DistanceMotorA++;
  }
  else
  {
    EncoderAInterruptPeriod = t - EncoderAInterruptTime;
    DistanceMotorA--;
  }
  EncoderAInterruptTime = t;
}

void EncoderBInterrupt() {
  byte direction = digitalReadDirect(ENCODER_B_DIRECTION_PIN);
  long t = micros();
  if(direction == LOW)
  {
    EncoderBInterruptPeriod = EncoderBInterruptTime - t;
    DistanceMotorB++;
  }
  else
  {
    EncoderBInterruptPeriod = t - EncoderBInterruptTime;        
    DistanceMotorB--;
  }
  EncoderBInterruptTime = t; 
}
