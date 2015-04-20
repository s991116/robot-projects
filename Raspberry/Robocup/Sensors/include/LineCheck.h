#ifndef LINECHECK_H
#define	LINECHECK_H

#include <Check.h>
#include <Setting.h>
#include <LineDetect.h>
#include <RobotCamera.h>
#include <SensorInfo.h>
#include <Logging.h>

class LineCheck : public Check, public Setting, public SensorInfo {
public:
  LineCheck(LineDetect* lineDetect, RobotCamera* robotCamera, int reCheck, bool noLineCheck, Logging* logging);
  void Prepare();
  bool Test();
  std::string GetInfo();
  std::string GetStatus();

private:
  LineInfo* GetLinePosition();
  CameraMode GetCameraMode();
  LineDetect* _LineDetect;
  RobotCamera* _RobotCamera;
  int _PositiveTest;
  int _Recheck;
  bool _NoLineCheck;
  bool _SearchAreaEnablled;
  float _SearchAreaMin;
  float _SearchAreaMax;
  int _CameraMode;
  bool _LineWidthCheckEnabled;
  int _MinLineWidth;
  int _MaxLineWidth;
  Logging* _Logging;
};

#endif	/* LINECHECK_H */

