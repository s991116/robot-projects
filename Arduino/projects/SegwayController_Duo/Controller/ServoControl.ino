#include <Servo.h> 
#include <ExpoData.h>
#include <ServoExpoMotion.h>

Servo horiontalServo;
Servo verticalServo;
ServoExpoMotion ServoHorizontal(&horiontalServo, 90, 16);
ServoExpoMotion ServoVertical(&verticalServo, 90, 16);

short VerticalServoMin = 65;
short VerticalServoMax = 180;
short VerticalServoAngle = 90;


short HorizontalServoMin = 40;
short HorizontalServoMax = 150;
short HorizontalServoAngle = 90;

byte VerticalServoSpeed = 0;
byte HorizontalServoSpeed = 1;

void InitializeServo()
{ 
  horiontalServo.attach(HORIZONTAL_SERVO_PIN); 
  verticalServo.attach(VERTICAL_SERVO_PIN);
} 

void ServoUpdate() {
  ServoHorizontal.UpdatePosition();
  ServoVertical.UpdatePosition();
}

void SetHorizontalAngle(short angle)
{
  if(angle > HorizontalServoMax)
    angle = HorizontalServoMax;
  else if(angle < HorizontalServoMin)
    angle = HorizontalServoMin;
  HorizontalServoAngle = angle;
  ServoHorizontal.SetPosition(angle);
}
 
void SetVerticalAngle(short angle)
{
  if(angle > VerticalServoMax)
    angle = VerticalServoMax;
  else if(angle < VerticalServoMin)
    angle = VerticalServoMin;
  VerticalServoAngle = angle;
  ServoVertical.SetPosition(angle);
}

short GetHorizontalAngle()
{
  return ServoHorizontal.GetEndPosition();
}
 
short GetVerticalAngle()
{
  return ServoVertical.GetEndPosition();
}

byte getVerticalServoSpeed() {
  return ServoVertical.GetSpeed();
}

byte getHorizontalServoSpeed() {
  return ServoHorizontal.GetSpeed();
}

void setVerticalServoSpeed(byte s) {
  return ServoVertical.SetSpeed(s);
}

void setHorizontalServoSpeed(byte s) {
  return ServoHorizontal.SetSpeed(s);
}

