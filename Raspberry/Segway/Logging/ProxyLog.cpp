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

void ProxyLog::Log(float value) {
  this->_Logging->Log(value);
}

void ProxyLog::Log(std::string message, int value) {
  this->_Logging->Log(message, value);
}

void ProxyLog::Log(std::string message, float value) {
  this->_Logging->Log(message, value);
}

void ProxyLog::Error(std::string message) {
  this->_Logging->Error(message);
}

void ProxyLog::ChangeLog(Logging* logging) {
  this->_Logging = logging;
}