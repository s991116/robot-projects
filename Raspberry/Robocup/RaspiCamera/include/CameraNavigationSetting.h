#ifndef CAMERANAVIGATIONSETTING_H
#define CAMERANAVIGATIONSETTING_H

class CameraNavigationSetting {
  public:
  CameraNavigationSetting(int position0, int position1);

  int Servo0Position;
  int Servo1Position;
};

#endif //CAMERANAVIGATIONSETTING_H