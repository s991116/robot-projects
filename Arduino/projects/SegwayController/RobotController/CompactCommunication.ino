#ifndef MANUAL_COMMUNICATION
bool CommandFromMasterReceived()
{
  return (Serial.available() >= 3);
}

byte ReadCommandFromMaster()
{  
  return Serial.read();
}

short ReadDataFromMaster()
{
  byte msb = Serial.read();
  byte lsb = Serial.read();
  return Bytes_ToShort(msb, lsb);
}

void SendReplyToMaster(short reply)
{
  Serial.write(MSB_FromShort(reply));
  Serial.write(LSB_FromShort(reply));  
}

#endif
