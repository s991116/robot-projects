/*
 Uses an Arduino motorshield
 PWM control for PWM-speed.
 Motor-speed is based on a PID-controller (input from Encoder and output to PWM-speed)
 Motor-speed is set/read with COM-interface
 PID-constants are set with COM-interface
*/

#include <PID_v1.h>
#include <digitalWriteFast.h>


#define ENCODER_B_INTERRUPT_PIN (0) // Encoder-0 Interrupt is on DIGITAL PIN 2
#define ENCODER_A_INTERRUPT_PIN (1) // Encoder-1 Interrupt is on DIGITAL PIN 3
#define ENCODER_B_INTERRUPT_CHANGE_PIN (2) // Encoder-0 is on DIGITAL PIN 2
#define ENCODER_A_INTERRUPT_CHANGE_PIN (3) // Encoder-1 is on DIGITAL PIN 3

#define MOTOR_A_DIRECTION_PIN (4) //MotorShield Motor B
#define MOTOR_A_PWM_PIN (5) //MotorShield Motor B
#define MOTOR_B_DIRECTION_PIN (7) //MotorShield Motor A
#define MOTOR_B_PWM_PIN (6) //MotorShield Motor A
#define ENCODER_B_DIRECTION_PIN (3) // Encoder-0 Direction is on DIGITAL PIN 9
#define ENCODER_A_DIRECTION_PIN (4) // Encoder-1 Direction is on DIGITAL PIN 8

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
float MotorA_Ki = 16;
float MotorA_Kd = 0;

float MotorB_Kp = 25;
float MotorB_Ki = 15;
float MotorB_Kd = 0;

PID motorAPID(&LastEncoder0TickSpeed, &MotorASpeed, &MotorATargetTickSpeed, MotorA_Kp, MotorA_Ki, MotorA_Kd, DIRECT);
PID motorBPID(&LastEncoder1TickSpeed, &MotorBSpeed, &MotorBTargetTickSpeed, MotorB_Kp, MotorB_Ki, MotorB_Kd, REVERSE);

unsigned long CalculationTime = 0;
unsigned long SampleTime = 40;
int SampleTimeToSmall = false;

void setup() 
{ 
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

  motorAPID.Compute();  
  motorBPID.Compute();
  
  SetMotorSpeed(MOTOR_A_DIRECTION_PIN, MOTOR_A_PWM_PIN, MotorASpeed);
  SetMotorSpeed(MOTOR_B_DIRECTION_PIN, MOTOR_B_PWM_PIN, MotorBSpeed);       

  unsigned long CalculationEndTime = millis();

  if(CalculationEndTime > cycleStartTime + SampleTime)
    SampleTimeToSmall = true;

  CalculationTime = CalculationEndTime - cycleStartTime;
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

void UpdateEncoderCounters()
{
  LastEncoder0TickSpeed = Encoder0TickSpeed;
  Encoder0TickSpeed = 0;  
  LastEncoder1TickSpeed = Encoder1TickSpeed;
  Encoder1TickSpeed = 0;     
  Encoder1TotalTicks += LastEncoder1TickSpeed;
  Encoder0TotalTicks += LastEncoder0TickSpeed;
}

void HandleSerialCommunication()
{
  byte command;
  short data;
  //Command available
  if(Serial.available() >= 3)
  {
    command = Serial.read();
    data = Serial.read();
    data = data << 8;      //MSB
    data |= Serial.read(); //LSB
    
    short response = HandleCommand(command, data);
    
    Serial.write((byte)(response >> 8));   //MSB
    Serial.write((byte)(response & 0xFF)); //LSB
  }
}

short HandleCommand(byte command, short data)
{
  switch(command)
  {
    case 1:
     MotorA_Kp = data;
     break;
      
    case 2:
     MotorA_Ki = data;
     break;

    case 3:
     MotorA_Kd = data;
     break;

    case 4:
     MotorB_Kp = data;
     break;

    case 5:
     MotorB_Ki = data;
     break;

    case 6:
     MotorB_Kd = data;
     break;
     
    case 7:
     MotorATargetTickSpeed = data;
     break;

    case 8:
     MotorBTargetTickSpeed = data;
     break;
    
    case 255:
      return data;
      break;
      
    default:
      return 0;
  }
}
