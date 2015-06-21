#pragma once

enum class CommandType : unsigned char {
    Set_Motor_Speed = 0,
    Set_MotorLeft_PID_Ki = 2,
    Set_MotorLeft_PID_Kp = 1,
    Set_MotorLeft_PID_Kd = 3,
    Set_MotorRight_PID_Kp = 4,
    Set_MotorRight_PID_Ki = 5,
    Set_MotorRight_PID_Kd = 6,
    Set_MotorLeft_Speed = 7,
    Set_MotorRight_Speed = 8,
    Get_MotorLeft_Speed = 9,
    Get_MotorRight_Speed = 10,
    Get_MotorLeft_Distance = 11,
    Get_MotorRight_Distance = 12,
    Set_Motor_Enabled = 13,
    Set_Logging_State = 15,
    Get_Logging_Value = 16,
    Get_MotorLeft_PID_Kp = 17,
    Get_MotorLeft_PID_Ki = 18,
    Get_MotorLeft_PID_Kd = 19,
    Get_MotorRight_PID_Kp = 20,
    Get_MotorRight_PID_Ki = 21,
    Get_MotorRight_PID_Kd = 22,
    Add_Logging_Data = 23,
    Get_Nr_Of_Logs = 24,
    Reset_Logger = 25,    
            
    Get_Motor_Echo_Command_Test = 126,
    Get_Motor_Echo_Data_Test = 127,

    Get_Gyro_YPR = 129,
    Get_Gyro_YPR_Accelration = 130,
    Set_Gyro_YPR_Factor = 131,
    Get_Distance_cm = 132,
    Get_Controller_Echo_Command_Test = 254,
    Get_Controller_Echo_Data_Test = 255
};
