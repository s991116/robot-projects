#include "LoggingSetting.h"

LoggingSetting::LoggingSetting(EmptyLog* emptyLog, Logging* logging, Logging* fileLogging) {
  _EmptyLog = emptyLog;
  _Logging = logging;
  _FileLogging = fileLogging;  
  SettingsInt["TYPE"] = &_LogType;
  _SelectedLog = new ProxyLog(_Logging);
}

Logging* LoggingSetting::GetLogging() {
  return _SelectedLog;
}

void LoggingSetting::UpdatedSetting(std::string name) {
  switch(_LogType)
  {
	  case 0:
	    _SelectedLog->ChangeLog(_EmptyLog);
		break;

	  case 1:
	    _SelectedLog->ChangeLog(_Logging);
		break;

	  case 2:
	    _SelectedLog->ChangeLog(_FileLogging);
		break;
	}
}