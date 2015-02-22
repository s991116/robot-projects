#include "SnapshotCommand.h"

SnapshotCommand::SnapshotCommand(PiCamera* piCamera, LineDetectSetting* bottomDetectSetting, LineDetectSetting* topDetectSetting, LineDetectSetting* leftDetectSetting, LineDetectSetting* rightDetectSetting) {
  _PiCamera = piCamera;
  _BottomDetectSetting = bottomDetectSetting;
  _TopDetectSetting = topDetectSetting;
  _LeftDetectSetting = leftDetectSetting;
  _RightDetectSetting = rightDetectSetting;
  
  _GrayMode = true;
  SettingsBool["GRAYMODE"] = &_GrayMode;
  
  _DisplayLineSearch = true;
  SettingsBool["DISPLINESEARCH"] = &_DisplayLineSearch;
}

std::string SnapshotCommand::Execute(vector<int> data) {
  string filename = "SnapShot";
  if (data.size() >= 1) {
    std::stringstream ss;
    ss << data[0];
    std::string str = ss.str();
    filename += "_";
    filename += str;
  }
  filename += ".jpg";

  cv::Mat image;
  if(_GrayMode)
  {
    image = _PiCamera->GetNextFrame();
  }
  else
  {
    image = _PiCamera->GetNextFrameColor();
  }
  
  if(_DisplayLineSearch)
  {
    _PiCamera->IndicateSearchArea(image, _BottomDetectSetting->ROI);
    _PiCamera->IndicateSearchArea(image, _TopDetectSetting->ROI);
    _PiCamera->IndicateSearchArea(image, _LeftDetectSetting->ROI);
    _PiCamera->IndicateSearchArea(image, _RightDetectSetting->ROI);
  }
 
  _PiCamera->SavePicture(filename, image);
  return "";
}