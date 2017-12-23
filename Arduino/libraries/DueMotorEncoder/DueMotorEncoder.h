#ifndef DUEMOTORENCODER_H
#define DUEMOTORENCODER_H

class DueMotorEncoder {
    public:
      DueMotorEncoder(short encoderPin1, short encoderPin2);
    
      void Compute();

      short GetSpeed();
      long GetDistance();

    private:
      static short _encoderPin1;
      static short _encoderPin2;

      static volatile short _encoderSteps;
      long _distance;
      short _speed;
      
      static void EncoderInterrupt();
};

#endif