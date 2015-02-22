#include "SnapshotCommand.h"

SnapshotCommand::SnapshotCommand(RobotCamera* robotCamera, LineDetectSetting* bottomDetectSetting, LineDetectSetting* topDetectSetting, LineDetectSetting* leftDetectSetting, LineDetectSetting* rightDetectSetting) {
  _RobotCamera = robotCamera;
  _BottomDetectSetting = bottomDetectSetting;
  _TopDetectSetting = topDetectSetting;
  _LeftDetectSetting = leftDetectSetting;
  _RightDetectSetting = rightDetectSetting;
    
  _DisplayLineSearch = true;
  SettingsBool["DISP_INFO"] = &_DisplayLineSearch;
  SettingsInt["CAMERA_MODE"] = &_RobotCameraMode;  
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
  
  image = _RobotCamera->GetNextFrame(static_cast<CameraPosition>(_RobotCameraMode));
  
  if(_DisplayLineSearch)
  {
    IndicateSearchArea(image, _BottomDetectSetting->ROI);
    IndicateSearchArea(image, _TopDetectSetting->ROI);
    IndicateSearchArea(image, _LeftDetectSetting->ROI);
    IndicateSearchArea(image, _RightDetectSetting->ROI);
  }
 
  SavePicture(filename, image);
  return "";
}

void SnapshotCommand::SavePicture(std::string filename, cv::Mat frame) {
    imwrite( filename.c_str(), frame );
}

void SnapshotCommand::IndicateSearchArea(cv::Mat frame, cv::Rect region)
{
    rectangle(frame, region, cv::Scalar(100,100,80), 2, 8, 0);
}