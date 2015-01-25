#include "LineInfo.h"
#include "Convert.h"


LineInfo::LineInfo(bool detected, int position, int imageWidth) {
    this->Detected = detected;
    this->Position = position;
    this->ImageWidth = imageWidth;
}

int LineInfo::GetPosition()
{
    return this->Position;
}

float LineInfo::GetNormalizePosition()
{
    int halfWidth = (this->ImageWidth+1) / 2;
    int normPos = this->Position -(halfWidth);
    return (float)normPos / (float)halfWidth;
}

bool LineInfo::LineDetected()
{
    return this->Detected;
}

std::string LineInfo::ToString() {
  std::string result = "";
  if(this->Detected)
  {
    result += "Line found at position ";
    int position = 100*GetNormalizePosition();
    result += Convert::IntToString(position);
    result += ".";
  }
  else
  {
    result = "No line detected.";
  }
  
  return result;
}