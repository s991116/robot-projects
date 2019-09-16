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
#include "BalancingControl.h"

#define LED_BLINK_TIME (300) //Blink timer in MS
#define LEDMode_OFF              (0)
#define LEDMode_ON               (1)
#define LEDMode_BLINK            (2)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Declaring global variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte low_bat;

int left_motor, throttle_left_motor, throttle_counter_left_motor, throttle_left_motor_memory;
int right_motor, throttle_right_motor, throttle_counter_right_motor, throttle_right_motor_memory;
int battery_voltage;

unsigned long loop_timer;

float angle, self_balance_pid_setpoint;
float pid_error_temp, pid_i_mem, pid_setpoint, gyro_input, pid_output, pid_last_d_error;
float pid_output_left, pid_output_right;

byte navigation = 0;
byte navigationReceiveCounter = 0;

Servo verticalServo, horizontalServo;
byte servo1Position, servo2Position;

byte balanceMode;

bool ledBlink;
long ledTimer;
byte ledMode;

Gyroscope gyroscope;
BalancingControl balancingControl;

void UpdateNavigation() {
    if(navigationReceiveCounter <= 25) navigationReceiveCounter ++;        //The received byte will be valid for 25 program loops (100 milliseconds)
    else navigation = 0x00;                                                //After 100 milliseconds the received byte is deleted 
}

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
    navigation = data;
    navigationReceiveCounter = 0;
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
    return navigation;
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
    return 0;
}

byte GetBalanceMode() {
    return balanceMode;
}

byte GetLightMode() {
    return ledMode;
}

byte GetBatteryLevelH() {
  unsigned short batteryLevel = analogRead(PIN_ANALOG_BATTERY_VOLTAGE);
  return batteryLevel >> 8;
}

byte GetBatteryLevelL() {
  unsigned short batteryLevel = analogRead(PIN_ANALOG_BATTERY_VOLTAGE);
  return batteryLevel & 0xFF;
}

byte GetAngle() {
  return angle; 
}

byte GetAngleAcc() {
  return gyroscope.angle_acc; 
}

