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
        case SERVO_HORIZONTAL_BYTE:
          SetHorizontalAngle(data);
          break;
          
        case SERVO_VERTICAL_BYTE:
          SetVerticalAngle(data);
          break;
          
        case SEGWAY_ENABLED_BYTE:
          SetSegwayEnabled(data);
          break;
          
        case SEGWAY_SPEED_BYTE:
          TargetSpeed = data/10.0;
          break;
          
        case SEGWAY_TURN_BYTE:
          TargetTurnSpeed = data/10.0;
          break;

      }
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
      switch(commandId)
      {
        case PID_ENCODER_A_P_SHORT:
          KpMotorA = data / 1000.0;
          UpdateControllerSettings();
          break;
          
        case PID_ENCODER_A_I_SHORT:
          KiMotorA = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_A_D_SHORT:
          KdMotorA = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_P_SHORT:
          KpMotorB = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_I_SHORT:
          KiMotorB = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_D_SHORT:
          KdMotorB = data / 1000.0;
          UpdateControllerSettings();
          break;

        case PID_GYRO_P_SHORT:
          AnglePCorr = data / 1000.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_GYRO_I_SHORT:
          AngleICorr = data / 1000.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_GYRO_D_SHORT:
          AngleDCorr = data / 1000.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_SPEED_P_SHORT:
          SpeedPCorr = data / 1000.0;
          UpdateSpeedPIDSettings();
          break;
          
        case PID_SPEED_I_SHORT:
          SpeedICorr = data / 1000.0;
          UpdateSpeedPIDSettings();
          break;
          
        case PID_SPEED_D_SHORT:
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
        case SERVO_HORIZONTAL_BYTE:
          return GetHorizontalAngle();
          break;
          
        case SERVO_VERTICAL_BYTE:
          return GetVerticalAngle();
          break;
          
        case SEGWAY_ENABLED_BYTE:
          return GetSegwayEnabled();
          break;
          
        case SEGWAY_SPEED_BYTE:
          return TargetSpeed*10;
          break;
          
        case SEGWAY_TURN_BYTE:
          return TargetTurnSpeed*10;
          break;
      }      
      break;
    
    case COMMAND_NO_DATA_SHORT_REPLY:
      switch(commandId)
      {
        case ANGLE_OFFSET_SHORT:
          return OffsetAngle;
          break;
          
        case PID_ENCODER_A_P_SHORT:
          return KpMotorA * 1000.0;
          break;

        case PID_ENCODER_A_I_SHORT:
          return KiMotorA * 1000.0;
          break;
          
        case PID_ENCODER_A_D_SHORT:
          return KdMotorA * 1000.0;
          break;
          
        case PID_ENCODER_B_P_SHORT:
          return KpMotorB * 1000.0;
          break;
          
        case PID_ENCODER_B_I_SHORT:
          return KiMotorB * 1000.0;
          break;
          
        case PID_ENCODER_B_D_SHORT:
          return KdMotorB * 1000.0;
          break;
          
        case PID_GYRO_P_SHORT:
          return AnglePCorr * 1000.0;
          break;
          
        case PID_GYRO_I_SHORT:
          return AngleICorr * 1000.0;
          break;
          
        case PID_GYRO_D_SHORT:
          return AngleDCorr * 1000.0;
          break;
          
        case PID_SPEED_P_SHORT:
          return SpeedPCorr * 1000.0;
          break;
          
        case PID_SPEED_I_SHORT:
          return SpeedICorr * 1000.0;
          break;
          
        case PID_SPEED_D_SHORT:
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

