#include <CommandTypes.h>
#include <SerialProtocol.h>

#define ENCODER_A_INTERRUPT_PIN (10)
#define ENCODER_B_INTERRUPT_PIN (12)
#define ENCODER_A_DIRECTION_PIN (11)
#define ENCODER_B_DIRECTION_PIN (13)

#define MOTOR_A_DIR_PIN (7)
#define MOTOR_A_SPEED_PIN (9)
#define MOTOR_B_DIR_PIN (5)
#define MOTOR_B_SPEED_PIN (8)

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
float KpMotorA = 15;
float KiMotorA = 20;
float KdMotorA = 0;


int CurrentEncoderCountB;
int MotorPowerB;
int TargetEncoderCountB;
float KpMotorB = 15;
float KiMotorB = 20;
float KdMotorB = 0;

long NextMotorPowerUpdateTime;
short MotorUpdatePeriod = 5;


void setup() 
{
  InitializeSerialCommand(); 
  InitializeMotor();
  InitializeEncoder();
  InitializeSpeedControl();
  InitializeGyro();
} 

void loop() 
{
  ReadCommand(); 
  MotorPowerUpdateTime();
  HandleGyroCommands();
}
