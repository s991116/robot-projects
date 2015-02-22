#include<FollowLineCommand.h>
#include <LineDetect.h>

FollowLineCommand::FollowLineCommand(PiCamera* piCamera, ComController* comController, FollowLineSetting* followLineSetting, Check* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect) {
  this->_PiCamera = piCamera;
  this->_ComController = comController;
  this->_FollowLineSetting = followLineSetting;
  this->_Check = check;
  this->_BottomLineDetect = bottomLineDetect;
  this->_TopLineDetect = topLineDetect;
}

FollowLineCommand::~FollowLineCommand() {
}

std::string FollowLineCommand::Execute(vector<int> input) {

  _Check->Prepare();
  _PiCamera->SetCameraPosition(CameraPosition::FOLLOW_LINE);

  while (_Check->Test()) {
    cv::Mat imageMat = this->_PiCamera->GetNextFrame();
    LineInfo* bottomLine = this->_BottomLineDetect->DetectLine(imageMat);
    LineInfo* topLine = this->_TopLineDetect->DetectLine(imageMat);

    Direction* direction = this->_FollowLineSetting->GetDirection(bottomLine, topLine);

    this->_ComController->SetDirection(direction);
  }

  return "";
}

void FollowLineCommand::PrintPosition(float position) {
  std::cout << "I";
  for (int i = 0; i < 15 * position; i++)
    std::cout << " ";

  std::cout << "x";
  for (int i = 15 * position; i < 30 * position; i++)
    std::cout << " ";

  std::cout << "I" << std::endl;
}