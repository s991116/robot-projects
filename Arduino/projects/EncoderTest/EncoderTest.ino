#include <digitalWriteFast.h>


#define ENCODER_0_INTERRUPT_PIN (0) // Encoder-0 Interrupt is on DIGITAL PIN 2
#define ENCODER_1_INTERRUPT_PIN (1) // Encoder-1 Interrupt is on DIGITAL PIN 3
#define ENCODER_0_INTERRUPT_CHANGE_PIN (2) // Encoder-0 is on DIGITAL PIN 2
#define ENCODER_1_INTERRUPT_CHANGE_PIN (3) // Encoder-1 is on DIGITAL PIN 3
#define ENCODER_0_DIRECTION_PIN (9) // Encoder-1 Direction is on DIGITAL PIN 9
#define ENCODER_1_DIRECTION_PIN (8) // Encoder-0 Direction is on DIGITAL PIN 8


void setup() 
{     
  //Attach the interrupt to the input pin and monitor
  attachInterrupt(ENCODER_0_INTERRUPT_PIN, Encoder0Count, CHANGE);
  attachInterrupt(ENCODER_1_INTERRUPT_PIN, Encoder1Count, RISING);

  //Set Direction for Encoder pins
  pinMode(ENCODER_0_DIRECTION_PIN, INPUT); 
  pinMode(ENCODER_1_DIRECTION_PIN, INPUT);
  

  
  //Serial Setup
  Serial.begin(9600);           // set up Serial library at 9600 bps  
  Serial.println("Ready");  // prints hello with ending line break 
}

volatile long Encoder0TickSpeed;
volatile boolean Encoder0State;
volatile long Encoder1TickSpeed;
volatile boolean Encoder1State;

void Encoder0Count()
{
  if(digitalReadFast(ENCODER_0_DIRECTION_PIN) == digitalReadFast(ENCODER_0_INTERRUPT_CHANGE_PIN))
    Encoder0TickSpeed++;
  else
    Encoder0TickSpeed--;
}

void Encoder1Count()
{
 if(digitalReadFast(ENCODER_1_DIRECTION_PIN) == digitalReadFast(ENCODER_1_INTERRUPT_CHANGE_PIN))
    Encoder1TickSpeed++;
  else
    Encoder1TickSpeed--;
}

void loop()
{
  delay(1000);
  Serial.print("Encoder 0: ");
  Serial.println(Encoder0TickSpeed, DEC);
  Serial.print("Encoder 1: ");
  Serial.println(Encoder1TickSpeed, DEC);
  Encoder0TickSpeed = 0;
  Encoder1TickSpeed = 0;
}
