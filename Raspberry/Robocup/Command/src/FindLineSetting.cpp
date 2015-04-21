#include "FindLineSetting.h"

FindLineSetting::FindLineSetting(LineDetect* leftDetect, LineDetect* rightDetect, LineDetect* topDetect) {
  _LeftDetect = leftDetect;
  _RightDetect = rightDetect;
  _TopDetect = topDetect;
}

void FindLineSetting::GetRightLinePosition(cv::Mat image, LinePosition* linePosition) {
  LineInfo* rightLineInfo = _RightDetect->DetectLine(image);
  if(rightLineInfo->LineDetected())
    linePosition->LineDetected = LinePosition::Middle;
  else
    linePosition->LineDetected =  LinePosition::NoLine;  
}

void FindLineSetting::GetLeftLinePosition(cv::Mat image, LinePosition* linePosition) {
  LineInfo* leftLineInfo = _LeftDetect->DetectLine(image);
  if(leftLineInfo->LineDetected())
    linePosition->LineDetected = LinePosition::Middle;
  else
    linePosition->LineDetected =  LinePosition::NoLine;  
}

void FindLineSetting::GetLinePosition(cv::Mat image, LinePosition* linePosition) {
  LineInfo* leftLineInfo = _LeftDetect->DetectLine(image);
  LineInfo* rightLineInfo = _RightDetect->DetectLine(image);
  LineInfo* topLineInfo = _TopDetect->DetectLine(image);
  
  linePosition->LineDetected = GetSearchStatus(leftLineInfo, rightLineInfo, topLineInfo);
  
  linePosition->Left = leftLineInfo->GetNormalizePosition();
  linePosition->Right = rightLineInfo->GetNormalizePosition();
  linePosition->Top = topLineInfo->GetNormalizePosition();
}

LinePosition::SearchStatusEnum FindLineSetting::GetSearchStatus(LineInfo* leftLineInfo, LineInfo* rightLineInfo, LineInfo* topLineInfo) {
  bool leftLineDetected  = leftLineInfo->LineDetected();
  bool rightLineDetected = rightLineInfo->LineDetected();
  bool topLineDetected   = topLineInfo->LineDetected();
  
  if(leftLineDetected && rightLineDetected)
    return LinePosition::Cros;

  if(!leftLineDetected && topLineDetected)
    return LinePosition::CrosLeft;
  
  if(!rightLineDetected && topLineDetected)
    return LinePosition::CrosRight;
  
  if(topLineDetected)
    return LinePosition::Middle;

  return LinePosition::NoLine;
}