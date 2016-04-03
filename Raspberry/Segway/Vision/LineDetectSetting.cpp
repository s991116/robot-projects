#include "LineDetectSetting.h"

LineDetectSetting::LineDetectSetting(std::string settingFilename, SettingFileReader* settingFileReader)
{
    _SettingFileReader = settingFileReader;
    _SettingFilename = settingFilename; 
    MapSettings();
    _SettingFileReader->UpdateSettings(_SettingFilename, this);
}

LineDetectSetting::LineDetectSetting(cv::Rect roi, int filterHalf, int filterThresshold, LineDetectSetting::PositionEnum position, LineDetectSetting::LineDirectionEnum direction, bool blackLine) {
  ROI = roi;
  FilterHalf = filterHalf;
  FilterThresshold = filterThresshold;
  PositionInt = position;
  LineDirectionInt = direction;
  BlackLine = blackLine;
  PositionOffset = 0;
  MinLineWidth = 0;
  
  MapSettings();
}

void LineDetectSetting::MapSettings() {
  SettingsInt["FILTERHALF"] = &FilterHalf;
  SettingsInt["FILTERTHRESSHOLD"] = &FilterThresshold;
  SettingsBool["BLACKLINE"] = &BlackLine;
  SettingsInt["WIDTH"] = &ROI.width;
  SettingsInt["HEIGHT"] = &ROI.height;
  SettingsInt["POSITIONX"] = &ROI.x;
  SettingsInt["POSITIONY"] = &ROI.y;
  SettingsInt["POSITION"] = &PositionInt;
  SettingsInt["LINEDIRECTION"] = &LineDirectionInt;
  SettingsInt["POSITIONOFFSET"] = &PositionOffset;
  SettingsInt["MINLINEWIDTH"] = &MinLineWidth;
}

void LineDetectSetting::SetPosition(LineDetectSetting::PositionEnum positionEnum) {
  PositionInt = static_cast<int> (positionEnum);
}

LineDetectSetting::PositionEnum LineDetectSetting::GetPosition() {
  return static_cast<LineDetectSetting::PositionEnum> (PositionInt);
}

LineDetectSetting::LineDirectionEnum LineDetectSetting::GetLineDirection() {
  return static_cast<LineDetectSetting::LineDirectionEnum> (LineDirectionInt);
}