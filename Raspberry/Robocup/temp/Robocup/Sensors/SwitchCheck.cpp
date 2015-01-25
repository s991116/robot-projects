#include "SwitchCheck.h"

SwitchCheck::SwitchCheck(ComController* comController, Check* portCheck, Check* distanceCheck, Check* leftLineCheck, Check* bottomLineCheck, Check* distanceSensorCheck)
{
  _PortCheck = portCheck;
  _DistanceCheck = distanceCheck;
  _LeftLineCheck = leftLineCheck;
  _BottomLineCheck = bottomLineCheck;
  _DistanceSensorCheck = distanceSensorCheck;
  
  _CurrentCheck = _DistanceCheck;
  _CurrentCheckWithBreak = new CheckWithBreak(_CurrentCheck, comController);
  
  SettingsInt["MODE"] = &_CheckValue;
}


void SwitchCheck::Prepare() {
  
    SetCheck(static_cast<SwitchCheck::CheckEnum>(_CheckValue));
    _CurrentCheckWithBreak->Prepare();
}

bool SwitchCheck::Test() {
    return _CurrentCheckWithBreak->Test();
}

void SwitchCheck::SetCheck(CheckEnum check)
{
  _CurrentCheck = GetCheck(check);
  _CurrentCheckWithBreak->ChangeCheck(_CurrentCheck);
}

Check* SwitchCheck::GetCheck(CheckEnum check)
{
  switch(check)
  {
    case Port:
      return _PortCheck;

    case LeftLine:
      return _LeftLineCheck;
	  
    case BottomLine:
      return _BottomLineCheck;
	 
    case DistanceSensor:
      return _DistanceSensorCheck;	
	   
    case Distance:
    default:
    return _DistanceCheck;  
  }
}