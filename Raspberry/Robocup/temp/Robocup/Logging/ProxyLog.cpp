#include "ProxyLog.h"

ProxyLog::ProxyLog(Logging* logging) {
  this->ChangeLog(logging);
}

void ProxyLog::Log(std::string message) {
  this->_Logging->Log(message);
}

void ProxyLog::Log(int value) {
  this->_Logging->Log(value);
}

void ProxyLog::Log(std::string message, int value) {
  this->_Logging->Log(message, value);
}

void ProxyLog::ChangeLog(Logging* logging) {
  this->_Logging = logging;
}