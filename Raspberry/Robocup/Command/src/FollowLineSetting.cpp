#include "FollowLineSetting.h"
#include "Setting.h"

FollowLineSetting::FollowLineSetting(int correctionFactor, float speedFactor, int maxSpeed, int minSpeed) {
  _Direction = new Direction(0, 0, 0);
  _CorrectionFactor = correctionFactor;
  _SpeedFactor = speedFactor;
  _MaxSpeed = maxSpeed;
  _MinSpeed = minSpeed;
  _CameraMode = static_cast<int>(CameraMode::FOLLOW_LINE);

  SettingsInt["CORRECTIONFACTOR"] = &_CorrectionFactor;
  SettingsFloat["SPEEDFACTOR"] = &_SpeedFactor;
  SettingsInt["MAXSPEED"] = &_MaxSpeed;
  SettingsInt["MINSPEED"] = &_MinSpeed;  
  SettingsInt["CAMERAMODE"] = &_CameraMode;
}

CameraMode FollowLineSetting::GetCameraMode() {
  return static_cast<CameraMode> (_CameraMode);
}

Direction* FollowLineSetting::GetDirection(LineInfo* bottomLine, LineInfo* topLine) {
  float bottomPosition = GetPosition(bottomLine, &_LastBottomPosition);
  float topPosition = GetPosition(topLine, &_LastTopPosition);

  if (topPosition < 0) {
    topPosition = -topPosition;
  }

  int speed = _MaxSpeed - topPosition * _SpeedFactor;

  if (speed < _MinSpeed)
    speed = _MinSpeed;

  _Direction->SetSpeed(speed);
  _Direction->SetDirection(bottomPosition * _CorrectionFactor);

  return this->_Direction;
}

float FollowLineSetting::GetPosition(LineInfo* bottomLine, float* lastKnownedPosition) {
  float position;
  if (bottomLine->LineDetected()) {
    position = bottomLine->GetNormalizePosition();
    *lastKnownedPosition = position;
  } else {
    if (*lastKnownedPosition > 0)
      position = 1;
    else
      position = -1;
  }
  return position;
}