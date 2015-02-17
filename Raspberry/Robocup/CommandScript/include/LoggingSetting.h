#ifndef LOGGINGSETTING_H
#define	LOGGINGSETTING_H

#include "Setting.h"
#include "Logging.h"
#include "EmptyLog.h"
#include "ProxyLog.h"

class LoggingSetting : public Setting {
public:
    LoggingSetting(EmptyLog* emptyLog, Logging* logging, Logging* fileLogging);
    Logging* GetLogging();
    void UpdatedSetting(std::string name);

private:
  Logging* _EmptyLog;
  Logging* _Logging;
  Logging* _FileLogging;
  ProxyLog* _SelectedLog; 
  int _LogType;  
};

#endif	/* LOGGINGSETTING_H */

