#ifndef MotorController_H
#define MotorController_H

class MotorController {
    public:
      MotorController(short speedPin, short controlPin1, short controlPin2, bool direction);

      void SetSpeed(short speed);
      short GetSpeed();

    private:
      short _Speed;
      short _SpeedPin;
      short _ControlPin1;
      short _ControlPin2;
      bool _Direction;
};

#endif