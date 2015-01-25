#include "ConsolLog.h"
#include "ConsolePrint.h"
#include <iostream>
#include <sstream>
#include "Convert.h"

ConsolLog::ConsolLog()
{
  
}

void ConsolLog::Log(std::string message)
{
  ConsolePrint::PrintLog(message);
}

void ConsolLog::Log(int value)
{
  this->Log("Logging: ", value);
}

void ConsolLog::Log(std::string message, int value)
{
  string strNumber = Convert::IntToString(value);
  
  std::stringstream ss;
  ss << message << strNumber;
  ConsolePrint::PrintLog(ss.str());
}