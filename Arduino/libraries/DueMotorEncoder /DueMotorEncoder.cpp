#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <DueMotorEncoder.h>

    DueMotorEncoder::DueMotorEncoder(short encoderLeft1Pin, short encoderLeft2Pin, short encoderRight1Pin, short encoderRight2Pin, updateEncoderTime) {

    }
    
    void DueMotorEncoder::Update() {

    }

    short DueMotorEncoder::GetSpeedLeft() {
      return 0;
    }

    short DueMotorEncoder::GetSpeedRight() {
      return 0;
    }

    unsigned long DueMotorEncoder::GetDistanceLeft() {
      return 0;
    }

    unsigned long DueMotorEncoder::GetDistanceRight() {
      return 0;
    }
