#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MotorEncoder.h>

    short MotorEncoder::_encoderPin1 = 0;
    short MotorEncoder::_encoderPin2 = 0;
    short volatile MotorEncoder::_encoderSteps = 0;

    MotorEncoder::MotorEncoder(short encoderPin1, short encoderPin2) {
      
      _encoderPin1 = encoderPin1;
      _encoderPin2 = encoderPin2;

      attachInterrupt(encoderPin1, MotorEncoder::EncoderInterrupt, CHANGE);
    }
    
    void MotorEncoder::Compute() {
        MotorEncoder::_speed = _encoderSteps;
        _encoderSteps = 0;
        MotorEncoder::_distance += MotorEncoder::_speed;        
    }

    short MotorEncoder::GetSpeed() {
      return MotorEncoder::_speed;
    }

    long MotorEncoder::GetDistance() {
      return MotorEncoder::_distance;
    }

    void MotorEncoder::EncoderInterrupt() {
      if(digitalRead(_encoderPin1) == digitalRead(_encoderPin2))
        _encoderSteps++;
      else
        _encoderSteps--;
    }