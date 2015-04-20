#include <TurnToCenterLine.h>

TurnToCenterLine::TurnToCenterLine(RobotCamera* robotCamera, ComController* comController, LineDetect* bottomLineDetect, LineDetect* topLineDetect) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _BottomLineDetect = bottomLineDetect;
  _TopLineDetect = topLineDetect;  
  _Direction = new Direction(0, 0, 0);
  _DirectionTurn = 1;
  _DirectionTurnFactor = 100;
  _DirectionTurnSpeed = 3;
  _LineDetectThresshold = 0.1;
  _BottomLineEnabled = true;
  _CameraMode = static_cast<int>(CameraMode::FOLLOW_LINE);
  
  SettingsInt["DIRECTIONTURN"] = &_DirectionTurn;
  SettingsInt["DIRECTIONTURNSPEED"] = &_DirectionTurnSpeed;
  SettingsInt["DIRECTIONTURNFACTOR"] = &_DirectionTurnFactor;

  SettingsFloat["LINETHRESSHOLD"] = &_LineDetectThresshold;
  SettingsBool["BOTTOM_LINE_DETECT"] = &_BottomLineEnabled;

  SettingsInt["CAMERAMODE"] = &_CameraMode;
}

std::string TurnToCenterLine::Execute(std::vector<int> input) {

  LineInfo* lineInfo;
  do{
    cv::Mat image = _RobotCamera->GetNextFrame(GetCameraMode());  
    if(_BottomLineEnabled)
        lineInfo = _BottomLineDetect->DetectLine(image);
	else
        lineInfo = _TopLineDetect->DetectLine(image);

    TurnRobot(lineInfo, _ComController);
  }while(LineNotInCenter(lineInfo));

  _Direction->SetDirection(0);
  _Direction->SetRotation(0);
  _Direction->SetSpeed(0);
  
  _ComController->SetDirection(_Direction);

  return "";
}

CameraMode TurnToCenterLine::GetCameraMode() {
  return static_cast<CameraMode> (_CameraMode);
}

bool TurnToCenterLine::LineNotInCenter(LineInfo* lineInfo) {
  if(lineInfo->LineDetected()) {
    float position = lineInfo->GetNormalizePosition();
    if(position >= -_LineDetectThresshold  && position <= _LineDetectThresshold)
      return false;
  }
  return true;
}

void TurnToCenterLine::TurnRobot(LineInfo* lineInfo, ComController* comController) {
  int directionSearch;
  _Direction->SetRotation(0);
  _Direction->SetSpeed(_DirectionTurnSpeed);
  
  if(!lineInfo->LineDetected())
    directionSearch = _DirectionTurn*_DirectionTurnFactor;
  else
  {
    float position = lineInfo->GetNormalizePosition();
    if(position >= _LineDetectThresshold)
    {
      directionSearch = _DirectionTurnFactor;
    }
    else if(position <= -_LineDetectThresshold)
    {
      directionSearch = -_DirectionTurnFactor;
    }
    else
    {
      directionSearch = 0;
      _Direction->SetSpeed(0);
    }  
  }
  _Direction->SetDirection(directionSearch);  
  
  comController->SetDirection(_Direction);
}