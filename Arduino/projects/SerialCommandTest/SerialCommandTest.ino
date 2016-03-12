#include <SerialProtocol.h>
#include <StreamStub.h>

int responseTypeTest;
int commandIdTest;
int dataTest;

void handleCommand(uint8_t commandId)
{
  Serial.print("Command Received for command id:");
  Serial.print(commandId);
}

void handleData(uint8_t responseType, uint8_t commandId, uint16_t data)
{
  switch(responseType)
  {
    case COMMAND_DATA_BYTE_NO_REPLY:
    Serial.print("Byte Received for command id:");
    Serial.print(commandId);
    Serial.print(" , data: ");
    Serial.println(data);
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
    Serial.print("Short Received for command id:");
    Serial.print(commandId);
    Serial.print(" , data: ");
    Serial.println(data);
      break;
  }
}

uint16_t handleReply(uint8_t responseType, uint8_t commandId)
{
  Serial.print("Handle reply received for command id:");
  Serial.print(commandId);

  switch(responseType)
  {
    case COMMAND_NO_DATA_BYTE_REPLY:
      return 13;
      break;
    
    case COMMAND_NO_DATA_SHORT_REPLY:
      return 17;
      break;    
  }
  return 0;
}


StreamStub stub;
SerialCommandProtocol serialCommand(&stub, handleCommand, handleData, handleReply);


void setup() {
  Serial.begin(115200);
  stub.write(32);
  stub.write(2);
  stub.write(6);
  stub.write(15);
  stub.write(13);

  stub.write(33);
  stub.write(0);
  stub.write(0);
  stub.write(0);
  stub.write(10);

  stub.write(32);
  stub.write(2);
  stub.write(6);
  stub.write(15);
  stub.write(4);
  
  stub.write(33);
  stub.write(0);
  stub.write(0);
  stub.write(0);
  stub.write(10);
  
  serialCommand.handleResponse();
  serialCommand.handleResponse();
  serialCommand.handleResponse();
  serialCommand.handleResponse();
/*
  Serial.print("Serial command data:");
  for(int n=1; n<=stub.available(); n++)
    Serial.println(stub.peek(n));

  Serial.print("Response data:");
  Serial.println(data);

  while(stub.available() > 0)
  {
    stubOther.write(stub.read());    
  }
  


  uint16_t data;
  serialCommandOther.handleResponse(&data);
  
  Serial.print("ResponseType:");
  Serial.println(responseTypeTest);
  Serial.print("CommandID:");
  Serial.println(commandIdTest);
  Serial.print("Data: ");
  Serial.println(dataTest);
  */
}

void loop() {
  // put your main code here, to run repeatedly:

}
