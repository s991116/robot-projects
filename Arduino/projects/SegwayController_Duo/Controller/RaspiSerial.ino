byte TestByte;
short TestShort;

void raspiHandleDataChar(char commandId, char length, char dataArray[]) {
      char data = dataArray[0];

      switch(commandId)
      {
        case SERVO_HORIZONTAL_BYTE:
          SetHorizontalAngle(data);
          break;
          
        case SERVO_VERTICAL_BYTE:
          SetVerticalAngle(data);
          break;

        case SERVO_SPEED_BYTE:
          setVerticalServoSpeed(dataArray[0]);
          Serial.println((byte)dataArray[0]);
          Serial.println((byte)dataArray[1]);
          setHorizontalServoSpeed(dataArray[1]);
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

        case TEST_BYTE:
          TestByte = data;
          break;

        case DISTANCE_SENSOR_ENABLE_BYTE:
          if(data == 0)
          {
            DistanceSensorEnable(false);
          }
          else
          {
            DistanceSensorEnable(true);
          }
          break;          
      }
}

void raspiHandleDataShort(char commandId, char length, short dataArray[]) {
      short data = dataArray[0];

      switch(commandId)
      {
        case PID_ENCODER_A_SHORT:
          KpMotorA = dataArray[0] / 100.0;
          KiMotorA = dataArray[1] / 100.0;
          KdMotorA = dataArray[2] / 100.0;

          UpdateControllerSettings();
          break;
          
        case PID_ENCODER_B_SHORT:
          KpMotorB = dataArray[0] / 100.0;
          KiMotorB = dataArray[1] / 100.0;
          KdMotorB = dataArray[2] / 100.0;

          UpdateControllerSettings();
          break;

        case PID_GYRO_SHORT:
          AnglePCorr = dataArray[0] / 100.0;
          AngleICorr = dataArray[1] / 100.0;
          AngleDCorr = dataArray[2] / 100.0;

          UpdateGyroPIDSettings();
          break;
                    
        case PID_SPEED_SHORT:
          SpeedPCorr = dataArray[0] / 100.0;
          SpeedICorr = dataArray[1] / 100.0;
          SpeedDCorr = dataArray[2] / 100.0;
          
          UpdateSpeedPIDSettings();
          break;
          
        case SPEED_CORR_LIMIT_SHORT:
          SpeedCorrLimit = data;
          break;

        case SPEED_PID_LIMIT_SHORT:
          SpeedPIDLimit = data;
          UpdateSpeedPIDSettings();
          break;

        case TEST_SHORT:
          TestShort = data;
          break;
      }
}

void raspiHandleReplyChar(char commandId, char length, char data[]) {

      switch(commandId)
      {
        case SERVO_HORIZONTAL_BYTE:
          data[0] = GetHorizontalAngle();
          break;
          
        case SERVO_VERTICAL_BYTE:
          data[0] = GetVerticalAngle();
          break;

        case SERVO_SPEED_BYTE:
          data[0] = getVerticalServoSpeed();
          data[1] = getHorizontalServoSpeed();
          break;
          
        case SEGWAY_ENABLED_BYTE:
          data[0] = GetSegwayEnabled();
          break;
          
        case SEGWAY_SPEED_BYTE:
          data[0] = TargetSpeedWanted + 127;
          break;
          
        case SEGWAY_TURN_BYTE:
          data[0] = TargetTurnSpeedWanted + 127;
          break;

        case TEST_BYTE:
          data[0] = TestByte;
          break;
      }      
}

void raspiHandleReplyShort(char commandId, char length, short data[]) {

      switch(commandId)
      {
        case ANGLE_OFFSET_SHORT:
          data[0] = OffsetAngle;
          break;

        case GYRO_MEASURE_SHORT:
          data[0] = Angle;
          data[1] = Angle_Acc;
          break;
          
        case PID_ENCODER_A_SHORT:
          data[0] = KpMotorA * 100.0;
          data[1] = KiMotorA * 100.0;
          data[2] = KdMotorA * 100.0;          
          break;
          
        case PID_ENCODER_B_SHORT:
          data[0] = KpMotorB * 100.0;
          data[1] = KiMotorB * 100.0;
          data[2] = KdMotorB * 100.0;
          break;
          
        case PID_GYRO_SHORT:
          data[0] = AnglePCorr * 100.0;
          data[1] = AngleICorr * 100.0;
          data[2] = AngleDCorr * 100.0;
          break;
          
        case PID_SPEED_SHORT:
          data[0] = SpeedPCorr * 100.0;
          data[1] = SpeedICorr * 100.0;
          data[2] = SpeedDCorr * 100.0;
          break;

        case DISTANCE_MEASURE_SHORT:
          data[0] = DistanceSensorMeasure();
          break;

        case DISTANCE:
          data[0] = DistanceEncoderCountA/10;
          data[1] = DistanceEncoderCountB/10;
          break;

        case DISTANCE_RESET:
          data[0] = DistanceEncoderCountA/10;
          ResetDistanceEncoderCountA();
          data[1] = DistanceEncoderCountB/10;
          ResetDistanceEncoderCountB();
          break;

       case SPEED_CORR_LIMIT_SHORT:
          data[0] = SpeedCorrLimit;
          break;

        case SPEED_PID_LIMIT_SHORT:
          data[0] = SpeedPIDLimit;
          break;

        case TEST_SHORT:
          data[0] = TestShort;
          break;
      }

}

ArduinoDataHandler raspiDataHandler(raspiHandleDataChar, raspiHandleDataShort, raspiHandleReplyChar, raspiHandleReplyShort);
MessageDataProtocol serialCommandRaspi = MessageDataFactory::Create(&Serial2, &raspiDataHandler);

void InitializeRaspiSerial()
{
  Serial2.begin(115200); 
}

void ReadRaspiCommand()
{
  serialCommandRaspi.Update();
}

void SendCommandToSerial(int data)
{
  char d[1] = {data};
  serialCommandRaspi.SendData(0, 1, d);
}

