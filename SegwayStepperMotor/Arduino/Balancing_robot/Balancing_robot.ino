///////////////////////////////////////////////////////////////////////////////////////
//Terms of use
///////////////////////////////////////////////////////////////////////////////////////
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>                                            //Include the Wire.h library so we can communicate with the gyro
#include <Servo.h>
#include "PinSetup.h"
#include "SerialCommunication.h"
#include "Gyroscope.h"
#include "Battery.h"
#include "BalancingControl.h"
#include "StepperMotor.h"
#include "HCSR04.h"

#define LED_BLINK_TIME (300) //Blink timer in MS
#define LEDMode_OFF              (0)
#define LEDMode_ON               (1)
#define LEDMode_BLINK            (2)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Declaring global variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long loop_timer;

HCSR04 distanceSensor(PIN_DISTANCE_TRIGGER, PIN_DISTANCE_ECHO);

Servo verticalServo, horizontalServo;
byte servo1Position, servo2Position;

byte balanceMode;

bool ledBlink;
long ledTimer;
byte ledMode;

Gyroscope gyroscope(Wire);
Battery battery;
StepperMotor stepperMotor;
BalancingControl balancingControl(&gyroscope, &stepperMotor, &battery);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Communication functions
//////////////////////////////////////////////////////////////////////////////////////////////////////

//SET FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////
byte testData;

void SetTestData(byte data) {
  testData = data;
}

void SetPidPLevel(byte data) {
  balancingControl.SetPidPLevel(data);
}

void SetPidILevel(byte data) {
  balancingControl.SetPidILevel(data);
}

void SetPidDLevel(byte data) {
  balancingControl.SetPidDLevel(data);
}

void SetNavigation(byte data) {
  balancingControl.SetNavigation(data);
}

void SetServo1Position(byte data) {
  servo1Position = data;
  verticalServo.write(servo1Position);
}

void SetServo2Position(byte data) {
  servo2Position = data;
  horizontalServo.write(servo2Position);
}

void SetBatteryAlarmLevel(byte data) {
}

void SetDistanceSensorMode(byte data) {
  distanceSensor.SetMeasureMode(data);  
}
void SetBalanceMode(byte data) {
  balanceMode = data;
  if(balanceMode==0)
    digitalWrite(PIN_STEPPERMOTOR_SLEEP, LOW);
  else
    digitalWrite(PIN_STEPPERMOTOR_SLEEP, HIGH);
}
void SetLightMode(byte data) {
  ledMode = data;
}

//GET FUNCTIONS////////////////////////////////////////////////////////////////////////
byte GetTestData() {
  return testData; 
}

byte GetNavigation() {
    return balancingControl.GetNavigation();
}

byte GetServo1Position() {
    return servo1Position;
}

byte GetServo2Position(){
    return servo2Position;
}

byte GetBatteryAlarmLevel() {
    return 0;
}

byte GetPidPLevel() {
  return balancingControl.GetPidPLevel();
}

byte GetPidILevel() {
  return balancingControl.GetPidILevel();
}

byte GetPidDLevel() {
  return balancingControl.GetPidDLevel();
}

byte GetDistanceSensorMode() {
    return distanceSensor.IsEnabled();
}

byte GetBalanceMode() {
    return balanceMode;
}

byte GetLightMode() {
    return ledMode;
}

byte GetBatteryLevelH() {
  unsigned short batteryLevel = battery.GetVoltage();
  return batteryLevel >> 8;
}

byte GetBatteryLevelL() {
  unsigned short batteryLevel = battery.GetVoltage();
  return batteryLevel & 0xFF;
}

byte GetAngle() {
  return gyroscope.angle; 
}

byte GetAngleAcc() {
  return gyroscope.angle_acc; 
}

byte GetDistance() {
  return distanceSensor.GetDistance();
}

receiveFunctionsArray ReceiveFunctions[] = {
  SetTestData, 
  SetNavigation,
  SetServo1Position,
  SetServo2Position,
  SetBatteryAlarmLevel,
  SetPidPLevel,
  SetPidILevel,
  SetPidDLevel,
  SetDistanceSensorMode,
  SetBalanceMode,
  SetLightMode,
};

transmitFunctionsArray TransmitFunctions[] = {
  GetTestData,
  GetNavigation,
  GetServo1Position,
  GetServo2Position,
  GetBatteryAlarmLevel,
  GetPidPLevel,
  GetPidILevel,
  GetPidDLevel,
  GetDistanceSensorMode,
  GetBalanceMode,
  GetLightMode,
  GetBatteryLevelH,
  GetBatteryLevelL,
  GetAngle,
  GetAngleAcc,
  GetDistance,
};

/////////////////////////////////////////////////////////////////////////////////////////

SerialCommunication serialCom(&Serial, ReceiveFunctions, TransmitFunctions);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Setup basic functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  serialCom.Initialize();
  distanceSensor.Initialize();
  balancingControl.Initialize();

  loop_timer = micros() + 4000;                                             //Set the loop_timer variable at the next end loop time

  pinMode(PIN_POWERLED, OUTPUT);
  digitalWrite(PIN_POWERLED, LOW);

  verticalServo.attach(PIN_SERVO_1);
  horizontalServo.attach(PIN_SERVO_2);
}

void UpdateLEDMode() {
  switch(ledMode) {
    case LEDMode_OFF:
      digitalWrite(PIN_POWERLED, LOW);
      break;
    
    case LEDMode_ON:
      digitalWrite(PIN_POWERLED, HIGH);
      break;

    case LEDMode_BLINK:
      if(ledTimer < millis()) {
        ledTimer = millis() + LED_BLINK_TIME;
        ledBlink = !ledBlink;
        digitalWrite(PIN_POWERLED, ledBlink);
      }
      break;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main program loop
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop(){
  
  serialCom.HandleCommunication();
  UpdateLEDMode();

  battery.UpdateBatteryLevel();

  balancingControl.Balance();

  distanceSensor.UpdateDistanceMeasure();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Loop time timer
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //The angle calculations are tuned for a loop time of 4 milliseconds. To make sure every loop is exactly 4 milliseconds a wait loop
  //is created by setting the loop_timer variable to +4000 microseconds every loop.
  while(loop_timer > micros());
  loop_timer += 4000;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Interrupt routine  TIMER2_COMPA_vect
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER2_COMPA_vect){
  stepperMotor.Update();
}