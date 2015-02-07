#include <DistanceCheck.h>
#include <Convert.h>

DistanceCheck::DistanceCheck(ComController* comController, int distance)
{
  _ComController = comController;
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
  return(currentDistance < _TargetDistance);
}

std::string DistanceCheck::GetStatus()
{
  int currentDistance = _ComController->GetAverageDistanceCommand();
  return Convert::IntToString(currentDistance);
}
