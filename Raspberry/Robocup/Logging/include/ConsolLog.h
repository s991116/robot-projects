#ifndef CONSOLLOG_H
#define	CONSOLLOG_H

#include <Logging.h>

class ConsolLog : public Logging {
public:
  ConsolLog();
  
  void Log(std::string message);
  void Log(int value);
  void Log(float value);
  void Log(std::string message, int value);
  void Log(std::string message, float value);
  void Error(std::string message);
};

#endif	/* CONSOLLOG_H */

