#include <DistanceCheck.h>
#include <Convert.h>

DistanceCheck::DistanceCheck(ComController* comController, int distance, Logging* logging)
{
  _ComController = comController;
  _Logging = logging;
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
  int leftDistance = _ComController->GetLeftDistanceCommand();
  int rightDistance = _ComController->GetLeftDistanceCommand();
  return "Left:" + Convert::IntToString(leftDistance) + 
         " , Right:" + Convert::IntToString(rightDistance) +
		 " , Avg.: " + Convert::IntToString(currentDistance);
}
