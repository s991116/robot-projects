#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MotorEncoder.h>

    MotorEncoder::MotorEncoder(short encoderPin1, short encoderPin2, bool direction) {      
      _encoderPin1 = encoderPin1;
      _encoderPin2 = encoderPin2;
      _encoderSteps = 0;
      if(direction) {
        EncoderInterruptFunc = &MotorEncoder::EncoderInterruptDirect;
      }
      else {
        EncoderInterruptFunc = &MotorEncoder::EncoderInterruptReverse;
      }
    }
    
    void MotorEncoder::Compute() {
        _speed = _encoderSteps;
        _encoderSteps = 0;
        _distance += _speed;        
    }

    short MotorEncoder::GetSpeed() {
      return _speed;
    }

    long MotorEncoder::GetDistance() {
      return _distance;
    }

    void MotorEncoder::EncoderInterrupt() {
      (*this.*EncoderInterruptFunc)();
    }

    void MotorEncoder::EncoderInterruptDirect() {
      if(digitalRead(_encoderPin1) == digitalRead(_encoderPin2))
        _encoderSteps++;
      else
        _encoderSteps--;
    }

    void MotorEncoder::EncoderInterruptReverse() {
      if(digitalRead(_encoderPin1) != digitalRead(_encoderPin2))
        _encoderSteps++;
      else
        _encoderSteps--;
    }