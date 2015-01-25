#include "DistanceSensorCheck.h"
#include "Convert.h"

DistanceSensorCheck::DistanceSensorCheck(ComController* comController) {
  _ComController = comController;
  
  MinDistance = 15;
  MaxDistance = 25;
  CheckInRange = 1;
  ReCheck = 1;
  
  SettingsInt["MINDISTANCE"] = &MinDistance;
  SettingsInt["MAXDISTANCE"] = &MaxDistance;
  SettingsBool["CHECKINRANGE"] = &CheckInRange;
  SettingsInt["RECHECK"] = &ReCheck;
}

void DistanceSensorCheck::Prepare() {
  PositiveCheck = 0;
}

bool DistanceSensorCheck::Test() {
  int distance = _ComController->GetDistanceSensor();
  if(CheckInRange)
  {
    if(distance >= MaxDistance || distance <= MinDistance)
	{
	  PositiveCheck = 0;
	}
	else
	{
	  PositiveCheck++;
	}
  }
  else
  {
    if(distance >= MaxDistance || distance <= MinDistance)
	{
	  PositiveCheck++;
	}
	else
	{
	  PositiveCheck = 0;
	}
  }
  
  return (PositiveCheck <= ReCheck);
}
