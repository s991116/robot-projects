#include <Servo.h>
#include <digitalWriteFast.h>
#include <Wire.h>
#include "MotorControllerCmd.h"
#include <AccelStepper.h>

#define MANUAL_COMMUNICATION

#define I2C_MOTOR_ADDRESS (4)
#define MessageLength (3)
#define ResponseLength (2)
#define SerialSpeed (9600)
#define LED_Pin (13)
boolean LED_Status;

int16_t gyro[3];       // [x, y, z]            gyroscopic output
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
short YPR_Factor = 600;

byte _CommandFromMaster;
short _DataFromMaster;
short _UnhandledResponse;
bool _UnhandleCommandFromMasterReceived = false;
bool _UnhandleReplyFromMaster = false;

float Gyro_PID_Kp = 1.7;
float Gyro_PID_Ki = 0.15;
float Gyro_PID_Kd = 0.15;
short Gyro_PID_Factor = 100;
bool Gyro_PID_Enabled = false;
short Gyro_Angle_Offset = -10;

float Speed_PID_Kp = 1.0;
float Speed_PID_Ki = 0.0;
float Speed_PID_Kd = 0.0;
short Speed_PID_Factor = 100;

short MeasuredSpeed;
short SpeedOffset;
long SpeedIntegration;
short Measured_Old;

short MotorSpeedLeft = 0;
short MotorSpeedRight = 0;
short Motor_max_speed = 500;

unsigned long UpdatePositionTime = 0;
unsigned long PID_Looptime_ms = 20;

#define SERVO_HORIZONTAL_PIN (10)
#define SERVO_VERTICAL_PIN (11)
#define DISTANCE_TRIGGER_PIN (12)
#define DISTANCE_ECHO_PIN (13)

#define LEFT_MOTOR_DIR_PIN (8)
#define LEFT_MOTOR_STEP_PIN (10)
#define LEFT_MOTOR_SLEEP_PIN (A6)

#define RIGHT_MOTOR_DIR_PIN (7)
#define RIGHT_MOTOR_STEP_PIN (9)
#define RIGHT_MOTOR_SLEEP_PIN (A7)

// Define the stepper and the pins it will use
AccelStepper leftStepper(1, LEFT_MOTOR_STEP_PIN, LEFT_MOTOR_DIR_PIN);
AccelStepper rightStepper(1, RIGHT_MOTOR_STEP_PIN, RIGHT_MOTOR_DIR_PIN);

void setup()
{
  SetupCommunication();
  //if(!InitializeMPU())
  //  while(true);
  
  //InitializeDistanceSensor();
  SetupServo();
  SetupMotor();
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
  #ifdef MANUAL_COMMUNICATION
  Serial.println("Ready.");
  #endif 
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

    ReceiveCommand();
    UpdateStepperMotors();
//    UpdateGyroData();
//    UpdateSegwayPosition();
    HandleCommand();
    UpdateStepperMotors();
//    UpdateGyroData();
//    UpdateSegwayPosition();
    SendCommandReply();
    UpdateStepperMotors();
//    UpdateGyroData();
//    UpdateSegwayPosition();

}

