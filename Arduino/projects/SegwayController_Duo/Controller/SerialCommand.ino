#include <SerialCommand.h>
SerialCommand SCmd;

void ReadCommand()
{
    SCmd.readSerial();
}

void AddCommand(char* cmd, void (* function)()) {
  Serial.print("Command added: ");
  Serial.println(cmd);
  SCmd.addCommand(cmd,function);
}

void InitializeSerialCommand() {
  Serial.begin(57600); 

  // Setup callbacks for SerialCommand commands 
  AddCommand("speed", speed_command);
  AddCommand("error", error_command);
  AddCommand("pidA", pidA_command);
  AddCommand("pidB", pidB_command);
  AddCommand("dir", dir_command);
  AddCommand("encoder", encoder_command);
  AddCommand("distance", distance_command);
  AddCommand("time", time_command);
  AddCommand("gyro", gyro_command);
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

bool TryGetNextArgumentAsFloat(char* parameterName, float* parameter)
{
  char* arg = SCmd.next();
  if (arg == NULL)
  {
    Serial.print("Need argument: ");
    Serial.println(parameterName);
    return false;    
  }
  *parameter = atof(arg);
  return true;
}


void speed_command()    
{
  TryGetNextArgumentAsInt("speed A", &TargetEncoderCountA);
  TryGetNextArgumentAsInt("speed B", &TargetEncoderCountB);
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
  Serial.print("EncoderCount A:");
  Serial.print(CurrentEncoderCountA);
  Serial.print(" , EncoderCount B:");
  Serial.print(CurrentEncoderCountB);
  Serial.println("");
}

void distance_command()
{
  Serial.print("Distance A:");
  Serial.print(DistanceEncoderCountA);  
  Serial.print(" , Distance B:");
  Serial.println(DistanceEncoderCountB);    
}

void error_command()
{
  int errorA = TargetEncoderCountA - CurrentEncoderCountA;
  int errorB = TargetEncoderCountB - CurrentEncoderCountB;

  Serial.print("Speed error A: ");
  Serial.print(errorA);  
  Serial.print(" , Speed error B: ");
  Serial.print(errorB);  
  Serial.println("");  
}

void pidA_command()
{
    TryGetNextArgumentAsFloat("P", &KpMotorA);
    TryGetNextArgumentAsFloat("I", &KiMotorA);
    TryGetNextArgumentAsFloat("D", &KdMotorA);

    UpdateControllerSettings();
}

void pidB_command()
{
    TryGetNextArgumentAsFloat("P", &KpMotorB);
    TryGetNextArgumentAsFloat("I", &KiMotorB);
    TryGetNextArgumentAsFloat("D", &KdMotorB);

    UpdateControllerSettings();
}

void time_command()
{
  int temp;
  TryGetNextArgumentAsInt("UpdateTime", &temp);
  MotorUpdatePeriod = temp;
}

void gyro_command()
{
  Serial.print("Angle:");
  Serial.println(Angle);
  Serial.print("Angle acc.:");
  Serial.println(Angle_Acc);
}

void unrecognized()
{
  Serial.println("What?"); 
}
