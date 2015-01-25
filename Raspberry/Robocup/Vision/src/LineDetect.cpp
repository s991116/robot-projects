#include <LineDetect.h>
#include <Convert.h>
#include <cmath>
#include <EmptyLog.h>

LineDetect::LineDetect(LineDetectSetting* lineDetectSetting, Logging* logging) {
  this->_LineDetectSetting = lineDetectSetting;
  if (_LineDetectSetting->ROI.width > _LineDetectSetting->ROI.height) 
  {
    _SearchWidth = _LineDetectSetting->ROI.width;
  } 
  else 
  {
    _SearchWidth = _LineDetectSetting->ROI.height;
  }
  this->IntensityLine = new int[_SearchWidth];
  this->FilterResult = new int[_SearchWidth];
  this->_logging = logging;
}

LineInfo* LineDetect::DetectLine(cv::Mat imageMat) {
  cv::Mat detectImage = imageMat(_LineDetectSetting->ROI);
  _logging->Log("IntensityLine\n");
  CalculateIntensityLine(detectImage, this->IntensityLine);
  _logging->Log("EdgeFilter\n");
  LineInfo* lineInfo = EdgeFilter(this->IntensityLine);
  return lineInfo;
}

void LineDetect::CalculateIntensityLine(cv::Mat detectImage, int* intensityLine) {
  int intensityPosition = 0;
  if (_LineDetectSetting->GetPosition() == LineDetectSetting::RIGHT) {
    for (int position = _SearchWidth - 1; position >= 0; position--) {
      CalculateIntensity(detectImage, intensityLine, &intensityPosition, position);
    }
  } else {
    for (int position = 0; position < _SearchWidth; position++) {
      CalculateIntensity(detectImage, intensityLine, &intensityPosition, position);
    }
  }
}

void LineDetect::CalculateIntensity(cv::Mat detectImage, int* intensityLine, int* intensityPosition, int position) {
  intensityLine[*intensityPosition] = CalculateIntensityAtPosition(detectImage, position);
  _logging->Log(intensityLine[*intensityPosition]);
  (*intensityPosition)++;
}

int LineDetect::CalculateIntensityAtPosition(cv::Mat detectImage, int position) {
  int intensity = 0;
  if (_LineDetectSetting->GetLineDirection() == LineDetectSetting::VERTICAL) {
    if (_LineDetectSetting->BlackLine) {
      for (int y = 0; y < _LineDetectSetting->ROI.height; y++) {
        cv::Scalar intensityScalar = detectImage.at<uchar>(y, position);
        intensity += 255 - intensityScalar.val[0];
      }
    } else {
      for (int y = 0; y < _LineDetectSetting->ROI.height; y++) {
        cv::Scalar intensityScalar = detectImage.at<uchar>(y, position);
        intensity += intensityScalar.val[0];
      }
    }
  } else {
    if (_LineDetectSetting->BlackLine) {
      for (int x = 0; x < _LineDetectSetting->ROI.width; x++) {
        cv::Scalar intensityScalar = detectImage.at<uchar>(position, x);
        intensity += 255 - intensityScalar.val[0];
      }
    } else {
      for (int x = 0; x < _LineDetectSetting->ROI.width; x++) {
        cv::Scalar intensityScalar = detectImage.at<uchar>(position, x);
        intensity += intensityScalar.val[0];
      }
    }
  }
  return intensity;
}

