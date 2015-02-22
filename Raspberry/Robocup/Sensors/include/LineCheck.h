#ifndef LINECHECK_H
#define	LINECHECK_H

#include <Check.h>
#include <Setting.h>
#include <LineDetect.h>
#include <RobotCamera.h>
#include <SensorInfo.h>

class LineCheck : public Check, public Setting, public SensorInfo {
public:
  LineCheck(LineDetect* lineDetect, RobotCamera* robotCamera, int reCheck, bool noLineCheck);
  void Prepare();
  bool Test();
  std::string GetInfo();
  std::string GetStatus();

private:
  LineInfo* GetLinePosition();
  LineDetect* _LineDetect;
  RobotCamera* _RobotCamera;
  int _PositiveTest;
  int _Recheck;
  bool _NoLineCheck;
  bool _SearchAreaEnablled;
  float _SearchAreaMin;
  float _SearchAreaMax;

};

#endif	/* LINECHECK_H */

