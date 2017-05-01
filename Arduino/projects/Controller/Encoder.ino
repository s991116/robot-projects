volatile long EncoderCountA;
volatile long EncoderCountB;
  
void SetupMotorEncoders() {
  attachInterrupt(digitalPinToInterrupt(INT_A_PIN), EncoderACount, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_B_PIN), EncoderBCount, RISING);
}

void EncoderACount() {
  long t = micros();
  if(digitalReadFast(DIR_A_PIN))
    EncoderCountA--;
  else
    EncoderCountA++;
  interruptTime = micros()-t;
}

void EncoderBCount() {
  if(digitalReadFast(DIR_B_PIN))
    EncoderCountB++;
  else
    EncoderCountB--;
}

void UpdateEncoderCount() {
  CurrentEncoderCountA = EncoderCountA;
  EncoderCountA = 0;
  TotalEncoderCountA += CurrentEncoderCountA;
  CurrentEncoderCountB = EncoderCountB;
  EncoderCountB = 0;
  TotalEncoderCountB += CurrentEncoderCountB;
}

void ResetDistanceEncoderCountA()
{
  TotalEncoderCountA = 0;
}

void ResetDistanceEncoderCountB()
{
  TotalEncoderCountB = 0;
}

