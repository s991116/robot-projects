#ifndef DUALDRIVER_H
#define DUALDRIVER_H

class DualDriver {
  public:
    DualDriver();
    DualDriver(int standby_pin, int motorA_pwm_pin, int motorA_in1_pin, int motorA_in2_pin, int motorB_pwm_pin, int motorB_in1_pin, int motorB_in2_pin);
  
    void SetSpeedA(int speed);
    void SetSpeedB(int speed);
	
  private:
    void Initialize(int standby_pin, int motorA_pwm_pin, int motorA_in1_pin, int motorA_in2_pin, int motorB_pwm_pin, int motorB_in1_pin, int motorB_in2_pin);
	void SetSpeed(int pwm_pin, int in1_pin, int in2_pin, int speed, bool dir_setup);
	int LimitSpeed(int speed);
	
	int _Standby_pin;
	int _MotorA_pwm_pin;
	int _MotorA_in1_pin;
	int _MotorA_in2_pin;
	int _MotorB_pwm_pin;
	int _MotorB_in1_pin;
	int _MotorB_in2_pin;
};
#endif //DUALDRIVER_H