#include "LineDetectSetting.h"

LineDetectSetting::LineDetectSetting() {
    FilterHalf = 15;
    FilterThresshold = 1500;
    BlackLine = false;
    ROI.height = 5;
    ROI.width = 320;
    ROI.x = 0;
    ROI.y = 220;
    PositionInt = PositionEnum::CENTER;
    LineDirectionInt = LineDirectionEnum::VERTICAL;
    PositionOffset = 0;
    MinLineWidth = 10;    
    
    MapSettings();
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