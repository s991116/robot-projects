#include <NewPing.h>

#define LED_1_COLOR_1_PIN 3
#define LED_1_COLOR_2_PIN 4
#define LED_1_COLOR_3_PIN 5
#define LED_2_COLOR_1_PIN 6
#define LED_2_COLOR_2_PIN 7
#define LED_2_COLOR_3_PIN 8
#define LED_3_COLOR_1_PIN 9
#define LED_3_COLOR_2_PIN 10
#define LED_3_COLOR_3_PIN 11

#define TRIGGER_PIN  12
#define ECHO_PIN     2

byte LED_1_COLOR_1 = 255;
byte LED_1_COLOR_2 = 255;
byte LED_1_COLOR_3 = 255;
byte LED_2_COLOR_1 = 255;
byte LED_2_COLOR_2 = 255;
byte LED_2_COLOR_3 = 255;
byte LED_3_COLOR_1 = 255;
byte LED_3_COLOR_2 = 255;
byte LED_3_COLOR_3 = 255;

byte *LEDColors[9] = {&LED_1_COLOR_1,&LED_1_COLOR_2,&LED_1_COLOR_3,&LED_2_COLOR_1,&LED_2_COLOR_2,&LED_2_COLOR_3,&LED_3_COLOR_1,&LED_3_COLOR_2,&LED_3_COLOR_3};

#define MAX_DISTANCE_IN_CM 25 
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_IN_CM);

#define COLOR_MODE_OFF 0
#define COLOR_MODE_CHANGE 1
#define COLOR_MODE_BLINK 2
#define COLOR_MODE_RUNNING 3

byte ColorMode = COLOR_MODE_CHANGE;
byte ChangeSpeed = 10;
byte BlinkState = 0;
byte ColorChangeState = 1;

void setup() {
  LEDSetup();
  ColorModeReset();
}

void ColorModeReset()
{
  ChangeSpeed = 10;
  BlinkState = 0;
  ColorChangeState = 1;
  SetColorOff();
}

void LEDSetup()
{
  pinMode(LED_1_COLOR_1, OUTPUT);
  pinMode(LED_1_COLOR_2, OUTPUT);
  pinMode(LED_1_COLOR_3, OUTPUT);
  pinMode(LED_2_COLOR_1, OUTPUT);
  pinMode(LED_2_COLOR_2, OUTPUT);
  pinMode(LED_2_COLOR_3, OUTPUT);
  pinMode(LED_3_COLOR_1, OUTPUT);
  pinMode(LED_3_COLOR_2, OUTPUT);
  pinMode(LED_3_COLOR_3, OUTPUT);
}

long timer;

void loop() {
  UpdateColor();
  SetColor();
  if(millis() - timer > 500)
  {
    byte newColorMode = ColorModeByDistance();
    if(newColorMode != ColorMode)
    {
      ColorMode = newColorMode;
      ColorModeReset();
    }
    timer = millis();
  }  
}

byte ColorModeByDistance()
{
  long distance = ultrasonic.ping_cm();
  if(distance == 0 || distance > MAX_DISTANCE_IN_CM)
    return COLOR_MODE_OFF;

  if(distance < MAX_DISTANCE_IN_CM-15)
    return COLOR_MODE_CHANGE;

  if(distance < MAX_DISTANCE_IN_CM-10)
    return COLOR_MODE_BLINK;

  if(distance < MAX_DISTANCE_IN_CM-5)
    return COLOR_MODE_RUNNING;
}

void UpdateColor() 
{
  switch(ColorMode)
  {
    case COLOR_MODE_OFF:
      SetColorOff();
      break;
      
    case COLOR_MODE_CHANGE:
      SetColorChanging();
      break;

    case COLOR_MODE_BLINK:
      SetColorBlinking();
      break;

    case COLOR_MODE_RUNNING:
      SetColorRunning();
      break;
  }
}

void SetColorOff()
{
  SetSameColorForAll(255, 255, 255);
}


