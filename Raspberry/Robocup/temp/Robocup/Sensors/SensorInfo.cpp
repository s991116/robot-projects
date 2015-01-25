#include "SensorInfo.h"
#include "Convert.h"

std::string SensorInfo::PrintStatus(std::string name, int value) {
  return "Sensor '" + name + "'=" + Convert::IntToString(value);
}
