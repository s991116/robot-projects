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

  SettingsInt["RECHECK"] = &_Recheck;
  SettingsBool["NOLINECHECK"] = &_NoLineCheck;
  SettingsBool["SEARCHAREAENABLED"] = &_SearchAreaEnablled;
  SettingsFloat["MINSEARCHAREA"] = &_SearchAreaMin;
  SettingsFloat["MAXSEARCHAREA"] = &_SearchAreaMax;
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
    return (_PositiveTest <= _Recheck);
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
    return (_PositiveTest <= _Recheck);
  }
}

LineInfo* LineCheck::GetLinePosition() {
  cv::Mat image = _RobotCamera->GetNextFrontLineFrame();
  return _LineDetect->DetectLine(image);
}

std::string LineCheck::GetStatus() {
  LineInfo* lineInfo = GetLinePosition();
  std::string result = lineInfo->ToString() + "\n";
  return result;
}
