#include <digitalWriteFast.h>

#define SerialSpeed (9600)
#define LED_Pin (13)

void setup() {
  Serial.begin(SerialSpeed);

  while(Serial.available() > 0)
  {
    Serial.read();
  }
  SetLED(true);
}

void SetLED(boolean stat)
{
  digitalWriteFast(LED_Pin, stat);  
}

void loop() {
  HandleCommand();
}

void HandleCommand()
{
  if(Serial.available() >= 3)
  {
    SetLED(false);
    int cmd = Serial.read();
    
    byte msb = Serial.read();
    byte lsb = Serial.read();
    
    int data = msb;
    data = data << 8;
    data = data | lsb;
    
    int reply = SendMessage(cmd, data);
    msb = reply >> 8;
    lsb = (reply & 0x00FF);
    Serial.write(msb);
    Serial.write(lsb);
  }
}

int SendMessage(int command, int data)
{
    switch(command)
    {       
      case 254:
        return command;
        
      case 255:
        return data;
    }
    return data;
}
