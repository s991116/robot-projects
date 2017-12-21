#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <DueMotorEncoder.h>

    short DueMotorEncoder::_encoderLeft1Pin = 0;
    short DueMotorEncoder::_encoderLeft2Pin = 0;
    short DueMotorEncoder::_encoderRight1Pin = 0;
    short DueMotorEncoder::_encoderRight2Pin = 0;
    short volatile DueMotorEncoder::_encoderLeftSteps = 0;
    short volatile DueMotorEncoder::_encoderRightSteps = 0;

    DueMotorEncoder::DueMotorEncoder(short encoderLeft1Pin, short encoderLeft2Pin, short encoderRight1Pin, short encoderRight2Pin, short updateEncoderTime) {
      
      _encoderLeft1Pin = encoderLeft1Pin;
      _encoderLeft2Pin = encoderLeft2Pin;
      _encoderRight1Pin = encoderRight1Pin;
      _encoderRight2Pin = encoderRight2Pin;
      _updateEncoderTime = updateEncoderTime;
      DueMotorEncoder::_updateEncoderTime = 0;

      attachInterrupt(encoderLeft1Pin, DueMotorEncoder::LeftEncoderInterrupt, CHANGE);
      attachInterrupt(encoderRight1Pin, DueMotorEncoder::RightEncoderInterrupt, CHANGE);

    }
    
    void DueMotorEncoder::Update() {
      if(millis() > DueMotorEncoder::_updateEncoderTime) {
        DueMotorEncoder::_speedLeft = _encoderLeftSteps;
        _encoderLeftSteps = 0;
        DueMotorEncoder::_distanceLeft += DueMotorEncoder::_speedLeft;
        
        DueMotorEncoder::_speedRight = _encoderRightSteps;
        _encoderRightSteps = 0;
        DueMotorEncoder::_distanceRight += DueMotorEncoder::_speedRight;
        
        DueMotorEncoder::_updateEncoderTime += DueMotorEncoder::_encoderUpdatePeriod;
      }
    }

    short DueMotorEncoder::GetSpeedLeft() {
      return DueMotorEncoder::_speedLeft;
    }

    short DueMotorEncoder::GetSpeedRight() {
      return DueMotorEncoder::_speedRight;
    }

    long DueMotorEncoder::GetDistanceLeft() {
      return DueMotorEncoder::_distanceLeft;
    }

    long DueMotorEncoder::GetDistanceRight() {
      return DueMotorEncoder::_distanceRight;
    }



    void DueMotorEncoder::LeftEncoderInterrupt() {
      if(digitalRead(_encoderLeft1Pin) == digitalRead(_encoderLeft2Pin))
        _encoderLeftSteps++;
      else
        _encoderLeftSteps--;
    }

    void DueMotorEncoder::RightEncoderInterrupt() {
      if(digitalRead(_encoderRight1Pin) == digitalRead(_encoderRight2Pin))
        _encoderRightSteps++;
      else
        _encoderRightSteps--;      
    }