byte GetDistance() {
  return 0; 
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
  gyroscope.Initialize();
  //To create a variable pulse for controlling the stepper motors a timer is created that will execute a piece of code (subroutine) every 20us
  //This subroutine is called TIMER2_COMPA_vect
  TCCR2A = 0;                                                               //Make sure that the TCCR2A register is set to zero
  TCCR2B = 0;                                                               //Make sure that the TCCR2A register is set to zero
  TIMSK2 |= (1 << OCIE2A);                                                  //Set the interupt enable bit OCIE2A in the TIMSK2 register
  TCCR2B |= (1 << CS21);                                                    //Set the CS21 bit in the TCCRB register to set the prescaler to 8
  OCR2A = 39;                                                               //The compare register is set to 39 => 20us / (1s / (16.000.000MHz / 8)) - 1
  TCCR2A |= (1 << WGM21);                                                   //Set counter 2 to CTC (clear timer on compare) mode
  
  pinMode(PIN_STEPPERMOTOR_LEFT_STEP, OUTPUT);
  pinMode(PIN_STEPPERMOTOR_LEFT_DIR, OUTPUT);
  pinMode(PIN_STEPPERMOTOR_RIGHT_STEP, OUTPUT);
  pinMode(PIN_STEPPERMOTOR_RIGHT_DIR, OUTPUT);

  loop_timer = micros() + 4000;                                             //Set the loop_timer variable at the next end loop time

  pinMode(PIN_POWERLED, OUTPUT);
  digitalWrite(PIN_POWERLED, LOW);

  pinMode(PIN_STEPPERMOTOR_SLEEP, OUTPUT);
  digitalWrite(PIN_STEPPERMOTOR_SLEEP, HIGH);

  verticalServo.attach(PIN_SERVO_1);
  horizontalServo.attach(PIN_SERVO_2);

  serialCom.Initialize();

  unsigned short batteryLevel = analogRead(PIN_ANALOG_BATTERY_VOLTAGE);
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
  UpdateNavigation();
  UpdateLEDMode();

  //Load the battery voltage to the battery_voltage variable.
  //85 is the voltage compensation for the diode.
  //Resistor voltage divider => (3.3k + 3.3k)/2.2k = 2.5
  //12.5V equals ~5V @ Analog 0.
  //12.5V equals 1023 analogRead(0).
  //1250 / 1023 = 1.222.
  //The variable battery_voltage holds 1050 if the battery voltage is 10.5V.
  battery_voltage = (analogRead(PIN_ANALOG_BATTERY_VOLTAGE) * 1.222) + 85;
  
  if(battery_voltage < 1050 && battery_voltage > 800){                      //If batteryvoltage is below 10.5V and higher than 8.0V
    //digitalWrite(13, HIGH);                                                 //Turn on the led if battery voltage is to low
    low_bat = 1;                                                            //Set the low_bat variable to 1
  }

  gyroscope.CalculateAngle();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //PID controller calculations
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //The balancing robot is angle driven. First the difference between the desired angel (setpoint) and actual angle (process value)
  //is calculated. The self_balance_pid_setpoint variable is automatically changed to make sure that the robot stays balanced all the time.
  //The (pid_setpoint - pid_output * 0.015) part functions as a brake function.
  pid_error_temp = gyroscope.angle_gyro - self_balance_pid_setpoint - pid_setpoint;
  if(pid_output > 10 || pid_output < -10)pid_error_temp += pid_output * 0.015 ;

  pid_i_mem += balancingControl.pid_i_gain * pid_error_temp;                                 //Calculate the I-controller value and add it to the pid_i_mem variable
  if(pid_i_mem > 400)pid_i_mem = 400;                                       //Limit the I-controller to the maximum controller output
  else if(pid_i_mem < -400)pid_i_mem = -400;
  //Calculate the PID output value
  pid_output = balancingControl.pid_p_gain * pid_error_temp + pid_i_mem + balancingControl.pid_d_gain * (pid_error_temp - pid_last_d_error);
  if(pid_output > 400)pid_output = 400;                                     //Limit the PI-controller to the maximum controller output
  else if(pid_output < -400)pid_output = -400;

  pid_last_d_error = pid_error_temp;                                        //Store the error for the next loop

  if(pid_output < 5 && pid_output > -5)pid_output = 0;                      //Create a dead-band to stop the motors when the robot is balanced

  if(gyroscope.angle_gyro > 30 || gyroscope.angle_gyro < -30 || gyroscope.start == 0 || low_bat == 1){    //If the robot tips over or the start variable is zero or the battery is empty
    pid_output = 0;                                                         //Set the PID controller output to 0 so the motors stop moving
    pid_i_mem = 0;                                                          //Reset the I-controller memory
    gyroscope.start = 0;                                                              //Set the start variable to 0
    self_balance_pid_setpoint = 0;                                          //Reset the self_balance_pid_setpoint variable
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Control calculations
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  pid_output_left = pid_output;                                             //Copy the controller output to the pid_output_left variable for the left motor
  pid_output_right = pid_output;                                            //Copy the controller output to the pid_output_right variable for the right motor

  if(navigation & B00000001){                                            //If the first bit of the receive byte is set change the left and right variable to turn the robot to the left
    pid_output_left += balancingControl.turning_speed;                                       //Increase the left motor speed
    pid_output_right -= balancingControl.turning_speed;                                      //Decrease the right motor speed
  }
  if(navigation & B00000010){                                            //If the second bit of the receive byte is set change the left and right variable to turn the robot to the right
    pid_output_left -= balancingControl.turning_speed;                                       //Decrease the left motor speed
    pid_output_right += balancingControl.turning_speed;                                      //Increase the right motor speed
  }

  if(navigation & B00000100){                                            //If the third bit of the receive byte is set change the left and right variable to turn the robot to the right
    if(pid_setpoint > -2.5)pid_setpoint -= 0.05;                            //Slowly change the setpoint angle so the robot starts leaning forewards
    if(pid_output > balancingControl.max_target_speed * -1)pid_setpoint -= 0.005;            //Slowly change the setpoint angle so the robot starts leaning forewards
  }
  if(navigation & B00001000){                                            //If the forth bit of the receive byte is set change the left and right variable to turn the robot to the right
    if(pid_setpoint < 2.5)pid_setpoint += 0.05;                             //Slowly change the setpoint angle so the robot starts leaning backwards
    if(pid_output < balancingControl.max_target_speed)pid_setpoint += 0.005;                 //Slowly change the setpoint angle so the robot starts leaning backwards
  }   

  if(!(navigation & B00001100)){                                         //Slowly reduce the setpoint to zero if no foreward or backward command is given
    if(pid_setpoint > 0.5)pid_setpoint -=0.05;                              //If the PID setpoint is larger then 0.5 reduce the setpoint with 0.05 every loop
    else if(pid_setpoint < -0.5)pid_setpoint +=0.05;                        //If the PID setpoint is smaller then -0.5 increase the setpoint with 0.05 every loop
    else pid_setpoint = 0;                                                  //If the PID setpoint is smaller then 0.5 or larger then -0.5 set the setpoint to 0
  }
  
  //The self balancing point is adjusted when there is not forward or backwards movement from the transmitter. This way the robot will always find it's balancing point
  if(pid_setpoint == 0){                                                    //If the setpoint is zero degrees
    if(pid_output < 0)self_balance_pid_setpoint += 0.0015;                  //Increase the self_balance_pid_setpoint if the robot is still moving forewards
    if(pid_output > 0)self_balance_pid_setpoint -= 0.0015;                  //Decrease the self_balance_pid_setpoint if the robot is still moving backwards
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Motor pulse calculations
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //To compensate for the non-linear behaviour of the stepper motors the folowing calculations are needed to get a linear speed behaviour.
  if(pid_output_left > 0)pid_output_left = 405 - (1/(pid_output_left + 9)) * 5500;
  else if(pid_output_left < 0)pid_output_left = -405 - (1/(pid_output_left - 9)) * 5500;

  if(pid_output_right > 0)pid_output_right = 405 - (1/(pid_output_right + 9)) * 5500;
  else if(pid_output_right < 0)pid_output_right = -405 - (1/(pid_output_right - 9)) * 5500;

  //Calculate the needed pulse time for the left and right stepper motor controllers
  if(pid_output_left > 0)left_motor = 400 - pid_output_left;
  else if(pid_output_left < 0)left_motor = -400 - pid_output_left;
  else left_motor = 0;

  if(pid_output_right > 0)right_motor = 400 - pid_output_right;
  else if(pid_output_right < 0)right_motor = -400 - pid_output_right;
  else right_motor = 0;

  //Copy the pulse time to the throttle variables so the interrupt subroutine can use them
  throttle_left_motor = left_motor;
  throttle_right_motor = right_motor;

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
  //Left motor pulse calculations
  throttle_counter_left_motor ++;                                           //Increase the throttle_counter_left_motor variable by 1 every time this routine is executed
  if(throttle_counter_left_motor > throttle_left_motor_memory){             //If the number of loops is larger then the throttle_left_motor_memory variable
    throttle_counter_left_motor = 0;                                        //Reset the throttle_counter_left_motor variable
    throttle_left_motor_memory = throttle_left_motor;                       //Load the next throttle_left_motor variable
    if(throttle_left_motor_memory < 0){                                     //If the throttle_left_motor_memory is negative                                                 //Set output 3 low to reverse the direction of the stepper controller
      STEPPERMOTOR_LEFT_REVERSE;
      throttle_left_motor_memory *= -1;                                     //Invert the throttle_left_motor_memory variable
    }
    else STEPPERMOTOR_LEFT_FORWARD;                                               //Set output 11 high for a forward direction of the stepper motor
  }
  else if(throttle_counter_left_motor == 1){
    STEPPERMOTOR_LEFT_HIGH;
  }
  else if(throttle_counter_left_motor == 2) {
    STEPPERMOTOR_LEFT_LOW;
  }
  //right motor pulse calculations
  throttle_counter_right_motor ++;                                          //Increase the throttle_counter_right_motor variable by 1 every time the routine is executed
  if(throttle_counter_right_motor > throttle_right_motor_memory){           //If the number of loops is larger then the throttle_right_motor_memory variable
    throttle_counter_right_motor = 0;                                       //Reset the throttle_counter_right_motor variable
    throttle_right_motor_memory = throttle_right_motor;                     //Load the next throttle_right_motor variable
    if(throttle_right_motor_memory < 0){                                    //If the throttle_right_motor_memory is negative
      STEPPERMOTOR_RIGHT_REVERSE;
      throttle_right_motor_memory *= -1;                                    //Invert the throttle_right_motor_memory variable
    }
    else STEPPERMOTOR_RIGHT_FORWARD;
  }
  else if(throttle_counter_right_motor == 1){
     STEPPERMOTOR_RIGHT_HIGH;
  }
  else if(throttle_counter_right_motor == 2){
     STEPPERMOTOR_RIGHT_LOW;
  }
}