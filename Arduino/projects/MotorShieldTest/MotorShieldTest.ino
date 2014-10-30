/*
 Arduino motorshield
*/


//int pbIn = 0;                  // Interrupt 0 is on DIGITAL PIN 2!
int pbIn = 1;                  // Interrupt 0 is on DIGITAL PIN 3!
volatile int state = LOW;      // The input state toggle

int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;                        
 
void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
      //Attach the interrupt to the input pin and monitor for ANY Change
      attachInterrupt(pbIn, stateChange, RISING);

} 

void stateChange()
{
  state = !state;
  delay(100);
}

 
void loop() 
{ 
  int value;
  for(value = 0 ; value <= 255; value+=5) 
  { 
    digitalWrite(M1,state);   
    digitalWrite(M2, state);       
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
/*    if(value == 0 || value== 255)
      delay(2000);
    else
*/    
      delay(30); 
  }  
}
