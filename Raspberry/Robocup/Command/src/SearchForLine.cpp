#include "SearchForLine.h"

SearchForLine::SearchForLine(FindLineSetting* findLineSetting, ComController* comController, CameraDetector* cameraDetector) {
  _SearchSpeed = 7;
  _FindLineSetting = findLineSetting;
  _LinePosition = new LinePosition();
  _ComController = comController;
  _CameraDetector = cameraDetector;
  _Direction = new Direction(0, 0, 0);
  
  SettingsInt["SEARCHSPEED"] = &_SearchSpeed;
}

std::string SearchForLine::Execute(std::vector<int> input) {

  _Direction->SetDirection(0);
  _Direction->SetRotation(0);
  _Direction->SetSpeed(_SearchSpeed);
  _ComController->SetDirection(_Direction);

  do{
    cv::Mat image = _CameraDetector->GetNextFrame();
    _FindLineSetting->GetLinePosition(image, _LinePosition);
  }while(_LinePosition->LineDetected == LinePosition::NoLine);
  
  return "";
}