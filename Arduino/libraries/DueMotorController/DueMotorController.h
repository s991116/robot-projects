#ifndef DUEMOTORCONTROLLER_H
#define DUEMOTORCONTROLLER_H

class DueMotorController {
    public:
      DueMotorController(short speedPin, short control1Pin, short control2Pin, bool direction);

      void SetSpeed(short speed);
      short GetSpeed();

    private:
      short _Speed;
      short _SpeedPin;
      short _Control1Pin;
      short _Control2Pin;
      bool _Direction;
};

#endif