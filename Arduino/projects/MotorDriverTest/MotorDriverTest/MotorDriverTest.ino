/*
  HG7881_Motor_Driver_Example - Arduino sketch
   
  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.
   
  This example is meant to illustrate how to operate the motor driver
  and is not intended to be elegant, efficient or useful.
   
  Connections:
   
    Arduino digital output D10 to motor driver input 1B2 / 1A1.
    Arduino digital output D11 to motor driver input 1A2 / 1B1.
    Motor driver VCC to operating voltage 5V.
    Motor driver GND to common ground.
    Motor driver MOTOR B screw terminals to a small motor.
     
  Related Banana Robotics items:
   
    BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
    https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 
  https://www.BananaRobotics.com
*/
 
// wired connections
#define HG7881_B_IA 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 11 // D11 --> Motor B Input B --> MOTOR B -

#define HG7881_A_IA 9 // D9 --> Motor B Input A --> MOTOR B +
#define HG7881_A_IB 8 // D8 --> Motor B Input B --> MOTOR B -
 
// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction

#define MOTOR_A_PWM HG7881_A_IA // Motor A PWM Speed
#define MOTOR_A_DIR HG7881_A_IB // Motor A Direction
 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 80  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes
 
void setup()
{
  Serial.begin( 9600 );
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );  
  SoftStopMotor();
  SetMotorSpeed(HIGH, PWM_FAST);  
  PrintMenu();
}
 
void loop()
{
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while( !Serial.available() ); // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch( c )
    {
      case '1': // 1) Fast forward
        Serial.println( "Fast forward..." );
        SoftStopMotor();
        // always stop motors briefly before abrupt changes
        delay( DIR_DELAY );
        SetMotorSpeed(HIGH, PWM_FAST);
        break;      
         
      case '2': // 2) Forward      
        Serial.println( "Forward..." );
        // always stop motors briefly before abrupt changes
        SoftStopMotor();
        delay( DIR_DELAY );
        // set the motor speed and direction
        SetMotorSpeed(HIGH, PWM_SLOW);
        break;      
         
      case '3': // 3) Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        SoftStopMotor();
        break;      
 
      case '4': // 4) Reverse
        Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        SoftStopMotor();
        delay( DIR_DELAY );
        // set the motor speed and direction
        SetMotorSpeed(LOW, PWM_SLOW);
        break;      
         
      case '5': // 5) Fast reverse
        Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        SoftStopMotor();
        delay( DIR_DELAY );
        // set the motor speed and direction
        SetMotorSpeed(LOW, PWM_FAST);
        break;
         
      case '6': // 6) Hard stop (use with caution)
        Serial.println( "Hard stop (brake)..." );
        digitalWrite( MOTOR_A_DIR, HIGH );
        digitalWrite( MOTOR_A_PWM, HIGH );
        digitalWrite( MOTOR_B_DIR, HIGH );
        digitalWrite( MOTOR_B_PWM, HIGH );
        break;      
         
      default:
        // wrong character! display the menu again!
        PrintMenu();
        break;
    }
}

void SoftStopMotor() {
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );

  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
}

void SetMotorSpeed(boolean forward, byte speed) { 
  digitalWrite( MOTOR_A_DIR, forward );
  digitalWrite( MOTOR_B_DIR, forward );
  if(forward)
  {
    speed = 255-speed;
  }
  analogWrite( MOTOR_A_PWM, speed );
  analogWrite( MOTOR_B_PWM, speed );
}

void PrintMenu() {
 // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Fast forward" );
  Serial.println( "2) Forward" );
  Serial.println( "3) Soft stop (coast)" );
  Serial.println( "4) Reverse" );
  Serial.println( "5) Fast reverse" );
  Serial.println( "6) Hard stop (brake)" );
  Serial.println( "-----------------------------" );
}
