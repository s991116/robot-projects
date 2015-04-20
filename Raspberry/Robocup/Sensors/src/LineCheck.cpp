#include <LineCheck.h>
#include <LineInfo.h>

LineCheck::LineCheck(LineDetect* lineDetect, RobotCamera* robotCamera, int recheck, bool noLineCheck) {
  _LineDetect = lineDetect;
  _RobotCamera = robotCamera;
  _Recheck = recheck;
  _NoLineCheck = noLineCheck;
  
  _SearchAreaEnablled = false;
  _SearchAreaMin = -1;
  _SearchAreaMax = 1;
  _CameraMode = static_cast<int>(CameraMode::FOLLOW_LINE);
  
  _LineWidthCheckEnabled = false;
  _MinLineWidth = 0;
  _MaxLineWidth = 1000;

  SettingsInt["RECHECK"] = &_Recheck;
  SettingsBool["NOLINECHECK"] = &_NoLineCheck;
  SettingsBool["SEARCHAREAENABLED"] = &_SearchAreaEnablled;
  SettingsFloat["MINSEARCHAREA"] = &_SearchAreaMin;
  SettingsFloat["MAXSEARCHAREA"] = &_SearchAreaMax;
  SettingsInt["CAMERAMODE"] = &_CameraMode;
  SettingsBool["LINEWIDTHCHECK"] = &_LineWidthCheckEnabled;
  SettingsInt["MINLINEWIDTH"] = &_MinLineWidth;
  SettingsInt["MAXLINEWIDTH"] = &_MaxLineWidth;
 }

void LineCheck::Prepare()
{
  _PositiveTest = 0;
}

bool LineCheck::Test()
{
  LineInfo* lineInfo = GetLinePosition();
  if(!_SearchAreaEnablled)
  {
    if(lineInfo->LineDetected() == _NoLineCheck)
    {
      _PositiveTest++;
    }
    else{
      _PositiveTest = 0;
    }
  }
  else if(_LineWidthCheckEnabled)
  {
	 if(lineInfo->LineDetected() && lineInfo->GetLineWidth() > _MinLineWidth && lineInfo->GetLineWidth() < _MaxLineWidth)
    {
      _PositiveTest++;
    }
    else{
      _PositiveTest = 0;
    }
  }
  else
  {
    float linePosition = lineInfo->GetNormalizePosition();
    if(lineInfo->LineDetected() && linePosition >=_SearchAreaMin && linePosition <= _SearchAreaMax)
    {
      _PositiveTest++;
	  std::cout << linePosition << std::endl;
    }
    else{
      _PositiveTest = 0;
    }
  }
  return (_PositiveTest <= _Recheck);
}

LineInfo* LineCheck::GetLinePosition() {
  cv::Mat image = _RobotCamera->GetNextFrame(GetCameraMode());
  return _LineDetect->DetectLine(image);
}

CameraMode LineCheck::GetCameraMode() {
  return static_cast<CameraMode> (_CameraMode);
}

std::string LineCheck::GetStatus() {
  LineInfo* lineInfo = GetLinePosition();
  std::string result = lineInfo->ToString() + "\n";
  result += _LineDetect->ToString();
  return result;
}
