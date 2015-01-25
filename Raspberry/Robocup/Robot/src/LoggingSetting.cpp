#include "LoggingSetting.h"

LoggingSetting::LoggingSetting(EmptyLog* emptyLog, Logging* logging, Logging* fileLogging) {
  _EmptyLog = emptyLog;
  _Logging = logging;
  _FileLogging = fileLogging;  
  _SelectedLog = new ProxyLog(_EmptyLog);
}

Logging* LoggingSetting::GetLogging() {
  return _SelectedLog;
}