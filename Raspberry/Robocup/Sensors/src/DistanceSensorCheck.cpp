#include "DistanceSensorCheck.h"
#include "Convert.h"

DistanceSensorCheck::DistanceSensorCheck(ComController* comController, CameraNavigation* cameraNavigation, Logging* logging) {
  _ComController = comController;
  _CameraNavigation = cameraNavigation;
  _Logging = logging;
  MinDistance = 15;
  MaxDistance = 25;
  CheckInRange = 1;
  ReCheck = 1;
  Position = 0;

  SettingsInt["MINDISTANCE"] = &MinDistance;
  SettingsInt["MAXDISTANCE"] = &MaxDistance;
  SettingsBool["CHECKINRANGE"] = &CheckInRange;
  SettingsInt["RECHECK"] = &ReCheck;
  SettingsInt["POSITION"] = &Position;
}

void DistanceSensorCheck::Prepare() {
  PositiveCheck = 0;
  _CameraNavigation->SetPosition(static_cast<CameraPosition>(Position));
}

std::string DistanceSensorCheck::GetStatus() {
  int distance = _ComController->GetDistanceSensor();
  return "Distance: " + Convert::IntToString(distance);
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