LineInfo* LineDetect::EdgeFilter(int* intensityLine) {
  int sumFirstHalf = LineDetect::FilterFirstHalf(intensityLine);
  int sumSecondHalf = LineDetect::FilterSecondHalf(intensityLine);

  int middle = _LineDetectSetting->FilterHalf;
  int end = 2 * _LineDetectSetting->FilterHalf;

  MaxFilterValue = sumFirstHalf - sumSecondHalf;
  MaxFilterIndex = middle;
  MinFilterValue = MaxFilterValue;
  MinFilterIndex = MaxFilterIndex;

  for (int start = 0; start < _SearchWidth - 2 * _LineDetectSetting->FilterHalf; start++) {
    sumFirstHalf = sumFirstHalf - intensityLine[start] + intensityLine[middle];
    sumSecondHalf = sumSecondHalf - intensityLine[middle] + intensityLine[end];
    middle++;
    end++;

    int FilterValue = sumFirstHalf - sumSecondHalf;
    FilterResult[start] = FilterValue;
    
    _logging->Log(FilterValue);
    if (_LineDetectSetting->GetPosition() == LineDetectSetting::CENTER) {
      if (FilterValue > MaxFilterValue) {
        MaxFilterIndex = middle;
        MaxFilterValue = FilterValue;
      } else if (FilterValue < MinFilterValue) {
        MinFilterIndex = middle;
        MinFilterValue = FilterValue;
      }
    } else {
      if (std::abs(FilterValue) > _LineDetectSetting->FilterThresshold) {
        if (_LineDetectSetting->GetPosition() == LineDetectSetting::RIGHT) {
          LogFilterResult(0, FilterValue, _SearchWidth - middle);
          return new LineInfo(true, _SearchWidth - middle, _SearchWidth);
        } else {
          LogFilterResult(0, FilterValue, middle);
          return new LineInfo(true, middle, _SearchWidth);
        }
      }
    }
  }

  if (_LineDetectSetting->GetPosition() == LineDetectSetting::CENTER) {
    if (MaxFilterValue > _LineDetectSetting->FilterThresshold || MinFilterValue < -_LineDetectSetting->FilterThresshold) {
      if (MaxFilterIndex > MinFilterIndex) {
        int centerIndex = MinFilterIndex + (MaxFilterIndex - MinFilterIndex) / 2;
        LogFilterResult(MinFilterValue, MaxFilterValue, centerIndex);
        return new LineInfo(true, centerIndex, _SearchWidth);
      }

      if (MaxFilterValue < -MinFilterValue) {
        return new LineInfo(true, _LineDetectSetting->ROI.width, _SearchWidth);
      } else {
        return new LineInfo(true, 0, _SearchWidth);
      }
    }
  }
  LogFilterResult(MinFilterValue, MaxFilterValue, 0);
  return new LineInfo(false, 0, _SearchWidth);
}

int LineDetect::FilterFirstHalf(int* intensityLine) {
  int sumFirstHalf = 0;
  for (int x = 0; x < _LineDetectSetting->FilterHalf; x++) {
    sumFirstHalf += intensityLine[x];
  }
  return sumFirstHalf;
}

int LineDetect::FilterSecondHalf(int* intensityLine) {
  int sumSecondHalf = 0;
  for (int x = _LineDetectSetting->FilterHalf; x < 2 * _LineDetectSetting->FilterHalf; x++) {
    sumSecondHalf += intensityLine[x];
  }
  return sumSecondHalf;
}

void LineDetect::LogFilterResult(int MinFilterValue, int MaxFilterValue, int centerIndex) {
  _logging->Log("MinFilterValue", MinFilterValue);
  _logging->Log("MaxFilterValue", MaxFilterValue);
  _logging->Log("CenterIndex", centerIndex);
  _logging->Log("_SearchWidth", _SearchWidth);
}

std::string LineDetect::ToString() {
  std::string result = "";
  result += "MinFilterValue: " + Convert::IntToString(MinFilterValue) + "\n";
  result += "MaxFilterValue: " + Convert::IntToString(MaxFilterValue) + "\n";
  result += "FilterThresshold: " + Convert::IntToString(this->_LineDetectSetting->FilterThresshold) + "\n";

  result += "Filter:";
  for (int start = 0; start < _SearchWidth - 2 * _LineDetectSetting->FilterHalf; start++) {
    result += Convert::IntToString(this->FilterResult[start]) + " , ";
  }
  result += "\n";
  
  return result;
}
