#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H

#if (ARDUINO > 0)
#define HARDWARECONTROLLER_CPP
#endif

#if (ARDUINO > 0)
  enum MotorCommandType {
#else
  enum class MotorCommandType : unsigned char {
#endif
    Set_Motor_Speed = 0,
    Set_MotorLeft_PID_Kp = 1,
    Set_MotorLeft_PID_Ki = 2,
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
    Get_WaitTime = 14,
    Set_Logging_State = 15,
    Get_Logging_Error = 16,
    Get_MotorLeft_PID_Kp = 17,
    Get_MotorLeft_PID_Ki = 18,
    Get_MotorLeft_PID_Kd = 19,
    Get_MotorRight_PID_Kp = 20,
    Get_MotorRight_PID_Ki = 21,
    Get_MotorRight_PID_Kd = 22,
    Add_Logging_Data = 23,
    Get_Nr_Of_Logs = 24,
    Reset_Logger = 25,
    Get_Logging_Target = 26,
    Next_Logging = 27,
    Logging_Full = 28,
    Get_Motor_Echo_Command_Test = 29,
    Get_Motor_Echo_Data_Test = 30,
    Set_Motor_Slack_Count = 31,
    Get_Motor_Slack_Count = 32,
    Set_Motor_Slack_Mode = 33,
    Get_Motor_Slack_Mode = 34,
    Test_MotorSlack = 35,
    Set_Motor_Slack_PWMSpeed = 36,
    Get_Motor_Slack_PWMSpeed = 37
  };
  
#define RobotCommandTypeOffset (128)

#if (ARDUINO > 0)
  enum RobotCommandType {
#else
  enum class RobotCommandType : unsigned char {
#endif
    Get_Gyro_YPR = 1,
    Get_Gyro_YPR_Accelration = 2,
    Set_Gyro_YPR_Factor = 3,
    Get_Distance_cm = 4,
    Get_Gyro_YPR_Factor = 5,
    Get_Controller_Echo_Command_Test = 6,
    Get_Controller_Echo_Data_Test = 7,
    Set_Gyro_PID_Kp = 8,
    Set_Gyro_PID_Ki = 9,
    Set_Gyro_PID_Kd = 10,
    Set_Gyro_PID_Factor = 11,
    Get_Gyro_PID_Kp = 12,
    Get_Gyro_PID_Ki = 13,
    Get_Gyro_PID_Kd = 14,
    Set_Gyro_State = 15,
    Get_Gyro_State = 16,
    Get_Gyro_PID_Factor = 17,
    Set_Gyro_Angle_Offset = 18,
    Get_Gyro_Angle_Offset = 19,

    Set_Vertical_Servo_Position = 20,
    Set_Vertical_Servo_Max_Position = 21,
    Set_Vertical_Servo_Min_Position = 22,
    
    Set_Horizontal_Servo_Position = 23,
    Set_Horizontal_Servo_Max_Position = 24,
    Set_Horizontal_Servo_Min_Position = 25,
    
    Get_Vertical_Servo_Position = 26,
    Get_Vertical_Servo_Max_Position = 27,
    Get_Vertical_Servo_Min_Position = 28,

    Get_Horizontal_Servo_Position = 29,
    Get_Horizontal_Servo_Max_Position = 30,
    Get_Horizontal_Servo_Min_Position = 31
  };

#ifndef HARDWARECONTROLLER_CPP
extern bool MotorCommandResponse[];
#else
bool MotorCommandResponse[] {
false, //Set_Motor_Speed = 0,
false, //Set_MotorLeft_PID_Kp = 1,
false, //Set_MotorLeft_PID_Ki = 2,
false, //Set_MotorLeft_PID_Kd = 3,
false, //Set_MotorRight_PID_Kp = 4,
false, //Set_MotorRight_PID_Ki = 5,
false, //Set_MotorRight_PID_Kd = 6,
false, //Set_MotorLeft_Speed = 7,
false, //Set_MotorRight_Speed = 8,
true,  //Get_MotorLeft_Speed = 9,
true,  //Get_MotorRight_Speed = 10,
true,  //Get_MotorLeft_Distance = 11,
true,  //Get_MotorRight_Distance = 12,
false, //Set_Motor_Enabled = 13,
true,  //Get_WaitTime = 14,
false, //Set_Logging_State = 15,
true,  //Get_Logging_Error = 16,
true,  //Get_MotorLeft_PID_Kp = 17,
true,  //Get_MotorLeft_PID_Ki = 18,
true,  //Get_MotorLeft_PID_Kd = 19,
true,  //Get_MotorRight_PID_Kp = 20,
true,  //Get_MotorRight_PID_Ki = 21,
true,  //Get_MotorRight_PID_Kd = 22,
false, //Add_Logging_Data = 23,
true,  //Get_Nr_Of_Logs = 24,
false, //Reset_Logger = 25,
true,  //Get_Logging_Target = 26,
false, //Next_Logging = 27,
true,  //Logging_Full = 28,
true,  //Get_Motor_Echo_Command_Test = 29,  
true,  //Get_Motor_Echo_Data_Test = 30,
false, //Set_Motor_Slack_Count = 31,
true,  //Get_Motor_Slack_Count = 32,
false, //Set_MotorSlack_Mode = 33,
true,  //Get_MotorSlack_Mode = 34,
false, //Test_MotorSlack = 35,
false, //Set_Motor_Slack_PWMSpeed = 36,
true,  //Get_Motor_Slack_PWMSpeed = 37

};
#endif

#ifndef HARDWARECONTROLLER_CPP
extern bool RobotCommandResponse[];
#else
bool RobotCommandResponse[] {
false, //0
true,  //Get_Gyro_YPR = 1,
true,  //Get_Gyro_YPR_Accelration = 2,
false, //Set_Gyro_YPR_Factor = 3,
true,  //Get_Distance_cm = 4,
true,  //Get_Gyro_YPR_Factor = 5,
true,  //Get_Controller_Echo_Command_Test = 6,
true,  //Get_Controller_Echo_Data_Test = 7
false, //Set_Gyro_PID_Kp = 8,
false, //Set_Gyro_PID_Ki = 9,
false, //Set_Gyro_PID_Kd = 10,
false, //Set_Gyro_PID_Factor = 11,
true,  //Get_Gyro_PID_Kp = 12,
true,  //Get_Gyro_PID_Ki = 13,
true,  //Get_Gyro_PID_Kd = 14,
false, //Set_Gyro_State = 15,
true,  //Get_Gyro_State = 16,
true,  //Get_Gyro_PID_Factor = 17,
false, //Set_Gyro_Angle_Offset = 18,
true,  //Get_Gyro_Angle_Offset = 19
false, //Set_Vertical_Servo_Position = 20,
false, //Set_Vertical_Servo_Max_Position = 21,
false, //Set_Vertical_Servo_Min_Position = 22,
false, //Set_Horizontal_Servo_Position = 23,
false, //Set_Horizontal_Servo_Max_Position = 24,
false, //Set_Horizontal_Servo_Min_Position = 25,
    
true,  //Get_Vertical_Servo_Position = 26,
true,  //Get_Vertical_Servo_Max_Position = 27,
true,  //Get_Vertical_Servo_Min_Position = 28,

true,  //Get_Horizontal_Servo_Position = 29,
true,  //Get_Horizontal_Servo_Max_Position = 30,
true   //Get_Horizontal_Servo_Min_Position = 31

};

#endif

#endif //COMMANDTYPE_H 