#include <SearchForLine.h>

SearchForLine::SearchForLine(FindLineSetting* findLineSetting, ComController* comController, RobotCamera* robotCamera) {
  _SearchSpeed = 7;
  _FindLineSetting = findLineSetting;
  _LinePosition = new LinePosition();
  _ComController = comController;
  _RobotCamera = robotCamera;
  _Direction = new Direction(0, 0, 0);
  _SpecialLine = 0;
  
  SettingsInt["SEARCHSPEED"] = &_SearchSpeed;
  SettingsInt["SPECIALLINE"] = &_SpecialLine;
  
}

std::string SearchForLine::Execute(std::vector<int> input) {

  _Direction->SetDirection(0);
  _Direction->SetRotation(0);
  _Direction->SetSpeed(_SearchSpeed);
  _ComController->SetDirection(_Direction);

  do{
    cv::Mat image = _RobotCamera->GetNextFrame(CameraMode::FOLLOW_LINE);
	switch(_SpecialLine)
	{
		case 0: //No special line:
          _FindLineSetting->GetLinePosition(image, _LinePosition);
		  break;
		  
        case -1: //Only left line:
          _FindLineSetting->GetLeftLinePosition(image, _LinePosition);	
    	  break;

	    case 1: //Only right line:
          _FindLineSetting->GetRightLinePosition(image, _LinePosition);
	      break;

	}
  }while(_LinePosition->LineDetected == LinePosition::NoLine);
  
  return "";
}