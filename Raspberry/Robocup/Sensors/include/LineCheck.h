#ifndef LINECHECK_H
#define	LINECHECK_H

#include <Check.h>
#include <Setting.h>
#include <LineDetect.h>
#include <PiCamera.h>
#include <SensorInfo.h>

class LineCheck : public Check, public Setting, public SensorInfo {
public:
  LineCheck(LineDetect* lineDetect, PiCamera* piCamera, int reCheck, bool noLineCheck);
  void Prepare();
  bool Test();
  std::string GetInfo();
  std::string GetStatus();

private:
  LineInfo* GetLinePosition();
  LineDetect* _LineDetect;
  PiCamera* _PiCamera;
  int _PositiveTest;
  int _Recheck;
  bool _NoLineCheck;
  bool _SearchAreaEnablled;
  float _SearchAreaMin;
  float _SearchAreaMax;

};

#endif	/* LINECHECK_H */

