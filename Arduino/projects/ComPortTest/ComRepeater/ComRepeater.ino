void setup()
{
    //Serial Setup
    Serial.begin(9600);       // set up Serial library at 9600 bps  
}

void loop()
{
  if(Serial.available() > 0) //Receive data
  {
    //Receive char
    char received = Serial.read();
    
    //Send same char
    Serial.write(received);
  }
}
