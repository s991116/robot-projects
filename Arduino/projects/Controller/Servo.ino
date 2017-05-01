#include <ServoTimer2.h>
#include <ServoTimer2ExpoMotion.h>

ServoTimer2 horiontalServo;
ServoTimer2 verticalServo;
ServoTimer2ExpoMotion ServoHorizontal(&horiontalServo, 1500, 16);
ServoTimer2ExpoMotion ServoVertical(&verticalServo, 1500, 16);

#define MinPulseLength (750)        // the shortest pulse sent to a servo  
#define MaxPulseLength (2250)       // the longest pulse sent to a servo

float PulseToAngleFactor;
float PulseToAngleOffset;
float AngleToPulseFactor;
float AngleToPulseOffset;

short VerticalServoMin = 20;
short VerticalServoMax = 160;
short VerticalServoAngle = 90;

short HorizontalServoMin = 20;
short HorizontalServoMax = 160;
short HorizontalServoAngle = 90;

void SetupServo()
{ 
  SetupConvertParameters(); 
  horiontalServo.attach(HORIZONTAL_SERVO_PIN); 
  verticalServo.attach(VERTICAL_SERVO_PIN);
  SetHorizontalAngle(HorizontalServoAngle);
  SetVerticalAngle(VerticalServoAngle);
} 

void SetupConvertParameters() {
  PulseToAngleFactor = 180.0 / (MaxPulseLength - MinPulseLength);
  PulseToAngleOffset = -(PulseToAngleFactor * MinPulseLength);
  AngleToPulseFactor = (MaxPulseLength - MinPulseLength)/180.0;
  AngleToPulseOffset = MinPulseLength;
}

void UpdateServo() {
  ServoHorizontal.UpdatePosition();
  ServoVertical.UpdatePosition();
}

short AngleToPulseLength(short angle) {
  short pulseLength = AngleToPulseFactor * angle + AngleToPulseOffset;
  if(pulseLength > MaxPulseLength)
    return MaxPulseLength;
  else if (pulseLength < MinPulseLength)
    return MinPulseLength;
  return pulseLength;
}

short PulseLengthToAngle(short pulseLength) {
  return  PulseToAngleFactor * pulseLength + PulseToAngleOffset;
}

void SetHorizontalAngle(short angle)
{
  if(angle > HorizontalServoMax)
    HorizontalServoAngle = HorizontalServoMax;
  else if(angle < HorizontalServoMin)
    HorizontalServoAngle = HorizontalServoMin;
  else
    HorizontalServoAngle = angle;

  short pulseLength = AngleToPulseLength(HorizontalServoAngle);
  ServoHorizontal.SetPosition(pulseLength);
}
 
void SetVerticalAngle(short angle)
{  
  if(angle > VerticalServoMax)
    VerticalServoAngle = VerticalServoMax;
  else if(angle < VerticalServoMin)
    VerticalServoAngle = VerticalServoMin;
  else
    VerticalServoAngle = angle;
    
  short pulseLength = AngleToPulseLength(VerticalServoAngle);
  ServoVertical.SetPosition(pulseLength);
}

short GetHorizontalAngle()
{
  return PulseLengthToAngle(ServoHorizontal.GetEndPosition());
}
 
short GetVerticalAngle()
{
  short pulseLength = ServoVertical.GetEndPosition();
  short angle = PulseLengthToAngle(pulseLength);
  return angle;
}

byte getVerticalServoSpeed() {
  return ServoVertical.GetSpeed();
}

byte getHorizontalServoSpeed() {
  return ServoHorizontal.GetSpeed();
}

void setVerticalServoSpeed(byte s) {
  ServoVertical.SetSpeed(s);
}

void setHorizontalServoSpeed(byte s) {
  ServoHorizontal.SetSpeed(s);
}

