#include <SerialCommand.h>

#define ENCODER_A_INTERRUPT_PIN (10)
#define ENCODER_B_INTERRUPT_PIN (12)
#define ENCODER_A_DIRECTION_PIN (11)
#define ENCODER_B_DIRECTION_PIN (13)

#define MOTOR_A_DIR_PIN (7)
#define MOTOR_A_SPEED_PIN (9)
#define MOTOR_B_DIR_PIN (5)
#define MOTOR_B_SPEED_PIN (8)

SerialCommand SCmd;
long CurrentSpeedA;
long CurrentSpeedB;
volatile long EncoderAInterruptTime;
volatile long EncoderBInterruptTime;
volatile long EncoderAInterruptPeriod;
volatile long EncoderBInterruptPeriod;
volatile long DistanceMotorA;
volatile long DistanceMotorB;

long NextMeasureTime;
int MeasureTimePeriod = 10000;

long LogCount = 0;
bool LogEnabled = false;
long LogTime = 0;
long LogPeriod = 100;

void setup() 
{
  InitializeSerialCommand(); 
  InitializeMotor();
  InitializeEncoder();
} 

void loop() 
{ 
  SCmd.readSerial();
  UpdateSpeedMeasure();
  log_Update();
}
