#ifdef MANUAL_COMMUNICATION

bool stringCommandComplete = false;
bool stringDataComplete = false;
String inputStringCommand;
String inputStringData;
String inputString;

bool stringComplete;

bool CommandFromMasterReceived()
{
  TryReadSerialCommand();
  return stringCommandComplete && stringDataComplete;
}

byte ReadCommandFromMaster()
{
  stringCommandComplete = false;
  return inputStringCommand.toInt();
}

short ReadDataFromMaster()
{
  stringDataComplete = false;
  return inputStringData.toInt();
}

void SendReplyToMaster(short reply)
{
  Serial.print("Reply:");
  Serial.print(reply, DEC);
  Serial.println("");
}


void TryReadSerialCommand() {
  serialEvent();
  if(stringComplete)
  {
    if(!stringCommandComplete)
    {
      stringCommandComplete = true;
      inputStringCommand = inputString;
      Serial.print("Cmd:");
      Serial.print(inputString);
      clearString();
    }
    else
    {
      stringDataComplete = true;
      inputStringData = inputString;
      Serial.print("Data:");
      Serial.println(inputString);
      clearString();
    }    
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void clearString() {
  if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

#endif
