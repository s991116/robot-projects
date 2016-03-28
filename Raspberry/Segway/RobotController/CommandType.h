#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H

  enum class HardwareControllerCommandTypeByte : unsigned char {
    SERVO_HORIZONTAL = 0,
    SERVO_VERTICAL   = 1,
    SEGWAY_ENABLED   = 2,
    SEGWAY_SPEED     = 3,
    SEGWAY_TURN      = 4
  };
  
  enum class HardwareControllerCommandTypeShort : unsigned char {
    ANGLE_OFFSET     = 0,
    PID_ENCODER_A_P  = 1,
    PID_ENCODER_A_I  = 2,
    PID_ENCODER_A_D  = 3,
    PID_ENCODER_B_P  = 4,
    PID_ENCODER_B_I  = 5,
    PID_ENCODER_B_D  = 6,
    PID_GYRO_P       = 7,
    PID_GYRO_I       = 8,
    PID_GYRO_D       = 9,
    PID_SPEED_P      = 10,
    PID_SPEED_I      = 11,
    PID_SPEED_D      = 12
  };
  
#endif //COMMANDTYPE_H 