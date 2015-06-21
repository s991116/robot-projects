#pragma once

enum class CommandType : unsigned char{
    Set_Motor_Speed = 0,
    Set_MotorA_PID_Kp = 1,
    Set_MotorA_PID_Ki = 2,
    Set_MotorA_PID_Kd = 3,
    Set_MotorB_PID_Kp = 4,
    Set_MotorB_PID_Ki = 5,
    Set_MotorB_PID_Kd = 6,
    Set_MotorA_Speed = 7,
    Set_MotorB_Speed = 8,
    Get_MotorA_Speed = 9,
    Get_MotorB_Speed = 10,
    Get_MotorA_Distance = 11,
    Get_MotorB_Distance = 12,
    Set_Motor_Enabled = 13,
    Set_Logging_State = 15,
    Get_Logging_Value = 16,
    Get_Motor_Echo_Command_Test = 126,
    Get_Motor_Echo_Data_Test = 127,

    Get_Gyro_YPR = 129,
    Get_Gyro_YPR_Accelration = 130,
    Set_Gyro_YPR_Factor = 131,
    Get_Distance_cm = 132,
    Get_Controller_Echo_Command_Test = 254,
    Get_Controller_Echo_Data_Test = 255
};
