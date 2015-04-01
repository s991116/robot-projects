#include "NavigateToLine.h"

NavigateToLine::NavigateToLine(FindLineSetting* findLineSetting, ComController* comController, RobotCamera* robotCamera) {
  _FindLineSetting = findLineSetting;
  _ComController = comController;
  _RobotCamera = robotCamera;
  _LinePosition = new LinePosition();
  _DistanceThresshold = 0.1;
  _AngleThresshold = 0.05;
  _NavigateSpeed = 6;
  _MaxAngle = 1;
  _AngleSpeed = 4;
  _DistanceOffset = 0.0;
  _Direction = new Direction(0, 0, 0);

  SettingsFloat["DISTANCETHRESSHOLD"] = &_DistanceThresshold;
  SettingsFloat["ANGLETHRESSHOLD"] = &_AngleThresshold;
  SettingsInt["NAVIGATIONSPEED"] = &_NavigateSpeed;
  SettingsInt["ANGLESPEED"] = &_AngleSpeed;
  SettingsFloat["DISTANCEOFFSET"] = &_DistanceOffset; 
}

std::string NavigateToLine::Execute(std::vector<int> input) {
  float leftSide;
  float rightSide;
  float angle, distance;  
  do{
    cv::Mat image = _RobotCamera->GetNextFrame(CameraMode::FOLLOW_LINE);
    _FindLineSetting->GetLinePosition(image, _LinePosition);

    GetCrossValues(&leftSide, &rightSide, _LinePosition);

    angle = GetAngle(leftSide, rightSide);
    distance = GetDistance(leftSide, rightSide, this->_DistanceOffset);

    SetDirection(_Direction, angle, distance);
    _ComController->SetDirection(_Direction);
  }while(!WithinThresshold(distance, angle));
  
  return "";
}

void NavigateToLine::GetCrossValues(float* leftSide, float* rightSide, LinePosition* linePosition) {
  if (linePosition->LineDetected == LinePosition::Cros) {
    *leftSide = linePosition->Left;
    *rightSide = linePosition->Right;
    return;
  }

  if (linePosition->LineDetected == LinePosition::CrosLeft) {
    float YRight = linePosition->Right;
    float X = linePosition->Top;
    float YLeft;
    if (X != 1)
      YLeft = 2 * (YRight - 1) / (1 - X);
    else
      YLeft = -1+YRight;

    *leftSide = YLeft;
    *rightSide = YRight;
    return;
  }

  if (linePosition->LineDetected == LinePosition::CrosRight) {
    float YLeft = linePosition->Left;
    float X = linePosition->Top;
    float YRight = 0;
    if (X != 1)
      YRight = 2 * (YLeft - 1) / (1 + X);
    else
      YRight = -1+YRight;

    *leftSide = YLeft;
    *rightSide = YLeft;
    return;
  }

  *leftSide = 0.0;
  *rightSide = 0.0;

  return;
}

float NavigateToLine::GetAngle(float leftSide, float rightSide) {
  float angle = rightSide - leftSide;
  if (angle > _MaxAngle)
    angle = _MaxAngle;

  if (angle < -_MaxAngle)
    angle = -_MaxAngle;
  
  return angle;
}

float NavigateToLine::GetDistance(float leftSide, float rightSide, float offset) {
  return (leftSide + rightSide) / 2.0 + offset;
}

void NavigateToLine::SetDirection(Direction* dir, float angle, float distance) {
  if (distance <= -_DistanceThresshold) {
    dir->SetDirectionNorm(angle);
    dir->SetSpeed(_NavigateSpeed);
    dir->SetRotation(0);
  } else if (distance >= _DistanceThresshold) {
    dir->SetDirectionNorm(-angle);
    dir->SetSpeed(-_NavigateSpeed);
    dir->SetRotation(0);
  } else {
    if (angle <= -_AngleThresshold) {
      dir->SetDirection(-_AngleSpeed);
      dir->SetSpeed(0);
      dir->SetRotation(1);
    } else if (angle >= _AngleThresshold) {
      dir->SetDirection(_AngleSpeed);
      dir->SetSpeed(0);
      dir->SetRotation(1);
    } else {
      dir->SetDirectionNorm(0);
      dir->SetSpeed(0);
      dir->SetRotation(0);
    }
  }
}

bool NavigateToLine::WithinThresshold(float distance, float angle) {
  if (distance > -_DistanceThresshold && distance < _DistanceThresshold &&
            angle > -_AngleThresshold && angle < _AngleThresshold)
    return true;
  else
    return false;
}
