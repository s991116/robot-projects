#include <ArduinoDataHandler.h>
#include <ArduinoSerial.h>
#include <DataHandler.h>
#include <DataHandlerInterface.h>
#include <DataPackets.h>
#include <MessageDataProtocol.h>
#include <SerialCom.h>
#include <MessageDataFactory.h>

#include <CommandTypes.h>

#define VERTICAL_SERVO_PIN (2)
#define HORIZONTAL_SERVO_PIN (3)
#define SWITCH_BUTTON_PIN (4)

#define ENCODER_B_INTERRUPT_PIN (10)
#define ENCODER_B_DIRECTION_PIN (11)
#define ENCODER_A_INTERRUPT_PIN (12)
#define ENCODER_A_DIRECTION_PIN (13)

#define DISTANCE_ECHO_PIN (6)

#define MOTOR_A_DIR_PIN (5)
#define MOTOR_B_DIR_PIN (7)
#define MOTOR_A_SPEED_PIN (8)
#define MOTOR_B_SPEED_PIN (9)

#define DISTANCE_TRIGGER_PIN (21)

#define DISTANCE_MAX (120)

long updateTime;
long updatePeriod;
long calcTime;

long CurrentSpeedA;
long CurrentSpeedB;
volatile long EncoderCountA;
volatile long EncoderCountB;
long DistanceEncoderCountA;
long DistanceEncoderCountB;

int CurrentEncoderCountA;
int MotorPowerA;
int TargetEncoderCountA;
float KpMotorA = 30;
float KiMotorA = 0;
float KdMotorA = 0;

double TargetSpeed = 0;
double TargetSpeedWanted = 0;
double TargetSpeedStepSizeChange = 0.1;
double TargetTurnSpeed = 0;
double TargetTurnSpeedWanted = 0;
double TargetTurnSpeedStepSizeChange = 0.1;

int CurrentEncoderCountB;
int MotorPowerB;
int TargetEncoderCountB;
float KpMotorB = 30;
float KiMotorB = 0;
float KdMotorB = 0;

double AnglePCorr = 1.0;
double AngleICorr = 1.2;
double AngleDCorr = 0;

short OffsetAngle;

double SpeedPCorr = 0;
double SpeedICorr = 0;
double SpeedDCorr = 0;
int    SpeedCorrLimit = 600;
int    SpeedPIDLimit = 1000;

long NextMotorPowerUpdateTime;
short MotorUpdatePeriod = 5;

void setup() 
{
  InitializeSerialCommand();
  InitializeRaspiSerial();
  InitalizeButton(); 
  InitializeMotor();
  InitializeServo();
  InitializeEncoder();
  //InitializeSpeedControl();  
  InitializeGyro();
  InitializeSegway();
  Serial.println("Setup complete.");
} 

void loop() 
{
  ReadCommand(); 
  ReadRaspiCommand();  
  HandleSegway();
  HandleGyroCommands();
  
  HandleButtonSwitch();
  DistanceSensorUpdate();
  ServoUpdate();
}
