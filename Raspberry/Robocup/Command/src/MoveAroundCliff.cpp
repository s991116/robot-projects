#include <MoveAroundCliff.h>


MoveAroundCliff::MoveAroundCliff(ComController* comController, CameraNavigation* cameraNavigation, Logging* logging)
{
	_ComController = comController;
	_CameraNavigation = cameraNavigation;
	_Logging = logging;
	_Direction = new Direction(0,0,0);
	_MaxErrorDistance = 100;
	
	SettingsInt["CIRCLE_DISTANCE"] = &_CircleDistance;
	SettingsInt["CLIFF_DETECT_OFFSET"] = &_CliffDetect;
	
	SettingsInt["NORMAL_DIRECTION"] = &_NormalDirection;
	SettingsInt["NORMAL_SPEED"] = &_NormalSpeed;
	
	SettingsInt["CLIFF_DIRECTION"] = &_CliffDirection;
	SettingsInt["CLIFF_SPEED"] = &_CliffSpeed;
	
	SettingsInt["MAX_DISTANCE"] = &_MaxErrorDistance;
}

std::string MoveAroundCliff::Execute(vector<int> data)
{
  //Set CameraPosition
  _CameraNavigation->SetPosition(CameraPosition::FLOOR_DISTANCE);

  //Measure ground distance  
  int groundDistance = MeasureDistance();
	  
  _Logging->Log("Ground distance: ", groundDistance);
  
  _ComController->ResetDistanceCommand();

  //Move around cliff until circle is reached
  SetDirection(_NormalDirection, _NormalSpeed);
  _CurrentState = false;

  while(_ComController->GetAverageDistanceCommand() < _CircleDistance) 
  {
    //Test if edge is close
    int distance = MeasureDistance();
    _Logging->Log("Current distance: ", distance);
	bool toCloseToEdge = (distance - groundDistance > _CliffDetect);
	UpdateDirection(toCloseToEdge);
	distance = _ComController->GetAverageDistanceCommand();
  }

  return "";
}

int MoveAroundCliff::MeasureDistance()
{
  int distance;
  do{
    distance = _ComController->GetDistanceSensor();
  } while(distance >= _MaxErrorDistance);
  return distance;
}

void MoveAroundCliff::UpdateDirection(bool toClose)
{
  if(_CurrentState != toClose)
  {
    if(toClose)
    {
      _Logging->Log("Cliff to close now");
      SetDirection(_NormalDirection, _NormalSpeed);
    }
    else
    {
      _Logging->Log("No Cliff");
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