short MotorEnabled;

void SetupMotor()
{
  pinMode(LEFT_MOTOR_SLEEP_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_SLEEP_PIN, OUTPUT);
  leftStepper.setMaxSpeed(10000.0);
  rightStepper.setMaxSpeed(10000.0);
  SetMotorSpeed(0);
  SetMotorState(0);
}

void UpdateStepperMotors() {
  leftStepper.runSpeed();
  rightStepper.runSpeed();
}

void SetMotorSpeed(short speed)
{
  if(speed > Motor_max_speed)
    speed = Motor_max_speed;
  if(speed < -Motor_max_speed)
    speed = -Motor_max_speed;
    
  MotorSpeedLeft = speed;
  MotorSpeedRight = speed;
  
  leftStepper.setSpeed(MotorSpeedLeft);  
  rightStepper.setSpeed(MotorSpeedRight);  
}

short GetCurrentSpeed()
{
  return (MotorSpeedLeft + MotorSpeedRight)/2;
}

void SetMotorState(short enabled)
{
  if(enabled == 1)
  {
    MotorEnabled = 1;
    digitalWriteFast(LEFT_MOTOR_SLEEP_PIN, HIGH);
    digitalWriteFast(RIGHT_MOTOR_SLEEP_PIN, HIGH);
  }
  else
  {
    MotorEnabled = 0;
    digitalWriteFast(LEFT_MOTOR_SLEEP_PIN, LOW);
    digitalWriteFast(RIGHT_MOTOR_SLEEP_PIN, LOW);    
  }
}

short GetMotorState()
{
  return MotorEnabled;
}

