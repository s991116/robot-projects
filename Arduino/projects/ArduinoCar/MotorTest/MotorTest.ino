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
 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_FAST 150 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes
 
void setup()
{
  Serial.begin( 9600 );
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  StopMotors();
}
 
void loop()
{
  boolean isValidInput;
  // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Fast forward" );
  Serial.println( "3) Soft stop (coast)" );
  Serial.println( "5) Fast reverse" );
  Serial.println( "-----------------------------" );
  do
  {
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while( !Serial.available() )
      ; // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch( c )
    {
      case '1': // 1) Fast forward
        Serial.println( "Fast forward..." );
        Straight(PWM_FAST ); // PWM speed = fast
        isValidInput = true;
        break;      
                  
      case '3': // 3) Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        StopMotors();
        isValidInput = true;
        break;      
          
      case '5': // 5) Fast reverse
        Serial.println( "Fast reverse..." );
        Straight(-PWM_FAST ); // PWM speed = fast
        isValidInput = true;
        break;
         
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while( isValidInput == true );
 
  // repeat the main loop and redraw the menu...
}

void StopMotors()
{
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
}

void Straight(short speed)
{
  StopMotors();
  delay( DIR_DELAY );
  SetMotorSpeed(MOTOR_A_PWM, MOTOR_A_DIR, speed);
  SetMotorSpeed(MOTOR_B_PWM, MOTOR_B_DIR, -speed);  
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



