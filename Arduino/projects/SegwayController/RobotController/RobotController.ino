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

void setup()
{
  SetupCommunication();
  if(InitializeMPU())
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
#ifdef DEBUG_MANUAL_COMMAND
  ManualRead();
#else
  //while (!MPUDataReady()) {
        HandleCommand();
  //  }
  //  UpdateGyroData();
#endif
}

short SendMessage(byte command, short data)
{
  if(command < 128)
  {
    SendMessageToMotorController(command, data);
    delay(10);
    return ReceiveResponseFromMotorController();
  }
  else
  {
    switch(command)
    {
      case 129: //Gyro Yaw, Pitch, Roll
        return ypr[data]*YPR_Factor;

      case 130: //Accelration Yaw, Pitch, Roll 
        return gyro[data];
        
      case 131: //YPR_Factor
        YPR_Factor = data;
        break;
        
      case 132: //Distance in cm
        return DistanceInCm();
       
      case 254:
        return command;
        
      case 255:
        return data;
    }
    return data;
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

short ReceiveResponseFromMotorController()
{
//  Wire.beginTransmission(I2C_MOTOR_ADDRESS);
  Wire.requestFrom((uint8_t)I2C_MOTOR_ADDRESS, (uint8_t)ResponseLength);
  byte msb = Wire.read();
  byte lsb = Wire.read();
  short receivedValue = Bytes_ToShort(msb, lsb);
//  Wire.endTransmission();
  return receivedValue;
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
