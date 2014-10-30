/*
 Uses an Arduino motorshield
 PWM control for PWM-speed.
 Motor-speed is based on a PID-controller (input from Encoder and output to PWM-speed)
 Motor-speed is set/read with COM-interface
 PID-constants are set with COM-interface
 
 Digital PIN 0, 1
 - COM RX/TX
 
 Digital PIN 2
 - Interrupt 0 is used for Encoder-B
 
 Digital PIN 3
 - Interrupt 1 is used for Encoder-A
 
 Digital PIN 4, 5, 6, 7
 - MotorShield PWM control (Motor A and Motor B)
 
 Digital PIN 8
 - Encoder-B direction
 
 Digital PIN 9
 - Encoder-A direction
 
 Digital PIN 10, 11
 Ultrasonic DistanceSensor (Echo Pin 11, Trigger Pin 10)
 
 Digital PIN 12
 - Servo-0 PWM
   
 Digital PIN 13
 - Switch
 */

#include <PID_v1.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <digitalWriteFast.h>
#include "MotorControllerCmd.h"

#define ENCODER_B_INTERRUPT_PIN (0) // Encoder-0 Interrupt is on DIGITAL PIN 2
#define ENCODER_A_INTERRUPT_PIN (1) // Encoder-1 Interrupt is on DIGITAL PIN 3
#define ENCODER_B_INTERRUPT_CHANGE_PIN (2) // Encoder-0 is on DIGITAL PIN 2
#define ENCODER_A_INTERRUPT_CHANGE_PIN (3) // Encoder-1 is on DIGITAL PIN 3

#define MOTOR_A_DIRECTION_PIN (4) //MotorShield Motor B
#define MOTOR_A_PWM_PIN (5) //MotorShield Motor B
#define MOTOR_B_DIRECTION_PIN (7) //MotorShield Motor A
#define MOTOR_B_PWM_PIN (6) //MotorShield Motor A
#define ENCODER_B_DIRECTION_PIN (9) // Encoder-0 Direction is on DIGITAL PIN 9
#define ENCODER_A_DIRECTION_PIN (8) // Encoder-1 Direction is on DIGITAL PIN 8
#define DISTANCE_SENSOR_TRIG   (10) // Distance sensor Trigger
#define DISTANCE_SENSOR_ECHO   (11) // Distance sensor Echo
#define SERVO_0_PIN            (12) // Signal for Servo-0 on DIGITAL PIN 12
#define SWITCH_PIN             (13) // Port Switch

#define MOTOR_FORWARD (0)
#define MOTOR_REVERSE (1)

volatile int Encoder0TickSpeed = 0;
volatile int Encoder1TickSpeed = 0;
int LastEncoder0TickSpeed = 0;
int LastEncoder1TickSpeed = 0;

long Encoder0TotalTicks = 0;
long Encoder1TotalTicks = 0;

int MotorATargetTickSpeed = 0; //Target ticks pr sample time
int MotorBTargetTickSpeed = 0; //Target ticks pr sample time
int MotorASpeed = 0; //PWM value in range [-255 ; +255]
int MotorBSpeed = 0; //PWM value in range [-255 ; +255]

float MotorA_Kp = 26;
float MotorA_Ki = 3;
float MotorA_Kd = 0;

float MotorB_Kp = 25;
float MotorB_Ki = 3;
float MotorB_Kd = 0;

#define PID_DIVISION_FACTOR (100.0)
float Dir_Kp = 8;
float Dir_Ki = 1;
float Dir_Kd = 0;

int CorrectionDir = 0;
int TargetDirSpeed = 0;
int TargetDir = 0;
int TargetRotation = 0;
int TargetDirRotation = 0;
int CurrentDir;
int MotorATargetDirTickSpeed = 0; //Target ticks pr sample time
int MotorBTargetDirTickSpeed = 0; //Target ticks pr sample time
#define DIRFACTOR (100.0)

int TargetDirDistance = 0;
int CurrentDirDistance = 0;
int AddingDistance = 0;
int MoveByDistance = 0;

#define DISTANCEMAXCOUNTER (20)
int TargetDirSpeedList[DISTANCEMAXCOUNTER];
int TargetDirList[DISTANCEMAXCOUNTER];
int TargetRotationList[DISTANCEMAXCOUNTER];
int TargetDirDistanceList[DISTANCEMAXCOUNTER];
int DistanceListCounter = 0;
int DistanceListIndex = 0;

PID motorAPID(&LastEncoder0TickSpeed, &MotorASpeed, &MotorATargetTickSpeed, MotorA_Kp, MotorA_Ki, MotorA_Kd, DIRECT);
PID motorBPID(&LastEncoder1TickSpeed, &MotorBSpeed, &MotorBTargetTickSpeed, MotorB_Kp, MotorB_Ki, MotorB_Kd, REVERSE);
PID DirPID(&CurrentDir, &CorrectionDir, &TargetDirRotation, Dir_Kp, Dir_Ki, Dir_Kd, REVERSE);

