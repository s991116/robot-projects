int MotorPowerA;
short lastSpeedA = 0;

float KpMotorA = 25.0;
float KiMotorA = 0.0;
float KdMotorA = 0.0;

int MotorPowerB;
short lastSpeedB = 0;

float KpMotorB = 25.0;
float KiMotorB = 0.0;
float KdMotorB = 0.0;

PID PIDMotorA(&CurrentEncoderCountA, &MotorPowerA, &TargetEncoderCountA, KpMotorA, KiMotorA, KdMotorA, DIRECT);
PID PIDMotorB(&CurrentEncoderCountB, &MotorPowerB, &TargetEncoderCountB, KpMotorB, KiMotorB, KdMotorB, DIRECT);

void SetupMotors() {
  SetupMotor(MOTOR_A_SPEED_PIN, MOTOR_A_DIR_PIN);
  SetupMotor(MOTOR_B_SPEED_PIN, MOTOR_B_DIR_PIN);

  PIDMotorA.SetOutputLimits(-255, 255);
  PIDMotorB.SetOutputLimits(-255, 255);
}

void SetupMotor(short speed_pin, short dir_pin) {
  pinMode(speed_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  UpdateControllerSettings(); 
  SetMotorASpeed(0);
  SetMotorBSpeed(0);
}

void SetMotorASpeed(short speed) {
  SetMotorSpeed(MOTOR_A_SPEED_PIN, MOTOR_A_DIR_PIN, speed, lastSpeedA);
  lastSpeedA = speed;
}

void SetMotorBSpeed(short speed) {
  SetMotorSpeed(MOTOR_B_SPEED_PIN, MOTOR_B_DIR_PIN, speed, lastSpeedB);
  lastSpeedB = speed;
}

void SetMotorSpeed(short speed_pin, short dir_pin, short speed, short lastSpeed) {
  if(speed > 0) {
    if(lastSpeed <=0) {
      digitalWriteFast(dir_pin, HIGH);
    }
    analogWrite(speed_pin, speed);
  }
  else if(speed < 0) {
    if(lastSpeed >=0) {
      digitalWriteFast(dir_pin, LOW);
    }
    analogWrite(speed_pin, -speed);    
  }
  else {
    if(lastSpeed != 0) {
    analogWrite(speed_pin, 0);    
    }
  }
}

void UpdateMotor() {

  if(SegwayEnabled)
  {  
    PIDMotorA.Compute();
    PIDMotorB.Compute();
    SetMotorASpeed(MotorPowerA);
    SetMotorBSpeed(MotorPowerB);
  }
  else
  {
    SetMotorASpeed(0);
    SetMotorBSpeed(0);    
  }  
}

void UpdateControllerSettings()
{
  PIDMotorA.SetTunings(KpMotorA, KiMotorA, KdMotorA);
  PIDMotorB.SetTunings(KpMotorB, KiMotorB, KdMotorB); 
}
