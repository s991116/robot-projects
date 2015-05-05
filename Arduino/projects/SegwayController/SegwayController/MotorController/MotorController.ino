/*
 Uses an Arduino motorshield
 PWM control for PWM-speed.
 Motor-speed is based on a PID-controller (input from Encoder and output to PWM-speed)
 Motor-speed is set/read with COM-interface
 PID-constants are set with COM-interface
*/

#include <PID_v1.h>
#include <digitalWriteFast.h>

#define ENCODER_A_INTERRUPT_PIN (0) // Encoder-0 Interrupt is on DIGITAL PIN 2
#define ENCODER_B_INTERRUPT_PIN (1) // Encoder-1 Interrupt is on DIGITAL PIN 3

#define ENCODER_A_INTERRUPT_CHANGE_PIN (2) // Encoder-0 is on DIGITAL PIN 2
#define ENCODER_B_INTERRUPT_CHANGE_PIN (3) // Encoder-1 is on DIGITAL PIN 3

#define MOTOR_B_DIRECTION_PIN (4) //MotorShield Motor B
#define MOTOR_B_PWM_PIN (5) //MotorShield Motor B
#define MOTOR_A_PWM_PIN (6) //MotorShield Motor A
#define MOTOR_A_DIRECTION_PIN (7) //MotorShield Motor A

#define ENCODER_A_DIRECTION_PIN (8) // Encoder-0 Direction is on DIGITAL PIN 4
#define ENCODER_B_DIRECTION_PIN (9) // Encoder-1 Direction is on DIGITAL PIN 5

#define MOTOR_FORWARD (0)
#define MOTOR_REVERSE (1)

#define PID_DIVISION_FACTOR (10000.0)

volatile short EncoderATickSpeed = 0;
volatile short EncoderBTickSpeed = 0;
int LastEncoderATickSpeed = 0;
int LastEncoderBTickSpeed = 0;

long EncoderATotalTicks = 0;
long EncoderBTotalTicks = 0;

int MotorATargetTickSpeed = 0; //Target ticks pr sample time
int MotorBTargetTickSpeed = 0; //Target ticks pr sample time
int MotorASpeed = 0; //PWM value in range [-255 ; +255]
int MotorBSpeed = 0; //PWM value in range [-255 ; +255]

float MotorA_Kp = 0.9;
float MotorA_Ki = 0;
float MotorA_Kd = 0;

float MotorB_Kp = 0.9;
float MotorB_Ki = 0;
float MotorB_Kd = 0;

PID motorAPID(&LastEncoderATickSpeed, &MotorASpeed, &MotorATargetTickSpeed, MotorA_Kp, MotorA_Ki, MotorA_Kd, REVERSE);
PID motorBPID(&LastEncoderBTickSpeed, &MotorBSpeed, &MotorBTargetTickSpeed, MotorB_Kp, MotorB_Ki, MotorB_Kd, REVERSE);

short CalculationTime = 0;
short SampleTime = 40;
int SampleTimeToSmall = false;

bool MotorsRunning = true;

void setup() 
{ 
  //Attach the interrupt to the input pin and monitor
  attachInterrupt(ENCODER_A_INTERRUPT_PIN, EncoderACount, RISING); //CHANGE, RISING
  attachInterrupt(ENCODER_B_INTERRUPT_PIN, EncoderBCount, RISING); //CHANGE, RISING

  //Set Direction for Encoder pins
  pinMode(ENCODER_A_DIRECTION_PIN, INPUT);
  pinMode(ENCODER_B_DIRECTION_PIN, INPUT);

  pinMode(ENCODER_A_INTERRUPT_CHANGE_PIN, INPUT);
  pinMode(ENCODER_B_INTERRUPT_CHANGE_PIN, INPUT);

  //Set Direction for Motor pins
  pinMode(MOTOR_A_DIRECTION_PIN, OUTPUT);   
  pinMode(MOTOR_B_DIRECTION_PIN, OUTPUT); 

  //Set MotorPID
  motorAPID.SetOutputLimits(-255, 255);
  motorBPID.SetOutputLimits(-255, 255);
  motorAPID.SetMode(AUTOMATIC);
  motorBPID.SetMode(AUTOMATIC);

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
    HandleSerialCommunication();
  }   
  cycleStartTime = millis();  

  UpdateEncoderCounters();

  AddMeasurement(LastEncoderATickSpeed);

  motorAPID.Compute();  
  motorBPID.Compute();
  
  if(MotorsRunning)
  {
    SetMotorSpeed(MOTOR_A_DIRECTION_PIN, MOTOR_A_PWM_PIN, MotorASpeed);
    SetMotorSpeed(MOTOR_B_DIRECTION_PIN, MOTOR_B_PWM_PIN, MotorBSpeed);       
  }
  else
  {
    StopMotors();
  }
  unsigned long CalculationEndTime = millis();

  if(CalculationEndTime > cycleStartTime + SampleTime)
    SampleTimeToSmall = true;

  CalculationTime = CalculationEndTime - cycleStartTime;
}

