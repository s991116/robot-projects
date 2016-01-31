#define ENCODER_A_INTERRUPT_PIN (10)
#define ENCODER_B_INTERRUPT_PIN (12)
#define ENCODER_A_DIRECTION_PIN (11)
#define ENCODER_B_DIRECTION_PIN (13)

#define MOTOR_A_DIR_PIN (7)
#define MOTOR_A_SPEED_PIN (9)
#define MOTOR_B_DIR_PIN (5)
#define MOTOR_B_SPEED_PIN (8)

long CurrentSpeedA;
long CurrentSpeedB;
volatile long EncoderCountA;
volatile long EncoderCountB;
long DistanceEncoderCountA;
long DistanceEncoderCountB;

int CurrentEncoderCountA;
int MotorPowerA;
int TargetEncoderCountA;
float KpMotorA = 10;
float KiMotorA = 0;
float KdMotorA = 0;

unsigned long TargetInterruptPeriod = 1000;

int CurrentEncoderCountB;
int MotorPowerB;
int TargetEncoderCountB;
float KpMotorB = 10;
float KiMotorB = 0;
float KdMotorB = 0;

long NextMotorPowerUpdateTime;
byte MotorPowerUpdatePeriod = 1;

void setup() 
{
  InitializeSerialCommand(); 
  InitializeMotor();
  InitializeEncoder();
  InitializeSpeedControl();
} 

void loop() 
{
  ReadCommand(); 
  MotorPowerUpdateTime();
}
