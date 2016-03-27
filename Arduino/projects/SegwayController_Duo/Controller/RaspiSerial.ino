#include <SerialProtocol.h>

void handleRaspiCommand(uint8_t commandId)
{
}

void handleRaspiData(uint8_t responseType, uint8_t commandId, int16_t data)
{
  switch(responseType)
  {
    case COMMAND_DATA_BYTE_NO_REPLY:
      switch(commandId)
      {
        case SERVO_HORIZONTAL:
          SetHorizontalAngle(data);
          break;
          
        case SERVO_VERTICAL:
          SetVerticalAngle(data);
          break;
          
        case SEGWAY_ENABLED:
          SetSegwayEnabled(data);
          break;
          
        case SEGWAY_SPEED:
          TargetSpeed = data/10.0;
          break;
          
        case SEGWAY_TURN:
          TargetTurnSpeed = data/10.0;
          break;

      }
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
      switch(commandId)
      {
        case PID_ENCODER_A_P:
          KpMotorA = data / 1000.0;
          UpdateControllerSettings();
          break;
          
        case PID_ENCODER_A_I:
          KiMotorA = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_A_D:
          KdMotorA = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_P:
          KpMotorB = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_I:
          KiMotorB = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_D:
          KdMotorB = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_GYRO_P:
          AnglePCorr = data / 1000.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_GYRO_I:
          AngleICorr = data / 1000.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_GYRO_D:
          AngleDCorr = data / 1000.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_SPEED_P:
          SpeedPCorr = data / 1000.0;
          UpdateSpeedPIDSettings();
          break;
          
        case PID_SPEED_I:
          SpeedICorr = data / 1000.0;
          UpdateSpeedPIDSettings();
          break;
          
        case PID_SPEED_D:
          SpeedDCorr = data / 1000.0;
          UpdateSpeedPIDSettings();
          break;
      }
      break;
  }
}

int16_t handleRaspiReply(uint8_t responseType, uint8_t commandId)
{
  switch(responseType)
  {
    case COMMAND_NO_DATA_BYTE_REPLY:
      switch(commandId)
      {
        case SERVO_HORIZONTAL:
          return GetHorizontalAngle();
          break;
          
        case SERVO_VERTICAL:
          return GetVerticalAngle();
          break;
          
        case SEGWAY_ENABLED:
          return GetSegwayEnabled();
          break;
          
        case SEGWAY_SPEED:
          return TargetSpeed*10;
          break;
          
        case SEGWAY_TURN:
          return TargetTurnSpeed*10;
          break;
      }      
      break;
    
    case COMMAND_NO_DATA_SHORT_REPLY:
      switch(commandId)
      {
        case ANGLE_OFFSET:
          return OffsetAngle;
          break;
          
        case PID_ENCODER_A_P:
          return KpMotorA * 1000.0;
          break;

        case PID_ENCODER_A_I:
          return KiMotorA * 1000.0;
          break;
          
        case PID_ENCODER_A_D:
          return KdMotorA * 1000.0;
          break;
          
        case PID_ENCODER_B_P:
          return KpMotorB * 1000.0;
          break;
          
        case PID_ENCODER_B_I:
          return KiMotorB * 1000.0;
          break;
          
        case PID_ENCODER_B_D:
          return KdMotorB * 1000.0;
          break;
          
        case PID_GYRO_P:
          return AnglePCorr * 1000.0;
          break;
          
        case PID_GYRO_I:
          return AngleICorr * 1000.0;
          break;
          
        case PID_GYRO_D:
          return AngleDCorr * 1000.0;
          break;
          
        case PID_SPEED_P:
          return SpeedPCorr * 1000.0;
          break;
          
        case PID_SPEED_I:
          return SpeedICorr * 1000.0;
          break;
          
        case PID_SPEED_D:
          return SpeedDCorr * 1000.0;
          break;
      }
      break;    
  }
  return 0;
}

SerialCommandProtocol serialCommandRaspi(&Serial2, handleRaspiCommand, handleRaspiData, handleRaspiReply);

void InitializeRaspiSerial()
{
  Serial2.begin(115200); 
}

void SendCommandToSerial(int data)
{
  serialCommandRaspi.sendCommandAndData((uint8_t) 0, (uint8_t) data);
}

