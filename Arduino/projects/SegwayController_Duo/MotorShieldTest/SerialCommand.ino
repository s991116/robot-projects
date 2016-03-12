void AddCommand(char* cmd, void (* function)()) {
  Serial.print("Command added: ");
  Serial.println(cmd);
  SCmd.addCommand(cmd,function);
}

void InitializeSerialCommand() {
  Serial.begin(9600); 

  // Setup callbacks for SerialCommand commands 
  AddCommand("speed", speed_command);
  AddCommand("dir", dir_command);
  AddCommand("encoder", encoder_command);
  AddCommand("distance", distance_command);
  AddCommand("log", log_command);
  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 
  Serial.println("Ready"); 
}

bool TryGetNextArgumentAsInt(char* parameterName, int* parameter)
{
  char* arg = SCmd.next(); 
  if (arg == NULL) 
  {
    Serial.print("Need argument: ");
    Serial.println(parameterName);
    return false;
  }
  *parameter = atoi(arg);
  return true;
}

void speed_command()    
{
  int speed;
  if(TryGetNextArgumentAsInt("speed A", &speed))
  {
    SetMotorPower(speed, MOTOR_A_SPEED_PIN, MOTOR_A_DIR_PIN);
  }
  if(TryGetNextArgumentAsInt("speed B", &speed))
  {
    SetMotorPower(speed, MOTOR_B_SPEED_PIN, MOTOR_B_DIR_PIN);
  }
}

void SetMotorPower(int speed, short speed_pin, short dir_pin)
{
    if(speed < 0)
    {
      analogWrite(speed_pin, -speed);
      digitalWriteDirect(dir_pin, LOW);
    }
    else
    {
      analogWrite(speed_pin, speed);
      digitalWriteDirect(dir_pin, HIGH);
    }
}

void dir_command()
{
  int dir;
  if(TryGetNextArgumentAsInt("enable", &dir))
  {
    digitalWrite(MOTOR_A_DIR_PIN, dir);
  }
  if(TryGetNextArgumentAsInt("enable", &dir))
  {
    digitalWrite(MOTOR_B_DIR_PIN, dir);
  }
}

void encoder_command()
{
  Serial.print("Interrupt A:");
  Serial.print(EncoderAInterruptPeriod);
  Serial.print(" , Interrupt B:");
  Serial.println(EncoderBInterruptPeriod);    
}

void distance_command()
{
  Serial.print("Distance A:");
  Serial.print(DistanceMotorA);  
  Serial.print(" , Distance B:");
  Serial.println(DistanceMotorB);    
}

void log_command()
{
  LogCount = 0;
  LogEnabled = true;
  LogTime = 0;
}

void log_Update()
{
  if(LogEnabled)
  {
    if((millis() > LogTime + LogPeriod) && LogCount < 100)
    {
      LogTime = millis();
      LogCount++;
      encoder_command();
    }    
  }
}

void unrecognized()
{
  Serial.println("What?"); 
}
