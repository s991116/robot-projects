#define SIN_TABLE_LENGTH (1000)
#define SIN_TABLE_FACTOR (1000.0)

unsigned int sinTable[SIN_TABLE_LENGTH];
double ticksPrDmm;

void UpdateSinTable(float COHeight_in_dmm, float VGyro) {
  for(int i=0; i<SIN_TABLE_LENGTH; i++) {
    float angle = (float)i * VGyro;
    sinTable[i] = COHeight_in_dmm * sin(angle) * SIN_TABLE_FACTOR;
  }
}

void UpdateWheelDistanceCount(float wheelRadius_in_dmm, int ticksPrRevolution) {
  ticksPrDmm = (2.0 * 3.14159 * wheelRadius_in_dmm)/((float) ticksPrRevolution);
}

int GetCOSpeed(int currentAngle, int lastAngle, int encoderTicksA, int encoderTicksB) {
  return GetHorizontalAngleDistance(currentAngle)-GetHorizontalAngleDistance(lastAngle) + GetHorizontalWheelDistance(encoderTicksA, encoderTicksB);
}

int GetHorizontalAngleDistance(int gyroAngleSpeed) {
  if(gyroAngleSpeed < 0)
  {
    return -(sinTable[-gyroAngleSpeed] / SIN_TABLE_FACTOR);
  }
  else
  {
    return sinTable[gyroAngleSpeed] / SIN_TABLE_FACTOR;
  }
}

int GetHorizontalWheelDistance(int encoderTicksA, int encoderTicksB) {
  int encoderTicks = (encoderTicksA + encoderTicksB) / 2;
  return encoderTicks*ticksPrDmm;
}
