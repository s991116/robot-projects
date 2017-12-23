#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <DueMotorEncoder.h>

    short DueMotorEncoder::_encoderPin1 = 0;
    short DueMotorEncoder::_encoderPin2 = 0;
    short volatile DueMotorEncoder::_encoderSteps = 0;

    DueMotorEncoder::DueMotorEncoder(short encoderPin1, short encoderPin2) {
      
      _encoderPin1 = encoderPin1;
      _encoderPin2 = encoderPin2;

      attachInterrupt(encoderPin1, DueMotorEncoder::EncoderInterrupt, CHANGE);
    }
    
    void DueMotorEncoder::Compute() {
        DueMotorEncoder::_speed = _encoderSteps;
        _encoderSteps = 0;
        DueMotorEncoder::_distance += DueMotorEncoder::_speed;        
    }

    short DueMotorEncoder::GetSpeed() {
      return DueMotorEncoder::_speed;
    }

    long DueMotorEncoder::GetDistance() {
      return DueMotorEncoder::_distance;
    }

    void DueMotorEncoder::EncoderInterrupt() {
      if(digitalRead(_encoderPin1) == digitalRead(_encoderPin2))
        _encoderSteps++;
      else
        _encoderSteps--;
    }