#include <ComMessage.h>

void ComMessage::GenerateMessage(char command, short data, char* message)
{
     message[0] = command;
     message[1] = (data>>8) & 0x00FF;
     message[2] = data & 0x00FF;
}

