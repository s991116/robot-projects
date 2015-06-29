#include <Wire.h>
#include <PID_v1.h>
#include <digitalWriteFast.h>
#include <DataLogger.h>
#include "MotorControllerCmd.h"

//#define DEBUG
#define DEBUG_CONSTSPEED (0)

#define ENCODER_LEFT_INTERRUPT_PIN (0) // Encoder-0 Interrupt is on DIGITAL PIN 2
#define ENCODER_RIGHT_INTERRUPT_PIN (1) // Encoder-1 Interrupt is on DIGITAL PIN 3

#define ENCODER_LEFT_INTERRUPT_CHANGE_PIN (2) // Encoder-0 is on DIGITAL PIN 2
#define ENCODER_RIGHT_INTERRUPT_CHANGE_PIN (3) // Encoder-1 is on DIGITAL PIN 3

#define MOTOR_LEFT_DIRECTION_PIN (4) //MotorShield Motor B
#define MOTOR_LEFT_PWM_PIN (5) //MotorShield Motor B
#define MOTOR_RIGHT_PWM_PIN (6) //MotorShield Motor A
#define MOTOR_RIGHT_DIRECTION_PIN (7) //MotorShield Motor A

#define ENCODER_LEFT_DIRECTION_PIN (13) // Encoder-0 Direction is on DIGITAL PIN 4
#define ENCODER_RIGHT_DIRECTION_PIN (8) // Encoder-1 Direction is on DIGITAL PIN 5

#define I2C_ADDRESS (0x04)

#define MOTOR_FORWARD (0)
#define MOTOR_REVERSE (1)

#define PID_DIVISION_FACTOR (1000.0)

volatile short EncoderLeftTickSpeed = 0;
volatile short EncoderRightTickSpeed = 0;
int LastEncoderLeftTickSpeed = 0;
int LastEncoderRightTickSpeed = 0;

long EncoderLeftTotalTicks = 0;
long EncoderRightTotalTicks = 0;

int MotorLeftTargetTickSpeed = 0; //Target ticks pr sample time
int MotorRightTargetTickSpeed = 0; //Target ticks pr sample time
int MotorLeftSpeed = 0; //PWM value in range [-255 ; +255]
int MotorRightSpeed = 0; //PWM value in range [-255 ; +255]

float MotorLeft_Kp = 3.7;
float MotorLeft_Ki = 0.2;
float MotorLeft_Kd = 0.08;

float MotorRight_Kp = 3.7;
float MotorRight_Ki = 0.2;
float MotorRight_Kd = 0.08;

PID motorLeftPID(&LastEncoderLeftTickSpeed, &MotorLeftSpeed, &MotorLeftTargetTickSpeed, MotorLeft_Kp, MotorLeft_Ki, MotorLeft_Kd, REVERSE);
PID motorRightPID(&LastEncoderRightTickSpeed, &MotorRightSpeed, &MotorRightTargetTickSpeed, MotorRight_Kp, MotorRight_Ki, MotorRight_Kd, DIRECT);

unsigned long CalculationStartTime;
unsigned long CalculationEndTime;
short WaitTime;
short SampleTime = 10;
int SampleTimeToSmall = false;
short LastResponse = 0;
bool MotorsRunning = true;

DataLogger logger;

void setup() 
{ 
  SetupPins();
  
  //Set MotorPID
  motorLeftPID.SetOutputLimits(-255, 255);
  motorRightPID.SetOutputLimits(-255, 255);
  motorLeftPID.SetMode(AUTOMATIC);
  motorRightPID.SetMode(AUTOMATIC);

  //Setup Communication
  SetupCommunication();
  
  #ifdef DEBUG
  Serial.begin(57600);
  MotorLeftTargetTickSpeed = DEBUG_CONSTSPEED;
  MotorRightTargetTickSpeed = DEBUG_CONSTSPEED;
  #endif
} 

void SetupPins()
{
    //Attach the interrupt to the input pin and monitor
  attachInterrupt(ENCODER_LEFT_INTERRUPT_PIN, EncoderLeftCount, RISING); //CHANGE, RISING
  attachInterrupt(ENCODER_RIGHT_INTERRUPT_PIN, EncoderRightCount, RISING); //CHANGE, RISING

  //Set Direction for Encoder pins
  pinMode(ENCODER_LEFT_DIRECTION_PIN, INPUT);
  pinMode(ENCODER_RIGHT_DIRECTION_PIN, INPUT);

  pinMode(ENCODER_LEFT_INTERRUPT_CHANGE_PIN, INPUT);
  pinMode(ENCODER_RIGHT_INTERRUPT_CHANGE_PIN, INPUT);

  //Set Direction for Motor pins
  pinMode(MOTOR_LEFT_DIRECTION_PIN, OUTPUT);   
  pinMode(MOTOR_RIGHT_DIRECTION_PIN, OUTPUT); 
}

