#include "LineDetectSetting.h"

LineDetectSetting::LineDetectSetting(cv::Rect roi, int filterHalf, int filterThresshold, LineDetectSetting::PositionEnum position, LineDetectSetting::LineDirectionEnum direction, bool blackLine) {
  ROI = roi;
  FilterHalf = filterHalf;
  FilterThresshold = filterThresshold;
  PositionInt = position;
  LineDirectionInt = direction;
  BlackLine = blackLine;
  
  SettingsInt["FILTERHALF"] = &FilterHalf;
  SettingsInt["FILTERTHRESSHOLD"] = &FilterThresshold;
  SettingsBool["BLACKLINE"] = &BlackLine;
  SettingsInt["WIDTH"] = &ROI.width;
  SettingsInt["HEIGHT"] = &ROI.height;
  SettingsInt["POSITIONX"] = &ROI.x;
  SettingsInt["POSITIONY"] = &ROI.y;
  SettingsInt["POSITION"] = &PositionInt;
  SettingsInt["LINEDIRECTION"] = &LineDirectionInt;
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