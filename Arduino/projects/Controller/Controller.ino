#include <PID_v1.h>
#include <digitalWriteFast.h>

//PWM pins are 3, 5, 6, 9, 10, and 11
// 2 Interrupt Encoder
// 3 Interrupt Encoder (None PWM)
// 4 Encoder Dir
// 5 Motor PWM (Move from Pin 11)
// 6 Servo PWM
// 7 Encoder Dir (Move from Pin 5  )
// 8 Motor Dir
// 9 Motor PWM
// 10 Servo PWM
// 11 None PWM
// 12 Motor Dir
// 13

#define MOTOR_A_DIR_PIN (12)
#define MOTOR_A_SPEED_PIN (9)
#define MOTOR_B_DIR_PIN (8)
#define MOTOR_B_SPEED_PIN (5)
#define INT_A_PIN (2)
#define DIR_A_PIN (4)
#define INT_B_PIN (3)
#define DIR_B_PIN (7)
#define HORIZONTAL_SERVO_PIN (6)
#define VERTICAL_SERVO_PIN (10)
#define LED_PIN (13)

long interruptTime;

double CurrentAngle;

int CurrentEncoderCountA;
int CurrentEncoderCountB;
int TargetEncoderCountA;
int TargetEncoderCountB;
long TotalEncoderCountA;
long TotalEncoderCountB;

double TargetSpeedWanted = 0;
int ControlSpeedFactor = 0;

#define MOTOR_UPDATE_PERIOD (10)
#define DEBUG_UPDATE_PERIOD (250)

double TargetAngle;

unsigned long NextExtraUpdateTime;
unsigned long NextMotorUpdateTime;
unsigned long NextDebugUpdateTime;

bool SegwayEnabled = false;

double TargetSpeed = 0;
double SpeedPCorr = 0;
double SpeedICorr = 0;
double SpeedDCorr = 0;

double AnglePCorr = 10.0;
double AngleICorr = 5.0;
double AngleDCorr = 0.0;
int    SpeedCorrLimit = 600;
int    SpeedPIDLimit = 1000;

short OffsetAngle;

double TargetSpeedStepSizeChange = 0.1;
double TargetTurnSpeed = 0;
double TargetTurnSpeedWanted = 0;
double TargetTurnSpeedStepSizeChange = 0.1;

short Angle;
short AngleAcc;
int coSpeed;

void SetupLED() {
  pinMode(LED_PIN, OUTPUT);
  digitalWriteFast(LED_PIN, true);
}

bool BlinkState;
void UpdateBlinkLED() {
  BlinkState = !BlinkState;
  digitalWriteFast(LED_PIN, BlinkState);
}

// connect motor controller pins to Arduino digital pins
void setup()
{
  SetupMotors();
  SetupMotorEncoders();
  SetupGyro();
  SetupRaspiSerial();
  SetupServo();
  SetupSegwayController();
  SetupLED();
  SetupTimer();

  SetSegwayEnabled(true);
}

void SetupTimer() {
  unsigned long t = millis();
  NextMotorUpdateTime = t + MOTOR_UPDATE_PERIOD;
  NextExtraUpdateTime = t + MOTOR_UPDATE_PERIOD + MOTOR_UPDATE_PERIOD/2.0;
}

void loop()
{
  unsigned long t = millis();
  if(t >= NextMotorUpdateTime) {
    NextMotorUpdateTime = t + MOTOR_UPDATE_PERIOD;
    UpdateEncoderCount();
    UpdateSegway();
    UpdateMotor();    
  }
  else if(t >= NextExtraUpdateTime) {
    NextExtraUpdateTime = t + MOTOR_UPDATE_PERIOD;
    UpdateServo();
    UpdateGyro();
    UpdateReadRaspiCommand();
  }
/*  else if(t >= NextDebugUpdateTime) {
    NextDebugUpdateTime = t + DEBUG_UPDATE_PERIOD;
    Serial.print(CurrentEncoderCountA);
    Serial.print(" , ");
    Serial.println(CurrentEncoderCountB);
    Serial.println(CurrentAngle);
  }*/
  UpdateGyro();
}
