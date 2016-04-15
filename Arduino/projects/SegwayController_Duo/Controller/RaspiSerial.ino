#include <SerialProtocol.h>

void handleRaspiCommand(uint8_t commandId)
{
  switch(commandId)
  {
    case DISTANCE_RESET:
      DistanceEncoderCountA = 0;
      DistanceEncoderCountB = 0;
      break;
  }
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
          TargetSpeedWanted = data-127;
          break;
          
        case SEGWAY_TURN_BYTE:
          TargetTurnSpeedWanted = data-127;
          break;

      }
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
      switch(commandId)
      {
        case PID_ENCODER_A_P_SHORT:
          KpMotorA = data / 100.0;
          UpdateControllerSettings();
          break;
          
        case PID_ENCODER_A_I_SHORT:
          KiMotorA = data / 100.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_A_D_SHORT:
          KdMotorA = data / 100.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_P_SHORT:
          KpMotorB = data / 100.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_I_SHORT:
          KiMotorB = data / 100.0;
          UpdateControllerSettings();
          break;

        case PID_ENCODER_B_D_SHORT:
          KdMotorB = data / 100.0;
          UpdateControllerSettings();
          break;

        case PID_GYRO_P_SHORT:
          AnglePCorr = data / 100.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_GYRO_I_SHORT:
          AngleICorr = data / 100.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_GYRO_D_SHORT:
          AngleDCorr = data / 100.0;
          UpdateGyroPIDSettings();
          break;
          
        case PID_SPEED_P_SHORT:
          SpeedPCorr = data / 100.0;
          UpdateSpeedPIDSettings();
          break;
          
        case PID_SPEED_I_SHORT:
          SpeedICorr = data / 100.0;
          UpdateSpeedPIDSettings();
          break;
          
        case PID_SPEED_D_SHORT:
          SpeedDCorr = data / 100.0;
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
          return TargetSpeedWanted + 127;
          break;
          
        case SEGWAY_TURN_BYTE:
          return TargetTurnSpeedWanted + 127;
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
          return KpMotorA * 100.0;
          break;

        case PID_ENCODER_A_I_SHORT:
          return KiMotorA * 100.0;
          break;
          
        case PID_ENCODER_A_D_SHORT:
          return KdMotorA * 100.0;
          break;
          
        case PID_ENCODER_B_P_SHORT:
          return KpMotorB * 100.0;
          break;
          
        case PID_ENCODER_B_I_SHORT:
          return KiMotorB * 100.0;
          break;
          
        case PID_ENCODER_B_D_SHORT:
          return KdMotorB * 100.0;
          break;
          
        case PID_GYRO_P_SHORT:
          return AnglePCorr * 100.0;
          break;
          
        case PID_GYRO_I_SHORT:
          return AngleICorr * 100.0;
          break;
          
        case PID_GYRO_D_SHORT:
          return AngleDCorr * 100.0;
          break;
          
        case PID_SPEED_P_SHORT:
          return SpeedPCorr * 100.0;
          break;
          
        case PID_SPEED_I_SHORT:
          return SpeedICorr * 100.0;
          break;
          
        case PID_SPEED_D_SHORT:
          return SpeedDCorr * 100.0;
          break;

        case DISTANCE:
          return (DistanceEncoderCountA + DistanceEncoderCountB) / 20;
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

void ReadRaspiCommand()
{
  serialCommandRaspi.handleResponse();
}

void SendCommandToSerial(int data)
{
  serialCommandRaspi.sendCommandAndData((uint8_t) 0, (uint8_t) data);
}

