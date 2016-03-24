void InitializeMotor()
{
  pinMode(MOTOR_A_SPEED_PIN, OUTPUT);   
  pinMode(MOTOR_B_SPEED_PIN, OUTPUT); 
  pinMode(MOTOR_A_DIR_PIN, OUTPUT); 
  pinMode(MOTOR_B_DIR_PIN, OUTPUT); 
  digitalWriteDirect(MOTOR_A_DIR_PIN, LOW);
  digitalWriteDirect(MOTOR_B_DIR_PIN, LOW);
  analogWrite(MOTOR_A_SPEED_PIN, 0);
  analogWrite(MOTOR_B_SPEED_PIN, 0);
}

void SetMotorPowerA(int power)
{
  SetMotorPower(power, MOTOR_A_SPEED_PIN, MOTOR_A_DIR_PIN);
}

void SetMotorPowerB(int power)
{
  SetMotorPower(power, MOTOR_B_SPEED_PIN, MOTOR_B_DIR_PIN);
}

void SetMotorPower(int speed, short speed_pin, short dir_pin)
{
    if(speed < 0)
    {
      analogWrite(speed_pin, -speed);
      digitalWriteDirect(dir_pin, -HIGH);
    }
    else
    {
      analogWrite(speed_pin, speed);
      digitalWriteDirect(dir_pin, -LOW);
    }
}

