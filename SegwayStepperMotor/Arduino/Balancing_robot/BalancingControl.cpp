#include "BalancingControl.h"


BalancingControl::BalancingControl(Gyroscope* gyroscope, StepperMotor* stepperMotor, Battery* battery) {
    _gyroscope = gyroscope;
    _stepperMotor = stepperMotor;
    _battery = battery;
}

void BalancingControl::Initialize() {
    this->_gyroscope->Initialize();
    this->_stepperMotor->Initialize();

    this->pid_p_gain = 15.0;                                       //Gain setting for the P-controller (15)
    this->pid_i_gain = 1.5;                                      //Gain setting for the I-controller (1.5)
    this->pid_d_gain = 10.0;                                       //Gain setting for the D-controller (30)
    this->turning_speed = 30;                                    //Turning speed (20)
    this->max_target_speed = 150;                                //Max target speed (100)

    this->self_balance_pid_setpoint = 0;
}

void BalancingControl::SetNavigation(byte data) {
    this->navigation = data;
    this->navigationReceiveCounter = 0;
}

byte BalancingControl::GetNavigation() {
    return this->navigation;
}

void BalancingControl::Balance() {
      this->UpdateNavigation();
      _gyroscope->CalculateAngle();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //PID controller calculations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //The balancing robot is angle driven. First the difference between the desired angel (setpoint) and actual angle (process value)
    //is calculated. The self_balance_pid_setpoint variable is automatically changed to make sure that the robot stays balanced all the time.
    //The (pid_setpoint - pid_output * 0.015) part functions as a brake function.
    this->pid_error_temp = _gyroscope->angle_gyro - this->self_balance_pid_setpoint - this->pid_setpoint;
    if(this->pid_output > 10 || this->pid_output < -10) this->pid_error_temp += this->pid_output * 0.015 ;

    this->pid_i_mem += this->pid_i_gain * this->pid_error_temp;                                 //Calculate the I-controller value and add it to the pid_i_mem variable
    if(this->pid_i_mem > 400) this->pid_i_mem = 400;                                       //Limit the I-controller to the maximum controller output
    else if(this->pid_i_mem < -400) this->pid_i_mem = -400;
    //Calculate the PID output value
    float p_Error = this->pid_p_gain * this->pid_error_temp;
    float i_Error = this->pid_i_mem;
    float d_Error = this->pid_d_gain * (this->pid_error_temp - this->pid_last_d_error);
    this->pid_output = p_Error + i_Error + d_Error;

    if(this->pid_output > 400) this->pid_output = 400;                                     //Limit the PI-controller to the maximum controller output
    else if(this->pid_output < -400) this->pid_output = -400;

    this->pid_last_d_error = this->pid_error_temp;                                        //Store the error for the next loop

    if(this->pid_output < 5 && this->pid_output > -5) this->pid_output = 0;                      //Create a dead-band to stop the motors when the robot is balanced

    if(_gyroscope->angle_gyro > 30 || _gyroscope->angle_gyro < -30 || _gyroscope->start == 0 || _battery->LowBattery() == 1){    //If the robot tips over or the start variable is zero or the battery is empty
        this->pid_output = 0;                                                         //Set the PID controller output to 0 so the motors stop moving
        this->pid_i_mem = 0;                                                          //Reset the I-controller memory
        _gyroscope->start = 0;                                                        //Set the start variable to 0
        this->self_balance_pid_setpoint = 0;                                          //Reset the self_balance_pid_setpoint variable
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Control calculations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    this->pid_output_left = this->pid_output;                                             //Copy the controller output to the pid_output_left variable for the left motor
    this->pid_output_right = this->pid_output;                                            //Copy the controller output to the pid_output_right variable for the right motor

    if(this->navigation & B00000001){                                            //If the first bit of the receive byte is set change the left and right variable to turn the robot to the left
        this->pid_output_left += this->turning_speed;                                       //Increase the left motor speed
        this->pid_output_right -= this->turning_speed;                                      //Decrease the right motor speed
    }
    if(this->navigation & B00000010){                                            //If the second bit of the receive byte is set change the left and right variable to turn the robot to the right
        this->pid_output_left -= this->turning_speed;                                       //Decrease the left motor speed
        this->pid_output_right += this->turning_speed;                                      //Increase the right motor speed
    }

    if(this->navigation & B00000100){                                            //If the third bit of the receive byte is set change the left and right variable to turn the robot to the right
        if(this->pid_setpoint > -2.5) this->pid_setpoint -= 0.05;                            //Slowly change the setpoint angle so the robot starts leaning forewards
        if(this->pid_output > this->max_target_speed * -1) this->pid_setpoint -= 0.005;            //Slowly change the setpoint angle so the robot starts leaning forewards
    }
    if(this->navigation & B00001000){                                            //If the forth bit of the receive byte is set change the left and right variable to turn the robot to the right
        if(this->pid_setpoint < 2.5) this->pid_setpoint += 0.05;                             //Slowly change the setpoint angle so the robot starts leaning backwards
        if(this->pid_output < this->max_target_speed) this->pid_setpoint += 0.005;                 //Slowly change the setpoint angle so the robot starts leaning backwards
    }   

    if(!(this->navigation & B00001100)){                                         //Slowly reduce the setpoint to zero if no foreward or backward command is given
        if(this->pid_setpoint > 0.5) this->pid_setpoint -=0.05;                              //If the PID setpoint is larger then 0.5 reduce the setpoint with 0.05 every loop
        else if(this->pid_setpoint < -0.5) this->pid_setpoint +=0.05;                        //If the PID setpoint is smaller then -0.5 increase the setpoint with 0.05 every loop
        else this->pid_setpoint = 0;                                                  //If the PID setpoint is smaller then 0.5 or larger then -0.5 set the setpoint to 0
    }
    
    //The self balancing point is adjusted when there is not forward or backwards movement from the transmitter. This way the robot will always find it's balancing point
    if(this->pid_setpoint == 0){                                                    //If the setpoint is zero degrees
        if(this->pid_output < 0) this->self_balance_pid_setpoint += 0.0015;                  //Increase the self_balance_pid_setpoint if the robot is still moving forewards
        if(this->pid_output > 0) this->self_balance_pid_setpoint -= 0.0015;                  //Decrease the self_balance_pid_setpoint if the robot is still moving backwards
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Motor pulse calculations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //To compensate for the non-linear behaviour of the stepper motors the folowing calculations are needed to get a linear speed behaviour.
    if(this->pid_output_left > 0) this->pid_output_left = 405 - (1/(this->pid_output_left + 9)) * 5500;
    else if(this->pid_output_left < 0) this->pid_output_left = -405 - (1/(this->pid_output_left - 9)) * 5500;

    if(this->pid_output_right > 0) this->pid_output_right = 405 - (1/(this->pid_output_right + 9)) * 5500;
    else if(this->pid_output_right < 0) this->pid_output_right = -405 - (1/(this->pid_output_right - 9)) * 5500;

    //Calculate the needed pulse time for the left and right stepper motor controllers
    if(this->pid_output_left > 0) this->left_motor = 400 - this->pid_output_left;
    else if(this->pid_output_left < 0) this->left_motor = -400 - this->pid_output_left;
    else this->left_motor = 0;

    if(this->pid_output_right > 0) this->right_motor = 400 - this->pid_output_right;
    else if(this->pid_output_right < 0) this->right_motor = -400 - this->pid_output_right;
    else this->right_motor = 0;
    //Copy the pulse time to the throttle variables so the interrupt subroutine can use them
    this->_stepperMotor->SetLeftMotor(this->left_motor);
    this->_stepperMotor->SetRightMotor(this->right_motor);
}

void BalancingControl::UpdateNavigation() {
    if(this->navigationReceiveCounter <= 25) this->navigationReceiveCounter ++;        //The received byte will be valid for 25 program loops (100 milliseconds)
    else this->navigation = 0x00;                                                //After 100 milliseconds the received byte is deleted 
}

void BalancingControl::SetPidPLevel(byte data) {
  pid_p_gain = data/4.0;
}
void BalancingControl::SetPidILevel(byte data) {
  pid_i_gain = data/4.0;
}
void BalancingControl::SetPidDLevel(byte data) {
  pid_d_gain = data/4.0;
}

byte BalancingControl::GetPidPLevel() {
    return 4*pid_p_gain;
}

byte BalancingControl::GetPidILevel() {
    return 4*pid_i_gain;
}

byte BalancingControl::GetPidDLevel() {
    return 4*pid_d_gain;
}
