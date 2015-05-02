#define SERIAL_BAUD_RATE (9600)

int ledpin = 13;
byte data = 0;

void setup() {
  pinMode(ledpin, OUTPUT);  
  Serial.begin(SERIAL_BAUD_RATE);
}

void HandleSerialCommunication()
{
  byte command;
  short data;
  //Command available
  if(Serial.available() >= 3)
  {
    command = Serial.read();
    data = Serial.read();
    data = data << 8;      //MSB
    data |= Serial.read(); //LSB
    
    short response = HandleCommand(command, data);
    
    Serial.write((byte)(response >> 8));   //MSB
    Serial.write((byte)(response & 0xFF)); //LSB
  }
}

short HandleCommand(byte command, short data)
{
  return data;
}

void loop() {
  digitalWrite(ledpin,HIGH);
  delay(200);
  
  if(data == 0)
  {
    digitalWrite(ledpin,LOW);
    delay(400);
  }
  
  HandleSerialCommunication(); 
}