void SetColorChanging()
{
  
  switch(ColorChangeState)
  {
     case 1:
       LedFadeUp(3,3);
       LedFadeDown(2,3);
       if(!LedFadeUp(1,1))
         ColorChangeState = 2;       
       break; 
   
     case 2:
       LedFadeDown(3,3);
       LedFadeUp(2,3);
       if(!LedFadeDown(1,1))
         ColorChangeState = 3;
       break; 

     case 3:
       LedFadeUp(3,1);     
       LedFadeDown(2,1);
       if(!LedFadeUp(1,3))
         ColorChangeState = 4;
       break; 

     case 4:
       LedFadeDown(3,1);     
       LedFadeUp(2,1);
       if(!LedFadeDown(1,3))
         ColorChangeState = 1;
       break; 

  }
  delay(1);
}

bool LedFadeUp(byte LED, byte color)
{
  byte ledColorIndex = (LED-1)*3+color-1;
  if((*LEDColors[ledColorIndex]) == 0)
  {
    return false;
  }
  (*LEDColors[ledColorIndex])--;
  return true;
}

bool LedFadeDown(byte LED, byte color)
{
  byte ledColorIndex = (LED-1)*3+color-1;
  if((*LEDColors[ledColorIndex]) == 255)
  {
    return false;
  }
  (*LEDColors[ledColorIndex])++;
  return true;
}

void SetColorBlinking()
{
  BlinkState++;
  switch(BlinkState)
  {
    case 1:
      SetColorForLED1(0, 255, 255);
      break;
      
    case 2:
      SetColorForLED1(255, 0, 255);
      break;

    case 3:
      SetColorForLED1(255, 255, 0);
      break;

    case 4:
      SetColorForLED2(0, 255, 255);
      break;
      
    case 5:
      SetColorForLED2(255, 0, 255);
      break;
      
    case 6:
      SetColorForLED2(255, 255, 0);
      break;
      
    case 7:
      SetColorForLED3(0, 255, 255);
      break;
      
    case 8:
      SetColorForLED3(255, 0, 255);
      break;
      
    case 9:
      SetColorForLED3(255, 255, 0);
      BlinkState = 0;
      break;
  }
  delay(250);
}

void SetColorRunning()
{
  BlinkState++;
  switch(BlinkState)
  {
    case 1:
      SetColorForLED1(0, 255, 255);
      SetColorForLED2(255, 0, 255);
      SetColorForLED3(255, 255, 0);      
      break;
      
    case 2:
      SetColorForLED1(255, 255, 255);      
      SetColorForLED2(0, 255, 255);
      SetColorForLED3(255, 0, 255);
      break;

    case 3:
      SetColorForLED1(255, 255, 0);
      SetColorForLED2(255, 255, 255);      
      SetColorForLED3(0, 255, 255);
      break;

    case 4:
      SetColorForLED1(255, 0, 255);
      SetColorForLED2(255, 255, 0);      
      SetColorForLED3(255, 255, 255);
      BlinkState = 0;      
      break;
  }
  delay(250);
}

void SetSameColorForAll(byte color1, byte color2, byte color3)
{
  LED_1_COLOR_1 = color1;
  LED_2_COLOR_1 = color1;
  LED_3_COLOR_1 = color1;

  LED_1_COLOR_2 = color2;
  LED_2_COLOR_2 = color2;
  LED_3_COLOR_2 = color2;

  LED_1_COLOR_3 = color3;
  LED_2_COLOR_3 = color3;
  LED_3_COLOR_3 = color3;
}

void SetColor()
{
  SetColorForLED1(LED_1_COLOR_1,LED_1_COLOR_2,LED_1_COLOR_3);
  SetColorForLED2(LED_2_COLOR_1,LED_2_COLOR_2,LED_2_COLOR_3);
  SetColorForLED3(LED_3_COLOR_1,LED_3_COLOR_2,LED_3_COLOR_3);  
}

void SetColorForLED1(byte color1, byte color2, byte color3)
{
  analogWrite(LED_1_COLOR_1_PIN, color1);
  analogWrite(LED_1_COLOR_2_PIN, color2);
  analogWrite(LED_1_COLOR_3_PIN, color3);
}

void SetColorForLED2(byte color1, byte color2, byte color3)
{
  analogWrite(LED_2_COLOR_1_PIN, color1);
  analogWrite(LED_2_COLOR_2_PIN, color2);
  analogWrite(LED_2_COLOR_3_PIN, color3);
}

void SetColorForLED3(byte color1, byte color2, byte color3)
{
  analogWrite(LED_3_COLOR_1_PIN, color1);
  analogWrite(LED_3_COLOR_2_PIN, color2);
  analogWrite(LED_3_COLOR_3_PIN, color3);
}

