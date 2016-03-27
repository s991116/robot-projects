#include <Servo.h> 

#define HORIZONTAL_SERVO_PIN (3)
#define VERTICAL_SERVO_PIN (2)

Servo horiontalServo;
Servo verticalServo;

short VerticalServoMin = 30;
short VerticalServoMax = 130;
short VerticalServoAngle = 90;


short HorizontalServoMin = 25;
short HorizontalServoMax = 155;
short HorizontalServoAngle = 90;


void InitializeServo()
{ 
  horiontalServo.attach(HORIZONTAL_SERVO_PIN); 
  verticalServo.attach(VERTICAL_SERVO_PIN);
} 

void SetHorizontalAngle(short angle)
{
  if(angle > HorizontalServoMax)
    angle = HorizontalServoMax;
  else if(angle < HorizontalServoMin)
    angle = HorizontalServoMin;
  HorizontalServoAngle = angle;
  horiontalServo.write(angle);
}
 
void SetVerticalAngle(short angle)
{
  if(angle > VerticalServoMax)
    angle = VerticalServoMax;
  else if(angle < VerticalServoMin)
    angle = VerticalServoMin;
  VerticalServoAngle = angle;
  verticalServo.write(angle);  
}

short GetHorizontalAngle()
{
  return HorizontalServoAngle;
}
 
short GetVerticalAngle()
{
  return VerticalServoAngle;
}

