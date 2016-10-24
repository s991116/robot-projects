#include <HC_SR04.h>

HC_SR04 DistanceSensor(DISTANCE_TRIGGER_PIN, DISTANCE_ECHO_PIN, DISTANCE_MAX);

void DistanceSensorUpdate()
{
  DistanceSensor.update();
}

int DistanceSensorMeasure()
{
  DistanceSensor.update();
  return DistanceSensor.getRange();
}

void DistanceSensorEnable(bool enable)
{
  DistanceSensor.enable(enable);
}

bool DistanceSensorEnabled()
{
  return DistanceSensor.enabled();
}