unsigned long CalculationTime = 0;
unsigned long SampleTime = 40;
int SampleTimeToSmall = false;

int PortCount = 0;
int totalTicks;

int (*CurrentDistanceCalculator)(void);

Servo servo0; // Define Servo-0
#define SERVO_0_STARTPOSITION (70)

Ultrasonic distanceSensor(DISTANCE_SENSOR_TRIG,DISTANCE_SENSOR_ECHO);

int SwitchCount = 0;
int SwitchChangeCount = 0;
bool LastSwitchLow = true;

void setup() 
{ 
  //Arduino Switch setup
  pinMode(SWITCH_PIN, INPUT);

  //Attach the interrupt to the input pin and monitor
  attachInterrupt(ENCODER_B_INTERRUPT_PIN, Encoder0Count, CHANGE);
  attachInterrupt(ENCODER_A_INTERRUPT_PIN, Encoder1Count, CHANGE);

  //Set Direction for Encoder pins
  pinMode(ENCODER_B_DIRECTION_PIN, INPUT); 
  pinMode(ENCODER_A_DIRECTION_PIN, INPUT);

  //Set Direction for Motor pins
  pinMode(MOTOR_A_DIRECTION_PIN, OUTPUT);   
  pinMode(MOTOR_B_DIRECTION_PIN, OUTPUT); 

  //Set MotorPID
  motorAPID.SetOutputLimits(-255, 255);
  motorBPID.SetOutputLimits(-255, 255);
  DirPID.SetOutputLimits(-10, 10);
  motorAPID.SetMode(AUTOMATIC);
  motorBPID.SetMode(AUTOMATIC);
  DirPID.SetMode(AUTOMATIC);

  UpdateSampleTime(SampleTime);

  //Servo setup
  servo0.attach(SERVO_0_PIN);
  servo0.write(SERVO_0_STARTPOSITION);

  //Serial Setup
  Serial.begin(9600);           // set up Serial library at 9600 bps  
} 

unsigned long cycleStartTime;
unsigned long cycleEndTime;

void loop() 
{      
  cycleEndTime = cycleStartTime + SampleTime;              
  while(millis() < cycleEndTime) 
  {
    HandleCom();
  }   
  cycleStartTime = millis();  

  UpdateEncoderCounters();

  if(MoveByDistance)
  {
    SetSpeedByDistance();
    AdjustDirection();
  }

  motorAPID.Compute();  
  motorBPID.Compute();
  
  SetMotorSpeed(MOTOR_A_DIRECTION_PIN, MOTOR_A_PWM_PIN, MotorASpeed);
  SetMotorSpeed(MOTOR_B_DIRECTION_PIN, MOTOR_B_PWM_PIN, MotorBSpeed);       

  SwitchRead();

  unsigned long CalculationEndTime = millis();

  if(CalculationEndTime > cycleStartTime + SampleTime)
    SampleTimeToSmall = true;

  CalculationTime = CalculationEndTime - cycleStartTime;
}

void SwitchRead()
{
  if(SwitchChangeCount == 0)
  {
    if(LastSwitchLow)
    {    
      if(digitalReadFast(SWITCH_PIN) == HIGH)
      {
        SwitchCount++;
        SwitchChangeCount = 10;
        LastSwitchLow = false;
      }
    }
    else
    {
      if(digitalReadFast(SWITCH_PIN) == LOW)
      {
        SwitchCount++;
        SwitchChangeCount = 10;
        LastSwitchLow = true;
      }
    }
  }
  else
  {
    SwitchChangeCount--;
  }
}

void Encoder0Count()
{
  if(digitalReadFast(ENCODER_B_DIRECTION_PIN) == digitalReadFast(ENCODER_B_INTERRUPT_CHANGE_PIN))
    Encoder0TickSpeed++;
  else
    Encoder0TickSpeed--;
}

void Encoder1Count()
{
  if(digitalReadFast(ENCODER_A_DIRECTION_PIN) == digitalReadFast(ENCODER_A_INTERRUPT_CHANGE_PIN))
    Encoder1TickSpeed--;
  else
    Encoder1TickSpeed++;
}

void SetMotorSpeed(int DirectionPin, int PWMPin, float Speed)
{
  //Set PWM-Speed and direction for Motor 
  if(Speed > 0)
  {
    digitalWrite(DirectionPin, MOTOR_FORWARD);
    analogWrite(PWMPin, Speed);
  }
  else 
  {
    digitalWrite(DirectionPin, MOTOR_REVERSE);
    analogWrite(PWMPin, -Speed);
  }
}

