#ifndef DUEMOTORENCODER_H
#define DUEMOTORENCODER_H

class DueMotorEncoder {
    public:
      DueMotorEncoder(short encoderLeft1Pin, short encoderLeft2Pin, short encoderRight1Pin, short encoderRight2Pin, short updateEncoderTime);
    
      void Update();

      short GetSpeedLeft();
      short GetSpeedRight();

      long GetDistanceLeft();
      long GetDistanceRight();

    private:
      static short _encoderLeft1Pin;
      static short _encoderLeft2Pin;
      static short _encoderRight1Pin;
      static short _encoderRight2Pin;

      static volatile short _encoderLeftSteps;
      static volatile short _encoderRightSteps;
      long _distanceLeft;
      short _speedLeft;
      long _distanceRight;
      short _speedRight;
      
      unsigned long _updateEncoderTime;
      short _encoderUpdatePeriod;

      static void LeftEncoderInterrupt();
      static void RightEncoderInterrupt();
};

#endif