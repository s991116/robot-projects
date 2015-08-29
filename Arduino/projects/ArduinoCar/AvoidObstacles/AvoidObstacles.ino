#include <NewPing.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     3
// wired connections
#define HG7881_A_IA 5 // D5 --> Motor B Input A --> MOTOR B +
#define HG7881_A_IB 6 // D6 --> Motor B Input B --> MOTOR B -
#define HG7881_B_IA 7 // D7 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 8 // D8 --> Motor B Input B --> MOTOR B -
 
// functional connections
#define MOTOR_A_PWM HG7881_A_IA // Motor A PWM Speed
#define MOTOR_A_DIR HG7881_A_IB // Motor A Direction
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction

#define STRAIGHT 1
#define TURN 2
short DriveMode = STRAIGHT;

#define redPin  9
#define greenPin 10
#define bluePin  11

byte colorValueRed = 255;
byte colorValueBlue = 255;
byte colorValueGreen = 255;

#define MAX_DISTANCE_IN_CM 10 
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_IN_CM);

#define MINDISTANCE 7
#define DRIVE_SPEED_B 140
#define DRIVE_SPEED_A 120

#define DIR_DELAY 500

void setup() {
  MotorSetup();
  LEDSetup();
}

void MotorSetup()
{
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  StopMotors();
}

void LEDSetup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop() {
  
  if(ToCloseToObject())
  {
    DriveMode = TURN;
  }
  else
  {
    DriveMode = STRAIGHT;
  }
  EnableMotors();
  delay(100);
}

bool ToCloseToObject()
{
  long distance = ultrasonic.ping_cm();
  return (distance > 0 && distance < MAX_DISTANCE_IN_CM-2);    
}

void EnableMotors()
{
  if(DriveMode == TURN)
  {
    Turn();
    SetColor(255,0,255);
  }
  else
  {
    DriveStraight();
    SetColor(255,255,0);
  }  
}

void DriveStraight()
{
  DriveMode = STRAIGHT;
  SetMotorSpeed(MOTOR_A_PWM, MOTOR_A_DIR, -DRIVE_SPEED_A);
  SetMotorSpeed(MOTOR_B_PWM, MOTOR_B_DIR, DRIVE_SPEED_B);  
}
 
void Turn()
{
  DriveMode = TURN;
  SetMotorSpeed(MOTOR_A_PWM, MOTOR_A_DIR, 0);
  SetMotorSpeed(MOTOR_B_PWM, MOTOR_B_DIR, -DRIVE_SPEED_B);
}

void StopMotors()
{  
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  
}

void SetMotorSpeed(byte PWM_Pin, byte DIR_Pin, short speed)
{
  if(speed > 0)
  {
    digitalWrite( DIR_Pin, HIGH ); // direction = forward
    speed = 255-speed;
  }
  else
  {
    digitalWrite( DIR_Pin, LOW ); // direction = forward
    speed = -speed;    
  }
  
  analogWrite( PWM_Pin, speed ); // PWM speed = fast
}

#define COLOR_SPEED 50
void UpdateLED()
{
  if(colorValueRed > COLOR_SPEED)
  {
    colorValueRed-= COLOR_SPEED;
  }
  else if(colorValueBlue > COLOR_SPEED)
  {
    colorValueBlue-= COLOR_SPEED;
  }
  else if(colorValueGreen > COLOR_SPEED)
  {
    colorValueGreen -= COLOR_SPEED;
  }
  else
  {
    colorValueRed = 255;
    colorValueBlue = 255;
    colorValueGreen = 255;
  }

  SetColor(colorValueRed, colorValueBlue, colorValueGreen);
// Write the color to each pin using PWM and the value gathered above
}

void SetColor(byte red, byte blue, byte green)
{
  
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);
  
}

