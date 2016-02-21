#include <SerialCommand.h>

#define DEBUG_MANUAL_COMMAND

void WriteLog(char* message)
{
#ifdef DEBUG_MANUAL_COMMAND
  Serial.println(F(message));
#endif  
}

void WriteLog(int message)
{
#ifdef DEBUG_MANUAL_COMMAND
  Serial.println(message);
#endif  
}