void SetupCommunication()
{
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(ReceiveMessageEvent);
  Wire.onRequest(RequestDataEvent);
}

void RequestDataEvent()
{
  uint8_t buffer[2];
  buffer[0] = MSB_FromShort(LastResponse);
  buffer[1] = LSB_FromShort(LastResponse);
  Wire.write(buffer, 2);
}

void ReceiveMessageEvent(int bytesAvailable) {
  if(bytesAvailable == 3)
  {
    byte command  = Wire.read();
    byte msb = Wire.read();
    byte lsb = Wire.read();
    short data = Bytes_ToShort(msb, lsb);
    HandleCommand(command, data);
  }
}

unsigned long cycleStartTime;
unsigned long cycleEndTime;

void loop() 
{      
  CalculationStartTime = millis();  
  #ifdef DEBUG
  Serial.print("Encoder Left: ");
  Serial.print(EncoderLeftTotalTicks, DEC);
  Serial.print(" , Encoder Right: ");
  Serial.println(EncoderRightTotalTicks, DEC);
  #endif

  UpdateEncoderCounters();

  AddMeasurement(LastEncoderLeftTickSpeed, MotorLeftTargetTickSpeed);

  motorLeftPID.Compute();  
  motorRightPID.Compute();
  
  if(MotorsRunning)
  {
    SetMotorSpeed(MOTOR_LEFT_DIRECTION_PIN, MOTOR_LEFT_PWM_PIN, MotorLeftSpeed);
    SetMotorSpeed(MOTOR_RIGHT_DIRECTION_PIN, MOTOR_RIGHT_PWM_PIN, MotorRightSpeed);       
  }
  else
  {
    StopMotors();
  }
  
  CalculationEndTime = millis();
  unsigned long cycleEndTime = CalculationStartTime + SampleTime;

  WaitTime = cycleEndTime - CalculationEndTime ;
  if(WaitTime <= 0)
  {
    SampleTimeToSmall = true;
  }
  else
  {
    while(millis() < cycleEndTime);
  }
}

void EncoderLeftCount()
{
  if(digitalReadFast(ENCODER_LEFT_DIRECTION_PIN))
    EncoderLeftTickSpeed--;
  else
    EncoderLeftTickSpeed++;
}

void EncoderRightCount()
{
  if(digitalReadFast(ENCODER_RIGHT_DIRECTION_PIN))
    EncoderRightTickSpeed++;
  else
    EncoderRightTickSpeed--;
}

void SetMotorSpeed(int DirectionPin, int PWMPin, float Speed)
{
  //Set PWM-Speed and direction for Motor 
  if(Speed > 0)
  {
    digitalWriteFast(DirectionPin, MOTOR_FORWARD);
    analogWrite(PWMPin, Speed);
  }
  else 
  {
    digitalWriteFast(DirectionPin, MOTOR_REVERSE);
    analogWrite(PWMPin, -Speed);
  }
}

void StopMotors()
{
  digitalWriteFast(MOTOR_LEFT_DIRECTION_PIN, MOTOR_FORWARD);
  analogWrite(MOTOR_LEFT_PWM_PIN, 0);
  digitalWriteFast(MOTOR_RIGHT_DIRECTION_PIN, MOTOR_FORWARD);
  analogWrite(MOTOR_RIGHT_PWM_PIN, 0);
  LastEncoderLeftTickSpeed = 0;
  LastEncoderRightTickSpeed = 0;
}

void UpdateEncoderCounters()
{
  LastEncoderLeftTickSpeed = EncoderLeftTickSpeed;
  EncoderLeftTickSpeed = 0;  
  EncoderLeftTotalTicks += LastEncoderLeftTickSpeed;

  LastEncoderRightTickSpeed = EncoderRightTickSpeed;
  EncoderRightTickSpeed = 0;     
  EncoderRightTotalTicks += LastEncoderRightTickSpeed;
}

short MeasureState = 0; //1 = AddMeasure, 0 = Readmeasure

void AddMeasurement(short error, short target)
{
  if(MeasureState == 1)
  {
      logger.AddMeasure(error, target);
  } 
}

