#include "SnapshotCommand.h"

SnapshotCommand::SnapshotCommand(CameraDetector* cameraDetector, LineDetectSetting* bottomDetectSetting, LineDetectSetting* topDetectSetting, LineDetectSetting* leftDetectSetting, LineDetectSetting* rightDetectSetting) {
  _CameraDetector = cameraDetector;
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
    image = _CameraDetector->GetNextFrame();
  }
  else
  {
    image = _CameraDetector->GetNextFrameColor();
  }
  
  if(_DisplayLineSearch)
  {
    _CameraDetector->IndicateSearchArea(image, _BottomDetectSetting->ROI);
    _CameraDetector->IndicateSearchArea(image, _TopDetectSetting->ROI);
    _CameraDetector->IndicateSearchArea(image, _LeftDetectSetting->ROI);
    _CameraDetector->IndicateSearchArea(image, _RightDetectSetting->ROI);
  }
 
  _CameraDetector->SavePicture(filename, image);

  return "";
}