#include "TimeCheck.h"

TimeCheck::TimeCheck() {
    this->SettingsInt["TIME_MS"] = &_TargetTime;
}

void TimeCheck::Prepare() {
  
  gettimeofday(&tv, NULL);
  _EndTime = tv.tv_usec + _TargetTime;
}

bool TimeCheck::Test() {
  gettimeofday(&tv, NULL);
  return (_EndTime <= tv.tv_usec);
}

TimeCheck::~TimeCheck() {
}

