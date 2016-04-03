#ifndef LINEDETECTSETTING_H
#define	LINEDETECTSETTING_H
#include <opencv/cv.h>
#include "Setting.h"
#include "SettingFileReader.h"
#include <string>

class LineDetectSetting : public Setting {
public:
    enum PositionEnum
    {
      LEFT,
      CENTER,
      RIGHT,
    };

    enum LineDirectionEnum
    {
      VERTICAL,
      HORIZONTAL,
    };
    
    LineDetectSetting(std::string settingFilename, SettingFileReader* settingFileReader);
    LineDetectSetting(cv::Rect roi, int filterHalf, int filterThresshold, LineDetectSetting::PositionEnum position, LineDetectSetting::LineDirectionEnum direction, bool blackLine);
    
    PositionEnum GetPosition();
    void SetPosition(LineDetectSetting::PositionEnum positionEnum);
    LineDirectionEnum GetLineDirection();

    cv::Rect ROI;
    int FilterHalf;
    int FilterThresshold;    
    bool BlackLine;
    int PositionOffset;
    int MinLineWidth;
    
private:
    void MapSettings();
    int PositionInt;
    int LineDirectionInt;    
    SettingFileReader* _SettingFileReader;
    std::string _SettingFilename;
};

#endif	/* LINEDETECTSETTING_H */

