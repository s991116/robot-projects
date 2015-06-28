void ManualRead()
{
  Serial.println("\n Enter Command:");
  byte cmd = ReadNumberFromSerial();
  Serial.println("\nEnter data:");
  short data = ReadNumberFromSerial();
    
  Serial.print("Cmd: ");
  Serial.print((int)cmd);
  Serial.print(" , Data: ");
  Serial.println((int)data);
  
  short response = SendMessage(cmd, data);

  Serial.print("Response: ");
  Serial.println((int)response);
}

short ReadNumberFromSerial()
{
  byte inChar;
  String inString = "";
  do{
    inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
  }while(inChar != '\n' && inChar != 13);
  
  return inString.toInt();
}