void HandleCom()
{
  int ReceivedCmd;
  int ReceivedData;
  if(Serial.available() >= 3) //Cmd contains 3 bytes
  {
    //Receive Cmd and data
    ReceivedCmd = Serial.read();
    ReceivedData = Serial.read(); //MSB
    ReceivedData = ReceivedData << 8;
    ReceivedData |= Serial.read(); //LSB

    //Execute Cmd
    long response = ExecuteCmd(ReceivedCmd, ReceivedData);
    char responseLength = ResponseLength[ReceivedCmd];
    if(responseLength > 0)
    {    
      //Send response
      switch(responseLength)
      {
      case 4:
        Serial.write((byte)(response >> 24)); //MSB
      case 3:
        Serial.write((byte)(response >> 16));
      case 2:
        Serial.write((byte)(response >> 8));      
      case 1:      
        Serial.write((byte)(response & 0xFF)); //LSB
      }
    }
  }
}

void UpdateSampleTime(int sampleTime)
{
  SampleTime = sampleTime;
  SampleTimeToSmall = false;
  motorAPID.SetSampleTime(SampleTime);
  motorBPID.SetSampleTime(SampleTime); 
  DirPID.SetSampleTime(SampleTime);  
}

long ExecuteCmd(int cmd, int data)
{
  switch(cmd)
  {
  case CMD_SET_DIRECTION:
    TargetDir = data;
    SetTargetMotorSpeed();      
    return 0;

  case CMD_SET_ROTATION:
    TargetRotation = data;
    SetTargetMotorSpeed();
    return 0;

  case CMD_SET_SPEED:
    TargetDirSpeed = data;
    SetTargetMotorSpeed();      
    return 0;

  case CMD_SET_DISTANCE:
    TargetDirDistance = data;
    return 0;

  case CMD_SET_MOVE_BY_DISTANCE:
    if(data == 1)
      GetNextMoveByDistance();
    
    MoveByDistance = data;
    return 0;
  
  case CMD_GET_MOVE_BY_DISTANCE:
    return MoveByDistance;
    
  case CMD_ADD_MOVE_BY_DISTANCE:
    AddMoveByDistance(data);
    return 0;
     
  case CMD_GET_MOTOR_A_DISTANCE:
    return Encoder0TotalTicks;

  case CMD_GET_MOTOR_B_DISTANCE:
    return Encoder1TotalTicks;

  case CMD_RESET_MOTOR_DISTANCE:
    ResetTotalTicks();
    return 0;

  case CMD_SET_MOTOR_A_KP:
    MotorA_Kp = data / PID_DIVISION_FACTOR;
    motorAPID.SetTunings(MotorA_Kp, MotorA_Ki, MotorA_Kd);
    return 0;

  case CMD_SET_MOTOR_A_KI:
    MotorA_Ki = data / PID_DIVISION_FACTOR;
    motorAPID.SetTunings(MotorA_Kp, MotorA_Ki, MotorA_Kd);
    return 0;

  case CMD_SET_MOTOR_A_KD:
    MotorA_Kd = data / PID_DIVISION_FACTOR;
    motorAPID.SetTunings(MotorA_Kp, MotorA_Ki, MotorA_Kd);
    return 0;

  case CMD_SET_PID_SAMPLETIME:
    UpdateSampleTime(data);
    return 0;

  case CMD_SET_MOTOR_B_KP:
    MotorB_Kp = data / PID_DIVISION_FACTOR;
    motorBPID.SetTunings(MotorB_Kp, MotorB_Ki, MotorB_Kd);
    return 0;

  case CMD_SET_MOTOR_B_KI:
    MotorB_Ki = data / PID_DIVISION_FACTOR;
    motorBPID.SetTunings(MotorB_Kp, MotorB_Ki, MotorB_Kd);
    return 0;

  case CMD_SET_MOTOR_B_KD:
    MotorB_Kd = data / PID_DIVISION_FACTOR;
    motorBPID.SetTunings(MotorB_Kp, MotorB_Ki, MotorB_Kd);
    return 0;

  case CMD_SET_DIR_KP:
    Dir_Kp = (data / PID_DIVISION_FACTOR);
    DirPID.SetTunings(Dir_Kp, Dir_Ki, Dir_Kd);
    return 0;

  case CMD_SET_DIR_KI:
    Dir_Ki = (data / PID_DIVISION_FACTOR);
    DirPID.SetTunings(Dir_Kp, Dir_Ki, Dir_Kd);
    return 0;

  case CMD_SET_DIR_KD:
    Dir_Kd = (data / PID_DIVISION_FACTOR);
    DirPID.SetTunings(Dir_Kp, Dir_Ki, Dir_Kd);
    return 0;

  case CMD_SET_SERVO_0_POSITION:
    servo0.write(data);
    return 0; 

  case CMD_GET_DISTANCESENSOR_MEASURE:
    return distanceSensor.Ranging(CM);

  case CMD_GET_MOTOR_A_TICKSPEED:
    return LastEncoder0TickSpeed;

  case CMD_GET_MOTOR_B_TICKSPEED:
    return LastEncoder1TickSpeed;

  case CMD_GET_SAMPLETIME_TO_SMALL:
    return SampleTimeToSmall;

  case CMD_GET_LAST_CYCLE_TIME:
    return CalculationTime;

  case CMD_RETURN_NEGATIV_TEST:
    return (long)(1000*MotorA_Kp);

  case CMD_GET_PORT_COUNT:
    return SwitchCount;

  case CMD_RESET_PORT_COUNT:
    SwitchCount = 0;
    return 0;      
  }
  return 0;  
}

