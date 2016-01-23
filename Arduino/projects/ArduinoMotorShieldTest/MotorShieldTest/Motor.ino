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
