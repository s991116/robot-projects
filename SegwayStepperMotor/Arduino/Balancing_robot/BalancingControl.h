#include <Arduino.h>
#include "Gyroscope.h"
#include "StepperMotor.h"
#include "Battery.h"

class BalancingControl{
    public:
        BalancingControl(Gyroscope* gyroscope, StepperMotor* stepperMotor, Battery* battery);
        void Initialize();
        void Balance();
        void SetNavigation(byte data);
        byte GetNavigation();
        
        void SetPidPLevel(unsigned char);
        void SetPidILevel(unsigned char);
        void SetPidDLevel(unsigned char);
 
        unsigned char GetPidPLevel();
        unsigned char GetPidILevel();
        unsigned char GetPidDLevel();

        StepperMotor* _stepperMotor;

    private:
        void UpdateNavigation();

        float pid_p_gain;
        float pid_i_gain;
        float pid_d_gain;
        float turning_speed;
        float max_target_speed;
        float pid_error_temp, pid_i_mem;
        float pid_setpoint;
        float gyro_input;
        float pid_output;
        float pid_last_d_error;
        float pid_output_left;
        float pid_output_right;
        float self_balance_pid_setpoint;
        byte navigation;
        byte navigationReceiveCounter;
        int left_motor;
        int right_motor;

        Gyroscope* _gyroscope;
        Battery*  _battery;
};