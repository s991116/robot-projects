#include <DistanceCheck.h>
#include <Convert.h>

DistanceCheck::DistanceCheck(ComController* comController, int distance)
{
  _ComController = comController;
  SetDistance(distance);
}

void DistanceCheck::SetDistance(int distance) {
  _TargetDistance = distance;
  SettingsInt["DISTANCE"] = &_TargetDistance;
}

void DistanceCheck::Prepare()
{
    _ComController->ResetDistanceCommand();
}

bool DistanceCheck::Test()
{
  int currentDistance = _ComController->GetAverageDistanceCommand();
  if(_TargetDistance >= 0)
  {
    return(currentDistance < _TargetDistance);
  }
  else
  {
    return(currentDistance > _TargetDistance);
  }
}

std::string DistanceCheck::GetStatus()
{
  int currentDistance = _ComController->GetAverageDistanceCommand();
  return Convert::IntToString(currentDistance);
}
