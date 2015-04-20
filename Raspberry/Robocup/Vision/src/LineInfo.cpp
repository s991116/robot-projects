#include "LineInfo.h"
#include "Convert.h"


LineInfo::LineInfo(bool detected, int position, int imageWidth) {
    this->Detected = detected;
    this->Position = position;
    this->ImageWidth = imageWidth;
	this->LineWidth = -1;
}

LineInfo::LineInfo(bool detected, int position, int imageWidth, int lineWidth) {
    this->Detected = detected;
    this->Position = position;
    this->ImageWidth = imageWidth;
	this->LineWidth = lineWidth;
}

void LineInfo::SetPosition(int position)
{
	this->Position = position;
}

int LineInfo::GetPosition()
{
    return this->Position;
}

int LineInfo::GetLineWidth()
{
	return this->LineWidth;
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
    result += "Line found at position: ";
    int position = 100*GetNormalizePosition();
    result += Convert::IntToString(position);
    result += " , ";
	result += "Linewidth: ";
	result += Convert::IntToString(LineWidth);
  }
  else
  {
    result = "No line detected.";
  }
  
  return result;
}