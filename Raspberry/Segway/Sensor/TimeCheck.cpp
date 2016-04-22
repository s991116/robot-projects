#include "TimeCheck.h"

TimeCheck::TimeCheck() {
    this->SettingsInt["TIME_MS"] = &_TargetTime;
    _TargetTime = 0;
}

void TimeCheck::Prepare() {
  gettimeofday(&tv, NULL);
  _EndTime_SEC = tv.tv_sec + (_TargetTime / 1000);
  _EndTime_MS = tv.tv_usec + (_TargetTime % 1000);
}

bool TimeCheck::Test() {
  gettimeofday(&tv, NULL);
  return (_EndTime_SEC <= tv.tv_sec && _EndTime_MS <= tv.tv_usec);
}

TimeCheck::~TimeCheck() {
}

