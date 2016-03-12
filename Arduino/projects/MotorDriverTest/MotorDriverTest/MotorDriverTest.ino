// functional connections
#define MOTOR_B_PWM (10) // Motor B PWM Speed
#define MOTOR_B_DIR (8) // Motor B Direction

#define MOTOR_A_PWM (9) // Motor A PWM Speed
#define MOTOR_A_DIR (7) // Motor A Direction
 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 80  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

#define MOTOR_A_INTERRUPT (2)
#define MOTOR_A_INTERRUPT_DIR (4)

long distanceMotorA;

void setup()
{
  SoftStopMotor();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(MOTOR_A_INTERRUPT), MotorStepAInterrupt, RISING);
  PrintMenu();
}

void MotorStepAInterrupt()
{
  if(digitalRead(MOTOR_A_INTERRUPT_DIR))
    distanceMotorA++;
  else
    distanceMotorA--;
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

      case '7':
        Serial.print("Distance: ");
        Serial.println(distanceMotorA);
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