void EncoderACount()
{
  if(digitalReadFast(ENCODER_A_DIRECTION_PIN))
    EncoderATickSpeed--;
  else
    EncoderATickSpeed++;
}

void EncoderBCount()
{
  if(digitalReadFast(ENCODER_B_DIRECTION_PIN))
    EncoderBTickSpeed++;
  else
    EncoderBTickSpeed--;
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
  digitalWriteFast(MOTOR_A_DIRECTION_PIN, MOTOR_FORWARD);
  analogWrite(MOTOR_A_PWM_PIN, 0);
  digitalWriteFast(MOTOR_B_DIRECTION_PIN, MOTOR_FORWARD);
  analogWrite(MOTOR_B_PWM_PIN, 0);
}

void UpdateEncoderCounters()
{
  LastEncoderATickSpeed = EncoderATickSpeed;
  EncoderATickSpeed = 0;  
  EncoderATotalTicks += LastEncoderATickSpeed;

  LastEncoderBTickSpeed = EncoderBTickSpeed;
  EncoderBTickSpeed = 0;     
  EncoderBTotalTicks += LastEncoderBTickSpeed;
}

void HandleSerialCommunication()
{
  byte command;
  short data;
  //Command available
  if(Serial.available() >= 3)
  {
    command = Serial.read();
    data = Serial.read(); //LSB
    data |= (Serial.read() << 8); //MSB

    short response = HandleCommand(command, data);
    
    Serial.write((byte)(response & 0xFF)); //LSB
    Serial.write((byte)(response >> 8));   //MSB
  }
}

short nextIndex = 0;
#define measureArrayLength (500)
short measureArray[500];
short MeasureState = 0; //0 = AddMeasure, 1 = Readmeasure


void AddMeasurement(short measure)
{
  if(MeasureState == 0)
  {
    measureArray[nextIndex] = measure;
    nextIndex++;
    if(nextIndex >= measureArrayLength)
    {
      nextIndex = 0;
    }
  } 
}

short GetMeasurement()
{
  if(MeasureState == 1)
  {
    nextIndex++;
    if(nextIndex >= measureArrayLength)
    {
      nextIndex = 0;
    }
    return measureArray[nextIndex];
  }
  return 0;
}

short HandleCommand(byte command, short data)
{
  switch(command)
  {
    case 1:
     MotorA_Kp = data / PID_DIVISION_FACTOR;
     UpdateMotorAPID();
     break;
      
    case 2:
     MotorA_Ki = data / PID_DIVISION_FACTOR;
     UpdateMotorAPID();
     break;

    case 3:
     MotorA_Kd = data / PID_DIVISION_FACTOR;
     UpdateMotorAPID();
     break;

    case 4:
     MotorB_Kp = data / PID_DIVISION_FACTOR;
     UpdateMotorBPID();
     break;

    case 5:
     MotorB_Ki = data / PID_DIVISION_FACTOR;
     UpdateMotorBPID();
     break;

    case 6:
     MotorB_Kd = data / PID_DIVISION_FACTOR;
     UpdateMotorBPID();
     break;
     
    case 7:
     MotorATargetTickSpeed = data;
     break;

    case 8:
     MotorBTargetTickSpeed = data;
     break;
    
    case 9:
      return LastEncoderATickSpeed;
      
    case 10:
      return LastEncoderBTickSpeed;
      
    case 11:
      return EncoderATotalTicks;

    case 12:
      return EncoderBTotalTicks;
      
    case 13:
      MotorsRunning = data;
      break;

    case 14:
      return CalculationTime;
      
    case 15:
      MeasureState = data;
      break;

    case 16:
      return GetMeasurement();

    case 255:
      return data;
      break;
  }
  return 0;
}

void UpdateMotorAPID()
{
  motorAPID.SetTunings(MotorA_Kp, MotorA_Ki, MotorA_Kd);
}

void UpdateMotorBPID()
{
  motorBPID.SetTunings(MotorB_Kp, MotorB_Ki, MotorB_Kd);
}
