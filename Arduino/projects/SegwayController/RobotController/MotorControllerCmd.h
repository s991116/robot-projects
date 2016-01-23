#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H

#if (ARDUINO > 0)
#define HARDWARECONTROLLER_CPP
#endif

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
    Get_Horizontal_Servo_Min_Position = 31,
    Set_MotorSpeed = 32,
    Get_MotorSpeed_Left = 33,
    Get_MotorSpeed_Right = 34,
    Set_Motor_Max_Speed = 35,
    Get_Motor_Max_Speed = 36,

    Set_Speed_PID_Kp = 37,
    Set_Speed_PID_Ki = 38,
    Set_Speed_PID_Kd = 39,
    Set_Speed_PID_Factor = 40,
    Get_Speed_PID_Factor = 41,
    Get_Speed_PID_Kp = 42,
    Get_Speed_PID_Ki = 43,
    Get_Speed_PID_Kd = 44,

    Set_Motor_State = 45,
    Get_Motor_State = 46
  };

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
true,  //Get_Horizontal_Servo_Min_Position = 31,
false, //Set_MotorSpeed = 32
true,  //Get_MotorSpeed_Left = 33
true,  //Get_MotorSpeed_Right = 34
false, //Set_Motor_Max_Speed = 35,
true,  //Get_Motor_Max_Speed = 36
false, //Set_Speed_PID_Kp = 37,
false, //Set_Speed_PID_Ki = 38,
false, //Set_Speed_PID_Kd = 39,
false, //Set_Speed_PID_Factor = 40,
true,  //Get_Speed_PID_Factor = 41,
true,  //Get_Speed_PID_Kp = 42,
true,  //Get_Speed_PID_Ki = 43,
true,  //Get_Speed_PID_Kd = 44,
false, //Set_Motor_State = 45,
true   //Get_Motor_State = 46
};

#endif

#endif //COMMANDTYPE_H 
