#include "NavigateToBall.h"

NavigateToBall::NavigateToBall(CameraDetector* cameraDetector, DetectObject* detectObject, ComController* comController) {
  _CameraDetector = cameraDetector;
  _DetectObject = detectObject;
  _ComController = comController;
  _Position = new Position();
  
  _DistanceThresshold = 0.1;
  _AngleThresshold = 0.1;
  _NavigateSpeed = 4;
  _AngleSpeed = 4;
  _DistanceOffset = 0;
  _Direction = new Direction(0, 0, 0);
  
  SettingsFloat["DISTANCETHRESSHOLD"] = &_DistanceThresshold;
  SettingsFloat["ANGLETHRESSHOLD"] = &_AngleThresshold;
  SettingsInt["NAVIGATIONSPEED"] = &_NavigateSpeed;
  SettingsInt["ANGLESPEED"] = &_AngleSpeed;
  SettingsFloat["DISTANCEOFFSET"] = &_DistanceOffset; 
}

std::string NavigateToBall::Execute(std::vector<int> input) {

  float angle, distance;  
  do{
    cv::Mat image = _CameraDetector->GetNextFrameColor();
    
    _DetectObject->GetPosition(image, _Position);
    
    angle = _Position->PositionX;
    distance = _Position->PositionY - _DistanceOffset;

    SetDirection(_Direction, angle, distance);
    _ComController->SetDirection(_Direction);
  }while(!WithinThresshold(distance, angle));
  
  return "";
}

void NavigateToBall::SetDirection(Direction* dir, float angle, float distance) {
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
      dir->SetDirection(-100);
      dir->SetSpeed(_AngleSpeed);
      dir->SetRotation(0);
    } else if (angle >= _AngleThresshold) {
      dir->SetDirection(100);
      dir->SetSpeed(_AngleSpeed);
      dir->SetRotation(0);
    } else {
      dir->SetDirectionNorm(0);
      dir->SetSpeed(0);
      dir->SetRotation(0);
    }
  }
}

bool NavigateToBall::WithinThresshold(float distance, float angle) {
  if (distance > -_DistanceThresshold && distance < _DistanceThresshold &&
            angle > -_AngleThresshold && angle < _AngleThresshold)
    return true;
  else
    return false;
}