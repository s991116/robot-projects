#ifndef ROBOTCAMERASETTING_H
#define	ROBOTCAMERASETTING_H

class RobotCameraSetting {
public:
  RobotCameraSetting(int servo0Position, int servo1Position, int frameWidth, int frameHeight, bool grayMode);
  int Servo0Position;
  int Servo1Position;
  
  int FrameWidth;
  int FrameHeight;
  
  bool GrayMode;

};

#endif	/* ROBOTCAMERASETTING_H */