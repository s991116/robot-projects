void HandleCommand()
{
  if(Serial.available() >= 3)
  {
    byte cmd = Serial.read();
    byte msb = Serial.read();
    byte lsb = Serial.read();
    short data = Bytes_ToShort(msb, lsb);
    
    short reply = SendMessage(cmd, data);
    Serial.write(MSB_FromShort(reply));
    Serial.write(LSB_FromShort(reply));
  }
}
