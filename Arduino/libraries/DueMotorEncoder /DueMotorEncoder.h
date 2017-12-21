#ifndef DUEMOTORENCODER_H
#define DUEMOTORENCODER_H

class DueMotorEncoder {
    public:
      DueMotorEncoder(short encoderLeft1Pin, short encoderLeft2Pin, short encoderRight1Pin, short encoderRight2Pin, updateEncoderTime);
    
      void Update();

      short GetSpeedLeft();
      short GetSpeedRight();

      unsigned long GetDistanceLeft();
      unsigned long GetDistanceRight();

    private:
      volatile short encoderLeftSteps;
      volatile short encoderRightSteps;
      long distanceLeft;
      short speedLeft;
      long distanceRight;
      short speedRight;
      
      unsigned long updateEncoderTime;
      short encoderUpdatePeriod = 10;

};

#endif