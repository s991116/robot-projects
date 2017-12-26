#ifndef MotorEncoder_H
#define MotorEncoder_H

class MotorEncoder {
    public:
      MotorEncoder(short encoderPin1, short encoderPin2, bool direction);
    
      void Compute();

      short GetSpeed();
      long GetDistance();

      void EncoderInterrupt();
      
    private:
      short _encoderPin1;
      short _encoderPin2;

      volatile short _encoderSteps;
      long _distance;
      short _speed;  
      
      void (MotorEncoder::*EncoderInterruptFunc)() = NULL;
      void EncoderInterruptDirect();
      void EncoderInterruptReverse();
};

#endif