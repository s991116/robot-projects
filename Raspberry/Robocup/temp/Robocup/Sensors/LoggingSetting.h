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
    
private:
  Logging* _EmptyLog;
  Logging* _Logging;
  Logging* _FileLogging;
  ProxyLog* _SelectedLog;  
};

#endif	/* LOGGINGSETTING_H */

