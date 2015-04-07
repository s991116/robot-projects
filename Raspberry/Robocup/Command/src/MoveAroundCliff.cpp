#include <MoveAroundCliff.h>


MoveAroundCliff::MoveAroundCliff(ComController* comController, CameraNavigation* cameraNavigation, Logging* logging)
{
	_ComController = comController;
	_CameraNavigation = cameraNavigation;
	_Logging = logging;
	_Direction = new Direction(0,0,0);
	
	SettingsInt["CIRCLE_DISTANCE"] = &_CircleDistance;
	SettingsInt["CLIFF_DETECT_OFFSET"] = &_CliffDetect;
	
	SettingsInt["NORMAL_DIRECTION"] = &_NormalDirection;
	SettingsInt["NORMAL_SPEED"] = &_NormalSpeed;
	
	SettingsInt["CLIFF_DIRECTION"] = &_CliffDirection;
	SettingsInt["CLIFF_SPEED"] = &_CliffSpeed;
}

std::string MoveAroundCliff::Execute(vector<int> data)
{
  //Set CameraPosition
  _CameraNavigation->SetPosition(CameraPosition::FLOOR_DISTANCE);

  //Measure ground distance  
  int groundDistance = _ComController->GetDistanceSensor();
  
  _ComController->ResetDistanceCommand();

  //Move around cliff until circle is reached
  SetDirection(_NormalDirection, _NormalSpeed);
  _CurrentState = false;

  while(_ComController->GetAverageDistanceCommand() < _CircleDistance) 
  {
    //Test if edge is close
	bool toCloseToEdge = (_ComController->GetDistanceSensor() - groundDistance > _CliffDetect);
	UpdateDirection(toCloseToEdge);
  }

  return "";
}

void MoveAroundCliff::UpdateDirection(bool toClose)
{
  if(_CurrentState != toClose)
  {
    if(toClose)
    {
  	  SetDirection(_NormalDirection, _NormalSpeed);
    }
    else
    {
  	  SetDirection(_CliffDirection, _CliffSpeed);
    }
    _CurrentState = toClose;
  }
}

void MoveAroundCliff::SetDirection(int dir, int speed)
{
	_Direction->SetDirection(dir);
	_Direction->SetRotation(0);
    _Direction->SetSpeed(speed);
    _ComController->SetDirection(_Direction);
}