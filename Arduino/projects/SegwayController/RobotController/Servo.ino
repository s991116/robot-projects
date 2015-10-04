Servo VerticalServo;
Servo HorizontalServo;

byte VerticalServoMax;
byte VerticalServoMin;
byte VerticalServoPos;

byte HorizontalServoMax;
byte HorizontalServoMin;
byte HorizontalServoPos;

void SetupServo()
{
  VerticalServo.attach(SERVO_VERTICAL_PIN); 
  HorizontalServo.attach(SERVO_HORIZONTAL_PIN); 

  VerticalServoMax = 130;
  VerticalServoMin = 30;
  VerticalServoPos = 80;

  HorizontalServoMax = 170;
  HorizontalServoMin = 25;
  HorizontalServoPos = 90;

  SetVerticalServoPosition(VerticalServoPos);
  SetHorizontalServoPosition(HorizontalServoPos);   
}

void SetVerticalServoPosition(byte position)
{
  if(VerticalServoMax < position)
    position = VerticalServoMax;
  else if(VerticalServoMin > position)
    position = VerticalServoMin;

  VerticalServoPos = position;
  VerticalServo.write(position);   
}

void SetHorizontalServoPosition(byte position)
{
  if(HorizontalServoMax < position)
    position = HorizontalServoMax;
  else if(HorizontalServoMin > position)
    position = HorizontalServoMin;
  
  HorizontalServoPos = position;
  HorizontalServo.write(position);     
}

short ServoCommand(byte command, short data)
{
  switch(command)
  {
    case Set_Vertical_Servo_Position:
      SetVerticalServoPosition(data);
      break;
      
    case Set_Vertical_Servo_Max_Position:
      VerticalServoMax = data;
      SetVerticalServoPosition(VerticalServoPos);
      break;

    case Set_Vertical_Servo_Min_Position:
      VerticalServoMin = data;
      SetVerticalServoPosition(VerticalServoPos);
      break;
    
    case Set_Horizontal_Servo_Position:
      SetHorizontalServoPosition(data);
      break;

    case Set_Horizontal_Servo_Max_Position:
      HorizontalServoMax = data;
      SetHorizontalServoPosition(HorizontalServoPos);
      break;

    case Set_Horizontal_Servo_Min_Position:
      HorizontalServoMin = data;
      SetHorizontalServoPosition(HorizontalServoPos);
      break;

    case Get_Vertical_Servo_Position:
      return VerticalServoPos;
      break;
      
    case Get_Vertical_Servo_Max_Position:
      return VerticalServoMax;
      break;
      
    case Get_Vertical_Servo_Min_Position:
      return VerticalServoMin;
      break;
      
    case Get_Horizontal_Servo_Position:
      return HorizontalServoPos;
      break;
      
    case Get_Horizontal_Servo_Max_Position:
      return HorizontalServoMax;
      break;
     
    case Get_Horizontal_Servo_Min_Position:
      return HorizontalServoMin;
      break;
  }
  return 0;
}

