#include <SerialCommand.h>
SerialCommand SCmd;

void ReadCommand()
{
    SCmd.readSerial();
}

void AddCommand(char* cmd, void (* function)()) {
  AddCommand(cmd, function, "");
}

void AddCommand(char* cmd, void (* function)(), char* comment) {
  Serial.print("Command added: ");
  Serial.print(cmd);
  Serial.print("  -  ");
  Serial.println(comment);
  SCmd.addCommand(cmd,function);
}

void InitializeSerialCommand() {
  Serial.begin(115200); 

  // Setup callbacks for SerialCommand commands 
  AddCommand("speed", speed_command);
  AddCommand("error", error_command);
  AddCommand("pidA", pidA_command, "Motor-A PID");
  AddCommand("pidB", pidB_command, "Motor-B PID");
  AddCommand("p", pidG_command, "Gyro PID");
  AddCommand("dir", dir_command);
  AddCommand("encoder", encoder_command);
  AddCommand("distance", distance_command);
  AddCommand("s", segway_command, "Start segway");
  AddCommand("g", gyro_command, "Gyro info");
  AddCommand("sh", servoHorizontal_command, "Servo horizontal");
  AddCommand("sv", servoVertical_command, "Servo vertical");
  AddCommand("tx", tx_command, "Send nummer to Raspberry Serial");
  AddCommand("turn", turn_command, "Turn around speed");

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

void pidG_command()
{
    TryGetNextArgumentAsFloat("P", &AnglePCorr);
    TryGetNextArgumentAsFloat("I", &AngleICorr);
    TryGetNextArgumentAsFloat("D", &AngleDCorr);
}


void time_command()
{
  int temp;
  TryGetNextArgumentAsInt("UpdateTime", &temp);
  MotorUpdatePeriod = temp;
}

void gyro_command()
{
  Serial.print("Offset:");
  Serial.println(OffsetAngle);

  Serial.print("Angle:");
  Serial.println(Angle);
  Serial.print("Angle acc.:");
  Serial.println(Angle_Acc);

  Serial.print("AngleError:");
  Serial.println(AngleError);
  Serial.print("AngleErrorSum:");
  Serial.println(AngleErrorSum);
  Serial.print("AngleErrorDiff:");
  Serial.println(AngleErrorDif);
}

void segway_command()
{

  Serial.print("Angle P Factor:");
  Serial.println(AnglePCorr,5);
  Serial.print("Angle I Factor:");
  Serial.println(AngleICorr,5);
  Serial.print("Angle D Factor:");
  Serial.println(AngleDCorr,5);

  bool s = GetSegwayEnabled();
  SetSegwayEnabled(!s);
  
}

void servoHorizontal_command()
{
  int angle;
  if(TryGetNextArgumentAsInt("angle", &angle))
  {
    SetHorizontalAngle(angle);
  }  
}

void servoVertical_command()
{
  int angle;
  if(TryGetNextArgumentAsInt("angle", &angle))
  {
    SetVerticalAngle(angle);
  }  
}

void tx_command()
{
  int data;
  if(TryGetNextArgumentAsInt("data", &data))
  {
    SendCommandToSerial(data);
  }  
}

void turn_command()
{
  TryGetNextArgumentAsFloat("Speed", &TurnSpeed);  
}

void unrecognized()
{
  Serial.println("What?"); 
}
