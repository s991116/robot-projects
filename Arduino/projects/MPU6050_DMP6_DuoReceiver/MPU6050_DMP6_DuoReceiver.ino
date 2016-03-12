void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);

  Serial.println("Reset.");
}

int charRead;

void loop() {
  WaitForDelimiter();
  short data1 = ReadShortValue();
  short data2 = ReadShortValue();
  Serial.print("Data1:");
  Serial.println(data1);
  Serial.print("Data2:");  
  Serial.println(data2);   
}

short ReadShortValue()
{
  uint8_t first_half = Serial.read();
  uint8_t second_half = Serial.read();

  short result = (second_half << 8) | first_half;
  return result;
}

void WaitForDelimiter()
{
  bool delimiterFound = false;
  while(!delimiterFound)
  {
    while(Serial3.available() >= 2)
    {
      byte data = Serial3.read();
      if(data == 0xFF)
      {
        byte data2 = Serial3.read();
        if(data2 == 0xFF)
        {
          delimiterFound = true;
        }
      }      
    } 
  }
}