void HandleCommand(byte command, short data)
{
  switch(command)
  {
    case Set_Motor_Speed:// 0:
     MotorLeftTargetTickSpeed = data;
     MotorRightTargetTickSpeed = data;
     break;
     
    case Set_MotorLeft_PID_Kp:
     MotorLeft_Kp = data / PID_DIVISION_FACTOR;
     UpdateMotorLeftPID();
     break;
      
    case Set_MotorLeft_PID_Ki:
     MotorLeft_Ki = data / PID_DIVISION_FACTOR;
     UpdateMotorLeftPID();
     break;

    case Set_MotorLeft_PID_Kd:
     MotorLeft_Kd = data / PID_DIVISION_FACTOR;
     UpdateMotorLeftPID();
     break;

    case Set_MotorRight_PID_Kp:
     MotorRight_Kp = data / PID_DIVISION_FACTOR;
     UpdateMotorRightPID();
     break;

    case Set_MotorRight_PID_Ki:
     MotorRight_Ki = data / PID_DIVISION_FACTOR;
     UpdateMotorRightPID();
     break;

    case Set_MotorRight_PID_Kd:
     MotorRight_Kd = data / PID_DIVISION_FACTOR;
     UpdateMotorRightPID();
     break;
     
    case Set_MotorLeft_Speed:
     MotorLeftTargetTickSpeed = data;
     break;

    case Set_MotorRight_Speed:
     MotorRightTargetTickSpeed = data;
     break;
    
     case Get_MotorLeft_Speed:
      LastResponse = LastEncoderLeftTickSpeed;
      break;
      
    case Get_MotorRight_Speed:
      LastResponse = LastEncoderRightTickSpeed;
      break;
      
    case Get_MotorLeft_Distance:
      LastResponse = EncoderLeftTotalTicks;
      break;

    case Get_MotorRight_Distance:
      LastResponse = EncoderRightTotalTicks;
      break;
      
    case Set_Motor_Enabled:
      MotorsRunning = data;
      break;

    case Get_WaitTime:
      LastResponse = WaitTime;
      break;
      
    case Set_Logging_State:
      MeasureState = data;
      break;

    case Get_Logging_Error:
      LastResponse = logger.GetMeasure1();
      break;

    case Get_MotorLeft_PID_Kp:
      LastResponse = MotorLeft_Kp * PID_DIVISION_FACTOR;
      break;

    case Get_MotorLeft_PID_Ki:
      LastResponse = MotorLeft_Ki * PID_DIVISION_FACTOR;
      break;

    case Get_MotorLeft_PID_Kd:
      LastResponse = MotorLeft_Kd * PID_DIVISION_FACTOR;
      break;

    case Get_MotorRight_PID_Kp:
      LastResponse = MotorRight_Kp * PID_DIVISION_FACTOR;
      break;

    case Get_MotorRight_PID_Ki:
      LastResponse = MotorRight_Ki * PID_DIVISION_FACTOR;
      break;

    case Get_MotorRight_PID_Kd:
      LastResponse = MotorRight_Kd * PID_DIVISION_FACTOR;
      break;
      
    case Add_Logging_Data:
      logger.AddMeasure(data, data);
      LastResponse = 0;
      break;
      
    case Get_Nr_Of_Logs:
      LastResponse = logger.GetNrOfMeasures();
      break;

    case Reset_Logger:
      logger.Reset();
      LastResponse = 0;
      break;

    case Get_Logging_Target:
      LastResponse = logger.GetMeasure2();
      break;

    case Next_Logging:
      logger.NextMeasure();
      LastResponse = 0;
      break;

    case Logging_Full:
      LastResponse = logger.LogFull();
      break;
    
    case Get_Motor_Echo_Command_Test:
      LastResponse = command;
      break;

    case Get_Motor_Echo_Data_Test:
      LastResponse = data;
      break;
  }
}

void UpdateMotorLeftPID()
{
  motorLeftPID.SetTunings(MotorLeft_Kp, MotorLeft_Ki, MotorLeft_Kd);
}

void UpdateMotorRightPID()
{
  motorRightPID.SetTunings(MotorRight_Kp, MotorRight_Ki, MotorRight_Kd);
}

byte MSB_FromShort(short data) {
  return (data >> 8);
}

byte LSB_FromShort(short data) {
  return (data & 0x00FF);
}

short Bytes_ToShort(byte msb, byte lsb) {
    short data = (msb << 8);
    data |= lsb;
    return data;
}
