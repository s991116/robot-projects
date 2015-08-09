#include <digitalWriteFast.h>
#include <Wire.h>
#include "MotorControllerCmd.h"

//#define DEBUG_MANUAL_COMMAND

#define I2C_MOTOR_ADDRESS (4)
#define MessageLength (3)
#define ResponseLength (2)
#define SerialSpeed (9600)
#define LED_Pin (13)
boolean LED_Status;

int16_t gyro[3];       // [x, y, z]            gyroscopic output
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
short YPR_Factor = 500;

short _ReplyFromMaster;
bool _UnhandleCommandReceivedFromMaster = false;
bool _UnhandledResponseFromMotorController = false;
bool _UnhandledResponseFromRobotController = false;
byte _CommandFromMaster;
short _DataFromMaster;
short _UnhandledResponse;
unsigned long _CommandSentTime;

float Gyro_PID_Kp = 4.5;
float Gyro_PID_Ki = 0;
float Gyro_PID_Kd = -0.5;
short Gyro_PID_Factor = 10;
bool Gyro_PID_Enabled = false;
short Gyro_Angle_Offset = -10;

void setup()
{
  SetupCommunication();
  if(!InitializeMPU())
    while(true);
  
  //InitializeDistanceSensor();
  
  SetLED(true);
}

void SetupCommunication()
{
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)

  Serial.begin(SerialSpeed);

  while(Serial.available() > 0)
  {
    Serial.read();
  }

  #ifdef DEBUG_MANUAL_COMMAND
  Serial.println("Debug started.");
  #endif
}

void SetLED(boolean stat)
{
  LED_Status = stat;
  digitalWriteFast(LED_Pin, LED_Status);  
}

void ToggleLED()
{
  LED_Status = !LED_Status;
  digitalWriteFast(LED_Pin, LED_Status);
}

void loop()
{
    ReceiveCommand();
    UpdateGyroData();
    HandleCommand();
    UpdateGyroData();
    SendCommandReply();
    UpdateGyroData();
}

void UpdateGyroData()
{
  if(GyroDataUpdated() && Gyro_PID_Enabled)
  {
    short angle = ypr[1]*YPR_Factor + Gyro_Angle_Offset;
    short angleAccelration = gyro[1];
    short speed = GetPIDSpeed(angle, angleAccelration);
    SendMessage(Set_Motor_Speed, speed);
  }
}

void SendMessage(byte command, short data)
{
  if(MotorControllerCommand(command))
  {
    SendMessageToMotorController(command, data);
  }
  else
  {
    switch(command-RobotCommandTypeOffset)
    {
      case Get_Gyro_YPR: //Gyro Yaw, Pitch, Roll
        _UnhandledResponse = ypr[data]*YPR_Factor;
        return;

      case Get_Gyro_YPR_Accelration: //Accelration Yaw, Pitch, Roll 
        _UnhandledResponse = gyro[data];
        return;
        
      case Set_Gyro_YPR_Factor: //YPR_Factor
        YPR_Factor = data;
        return;
        
      case Get_Distance_cm: //Distance in cm
        _UnhandledResponse = DistanceInCm();
        return;

      case Get_Gyro_YPR_Factor: //YPR_Factor
        _UnhandledResponse = YPR_Factor;
        return;
       
      case Get_Controller_Echo_Command_Test:
        _UnhandledResponse = command;
        return;
        
      case Get_Controller_Echo_Data_Test:
        _UnhandledResponse = data;
        return;

      case Set_Gyro_PID_Kp:
        Gyro_PID_Kp = ((float)data) / ((float)Gyro_PID_Factor);
        return;
        
      case Set_Gyro_PID_Ki:
        Gyro_PID_Ki = ((float)data) / ((float)Gyro_PID_Factor);
        return;
        
      case Set_Gyro_PID_Kd:
        Gyro_PID_Kd = ((float)data) / ((float)Gyro_PID_Factor);
        return;
        
      case Set_Gyro_PID_Factor:
        Gyro_PID_Factor = data;
        return;

      case Get_Gyro_PID_Factor:
        _UnhandledResponse = Gyro_PID_Factor;
        return;
        
      case Get_Gyro_PID_Kp:
        _UnhandledResponse = Gyro_PID_Factor * Gyro_PID_Kp;
        return;
        
      case Get_Gyro_PID_Ki:
        _UnhandledResponse = Gyro_PID_Factor * Gyro_PID_Ki;
        return;
        
      case Get_Gyro_PID_Kd:
        _UnhandledResponse = Gyro_PID_Factor * Gyro_PID_Kd;
        return;
        
      case Set_Gyro_State:
        Gyro_PID_Enabled = data;
        SendMessageToMotorController(Set_Motor_Enabled, Gyro_PID_Enabled);
        return;

      case Get_Gyro_State:
        _UnhandledResponse = Gyro_PID_Enabled;
        return;

      case Set_Gyro_Angle_Offset:
        Gyro_Angle_Offset = data;
        return;
        
      case Get_Gyro_Angle_Offset:
        _UnhandledResponse = Gyro_Angle_Offset;
        return;
        
    }
    return;
  }
}

void SendMessageToMotorController(byte command, short data)
{
  Wire.beginTransmission(I2C_MOTOR_ADDRESS);
  Wire.write(command);
  Wire.write(MSB_FromShort(data));
  Wire.write(LSB_FromShort(data));
  Wire.endTransmission();
}

short GetReplyFromMotorController()
{
  Wire.requestFrom((uint8_t)I2C_MOTOR_ADDRESS, (uint8_t)ResponseLength);    
  byte msb = Wire.read();
  byte lsb = Wire.read();
  return  Bytes_ToShort(msb, lsb);
}

byte MSB_FromShort(short data) {
  return (data >> 8);
}

byte LSB_FromShort(short data) {
  return (data & 0x00FF);
}

short Bytes_ToShort(byte msb, byte lsb) {
    short data = (msb << 8);
    data |= lsb;
    return data;
}
