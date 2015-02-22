#include <TurnToCenterLine.h>

TurnToCenterLine::TurnToCenterLine(RobotCamera* robotCamera, ComController* comController, LineDetect* bottomLineDetect) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _BottomLineDetect = bottomLineDetect;
  _Direction = new Direction(0, 0, 0);
  _DirectionTurn = 1;
  _DirectionTurnFactor = 100;
  _DirectionTurnSpeed = 3;
  _LineDetectThresshold = 0.1;
  
  SettingsInt["DIRECTIONTURN"] = &_DirectionTurn;
  SettingsInt["DIRECTIONTURNSPEED"] = &_DirectionTurnSpeed;
  SettingsFloat["LINETHRESSHOLD"] = &_LineDetectThresshold;
}

std::string TurnToCenterLine::Execute(std::vector<int> input) {

  LineInfo* bottomLineInfo;
  do{
    cv::Mat image = _RobotCamera->GetNextFrame(CameraPosition::FOLLOW_LINE);  
    bottomLineInfo = _BottomLineDetect->DetectLine(image);
    TurnRobot(bottomLineInfo, _ComController);
  }while(LineNotInCenter(bottomLineInfo));

  _Direction->SetDirection(0);
  _Direction->SetRotation(0);
  _Direction->SetSpeed(0);
  
  _ComController->SetDirection(_Direction);

  return "";
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