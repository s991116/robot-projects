#include<FollowLineCommand.h>
#include <LineDetect.h>

FollowLineCommand::FollowLineCommand(RobotCamera* robotCamera, ComController* comController, FollowLineSetting* followLineSetting, Check* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect) {
  this->_RobotCamera = robotCamera;
  this->_ComController = comController;
  this->_FollowLineSetting = followLineSetting;
  this->_Check = check;
  this->_BottomLineDetect = bottomLineDetect;
  this->_TopLineDetect = topLineDetect;
}

FollowLineCommand::~FollowLineCommand() {
}

std::string FollowLineCommand::Execute(vector<int> input) {
	return this->Execute();
}

std::string FollowLineCommand::Execute() {

  _Check->Prepare();

  while (_Check->Test()) {
    cv::Mat imageMat = _RobotCamera->GetNextFrame(CameraPosition::FOLLOW_LINE);
    LineInfo* bottomLine = _BottomLineDetect->DetectLine(imageMat);
    LineInfo* topLine = _TopLineDetect->DetectLine(imageMat);

    Direction* direction = _FollowLineSetting->GetDirection(bottomLine, topLine);

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