void UpdateEncoderCounters()
{
  LastEncoder0TickSpeed = Encoder0TickSpeed;
  Encoder0TickSpeed = 0;  
  LastEncoder1TickSpeed = Encoder1TickSpeed;
  Encoder1TickSpeed = 0;     
  Encoder1TotalTicks += LastEncoder1TickSpeed;
  Encoder0TotalTicks += LastEncoder0TickSpeed;
}

void ResetTotalTicks()
{
  Encoder0TotalTicks = 0;
  Encoder1TotalTicks = 0;
}

int DistanceForward()
{
  return Encoder0TotalTicks + Encoder1TotalTicks;
}

int DistanceBackward()
{
  return -Encoder0TotalTicks - Encoder1TotalTicks;
}

int DistanceClockwise()
{
  return Encoder0TotalTicks - Encoder1TotalTicks;
}

int DistanceCounterClockwise()
{
  return -Encoder0TotalTicks + Encoder1TotalTicks;
}

void SetSpeedByDistance()
{
  CurrentDirDistance = CurrentDistanceCalculator();  
  
  if(TargetDirDistance <= CurrentDirDistance)
  {
    if(DistanceListIndex == DistanceListCounter)
    {
      TargetDirSpeed = 0;
      SetTargetMotorSpeed();
      MoveByDistance = 0;
      DistanceListIndex = 0;
      DistanceListCounter = 0;
    }
    else
    {
      GetNextMoveByDistance();
    }
  }
}

void GetNextMoveByDistance()
{
  GetNextDirDistanceFromList();
  ResetTotalTicks();
  CurrentDirDistance = 0;
  SetTargetMotorSpeed();
}

void GetNextDirDistanceFromList()
{
  TargetDirSpeed = TargetDirSpeedList[DistanceListIndex];
  TargetDir = TargetDirList[DistanceListIndex];
  TargetRotation = TargetRotationList[DistanceListIndex];
  TargetDirDistance = TargetDirDistanceList[DistanceListIndex];
  DistanceListIndex++;
}

void AddMoveByDistance(int addDistance)
{
  if(addDistance == 0)
  {
    AddDirToDistanceList();
  }
  AddingDistance = addDistance;
}

void AddDirToDistanceList()
{
  TargetDirSpeedList[DistanceListCounter] = TargetDirSpeed;
  TargetDirList[DistanceListCounter] = TargetDir;
  TargetRotationList[DistanceListCounter] = TargetRotation;
  TargetDirDistanceList[DistanceListCounter] = TargetDirDistance;
  DistanceListCounter++;
}

void SetTargetMotorSpeed()
{
  if(AddingDistance == 0)
  {
    if(TargetRotation == 0)
    {
      TargetDirRotation = TargetDirSpeed * (TargetDir / DIRFACTOR);
    }
    else
    {
      TargetDirRotation = TargetDir;
    }
    
    MotorATargetDirTickSpeed = TargetDirSpeed + TargetDirRotation;
    MotorBTargetDirTickSpeed = TargetDirSpeed - TargetDirRotation;
    MotorATargetTickSpeed = MotorATargetDirTickSpeed;
    MotorBTargetTickSpeed = MotorBTargetDirTickSpeed;

    if(MotorATargetTickSpeed >= 0)
    {
      if(MotorBTargetTickSpeed >= 0)
      {
        CurrentDistanceCalculator = DistanceForward;
      }
      else
      {
        CurrentDistanceCalculator = DistanceClockwise;
      }
    }
    else
    {
      if(MotorBTargetTickSpeed >= 0)
      {
        CurrentDistanceCalculator = DistanceCounterClockwise;
      }
      else
      {
        CurrentDistanceCalculator = DistanceBackward;
      }
    }    
  }
}


void AdjustDirection()
{
  CurrentDir = (LastEncoder0TickSpeed - LastEncoder1TickSpeed) >> 1;
  DirPID.Compute();
  
  MotorATargetTickSpeed = MotorATargetDirTickSpeed - CorrectionDir;
  MotorBTargetTickSpeed = MotorBTargetDirTickSpeed + CorrectionDir;
}
