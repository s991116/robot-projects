#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H
#include <Arduino.h>

class StepperMotor {
    public:
        void Update();
        void SetLeftMotor(int throttle);
        void SetRightMotor(int throttle);

    private:
        int throttle_left_motor;
        int throttle_counter_left_motor;
        int throttle_left_motor_memory;
        int throttle_right_motor;
        int throttle_counter_right_motor;
        int throttle_right_motor_memory;

};

#endif