inline void digitalWriteDirect(int pin, boolean val){
  if(val) g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  else    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}

inline int digitalReadDirect(int pin){
  return !!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin);
}

unsigned long EncoderInterruptPeriodA;
unsigned long EncoderInterruptTimeA;

bool ForwardDirectionA;

void InitializeEncoder()
{
  attachInterrupt(ENCODER_A_INTERRUPT_PIN, EncoderAInterrupt, CHANGE);
  attachInterrupt(ENCODER_B_INTERRUPT_PIN, EncoderBInterrupt, CHANGE);  
  pinMode(ENCODER_A_DIRECTION_PIN, INPUT);   
  pinMode(ENCODER_B_DIRECTION_PIN, INPUT);   
}

void ResetDistanceEncoderCountA()
{
  DistanceEncoderCountA = 0;
}

void ResetDistanceEncoderCountB()
{
  DistanceEncoderCountB = 0;
}

void UpdateCurrentEncoderA()
{
  CurrentEncoderCountA = EncoderCountA;
  EncoderCountA = 0;
  DistanceEncoderCountA = DistanceEncoderCountA + CurrentEncoderCountA;
}

void UpdateCurrentEncoderB()
{
  CurrentEncoderCountB = EncoderCountB;
  EncoderCountB = 0;
  DistanceEncoderCountB = DistanceEncoderCountB + CurrentEncoderCountB;
}

void EncoderAInterrupt() {

  byte direction = digitalReadDirect(ENCODER_A_DIRECTION_PIN);
  byte interrupt = digitalReadDirect(ENCODER_A_INTERRUPT_PIN);

  if(direction == interrupt)
  {
    ForwardDirectionA = true;
    EncoderCountA++;
  }
  else
  {
    ForwardDirectionA = false;
    EncoderCountA--;
  }
  
  unsigned long timer = micros();
  InterruptPeriodA = timer - EncoderInterruptTimeA;
  EncoderInterruptTimeA = timer;

//  UpdateMotorPowerAfterInterrupt();
}

void EncoderBInterrupt() {
  byte direction = digitalReadDirect(ENCODER_B_DIRECTION_PIN);
  byte interrupt = digitalReadDirect(ENCODER_B_INTERRUPT_PIN);
  if(direction == interrupt)
  {
    EncoderCountB++;
  }
  else
  {
    EncoderCountB--;
  }
}
