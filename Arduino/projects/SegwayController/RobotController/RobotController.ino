#include <digitalWriteFast.h>
#include <Wire.h>

//#define DEBUG_MANUAL_COMMAND

#define I2C_MOTOR_ADDRESS (4)
#define MessageLength (3)
#define ResponseLength (2)
#define SerialSpeed (9600)
#define LED_Pin (13)
boolean LED_Status;

int16_t gyro[3];       // [x, y, z]            gyroscopic output
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
short YPR_Factor = 100;

short _ReplyFromMaster;
bool _UnhandleCommandReceivedFromMaster = false;
bool _UnhandledResponseFromMotorController = false;
bool _UnhandledResponseFromRobotController = false;
byte _CommandFromMaster;
short _DataFromMaster;
short _UnhandledResponse;
unsigned long _CommandSentTime;

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

void SendMessage(byte command, short data)
{
  if(MotorControllerCommand(command))
  {
    SendMessageToMotorController(command, data);
  }
  else
  {
    switch(command)
    {
      case 129: //Gyro Yaw, Pitch, Roll
        _UnhandledResponse = ypr[data]*YPR_Factor;
        return;

      case 130: //Accelration Yaw, Pitch, Roll 
        _UnhandledResponse = gyro[data];
        return;
        
      case 131: //YPR_Factor
        YPR_Factor = data;
        _UnhandledResponse = data;
        return;
        
      case 132: //Distance in cm
        _UnhandledResponse = DistanceInCm();
        return;

      case 133: //YPR_Factor
        _UnhandledResponse = YPR_Factor;
        return;
       
      case 254:
        _UnhandledResponse = command;
        return;
        
      case 255:
        _UnhandledResponse = data;
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
